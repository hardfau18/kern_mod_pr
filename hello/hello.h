#include <linux/fs.h>

#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"

ssize_t read(struct file *filename, char __user *user, size_t size,
             loff_t *offset);

ssize_t write(struct file *file_name, const char __user *user, size_t size,
              loff_t *offset);

int open(struct inode *, struct file *);
int release(struct inode *, struct file *);
loff_t seek (struct file *, loff_t, int);
