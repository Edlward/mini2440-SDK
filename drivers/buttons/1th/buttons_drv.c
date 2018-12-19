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

/*
 * GPIO definition for mini2440 :
 *
 *	key 1      GPG0          EINT8
 *	key 2      GPG3          EINT11
 *	key 3      GPG5          EINT13
 *	key 4      GPG6          EINT14
 *	key 5      GPG7          EINT15
 *	key 6      GPG11         EINT19
*/



#define GPG_BASE			0x56000060
#define GPGCON_ADDR			GPG_BASE
#define GPGDAT_ADDR			GPG_BASE + 4
#define GPGUP_ADDR			GPG_BASE + 8

volatile unsigned long *gpgcon = NULL;
volatile unsigned long *gpgdat = NULL;

static int major;

static struct class *buttonsdrv_class;
static struct class_device *buttonsdrv_class_dev;


static void buttons_gpio_init(void)
{
	// set gpio-key as input
	*gpgcon &= ~((0x3 << (0 * 2)) | (0x3 << (3 *2)) | (0x3 << (5 * 2 )) | \
				(0x3 << (6 * 2)) | (0x3 << (7 * 2)) | (0x3 << (11 * 2))
	);
}

static int buttons_drv_open(struct inode * inode, struct file * file)
{
	buttons_gpio_init();
	return 0;
}

static ssize_t buttons_drv_read(struct file * file, char __user * userbuf, size_t count, loff_t * off)
{
	// return the status of keys
	unsigned char status[6];
	int retval;

	if(count != sizeof(status))
		return -EINVAL;

	retval = *gpgdat;
	status[0] = (retval & (1 << 0)) ? 1 : 0;
	status[1] = (retval & (1 << 3)) ? 1 : 0;
	status[2] = (retval & (1 << 5)) ? 1 : 0;
	status[3] = (retval & (1 << 6)) ? 1 : 0;
	status[4] = (retval & (1 << 7)) ? 1 : 0;
	status[5] = (retval & (1 << 11)) ? 1 : 0;

	if(copy_to_user(userbuf, status, sizeof(status)))
		return  -EFAULT;
	
	return sizeof(status);
}



static struct file_operations buttons_drv_fops = 
{
	.owner      = THIS_MODULE,
	.open       = buttons_drv_open,
	.read       = buttons_drv_read
};

static int buttons_drv_init(void)
{
	major = register_chrdev(0, "buttons", &buttons_drv_fops);

	buttonsdrv_class = class_create(THIS_MODULE, "buttons_drv");

	buttonsdrv_class_dev = class_device_create(buttonsdrv_class, NULL, MKDEV(major, 0), NULL, "buttons");
	
	gpgcon = (volatile unsigned long *)ioremap(GPG_BASE, 16);
	gpgdat = gpgcon + 1;

	return 0;
}

static void buttons_drv_exit(void)
{
	iounmap(gpgcon);

	class_device_unregister(buttonsdrv_class_dev);
	class_destroy(buttonsdrv_class);
	
	unregister_chrdev(major, "buttons");
}

module_init(buttons_drv_init);
module_exit(buttons_drv_exit);
MODULE_LICENSE("GPL");

