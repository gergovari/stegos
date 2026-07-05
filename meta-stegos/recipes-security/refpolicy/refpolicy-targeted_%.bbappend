FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos-custom.te \
    file://stegos-custom.fc \
    file://stegos-custom.if \
"
do_patch:append() {
    mkdir -p ${S}/policy/modules/contrib/stegos-custom
    cp ${WORKDIR}/stegos-custom.te ${S}/policy/modules/contrib/stegos-custom/stegos-custom.te
    cp ${WORKDIR}/stegos-custom.fc ${S}/policy/modules/contrib/stegos-custom/stegos-custom.fc
    cp ${WORKDIR}/stegos-custom.if ${S}/policy/modules/contrib/stegos-custom/stegos-custom.if
}

do_configure:append() {
    sed -i -e '/^stegos-custom =/d' ${S}/policy/modules.conf

    echo "stegos-custom = module" >> ${S}/policy/modules.conf
}
