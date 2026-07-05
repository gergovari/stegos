require recipes-core/images/core-image-minimal.bb
require stegos-pkgs.inc
require stegos-harden.inc
require stegos-users.inc

DESCRIPTION = "Packages StegOS as a bootable Live CD."
IMAGE_FSTYPES += "iso"

# TODO: REMOVE
set_selinux_permissive() {
    sed -i 's/^SELINUX=enforcing/SELINUX=permissive/' ${IMAGE_ROOTFS}/etc/selinux/config
}

ROOTFS_POSTPROCESS_COMMAND += "set_selinux_permissive; "
