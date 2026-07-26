SUMMARY = "stegOS Utilities"
DESCRIPTION = "Utility scripts for stegOS."
HOMEPAGE = "https://github.com/gergovari/stegos-utils"
LICENSE = "CLOSED"

SRC_URI = "git://${TOPDIR}/../../../stegos-utils;protocol=file;branch=master"
inherit python3-dir update-rc.d
SRCREV = "${AUTOREV}"

INITSCRIPT_PACKAGES = "${PN} ${PN}-stegmap"
INITSCRIPT_NAME:${PN} = "stegd"
INITSCRIPT_PARAMS:${PN} = "defaults 90 10"
INITSCRIPT_NAME:${PN}-stegmap = "stegmap"
INITSCRIPT_PARAMS:${PN}-stegmap = "defaults 91 09"

do_install() {
    install -d ${D}${bindir}
    install -d ${D}${sysconfdir}/bash_completion.d
    install -d ${D}${sysconfdir}/init.d
    install -d ${D}${PYTHON_SITEPACKAGES_DIR}/steglib
    
    install -m 0755 ${S}/init/stegd.init ${D}${sysconfdir}/init.d/stegd
    install -m 0755 ${S}/init/stegmap.init ${D}${sysconfdir}/init.d/stegmap
    
    install -m 0644 ${S}/lib/steglib/*.py ${D}${PYTHON_SITEPACKAGES_DIR}/steglib/
    
    for script in ${S}/bin/*; do
        if [ -f "$script" ]; then
            script_name=$(basename "$script")
            if [ "$script_name" = "stegos-completion.sh" ]; then
                install -m 0644 "$script" "${D}${sysconfdir}/bash_completion.d/stegos-utils.sh"
            else
                # Automatically strip .sh extension during installation if present
                script_name=${script_name%.sh}
                install -m 0755 "$script" "${D}${bindir}/$script_name"
            fi
        fi
    done
}

PACKAGES =+ "${PN}-stegmap"
FILES:${PN}-stegmap = "${sysconfdir}/init.d/stegmap"
RDEPENDS:${PN}-stegmap = "${PN}"

FILES:${PN} += "${bindir}/* ${sysconfdir}/bash_completion.d/* ${PYTHON_SITEPACKAGES_DIR}/steglib/* ${sysconfdir}/init.d/stegd"

RDEPENDS:${PN} += " \
    ${PN}-stegmap \
    python3-core \
    python3-pyyaml \
    python3-jinja2 \
    python3-jsonschema \
    e2fsprogs \
    e2fsprogs-mke2fs \
    git \
"
