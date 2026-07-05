FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-docker-cgroups.cfg"

do_kernel_metadata:prepend() {
    # Find any .cfg files in the working directory and delete the ext3 line
    find ${WORKDIR} -type f -name "*.cfg" -exec sed -i '/CONFIG_EXT3_FS_SECURITY/d' {} +
}

KERNEL_FEATURES += "features/docker/docker.scc"
