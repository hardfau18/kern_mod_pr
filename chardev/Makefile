MODULE_NAME := chr_led
BUILD_DIR := $(PWD)/build

obj-m := $(MODULE_NAME).o
SRCS = src/chr_led.c
ccflags-y := -I$(PWD)/include
OBJS =  $(SRCS:.c=.o)
$(MODULE_NAME)-y = $(OBJS)
device ?=c


KERN_SRC=~/playground/embedded/beaglebone/linux/ti-linux-kernel

.PHONY: up


default: | $(BUILD_DIR)
	compiledb make -C $(KERN_SRC) M=$(BUILD_DIR) KBUILD_EXTMOD_SRC=$(PWD) ARCH=arm CROSS_COMPILE=arm-none-eabi- modules

clean:
	@-mv compile_commands.json /tmp
	make -C $(KERN_SRC) M=$(PWD)  clean
	@-mv /tmp/compile_commands.json .
up:
	# @-scp "$(BUILD_DIR)/$(MODULE_NAME).ko" root@192.168.51.11:/home/root/
	@sudo mount /dev/sd$(device)2 /mnt && sudo cp $(BUILD_DIR)/$(MODULE_NAME).ko /mnt/home/root && sudo sync && sudo umount /mnt

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%:
	make -C $(KERN_SRC) M=$(PWD) $@




