/*
*  File : led_drv.c
*
*/

#include <linux/module.h>
#include <linux/kernel.h>        /* printk() , ... */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#include <linux/device.h>    /* class_create() , ...  */


static int major ;

static struct class *leddrv_class;
static struct class_device *leddrv_class_dev;

#define GPB_BASE			0x56000010
volatile unsigned long *gpbcon = NULL;
volatile unsigned long *gpbdat = NULL;

static int led_drv_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "open \n");

	// set GPB5,6,7,8 as output
	*gpbcon &= ~((0x3 << (5 * 2)) | (0x3 << (6 * 2)) | (0x3 << (7 * 2)) | (0x3 << (8 * 2))) ;
	*gpbcon |= ((0x1 << (5 * 2)) | (0x1 << (6 * 2)) | (0x1 << (7 * 2)) | (0x1 << (8 * 2)));

	return 0;
}

static ssize_t led_drv_write(struct file *file, const char __user *buf,
			 size_t count, loff_t *ppos)

{
	printk(KERN_INFO "write \n");
	int val;

	if (copy_from_user(&val, buf, count))
			return -EFAULT;	

	printk(KERN_INFO "value : %d \n", val);
	if(val == 1)
	{
		*gpbdat &=  ~((1 << 5) | (1 << 6) | (1 << 7) | (1 << 8));		
	}
	else if(0 == val)
	{
		*gpbdat |=  (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8);
	}
	else
	{
	}


	return 0;
}


static struct file_operations led_drv_fops = 
{
	.owner   = THIS_MODULE,
	.open    = led_drv_open,
	.write   = led_drv_write,
};


static int led_drv_init(void)
{
	major = register_chrdev(0, "led_drv", &led_drv_fops);
	
	leddrv_class = class_create(THIS_MODULE, "myled");

	leddrv_class_dev = class_device_create(leddrv_class, NULL, MKDEV(major, 0), NULL, "myled");

	gpbcon = (volatile unsigned long *)ioremap(GPB_BASE, 16);
	gpbdat = gpbcon + 1;

	return 0;
}


static void led_drv_exit(void)
{
	iounmap(gpbcon);

	class_device_unregister(leddrv_class_dev);
	class_destroy(leddrv_class);

	unregister_chrdev(major, "led_drv");
}


module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");
