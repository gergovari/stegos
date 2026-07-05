require recipes-core/images/core-image-minimal.bb
require stegos-pkgs.inc
require stegos-users.inc

DESCRIPTION = "Packages StegOS as a bootable Live CD."
IMAGE_FSTYPES += "iso"
