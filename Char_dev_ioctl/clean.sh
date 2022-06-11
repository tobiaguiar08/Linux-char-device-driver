
module="my_ioc_ldd"
device="my_ioc_device"

sudo rmmod $module
sudo rm -f /dev/$device
make clean
