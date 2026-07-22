# Network configuration for stegOS

# Install standard networking utilities
IMAGE_INSTALL += "busybox-udhcpc ifupdown"

setup_networking() {
    # Provide standard nsswitch.conf for DNS resolution
    echo "hosts: files dns" > ${IMAGE_ROOTFS}/etc/nsswitch.conf
    
    # Configure eth0 to use DHCP standardly
    mkdir -p ${IMAGE_ROOTFS}/etc/network
    cat << 'NET_EOF' > ${IMAGE_ROOTFS}/etc/network/interfaces
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet dhcp
NET_EOF

    # Remove any static resolv.conf so udhcpc can manage it
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    
    # Optional: If the internal QEMU DNS (10.0.2.3) fails on this host environment,
    # we can append a public fallback DNS to udhcpc's resolv.conf using a standard udhcpc hook,
    # but normally bare-metal DHCP handles this purely via the DHCP lease.
}

ROOTFS_POSTPROCESS_COMMAND += "setup_networking; "
