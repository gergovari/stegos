IMAGE_FEATURES += "read-only-rootfs"

IMAGE_INSTALL += " \
    packagegroup-core-selinux \
    policycoreutils \
"

setup_readonly_volatiles() {
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
exit 0
EOF
    fi
}

ROOTFS_POSTPROCESS_COMMAND += "setup_readonly_volatiles; "

# Enable swap accounting for Docker
APPEND += " swapaccount=1 cgroup_enable=memory"
QB_KERNEL_CMDLINE_APPEND += " swapaccount=1 cgroup_enable=memory"
