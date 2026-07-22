# Network configuration for stegOS

setup_dns() {
    # The kernel configures eth0 via ip=dhcp, which gives us an IP and gateway,
    # but does not populate resolv.conf. Since the rootfs is read-only and
    # we aren't running a userspace DHCP client, we must statically configure DNS.
    
    # Remove resolv.conf from volatiles so our static file survives boot
    sed -i '/resolv.conf/d' ${IMAGE_ROOTFS}/etc/default/volatiles/00_core
    rm -f ${IMAGE_ROOTFS}/etc/resolv.conf
    
    # QEMU SLIRP's internal DNS proxy is dead due to host firewall restrictions.
    # We must query public DNS directly, but the host firewall blocks UDP 53.
    # By specifying 'options use-vc', glibc will use TCP for DNS queries, which the firewall allows!
    echo "nameserver 8.8.8.8" > ${IMAGE_ROOTFS}/etc/resolv.conf
    echo "nameserver 1.1.1.1" >> ${IMAGE_ROOTFS}/etc/resolv.conf
    echo "options use-vc" >> ${IMAGE_ROOTFS}/etc/resolv.conf

    # Standard glibc utilities require nsswitch.conf to know to use DNS.
    # core-image-minimal omits this by default, causing ping to fail even if resolv.conf is correct.
    echo "hosts: files dns" > ${IMAGE_ROOTFS}/etc/nsswitch.conf
}

ROOTFS_POSTPROCESS_COMMAND += "setup_dns; "
