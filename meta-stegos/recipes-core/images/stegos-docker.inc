IMAGE_INSTALL += " \
    docker \
    docker-compose \
"

setup_docker_ramfs() {
    # FIXME: this smells sysvinit specific
    install -d ${IMAGE_ROOTFS}/etc/default/volatiles
    echo "d root root 0711 /var/lib/docker none" > ${IMAGE_ROOTFS}/etc/default/volatiles/99_docker
}

ROOTFS_POSTPROCESS_COMMAND += "setup_docker_ramfs; "
