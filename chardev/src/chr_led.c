#include "chr_led.h"
#define DEVICE_NAME     "nameless"
#define BUFF_LEN        100
#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"

// initialize all buffers
static int major_num;
static char msg[BUFF_LEN];
static int Device_open = 0;
static char*  msg_ptr;
// initialize fileoperations
static struct file_operations fops = {
    .read = device_read,
    .open = device_open,
    .release = device_release,
    .write = device_write 
};


static ssize_t device_read(struct file* f_read, char * dest, size_t size, loff_t* offset){
    // use put_user to write to user buffer
    ssize_t bytes_read=0;
    while(size && *msg_ptr){
        if(EFAULT == put_user(*msg_ptr++, dest++)){
            printk(KERN_WARNING "hello couldn't able to write to user %d\n", EFAULT);
            return bytes_read;
        }
        size--;
        bytes_read++;
    }
    return bytes_read;
}

static ssize_t device_write(struct file* f_read, const char * dest, size_t size, loff_t* offset){
    // print error message
    printk(KERN_ALERT "Sorry shop is closed today!!!\n");
    return EINVAL;
}

static int device_open(struct inode* inode, struct file* file){
    // incriment device open write message to buffer
    sprintf(msg, "already told you %d times that \"No its not possible\" \n", ++Device_open);
    // update msg_ptr
    msg_ptr = msg;
    // module-get
    if (! try_module_get(THIS_MODULE)) return -1;
    return 0;
}

static int device_release(struct inode* inode, struct file* file){
    // put the module
    module_put(THIS_MODULE);
    return 0;
}

int init_module(void) {
    // get the major number
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0){
        printk(KERN_ERR "hello : couldn't register device, return code is %d\n", major_num);
        return major_num;
    }
    printk(KERN_INFO "hello : registered device - %d\n", major_num);
    return 0;
}

void cleanup_module(void)
{
    // unregister device
    unregister_chrdev(major_num, DEVICE_NAME) ;
    printk(KERN_INFO "hello: Good bye Satan\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_SUPPORTED_DEVICE("TrashCan");
