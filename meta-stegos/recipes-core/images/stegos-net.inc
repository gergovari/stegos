# Network configuration for StegOS

setup_network() {
    # Configure eth0 for DHCP automatically at boot
    if ! grep -q "eth0" ${IMAGE_ROOTFS}/etc/network/interfaces; then
        cat << 'EOF' >> ${IMAGE_ROOTFS}/etc/network/interfaces

auto eth0
iface eth0 inet dhcp
EOF
    fi
}

ROOTFS_POSTPROCESS_COMMAND += "setup_network; "
