ccflags-y := -Wno-error=date-time -Wdate-time
obj-m := my_ioc_ldd.o
my_ioc_ldd-objs := mytuxit_io.o

all:
	make -C /lib/modules/$(shell uname -r)/build  M=`pwd` modules
	gcc test_io.c -Werror -Wno-error -o exec_test_ioctl
clean:
	make -C /lib/modules/$(shell uname -r)/build  M=`pwd` clean
	rm exec_test_ioctl
