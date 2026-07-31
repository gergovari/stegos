require recipes-core/images/core-image-minimal.bb
require stegos-pkgs.inc
require stegos-harden-image.inc
require stegos-users.inc
require stegos-net.inc
require stegos-firewall.inc

DESCRIPTION = "Packages stegOS as a bootable Live CD."
IMAGE_FSTYPES += "iso"

# ---------------------------------------------------------------------------
# ISO bootloader configuration (ISOLINUX / syslinux.bbclass)
# These are baked into the ISO so every boot — bare-metal or QEMU — behaves
# identically without any runtime runqemu flags.
# ---------------------------------------------------------------------------

# Route all output to ttyS0 (serial). This is what QEMU's -nographic exposes
# and what a headless bare-metal server uses. Drop SYSLINUX_SERIAL so the
# menu generator produces a single set of entries (no Graphics/Serial split)
# and SYSLINUX_DEFAULT_CONSOLE becomes the console for every label.
SYSLINUX_SERIAL = ""
SYSLINUX_DEFAULT_CONSOLE = "console=ttyS0,115200"

# Suppress verbose kernel + userspace boot messages — same as a shipping OS.
SYSLINUX_KERNEL_ARGS = "quiet loglevel=3"

# Boot immediately with no interactive menu.
SYSLINUX_TIMEOUT = "0"
SYSLINUX_PROMPT = "0"
