inherit extrausers

EXTRA_USERS_PARAMS = " \
    useradd -G sudo steguser; \
"

setup_autologin() {
    install -d ${IMAGE_ROOTFS}/usr/sbin
    echo '#!/bin/sh' > ${IMAGE_ROOTFS}/usr/sbin/autologin

    echo 'exec /bin/login -f steguser' >> ${IMAGE_ROOTFS}/usr/sbin/autologin
    chmod 0755 ${IMAGE_ROOTFS}/usr/sbin/autologin

    if [ -f ${IMAGE_ROOTFS}/etc/inittab ]; then
        sed -i 's|/sbin/getty|/sbin/getty -n -l /usr/sbin/autologin|g' ${IMAGE_ROOTFS}/etc/inittab
    fi

    # FIXME: if switching init systems this needs to be changed
}

ROOTFS_POSTPROCESS_COMMAND += "setup_autologin; "

setup_sudoers() {
    install -d ${IMAGE_ROOTFS}/etc/sudoers.d

    echo '%sudo ALL=(ALL) NOPASSWD: ALL' > ${IMAGE_ROOTFS}/etc/sudoers.d/sudo

    chmod 0440 ${IMAGE_ROOTFS}/etc/sudoers.d/sudo
}

ROOTFS_POSTPROCESS_COMMAND += "setup_sudoers; "
