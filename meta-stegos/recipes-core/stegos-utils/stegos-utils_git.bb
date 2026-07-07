SUMMARY = "StegOS Utilities"
DESCRIPTION = "Utility scripts for StegOS."
HOMEPAGE = "https://github.com/gergovari/stegos-utils"
LICENSE = "CLOSED"

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
}

FILES:${PN} += "${bindir}/*"
