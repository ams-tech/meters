
#include <linux/module.h> /* Module init and exit */
#include <linux/kernel.h> /* printk */
#include <linux/fs.h>
#include "meter_dev.h"
#include "meter_init.h"
#include "meter_mod.h"
#include "meter_app.h"

int __init mod_init(void);
void __exit mod_exit(void);

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
	}
	
	return 0;
}

void __exit mod_exit(void)
{
	printk(KERN_EMERG "Goodbye kernel!  Our module has exited.\r\n");
}
