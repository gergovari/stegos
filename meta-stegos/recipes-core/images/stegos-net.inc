# Network configuration for stegOS

# Install standard networking utilities
IMAGE_INSTALL += "init-ifupdown busybox-udhcpc"

setup_networking() {
    # Provide standard nsswitch.conf for DNS resolution
    echo "hosts: files dns" > ${IMAGE_ROOTFS}/etc/nsswitch.conf
    
    # Remove any static resolv.conf so udhcpc can manage it dynamically
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    
    # Configure eth0 to use DHCP standardly.
    # The init-ifupdown package provides /etc/init.d/networking which reads this file
    # and calls udhcpc to obtain an IP address and populate resolv.conf.
    mkdir -p ${IMAGE_ROOTFS}/etc/network
    cat << 'NET_EOF' > ${IMAGE_ROOTFS}/etc/network/interfaces
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet dhcp
NET_EOF
}

ROOTFS_POSTPROCESS_COMMAND += "setup_networking; "
