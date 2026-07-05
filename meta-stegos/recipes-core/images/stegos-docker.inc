IMAGE_INSTALL += " \
    docker \
    docker-compose \
"

setup_docker_fixes() {
    # FIXME: this smells sysvinit specific
    install -d ${IMAGE_ROOTFS}/etc/default/volatiles
    echo "d root root 0711 /var/lib/docker none" > ${IMAGE_ROOTFS}/etc/default/volatiles/99_docker

    # Switch cgroup mounts to cgroup2 to solve Docker's cgroup v1 deprecation warning
    if [ -f ${IMAGE_ROOTFS}/bin/cgroups-mount ]; then
        cat << 'EOF' > ${IMAGE_ROOTFS}/bin/cgroups-mount
#!/bin/sh
set -e
if grep -v '^#' /etc/fstab | grep -q cgroup; then
    echo "cgroups mounted from fstab, not mounting /sys/fs/cgroup"
    exit 0
fi
mountpoint -q /sys/fs/cgroup || mount -t cgroup2 -o rw,nosuid,nodev,noexec,relatime,nsdelegate cgroup2 /sys/fs/cgroup
# Enable controllers for children so docker sub-cgroups get limits
if [ -f /sys/fs/cgroup/cgroup.controllers ]; then
    for c in $(cat /sys/fs/cgroup/cgroup.controllers); do
        echo "+$c" > /sys/fs/cgroup/cgroup.subtree_control 2>/dev/null || true
    done
fi
exit 0
EOF
    fi

    # Put dockerd in its own cgroup to satisfy Docker's swap limit check on cgroup v2
    for f in ${IMAGE_ROOTFS}/etc/init.d/docker* ; do
        if [ -f "$f" ]; then
            # Remove hardcoded localhost:5000 registry to fix docker pull
            sed -i 's/--registry-mirror=http:\/\/localhost:5000//g' "$f"
            sed -i 's/--insecure-registry=http:\/\/localhost:5000//g' "$f"

            sed -i '/printf "Starting $prog/a \
        if [ -d /sys/fs/cgroup ]; then \
            mkdir -p /sys/fs/cgroup/docker_daemon \
            echo $$ > /sys/fs/cgroup/docker_daemon/cgroup.procs 2>/dev/null || true \
        fi' "$f"
        fi
    done
}

ROOTFS_POSTPROCESS_COMMAND += "setup_docker_fixes; "

# Enable swap accounting for Docker
APPEND += " swapaccount=1 cgroup_enable=memory"
QB_KERNEL_CMDLINE_APPEND += " swapaccount=1 cgroup_enable=memory"
