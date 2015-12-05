#ifndef __METER_APP_H__
#define __METER_APP_H__

#ifdef __KERNEL__
	#include <linux/types.h>
#else
	#include <sys/ioctl.h>
#endif

#define MODULE_NAME "meter"

#define METER_MAGIC_NUMBER 'g'

/*
 *  * _IOR means that we're creating an ioctl command 
    * number for passing information from a user process
    * to the kernel module. 
    *
    * _IOW means we're passing kernel information to the user
    *
    * Commands that start with a B_ are buffered commands.  
    * Access them via get/set_buffered_result
    */

#define IOCTL_GET_MAGIC_NUMBER	_IOW(METER_MAGIC_NUMBER, 1, char)


#endif
