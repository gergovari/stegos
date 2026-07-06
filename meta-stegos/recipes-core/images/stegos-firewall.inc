IMAGE_INSTALL += "iptables"

STEGOS_FIREWALL_EXT_IFACE ?= "eth0"

# Host ports to expose to the outside world
# Example: STEGOS_FIREWALL_TCP_PORTS = "22"
STEGOS_FIREWALL_TCP_PORTS ?= ""

setup_firewall() {
    install -d ${IMAGE_ROOTFS}/etc/init.d
    install -d ${IMAGE_ROOTFS}/etc/rcS.d

    cat << 'EOF' > ${IMAGE_ROOTFS}/etc/init.d/stegos-firewall
#!/bin/sh
### BEGIN INIT INFO
# Provides:          stegos-firewall
# Required-Start:    $local_fs
# Required-Stop:     
# Default-Start:     S
# Default-Stop:      0 6
# Short-Description: StegOS Firewall
### END INIT INFO

case "$1" in
  start)
    echo "Starting StegOS Firewall..."
    
    # Run iptables commands without console output to avoid SELinux tty_device_t denials
    {
        # 1. Host Firewall (INPUT chain)
        # This protects the host itself. Docker containers are managed automatically
        # by Docker in the PREROUTING/FORWARD chains.
        iptables -P INPUT DROP
        iptables -P FORWARD DROP
        iptables -A INPUT -i lo -j ACCEPT
        iptables -A INPUT -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT

        # Custom Host Ports (Injected at build time)
        #HOST_PORTS_MARKER#
    } </dev/null >/dev/null 2>&1
    ;;
  *)
    echo "Usage: $0 {start}"
    exit 1
    ;;
esac
exit 0
EOF

    # Inject external interface
    sed -i "s|#EXT_IFACE#|${STEGOS_FIREWALL_EXT_IFACE}|g" ${IMAGE_ROOTFS}/etc/init.d/stegos-firewall

    # Inject Host Ports
    for port in ${STEGOS_FIREWALL_TCP_PORTS}; do
        sed -i "/#HOST_PORTS_MARKER#/a \    iptables -A INPUT -i ${STEGOS_FIREWALL_EXT_IFACE} -p tcp --dport $port -j ACCEPT" ${IMAGE_ROOTFS}/etc/init.d/stegos-firewall
    done

    chmod 755 ${IMAGE_ROOTFS}/etc/init.d/stegos-firewall
    ln -s ../init.d/stegos-firewall ${IMAGE_ROOTFS}/etc/rcS.d/S39stegos-firewall
}

ROOTFS_POSTPROCESS_COMMAND += "setup_firewall; "
