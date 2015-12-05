#include "module/meter_app.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/errno.h>

int main(void)
{
	int retval, fd;
	char magic;

	retval = open("/dev/meter0", O_RDONLY);
	
	if(retval < 0)
	{
		printf("Error opening device\r\n");
		return retval;
	}

	fd = retval;

	printf("Successfully opened device\r\n");

	retval = ioctl(fd, IOCTL_GET_MAGIC_NUMBER, &magic);

	if(retval != 0)
	{
		if(magic != METER_MAGIC_NUMBER)
		{
			printf("ERROR! Magic number did not match\r\n");
			retval -ENOTTY;
		}
	}
	else
	{
		printf("ERROR! IOCTL command failed\r\n");
	}

	close(fd);
	return retval;
}
