FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-custom.te"

do_inject_stegos_policy() {
    install -m 0644 ${UNPACKDIR}/stegos-custom.te ${S}/policy/modules/system/stegos-custom.te
    
    touch ${S}/policy/modules/system/stegos-custom.if
    
    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}

addtask inject_stegos_policy after do_configure before do_compile
