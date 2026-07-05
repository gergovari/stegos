# Network configuration for StegOS

setup_dns() {
    # The kernel configures eth0 via ip=dhcp, which gives us an IP and gateway,
    # but does not populate resolv.conf. Since the rootfs is read-only and
    # we aren't running a userspace DHCP client, we must statically configure DNS.
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    
    # QEMU SLIRP default DNS
    echo "nameserver 10.0.2.3" > ${IMAGE_ROOTFS}/etc/resolv.conf
    # Fallback public DNS
    echo "nameserver 8.8.8.8" >> ${IMAGE_ROOTFS}/etc/resolv.conf
}

ROOTFS_POSTPROCESS_COMMAND += "setup_dns; "
