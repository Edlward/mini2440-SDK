KERN_DIR = ~/mini2440/kernel

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order Module.symvers

obj-m	+= second_drv.o
