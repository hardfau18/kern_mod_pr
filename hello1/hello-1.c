#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#define AUTHOR "hardfault"
#define DESCRIPTION "module for testing"


/* 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */
static int age = 10;
module_param(age, int, S_IRUSR);

/* module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); */
/* MODULE_PARM_DESC(myshort, "A short integer"); */
/* module_param(mystring, charp, 0000); */
/* MODULE_PARM_DESC(mystring, "A character string"); */

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */
/* module_param_array(); */
/* MODULE_PARM_DESC(); */

static int __init start_here(void)
{
    return 0;
}

static void __exit end_here(void)
{
	printk(KERN_INFO "Goodbye, satan \n");
}



module_init(start_here);
module_exit(end_here);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_SUPPORTED_DEVICE("TrashCan");

