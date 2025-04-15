#include <linux/module.h>
#include <linux/init.h>


static int __init my_init(void)
{
    printk("Hello Kernel!\n");
    return 0;
}

static void __exit my_exit(void)
{
    printk("GoodBye Kernel !!!\n");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prathamesh Rahate <patyarahate@gmail.com>");
MODULE_DESCRIPTION("Better Hello world module");
