
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

#include <linux/device.h>    /* class_create() , ...  */

#define ARRAY_SIZE(a)		(sizeof(a) / sizeof(a[0]))
#define MIN(x, y)			((x) < (y) ? (x) : (y))

#define CHRDEV_DEVICE_NAME     "buttons"

static int major;

static struct class *buttons_class;
static struct class_device *buttons_class_dev;


struct button_pin_desc {
	int irq;
	unsigned int pin;
	int pin_setting;
	unsigned int id;
	char *name;
};
     

static struct button_pin_desc button_pins [] = {
	{IRQ_EINT8 , S3C2410_GPG0 ,  S3C2410_GPG0_EINT8  , 0, "K0"},
	{IRQ_EINT11, S3C2410_GPG3 ,  S3C2410_GPG3_EINT11 , 1, "K1"},
	{IRQ_EINT13, S3C2410_GPG5 ,  S3C2410_GPG5_EINT13 , 2, "K2"},
	{IRQ_EINT15, S3C2410_GPG7 ,  S3C2410_GPG7_EINT15 , 3, "K3"},
	{IRQ_EINT14, S3C2410_GPG6 ,  S3C2410_GPG6_EINT14 , 4, "K4"},
	{IRQ_EINT19, S3C2410_GPG11,  S3C2410_GPG11_EINT19, 5, "K5"}
};

static unsigned char key_value;


static DECLARE_WAIT_QUEUE_HEAD(button_waitq);     

static volatile int event_press = 0;

irqreturn_t buttons_isr_handler(int vec, void *dev_id)
{
	struct button_pin_desc *button_pin = (struct button_pin_desc *)dev_id;

	unsigned int ret = 0;

	ret = s3c2410_gpio_getpin(button_pin->pin);
	if(ret == 1)
	{
		// pressed
		key_value = 0x80 | button_pin->id;
	}
	else
	{
		key_value = button_pin->id;
	}

	event_press = 1;
	wake_up_interruptible(&button_waitq);
	
	return IRQ_RETVAL(IRQ_HANDLED);
}


static int buttons_driver_open(struct inode * inode, struct file * file)
{
	// 
	int i ;
	int ret;
	
	for(i = 0; i < ARRAY_SIZE(button_pins); i++)
	{
		ret = request_irq(button_pins[i].irq, buttons_isr_handler, IRQT_BOTHEDGE, 
			               button_pins[i].name, &button_pins[i]);

		if(ret != 0)
			break;
	}

	if(ret != 0)
	{
		i--;
		for(;i >= 0;i--)
		{
			disable_irq(button_pins[i].irq);
			free_irq(button_pins[i].irq, &button_pins[i]);
		}
	}
	return 0;
}

static ssize_t buttons_driver_read(struct file * file, char __user * userbuf, size_t count, loff_t * off)
{
	if(count != 1)
		return -EINVAL;

	wait_event_interruptible(button_waitq, event_press);

	if(copy_to_user(userbuf, (void *)&key_value, 1) != 0)
		return -EFAULT;

	event_press = 0;
	
	return 1;
}

static int buttons_driver_close (struct inode *inode, struct file *file)
{
	int i;

	for(i = 0; i < ARRAY_SIZE(button_pins); i++)
	{
		free_irq(button_pins[i].irq, &button_pins[i]);
	}
	return 0;
}


static struct file_operations buttons_driver_fops = 
{
	.owner     = THIS_MODULE,
	.open      = buttons_driver_open,
	.read      = buttons_driver_read,
	.release   = buttons_driver_close
};


static int buttons_driver_init(void)
{
	major = register_chrdev(0, CHRDEV_DEVICE_NAME, &buttons_driver_fops);

	buttons_class = class_create(THIS_MODULE, "buttons_drv");

	buttons_class_dev = class_device_create(buttons_class, NULL, MKDEV(major, 0), NULL, "buttons");
	
	return 0;
}

static void buttons_driver_exit(void)
{
	class_device_unregister(buttons_class_dev);
	class_destroy(buttons_class);
	
	unregister_chrdev(major, CHRDEV_DEVICE_NAME);
}

module_init(buttons_driver_init);
module_exit(buttons_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Flinn");
MODULE_DESCRIPTION("Buttons driver for mini2440");

