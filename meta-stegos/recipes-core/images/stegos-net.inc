# Network configuration for stegOS
#
# QEMU SLIRP mode: the kernel configures eth0 via ip=dhcp (set by runqemu),
# which provides an IP address and default route. We only need to configure DNS.
#
# On bare metal: replace the kernel ip=dhcp with a real DHCP client by adding
# init-ifupdown and busybox-udhcpc to IMAGE_INSTALL and configuring
# /etc/network/interfaces.

# Port forwarding for development (SSH, HTTP, HTTPS)
QB_SLIRP_OPT = "-netdev user,id=net0,hostfwd=tcp::2222-:22,hostfwd=tcp::8080-:80,hostfwd=tcp::8443-:443"

# Tell the kernel to configure eth0 via DHCP at boot.
# APPEND writes to the ISO bootloader config (syslinux), which is what
# actually supplies the kernel command line when booting from an ISO.
# (QB_CMDLINE_IP_SLIRP only works for direct kernel boot, not ISO boot.)
APPEND += "ip=dhcp"

setup_networking() {
    # glibc requires nsswitch.conf to know to use DNS for host lookups.
    # core-image-minimal omits this by default.
    echo "hosts: files dns" > ${IMAGE_ROOTFS}/etc/nsswitch.conf

    # The kernel's ip=dhcp configures the interface but does not populate
    # resolv.conf. Point it at QEMU's built-in DNS proxy (10.0.2.3).
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    echo "nameserver 10.0.2.3" > ${IMAGE_ROOTFS}/etc/resolv.conf

    # Prevent the volatiles system from overwriting our resolv.conf on boot
    sed -i '/resolv.conf/d' ${IMAGE_ROOTFS}/etc/default/volatiles/00_core
}

ROOTFS_POSTPROCESS_COMMAND += "setup_networking; "
