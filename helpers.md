# Read elf RPATH

`readelf -d <exec_name> | grep RUNPATH`

# Remove RPATH

`patchelf --remove-rpath <exec_name>`

# Set RPATH

`patchelf --set-rpath <path> <exec_name>`

Examples of paths: `$ORIGIN/../lib`, `$ORIGIN/../lib:$ORIGIN/../lib64`

# Service

The file [dgapp.sample.service](./dgapp.sample.service) is a sample for systemd, you can create a `dgapp.service`, following the sample, then just run:

`sudo cp ./dgapp.sample.service /etc/systemd/system/dgapp.service` and
`sudo systemctl unmask dgapp.service` to unmask and enable it