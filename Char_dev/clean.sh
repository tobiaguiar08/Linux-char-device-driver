
module="my_ldd"
device="my_device"

sudo rmmod $module
sudo rm -f /dev/$device
