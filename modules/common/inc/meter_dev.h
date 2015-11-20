/* This is a header file describing our meter device interface */
#ifndef __METER_DEV_H__
#define __METER_DEV_H__


#include <linux/module.h>
#include <linux/cdev.h>

#define DEVICE_NAME_MAX_LEN	40

typedef struct meter_dev_X
{
	char name[DEVICE_NAME_MAX_LEN];
	dev_t dev_id; /* Our device ID and location in devices_in_ram array */
	struct cdev cdev;
}meter_dev_t;

#endif
