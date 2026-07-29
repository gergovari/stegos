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

def get_python_requirements(d):
    import os, re
    reqs = []
    topdir = d.getVar('TOPDIR')
    if topdir:
        req_file = os.path.normpath(os.path.join(topdir, '../../../stegos-utils/requirements.txt'))
        if os.path.exists(req_file):
            with open(req_file, 'r') as f:
                for line in f:
                    line = line.split('#')[0].strip()
                    if line and not line.startswith('-'):
                        pkg_name = re.split(r'[>=<~]', line)[0].strip().lower()
                        if pkg_name:
                            reqs.append('python3-' + pkg_name.replace('_', '-'))
    return " ".join(reqs)

RDEPENDS:${PN} += " \
    ${PN}-stegmap \
    python3-core \
    ${@get_python_requirements(d)} \
    e2fsprogs \
    e2fsprogs-mke2fs \
    git \
"
