/* This is a header file describing our meter device interface */
#ifndef __METER_DEV_H__
#define __METER_DEV_H__

#include "meter_app.h"
#include <linux/module.h>
#include <linux/cdev.h>

#define DEVICE_NAME_MAX_LEN	40

struct meter_dev_X;

typedef int (*meter_read_f)(struct meter_dev_X dev, unsigned int samples, meter_data_t * result); 
typedef int (*meter_init_f)(struct meter_dev_X dev);
typedef void (*meter_exit_f)(struct meter_dev_X dev);

typedef struct meter_interface_X
{
	meter_read_f read;
	meter_init_f init;
	meter_exit_f exit;
}meter_interface_t;

typedef struct meter_dev_X
{
	char name[DEVICE_NAME_MAX_LEN];
	dev_t dev_id; /* Our device ID and location in devices_in_ram array */
	struct cdev cdev;
	meter_interface_t phy_interface;
}meter_dev_t;

extern dev_t dev_id;
extern meter_dev_t * devices_in_ram[];

#endif
