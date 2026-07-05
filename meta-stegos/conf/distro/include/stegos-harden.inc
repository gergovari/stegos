EXTRA_IMAGE_FEATURES:remove = "debug-tweaks"

IMAGE_FEATURES:remove = "package-management"

DISTRO_FEATURES:append = " acl xattr pam selinux"

PREFERRED_PROVIDER_virtual/refpolicy = "refpolicy-targeted"
