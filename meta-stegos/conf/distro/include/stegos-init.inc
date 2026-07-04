INIT_MANAGER = "sysvinit"
VIRTUAL-RUNTIME_init_manager = "openrc"
VIRTUAL-RUNTIME_initscripts = "openrc"

DISTRO_FEATURES:append = " openrc "
DISTRO_FEATURES:remove = " systemd "
