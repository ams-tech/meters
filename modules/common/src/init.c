
#include <linux/module.h> /* Module init and exit */
#include <linux/kernel.h> /* printk */
#include "meter_dev.h"
#include "meter_init.h"

int __init mod_init(void);
void __exit mod_exit(void);

dev_t dev_id;

module_init(mod_init);
module_exit(mod_exit);

/* Passed from the build system */
METER_EXTERN_STR;
static meter_dev_t * devices_in_ram[NUM_METERS] = METER_INIT_STR;
/* End passed from build system */

int __init mod_init(void)
{
	
	return 0;
}

void __exit mod_exit(void)
{
	printk(KERN_EMERG "Goodbye kernel!  Our module has exited.\r\n");
}
