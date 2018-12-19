/* second drv : add mdev  */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#include <linux/device.h>    /* class_create() , ...  */


static int major;

static struct class *seconddrv_class;
static struct class_device *seconddrv_class_dev;

static int second_drv_open(struct inode * inode, struct file * file)
{
	printk(KERN_INFO"second_drv_open .\n");
	return 0;
}

static ssize_t second_drv_write(struct file * file, const char __user * userbuf,
		     size_t count, loff_t * off)
{
	printk(KERN_INFO"second_drv_write .\n");
	return 0;
}


static struct file_operations second_drv_fops = {
	.owner     = THIS_MODULE,
	.write		= second_drv_write,
	.open		= second_drv_open,
};


static int  second_drv_init(void)
{
	major = register_chrdev(0, "second_drv", &second_drv_fops);

	seconddrv_class = class_create(THIS_MODULE,  "seconddrv");

	seconddrv_class_dev = class_device_create(seconddrv_class, NULL, MKDEV(major, 0), NULL, "xyz");
	
	return 0;
}

static void  second_drv_exit(void)
{
	class_device_unregister(seconddrv_class_dev);
        class_destroy(seconddrv_class);

	unregister_chrdev(major, "second_drv");
}


module_init(second_drv_init);
module_exit(second_drv_exit);
MODULE_LICENSE("GPL");
