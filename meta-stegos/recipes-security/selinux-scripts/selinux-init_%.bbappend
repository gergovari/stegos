do_install:append() {
    # auditd starts before populate-volatile.sh on first boot, which tries to mkdir -p /var/log/audit
    # /var/log is a symlink to /var/volatile/log, which doesn't exist yet, causing a "File exists" error.
    # Create the target directory before starting auditd.
    sed -i '/test -x \/etc\/init.d\/auditd/i \	mkdir -p /var/volatile/log' ${D}${sysconfdir}/init.d/selinux-init
}
