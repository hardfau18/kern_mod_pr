#include<linux/module.h>
#include<linux/kernel.h>


int init_module(void){
    printk(KERN_INFO "hello-1: finally\n");
    printk(KERN_INFO "hello-1: autocomplete working\n");
    return 0;
}

void cleanup_module(void){
    printk(KERN_INFO "hello-1: good bye you idiot\n");
}

