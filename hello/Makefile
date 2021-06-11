obj-m := hello.o  

KERN_SRC=~/programs/sourcecode/linux-ti-staging


all:
	compiledb make -C $(KERN_SRC) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-none-eabi- modules

clean:
	compiledb make -C $(KERN_SRC) M=$(PWD) clean

%:
	make -C $(KERN_SRC) M=$(PWD) $@

trans:
	scp -i ~/.ssh/beagle *.ko beagle:/home/gireesh/trash
