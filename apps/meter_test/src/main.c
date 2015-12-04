#include "module/meter_app.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main(void)
{
	int retval;
	char magic;

	retval = open("/dev/ph0", O_RDONLY);
	
	if(retval < 0)
	{
		printf("Error opening device\r\n");
		return retval;
	}

	printf("Successfully opened device\r\n");

	close(retval);
	return 0;
}
