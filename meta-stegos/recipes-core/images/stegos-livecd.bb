require recipes-core/images/core-image-minimal.bb
require stegos-pkgs.inc
require stegos-harden.inc
require stegos-users.inc
require stegos-net.inc
require stegos-firewall.inc

DESCRIPTION = "Packages stegOS as a bootable Live CD."
IMAGE_FSTYPES += "iso"
