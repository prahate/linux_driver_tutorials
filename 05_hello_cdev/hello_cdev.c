#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

int major;

ssize_t my_read (struct file *fp, char __user *ubuff, size_t size, loff_t * off)
{
	pr_info("Read called\n");
	return 0;
}

static struct file_operations fops = {
	.read = my_read
};

static int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops);
	if (major < 0) {
		pr_err("Error registering the device\n");
		return major;
	}

	pr_info("Registerted with Major device no %d\n", major);
    	return 0;
}

static void __exit my_exit(void)
{
	unregister_chrdev(major, "hello_cdev");
    	printk("GoodBye Kernel !!!\n");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prathamesh Rahate <patyarahate@gmail.com>");
MODULE_DESCRIPTION("Registering the character device");
