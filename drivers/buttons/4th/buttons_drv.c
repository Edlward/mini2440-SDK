/**
*  File     :  buttons_input_drv.c
*
*  create   :    Oct 24, 2018
*   Note(s) :    buttons drv from input-subsystem
*/

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

#include <linux/input.h>

#include <linux/device.h>    /* class_create() , ...  */

static struct input_dev *buttons_dev;


struct pin_desc 
{
	int irq;
	char *name;
	unsigned int pin;
	unsigned int key_value;
};

static struct pin_desc pins[] = 
{
	{IRQ_EINT8   , "K1",  S3C2410_GPG0 , 0x01},
	{IRQ_EINT11  , "K2",  S3C2410_GPG3 , 0x02},
	{IRQ_EINT13  , "K3",  S3C2410_GPG5 , 0x03},
	{IRQ_EINT14  , "K4",  S3C2410_GPG6 , 0x04},
	{IRQ_EINT15  , "K5",  S3C2410_GPG7 , 0x05},
	{IRQ_EINT19  , "K6",  S3C2410_GPG11, 0x06}
};

irqreturn_t key_irq_handler(int irq, void *dev_id)
{
	struct pin_desc *pin = (struct pin_desc *)dev_id;

	return IRQ_HANDLED;
}



static int buttons_drv_init(void)
{
	int i;

	buttons_dev = input_allocate_device();
	if (!buttons_dev)
		return -ENOMEM;


	buttons_dev->name = "buttons";	
	set_bit(EV_KEY, buttons_dev->evbit);

	set_bit(KEY_L, buttons_dev->keybit);
	set_bit(KEY_S, buttons_dev->keybit);
	set_bit(KEY_ENTER, buttons_dev->keybit);
	set_bit(KEY_P, buttons_dev->keybit);
	set_bit(KEY_S, buttons_dev->keybit);
	set_bit(KEY_BACKSPACE, buttons_dev->keybit);
	
	input_register_device(buttons_dev);

	for(i = 0 ; i < (sizeof(pins)/sizeof(pins[0])) ; i++)
	{
		if(request_irq(pins[i].irq, key_irq_handler, IRQT_BOTHEDGE, pins[i].name, &pins[i]) != 0)
			break;
	}

	return 0;
}

static void buttons_drv_exit(void)
{	
	int i;
	for(i = 0 ; i < (sizeof(pins)/sizeof(pins[0])) ; i++)
	{
		free_irq(pins[i].irq,  &pins[i]);
	}

	// free input-device
	input_unregister_device(buttons_dev);
	input_free_device(buttons_dev);
}


module_init(buttons_drv_init);
module_exit(buttons_drv_exit);
MODULE_LICENSE("GPL");

