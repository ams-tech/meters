/* This is a header file describing our meter device interface */

#include <linux/module.h>

#define DEVICE_NAME_MAX_LEN	40

typedef struct meter_dev_X
{
	char name[DEVICE_NAME_MAX_LEN];
	dev_t dev_id; /* Our device ID and location in devices_in_ram array */
}meter_dev_t;
