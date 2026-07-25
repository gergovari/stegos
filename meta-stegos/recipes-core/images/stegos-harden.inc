IMAGE_FEATURES += "read-only-rootfs"

IMAGE_INSTALL += " \
    packagegroup-core-selinux \
    policycoreutils \
"

setup_harden_fixes() {
    install -d ${IMAGE_ROOTFS}/etc/default/volatiles

    # urandom init script needs to write/delete random-seed
    echo "d root root 0755 /var/lib/urandom none" > ${IMAGE_ROOTFS}/etc/default/volatiles/98_urandom

    # Fix overlayfs on read-only rootfs with SELinux (force bind mount fallback)
    if [ -f ${IMAGE_ROOTFS}/etc/init.d/read-only-rootfs-hook.sh ]; then
        sed -i 's|if ! mount -t overlay.*|if false; then : ; else|' ${IMAGE_ROOTFS}/etc/init.d/read-only-rootfs-hook.sh
    fi

    # Fix /var/log mkdir File exists error on first boot
    if [ -f ${IMAGE_ROOTFS}/etc/init.d/selinux-init ]; then
        sed -i 's|test -x /etc/init.d/auditd|mkdir -p /var/volatile/log\n\ttest -x /etc/init.d/auditd|' ${IMAGE_ROOTFS}/etc/init.d/selinux-init
    fi

    # Suppress verbose kernel networking messages (veth creations)
    install -d ${IMAGE_ROOTFS}/etc/sysctl.d
    echo "kernel.printk = 4 4 1 7" > ${IMAGE_ROOTFS}/etc/sysctl.d/99-quiet-network.conf
}

ROOTFS_POSTPROCESS_COMMAND += "setup_harden_fixes; "

inherit selinux-image
