#pragma once
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"

// prototypes for device open release read write
static int device_open(struct inode *, struct file *);
static int device_release(struct inode*, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int major_num;

// buffer for device name,  message buffer
#define DEVICE_NAME     "nameless"
#define BUFF_LEN        100

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_SUPPORTED_DEVICE("TrashCan");

