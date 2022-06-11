ccflags-y := -Wno-error=date-time -Wdate-time
obj-m := my_ldd_io_sleep.o
my_ldd_io_sleep-objs := mytuxit_io_sleep.o

all:
	make -C /lib/modules/$(shell uname -r)/build  M=`pwd` modules
	gcc test_io_sleep.c -o exec_test_ioctl_sleep
clean:
	make -C /lib/modules/$(shell uname -r)/build  M=`pwd` clean
	rm exec_test_ioctl_sleep
