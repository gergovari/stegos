FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos_custom.te \
    file://stegos_custom.if \
    file://stegos_custom.fc \
"

do_patch:append() {
    install -m 0644 ${UNPACKDIR}/stegos_custom.te ${S}/policy/modules/system/stegos_custom.te
    install -m 0644 ${UNPACKDIR}/stegos_custom.if ${S}/policy/modules/system/stegos_custom.if
    install -m 0644 ${UNPACKDIR}/stegos_custom.fc ${S}/policy/modules/system/stegos_custom.fc
}
