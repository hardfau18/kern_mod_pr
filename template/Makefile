MODULE_NAME := 
BUILD_DIR := $(PWD)/build

obj-m := $(MODULE_NAME).o
SRCS := 
ccflags-y := -I$(PWD)/include
OBJS =  $(SRCS:.c=.o)
$(MODULE_NAME)-y = $(OBJS)


KERN_SRC=~/playground/embedded/beaglebone/linux/ti-linux-kernel


default: | $(BUILD_DIR)
	compiledb make -C $(KERN_SRC) M=$(BUILD_DIR) KBUILD_EXTMOD_SRC=$(PWD) ARCH=arm CROSS_COMPILE=arm-none-eabi- modules

clean:
	@-mv compile_commands.json /tmp
	make -C $(KERN_SRC) M=$(PWD)  clean
	@-mv /tmp/compile_commands.json .

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%:
	make -C $(KERN_SRC) M=$(PWD) $@




