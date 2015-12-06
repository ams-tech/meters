
#include <linux/module.h> /* Module init and exit */
#include <linux/kernel.h> /* printk */
#include <linux/fs.h>
#include <linux/mutex.h>
#include "meter_dev.h"
#include "meter_init.h"
#include "meter_mod.h"
#include "meter_app.h"
#include "meter_fops.h"

DEFINE_MUTEX(module_power_lock);

int __init mod_init(void);
void __exit mod_exit(void);

MODULE_AUTHOR("ams-tech");
MODULE_LICENSE("GPL v2");

dev_t dev_id = MKDEV(DEFAULT_MAJOR_ID, 0);

module_init(mod_init);
module_exit(mod_exit);

/* Passed from the build system */
METER_EXTERN_STR;
meter_dev_t * devices_in_ram[NUM_METERS] = METER_INIT_STR;
/* End passed from build system */

int __init mod_init(void)
{
	int result, i;

	/* register the major ID */
	if (DEFAULT_MAJOR_ID != 0)
		result = register_chrdev_region(dev_id, NUM_METERS,
				MODULE_NAME);
	else 
	{
		result = alloc_chrdev_region(&dev_id, 0, NUM_METERS,
				MODULE_NAME);
	}
	if (result < 0)
		return result;

	for (i=0; i < NUM_METERS; i++)
	{
		/* Device initialization goes here */
		meter_dev_t * temp = devices_in_ram[i];
		temp->dev_id = MKDEV(MAJOR(dev_id), i);
		fops_init(temp);
	}
	
	return 0;
}

void __exit mod_exit(void)
{
	int i;

	unregister_chrdev_region(dev_id, NUM_METERS);	

	for (i=0; i < NUM_METERS; i++)
	{
		fops_exit(devices_in_ram[i]);
	}

	printk(KERN_EMERG "Goodbye kernel!  Our module has exited.\r\n");
}
