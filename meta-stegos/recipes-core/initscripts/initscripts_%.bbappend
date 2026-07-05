do_install:append() {
    # Force read-only-rootfs-hook to use bind mount instead of overlayfs
    # Overlayfs on tmpfs with SELinux enforcing often falls back to read-only 
    # due to xattr creation denials, which breaks /var/lib writability.
    if [ -f ${D}${sysconfdir}/init.d/read-only-rootfs-hook.sh ]; then
        sed -i 's|if ! mount -t overlay.*|if false; then : ; else|' ${D}${sysconfdir}/init.d/read-only-rootfs-hook.sh
    fi
}
