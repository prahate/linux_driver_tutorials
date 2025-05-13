#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/fcntl.h>

int major;
char text[64];

static ssize_t my_read(struct file *fp, char __user *ubuf, size_t len, loff_t *off)
{
	pr_info("Read is called\n");
	int not_copied, delta, to_copy = (len + *off) <  sizeof(text) ? len : (sizeof(text) - *off);


	not_copied = copy_to_user(ubuf, &text[*off], to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("could not read %d bytes\n", delta);

	*off += delta;
	return delta;
}

static ssize_t my_write(struct file *fp, const char __user *ubuf, size_t len, loff_t *off)
{
	pr_info("Write is called\n");
	int not_copied, delta, to_copy = (len + *off) <  sizeof(text) ? len : (sizeof(text) - *off);


	not_copied = copy_from_user(&text[*off], ubuf, to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("could not write %d bytes\n", delta);

	*off += delta;
	return delta;
}

static struct file_operations fops = {
	.read = my_read,
	.write = my_write
};


static int __init my_init(void)
{
	int major;
	major = register_chrdev(0, "hello_cdev", &fops);
	if (major == -EINVAL || major == -EBUSY)
	{
		pr_err("Registering device failed\n");
		return -1;
	}

	pr_info("Device registered with major number %d\n", major);
    	return 0;
}

static void __exit my_exit(void)
{
    printk("Unregistering the device !!!\n");
    unregister_chrdev(major, "hello_cdev");
}

module_init(my_init);
module_exit(my_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Prathamesh Rahate <patyarahate@gmail.com>");
MODULE_DESCRIPTION("Simple Cdev with read write operations implemented");
