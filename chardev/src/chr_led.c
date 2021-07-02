#include "chr_led.h"
#define DEVICE_NAME "nameless"
#define BUFF_LEN 100
#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"

// initialize all buffers
static int major_num;
static char msg[BUFF_LEN];
static int Device_open = 0;
static char *msg_ptr;
dev_t dev = 0;
static struct cdev chrdev;
static struct class *chr_class;
static struct device *sdevice;
// initialize fileoperations
static struct file_operations fops = { .read = device_read, .open = device_open, .release = device_release, .write = device_write };

static ssize_t device_read(struct file *f_read, char *dest, size_t size, loff_t *offset)
{
	// use put_user to write to user buffer
	ssize_t bytes_read = 0;
	while (size && *msg_ptr) {
		if (EFAULT == put_user(*msg_ptr++, dest++)) {
			printk(KERN_WARNING "hello couldn't able to write to user %d\n", EFAULT);
			return bytes_read;
		}
		size--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t device_write(struct file *f_read, const char *dest, size_t size, loff_t *offset)
{
	// print error message
	printk(KERN_ALERT "Sorry shop is closed today!!!\n");
	return EINVAL;
}

static int device_open(struct inode *inode, struct file *file)
{
	// incriment device open write message to buffer
	sprintf(msg, "already told you %d times that \"No its not possible\" \n", ++Device_open);
	// update msg_ptr
	msg_ptr = msg;
	// module-get
	if (!try_module_get(THIS_MODULE))
		return -1;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	// put the module
	module_put(THIS_MODULE);
	return 0;
}

int __init init_dev(void)
{
	int err;
	if ((err = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME)) < 0) {
		printk(KERN_ERR "Couldn't allocate chrdev, with error code %d\n", err);
	}
	printk(KERN_INFO "chrdev : registered device - Major %d, Minor %d\n", MAJOR(dev), MINOR(dev));

	// create cdev structure
	cdev_init(&chrdev, &fops);

	// add cdev to system
	if ((err = cdev_add(&chrdev, dev, 1)) < 0) {
		printk(KERN_ERR "chrdev: cannot add the device to system, exits with error %d\n", err);
		goto c_ret;
	}

	if ((chr_class = class_create(THIS_MODULE, DEVICE_NAME)) == NULL) {
		printk(KERN_ERR "chrdev: failed to create device class\n");
		err = -1;
		goto c_ret;
	}

	// create device and register to sysfs
	if ((sdevice = device_create(chr_class, NULL, dev, NULL, DEVICE_NAME)) == NULL) {
		printk(KERN_ERR "chrdev: failed to create sysfs device\n");
		err = -1;
		goto dest_ret;
	}
	printk(KERN_INFO "chrdev: initialized\n");
	return 0;
dest_ret:
	class_destroy(chr_class);
c_ret:
	unregister_chrdev_region(dev, 1);
	return err;
}

void __exit bye_satan(void)
{
	device_destroy(chr_class, dev);
	class_destroy(chr_class);
	cdev_del(&chrdev);
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "hello: Good bye Satan\n");
}

module_init(init_dev);
module_exit(bye_satan);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_SUPPORTED_DEVICE("TrashCan");
