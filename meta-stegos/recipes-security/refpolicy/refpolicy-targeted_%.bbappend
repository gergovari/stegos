FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://stegos-custom.te"

do_configure:append() {
    install -m 0644 ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/stegos-custom.te

    touch ${S}/policy/modules/contrib/stegos-custom.if

    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}
