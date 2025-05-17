#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

#include "ioctl_cmd.h"

int major;
int32_t value = 786;

static long int my_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
		case WR_VALUE:
			if(copy_from_user(&value, (int32_t *)arg, sizeof(value)))
				pr_err("Error writing the value");
			pr_info("Wrote %d\n", value);
			break;
		case RD_VALUE:
			if(copy_to_user((int32_t *)arg, &value, sizeof(value)))
				pr_err("Error reading the value\n");
			pr_info("Read Success\n");
			break;
		default:
			break;
	}
	return 0;
}

static int my_open (struct inode *inode, struct file *fp)
{
	pr_info("hello_cdev: Device Major no %d\t Minor no%d\n", imajor(inode), iminor(inode));

	pr_info("hello_cdev: File mode %x\n", fp->f_mode); 
	return 0;
}

static int my_release(struct inode *inode, struct file *fp)
{
	pr_info("hello_cdev: File closed\n");
	return 0;
}

static struct file_operations fops = {
	.open = my_open,
	.release = my_release,
	.unlocked_ioctl = my_ioctl
};

static int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops);
	if (major < 0) {
		pr_err("hello_cdev: Error registering the device\n");
		return major;
	}

	pr_info("hello_cdev: Registerted with Major device no %d\n", major);
    	return 0;
}

static void __exit my_exit(void)
{
	unregister_chrdev(major, "hello_cdev");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prathamesh Rahate <patyarahate@gmail.com>");
MODULE_DESCRIPTION("A simple character device with open and release fucntions");
