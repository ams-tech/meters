#ifndef __METER_FOPS_H__
#define __METER_FOPS_H__

#include "meter_dev.h"

int fops_init(meter_dev_t * dev);
void fops_exit(meter_dev_t * dev);

#endif
