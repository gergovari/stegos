# Network configuration for stegOS

setup_dns() {
    # The kernel configures eth0 via ip=dhcp, which gives us an IP and gateway,
    # but does not populate resolv.conf. Since the rootfs is read-only and
    # we aren't running a userspace DHCP client, we must statically configure DNS.
    
    # Remove resolv.conf from volatiles so our static file survives boot
    sed -i '/resolv.conf/d' ${IMAGE_ROOTFS}/etc/default/volatiles/00_core
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    
    # QEMU SLIRP default DNS
    echo "nameserver 10.0.2.3" > ${IMAGE_ROOTFS}/etc/resolv.conf
    # Fallback public DNS
    echo "nameserver 8.8.8.8" >> ${IMAGE_ROOTFS}/etc/resolv.conf
}

ROOTFS_POSTPROCESS_COMMAND += "setup_dns; "
