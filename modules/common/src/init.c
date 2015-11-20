
#include <linux/module.h> /* Module init and exit */
#include <linux/kernel.h> /* printk */
#include "meter_dev.h"
#include "meter_init.h"

int __init mod_init(void);
void __exit mod_exit(void);

dev_t dev_id = MKDEV(DEFAULT_MAJOR_ID, 0);

module_init(mod_init);
module_exit(mod_exit);

/* Passed from the build system */
METER_EXTERN_STR;
static meter_dev_t * devices_in_ram[NUM_METERS] = METER_INIT_STR;
/* End passed from build system */

int __init mod_init(void)
{
	int result;

	/* register the major ID */
	if (DEFAULT_MAJOR_ID != 0)
		result = register_chrdev_region(dev_id, METER_NUM_DEVS,
				MODULE_NAME);
	else 
	{
		result = alloc_chrdev_region(&dev_id, 0, METER_NUM_DEVS,
				MODULE_NAME);
	}
	if (result < 0)
		return result;

	for (i=0; i < METER_NUM_DEVS; i++)
	{
		/* Device initialization goes here */
		meter_dev_t * temp = devices_in_ram[i];
		temp->dev_id = MKDEV(MAJOR(dev_id), i);
	}
	
	return 0;
}

void __exit mod_exit(void)
{
	printk(KERN_EMERG "Goodbye kernel!  Our module has exited.\r\n");
}
