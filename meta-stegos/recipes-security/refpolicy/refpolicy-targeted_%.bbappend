FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos_custom.te \
    file://stegos_custom.if \
    file://stegos_custom.fc \
"

do_copy_stegos_policy() {
    install -m 0644 ${UNPACKDIR}/stegos_custom.te ${S}/policy/modules/system/stegos_custom.te
    install -m 0644 ${UNPACKDIR}/stegos_custom.if ${S}/policy/modules/system/stegos_custom.if
    install -m 0644 ${UNPACKDIR}/stegos_custom.fc ${S}/policy/modules/system/stegos_custom.fc
}

addtask copy_stegos_policy after do_patch before do_configure

do_configure:append() {
    sed -i 's/^stegos_custom\s*=.*/stegos_custom = module/' ${S}/policy/modules.conf
    
    grep -q "^stegos_custom" ${S}/policy/modules.conf || echo "stegos_custom = module" >> ${S}/policy/modules.conf
}
