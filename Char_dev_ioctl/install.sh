
module="my_ioc_ldd"
device="my_ioc_device"

# install the LKM and exit if insmod fails with an error
sudo insmod $module.ko 

# query the /proc/devices file
major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)
minor=0

echo major:$major

# create the new file system node
sudo mknod /dev/$device c $major $minor

# ensure device file is readable by all
sudo chmod 777 /dev/$device
