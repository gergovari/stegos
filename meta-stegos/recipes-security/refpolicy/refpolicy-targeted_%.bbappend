FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://stegos_custom.te \
    file://stegos_custom.fc \
    file://stegos_custom.if \
"

do_compile:prepend() {
    # Copy custom module into the source tree before make conf discovers modules
    cp ${UNPACKDIR}/stegos_custom.te ${S}/policy/modules/system/
    cp ${UNPACKDIR}/stegos_custom.fc ${S}/policy/modules/system/
    cp ${UNPACKDIR}/stegos_custom.if ${S}/policy/modules/system/
}

enable_stegos_modules() {
    # make conf auto-discovers our .te but leaves it commented out / off
    # for targeted policy — explicitly enable it
    sed -i 's/^#\?\s*stegos_custom\s*=.*/stegos_custom = module/' ${S}/policy/modules.conf
    # If it wasn't found at all, append it
    if ! grep -q '^stegos_custom = module' ${S}/policy/modules.conf; then
        echo 'stegos_custom = module' >> ${S}/policy/modules.conf
    fi
}

do_compile() {
    if [ -f "${WORKDIR}/modules.conf" ] ; then
        cp -f ${WORKDIR}/modules.conf ${S}/policy/modules.conf
    fi
    oe_runmake conf
    disable_policy_modules
    enable_stegos_modules
    oe_runmake policy
}
