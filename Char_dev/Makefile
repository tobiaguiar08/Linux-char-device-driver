ccflags-y := -Wno-error=date-time -Wdate-time
obj-m := my_ldd.o
my_ldd-objs := mytuxit.o

all:
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) modules
	gcc test.c -o exec_test
clean:
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) clean
	rm -f exec_test
