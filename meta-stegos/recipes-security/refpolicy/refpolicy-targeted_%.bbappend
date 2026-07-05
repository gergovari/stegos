FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos-custom.te \
    file://stegos-custom.fc \
    file://stegos-custom.if \
"

do_configure:prepend() {
    install -d ${S}/policy/modules/contrib/stegos-custom
    
    install -m 0644 ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/stegos-custom/
    install -m 0644 ${WORKDIR}/stegos-custom.fc ${S}/policy/modules/contrib/stegos-custom/
    install -m 0644 ${WORKDIR}/stegos-custom.if ${S}/policy/modules/contrib/stegos-custom/
}

do_configure:append() {
    if ! grep -q "stegos-custom" ${S}/policy/modules.conf; then
        echo "stegos-custom = module" >> ${S}/policy/modules.conf
    fi
}
