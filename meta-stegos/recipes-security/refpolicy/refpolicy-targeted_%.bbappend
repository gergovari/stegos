FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos_custom.te \
    file://stegos_custom.fc \
    file://stegos_custom.if \
"

do_compile:prepend() {
    cp ${UNPACKDIR}/stegos_custom.te ${S}/policy/modules/system/
    cp ${UNPACKDIR}/stegos_custom.fc ${S}/policy/modules/system/
    cp ${UNPACKDIR}/stegos_custom.if ${S}/policy/modules/system/
}
