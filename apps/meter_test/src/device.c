#include "meter_test.h"
#include "module/meter_app.h"
#include <fcntl.h>
#include <linux/errno.h>
#include <stdio.h>

int device_open(char *name)
{
	int retval;

	if(name == NULL)
		return -EINVAL;

	retval = open(name, O_RDONLY);

	if(retval < 0)
	{
		PRINT_DEBUG(("Error opening device\r\n"));
	}

	return retval;
}
