SUMMARY = "StegOS Utilities"
DESCRIPTION = "Utility scripts for StegOS."
HOMEPAGE = "https://github.com/gergovari/stegos-utils"
LICENSE = "GPL"

SRC_URI = "git://github.com/gergovari/stegos-utils.git;protocol=https;branch=master"
SRCREV = "${AUTOREV}"

do_install() {
    install -d ${D}${bindir}
    for script in ${S}/*.sh; do
        if [ -f "$script" ]; then
            script_name=$(basename "$script" .sh)
            install -m 0755 "$script" "${D}${bindir}/$script_name"
        fi
    done
    
    # Install Python stegpkg manager
    if [ -f "${S}/stegpkg" ]; then
        install -m 0755 "${S}/stegpkg" "${D}${bindir}/stegpkg"
    fi
}

FILES:${PN} += "${bindir}/*"

RDEPENDS:${PN} += " \
    python3-core \
    python3-pyyaml \
    python3-jinja2 \
    python3-jsonschema \
"
