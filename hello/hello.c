#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "hello.h"

int major_num;
char *data;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read,
    .write = write,
    .open = open,
    .release = release,
    .llseek = seek,
};
int open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "hello: open called on %s \n", inode->i_link);
  //
  return 0;
}
int release(struct inode *inode, struct file *file) {
  //
  return 0;
}
loff_t seek(struct file *file, loff_t offset, int whence) {
  //
  return 0;
}

ssize_t read(struct file *filename, char __user *user, size_t size,
             loff_t *offset) {
  int ret;
  ssize_t size_of_data = sizeof(data);
  ssize_t read_size =
      *offset + size > size_of_data ? size_of_data - *offset : size;

  if (*offset > size_of_data)
    return 0;

  if ((ret = copy_to_user(user, data, read_size)) < 0) {
    printk(KERN_ALERT "Failed to write to user with value %d\n", ret);
    return ret;
  }
  *offset += read_size;
  return read_size;
}

ssize_t write(struct file *file_name, const char __user *user, size_t size,
              loff_t *offset) {
  printk(KERN_INFO "write operation performed with size %d \n", size);
  return 0;
}

static int __init start_here(struct platform_device *pd) {

  printk(KERN_INFO "hello inserted\n");
  major_num = register_chrdev(0, "hello_chr", &fops);
  printk(KERN_INFO "major number is %d\n", major_num);
  return 0;
}

static int end_here(struct platform_device *pd) {
  printk(KERN_INFO "Goodbye, satan \n");
  unregister_chrdev(major_num, "hello_chr");
  return 0;
}

static struct platform_driver driver = {
    .driver = { 
        .name = "hello",
    },
    .probe = start_here,
    .remove = end_here
};

module_platform_driver(driver);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
