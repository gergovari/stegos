# The meta-selinux layer requests CONFIG_EXT3_FS_SECURITY, which no longer 
# exists in modern kernels (handled by ext4). This causes a config warning.
# We intercept the unpacked config fragments and strip the offending line 
# before the kernel metadata task analyzes them.

do_kernel_metadata:prepend() {
    # Find any .cfg files in the working directory and delete the ext3 line
    find ${WORKDIR} -type f -name "*.cfg" -exec sed -i '/CONFIG_EXT3_FS_SECURITY/d' {} +
}
