FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://selinux.cfg"

do_kernel_metadata:prepend() {
    find ${WORKDIR} -type f -name "*.cfg" -exec sed -i '/CONFIG_EXT3_FS_SECURITY/d' {} +
}
