# Read elf RPATH

`readelf -d <exec_name> | grep RUNPATH`

# Remove RPATH

`patchelf --remove-rpath <exec_name>`

# Set RPATH

`patchelf --set-rpath <path> <exec_name>`

Examples of paths: `$ORIGIN/../lib`, `$ORIGIN/../lib:$ORIGIN/../lib64`