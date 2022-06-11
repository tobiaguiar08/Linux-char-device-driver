
module="my_ldd_io_sleep"
device="my_device"

sudo rmmod $module
sudo rm -f /dev/$device
