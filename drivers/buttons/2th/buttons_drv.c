/*  基于中断方式的按键驱动程序             */

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


struct pin_desc {
	unsigned int pin;
	unsigned int key_val;
};

/*
 * pressed : 0x01 , 02, 03, 04, 05, 06
 * free    : 0x81, 82, 83, 84, 85, 86
*/
static struct pin_desc pins[6] = {
	{S3C2410_GPG0 , 0x01},
	{S3C2410_GPG3 , 0x02},
	{S3C2410_GPG5 , 0x03},
	{S3C2410_GPG6 , 0x04},
	{S3C2410_GPG7 , 0x05},
	{S3C2410_GPG11 , 0x06}
};

#define GPG_BASE			0x56000060
#define GPGCON_ADDR			GPG_BASE
#define GPGDAT_ADDR			GPG_BASE + 4
#define GPGUP_ADDR			GPG_BASE + 8

volatile unsigned long *gpgcon = NULL;
volatile unsigned long *gpgdat = NULL;


static int major;

static struct class *buttonsdrv_class;
static struct class_device *buttonsdrv_class_dev;

static unsigned char key_value;

static DECLARE_WAIT_QUEUE_HEAD(buttons_wait);
static volatile int event_press = 0;     // flasg of wait , =1 while interrupt occure

irqreturn_t key_irq_handler(int irq, void *dev_id)
{
	struct pin_desc *pin = (struct pin_desc *)dev_id;

	unsigned int ret ;

	ret = s3c2410_gpio_getpin(pin->pin);
	if(ret)
	{
		// pressed
		key_value = 0x80 | pin->key_val;
	}
	else
	{
		key_value = pin->key_val;
	}

	event_press = 1;
	wake_up_interruptible(&buttons_wait);

	return IRQ_RETVAL(IRQ_HANDLED);
}


static int buttons_drv_open(struct inode * inode, struct file * file)
{
	//buttons_gpio_init();

	s3c2410_gpio_cfgpin(S3C2410_GPG0, S3C2410_GPG0_EINT8);
	s3c2410_gpio_cfgpin(S3C2410_GPG3, S3C2410_GPG3_EINT11);
	s3c2410_gpio_cfgpin(S3C2410_GPG5, S3C2410_GPG5_EINT13);
	s3c2410_gpio_cfgpin(S3C2410_GPG6, S3C2410_GPG6_EINT14);
	s3c2410_gpio_cfgpin(S3C2410_GPG7, S3C2410_GPG7_EINT15);
	s3c2410_gpio_cfgpin(S3C2410_GPG11, S3C2410_GPG11_EINT19);

	if(request_irq(IRQ_EINT8, key_irq_handler, IRQT_BOTHEDGE, "K1", &pins[0]) != 0)
	{
		printk("request_irq IRQ_EINT8 err . \n");
		return -ENODEV;
	}
	if(request_irq(IRQ_EINT11, key_irq_handler, IRQT_BOTHEDGE, "K2", &pins[1]) != 0)
        {
		printk("request_irq IRQ_EINT11 err . \n" );
                return -ENODEV;
	}
	if(request_irq(IRQ_EINT13, key_irq_handler, IRQT_BOTHEDGE, "K3", &pins[2]) != 0)
        {
                printk("request_irq IRQ_EINT13 err . \n" );
                return -ENODEV;
        }
	if(request_irq(IRQ_EINT14, key_irq_handler, IRQT_BOTHEDGE, "K4", &pins[3]) != 0)
        {
                printk("request_irq IRQ_EINT14 err . \n" );
                return -ENODEV;
        }
	if(request_irq(IRQ_EINT15, key_irq_handler, IRQT_BOTHEDGE, "K5", &pins[4]) != 0)
        {
                printk("request_irq IRQ_EINT15 err . \n" );
                return -ENODEV;
        }
	if(request_irq(IRQ_EINT19, key_irq_handler, IRQT_BOTHEDGE, "K6", &pins[5]) != 0)
        {
                printk("request_irq IRQ_EINT19 err . \n" );
                return -ENODEV;
        }
	
	return 0;
}

static ssize_t buttons_drv_read(struct file * file, char __user * userbuf, size_t count, loff_t * off)
{
	// return the status of keys
	//unsigned char status[6];

	if(count != 1)
		return -EINVAL;
	
	// 如果没有按键动作， 休眠
	wait_event_interruptible(buttons_wait, event_press);

	copy_to_user(userbuf, &key_value, 1);
	event_press = 0;
	
	return 1;
}



int buttons_drv_release (struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT19, &pins[5]);
	free_irq(IRQ_EINT15, &pins[4]);
	free_irq(IRQ_EINT14, &pins[3]);
	free_irq(IRQ_EINT13, &pins[2]);
	free_irq(IRQ_EINT11, &pins[1]);
	free_irq(IRQ_EINT8, &pins[0]);
	return 0;
}


static struct file_operations buttons_drv_fops = 
{
	.owner      = THIS_MODULE,
	.open       = buttons_drv_open,
	.read       = buttons_drv_read,
	.release    = buttons_drv_release
};

static int buttons_drv_init(void)
{
	major = register_chrdev(0, "buttons", &buttons_drv_fops);

	buttonsdrv_class = class_create(THIS_MODULE, "buttons_drv");

	// "/dev/buttons"
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
