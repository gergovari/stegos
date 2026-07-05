FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-custom.te"

do_patch:append() {
    install -d ${S}/policy/modules/contrib
    install -m 0644 ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/
    touch ${S}/policy/modules/contrib/stegos-custom.if
    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}
