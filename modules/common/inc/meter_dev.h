/* This is a header file describing our meter device interface */

#define DEVICE_NAME_MAX_LEN	40

typedef struct meter_dev_X
{
	char name[DEVICE_NAME_MAX_LEN];
}meter_dev_t;
