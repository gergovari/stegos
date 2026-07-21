SUMMARY = "stegOS Utilities"
DESCRIPTION = "Utility scripts for stegOS."
HOMEPAGE = "https://github.com/gergovari/stegos-utils"
LICENSE = "CLOSED"

SRC_URI = "git://github.com/gergovari/stegos-utils.git;protocol=https;branch=master"
SRCREV = "${AUTOREV}"

do_install() {
    install -d ${D}${bindir}
    for script in ${S}/bin/*; do
        if [ -f "$script" ]; then
            script_name=$(basename "$script")
            # Automatically strip .sh extension during installation if present
            script_name=${script_name%.sh}
            install -m 0755 "$script" "${D}${bindir}/$script_name"
        fi
    done
}

FILES:${PN} += "${bindir}/*"

RDEPENDS:${PN} += " \
    python3-core \
    python3-pyyaml \
    python3-jinja2 \
    python3-jsonschema \
    e2fsprogs \
    e2fsprogs-mke2fs \
"
