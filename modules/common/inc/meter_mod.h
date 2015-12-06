/* Defines related to our kernel module */
#ifndef __METER_MOD_H__
#define __METER_MOD_H__

#include <linux/module.h>
#include <linux/mutex.h>

#define DEFAULT_MAJOR_ID	0 /*Dynamic*/

extern dev_t dev_id;

/* This is a module wide lock taken by devices that cannot be powered on simultaniously */
extern struct mutex module_power_lock;

#endif
