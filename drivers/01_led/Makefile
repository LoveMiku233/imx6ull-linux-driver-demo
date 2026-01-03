KERNEL_DIR = /home/book/100ask_imx6ull-sdk/Linux-4.9.88

all:
	make -C $(KERNEL_DIR) M=`pwd` modules
	$(CROSS_COMPILE)gcc -o yankai_led_test led_test.c

clean:
	make -C $(KERNEL_DIR) M=`pwd` modules clean
	rm -rf modules.order
	rm -f yankai_led_test

obj-m += led_drv.o

