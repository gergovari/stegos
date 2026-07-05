IMAGE_FEATURES += "read-only-rootfs"

IMAGE_INSTALL += " \
    packagegroup-core-selinux \
    policycoreutils \
"

setup_readonly_volatiles() {
    install -d ${IMAGE_ROOTFS}/etc/default/volatiles

    # urandom init script needs to write/delete random-seed
    echo "d root root 0755 /var/lib/urandom none" > ${IMAGE_ROOTFS}/etc/default/volatiles/98_urandom

    # /var/log must be writable for syslogd
    echo "d root root 0755 /var/log none" > ${IMAGE_ROOTFS}/etc/default/volatiles/98_varlog
}

ROOTFS_POSTPROCESS_COMMAND += "setup_readonly_volatiles; "
