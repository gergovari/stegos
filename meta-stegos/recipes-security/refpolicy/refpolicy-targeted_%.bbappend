FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-custom.te"

do_configure:append() {
    cp ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/
    
    touch ${S}/policy/modules/contrib/stegos-custom.if
    
    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}
