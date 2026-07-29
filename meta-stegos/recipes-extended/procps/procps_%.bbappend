do_install:append() {
    echo "kernel.printk = 3 4 1 3" >> ${D}${sysconfdir}/sysctl.conf
}
