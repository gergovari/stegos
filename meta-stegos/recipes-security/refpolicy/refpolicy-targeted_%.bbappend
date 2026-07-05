FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-custom.te"

do_inject_stegos_policy() {
    install -d ${S}/policy/modules/contrib
    
    install -m 0644 ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/stegos-custom.te
    
    touch ${S}/policy/modules/contrib/stegos-custom.if
    
    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}

# 2. Wire the new task into the build pipeline
addtask inject_stegos_policy after do_patch before do_configure
