#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"

static int data[500] __initdata = {0,1};

static int __init start_here(void){
    printk(KERN_INFO "kernel init data %d\n", data[1]);
    printk(KERN_WARNING "some warnings ");
    return 0;
}

static void __exit end_here(void){
    printk(KERN_INFO "hello-1: good bye you idiot\n");
}

module_init(start_here);
module_exit(end_here);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_SUPPORTED_DEVICE("TrashCan");
