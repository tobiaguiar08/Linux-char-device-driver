
module="EnsiCaen_ldd"
device="EnsiCaen_device"

sudo rmmod $module
sudo rm -f /dev/$device
