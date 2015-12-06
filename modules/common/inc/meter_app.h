#ifndef __METER_APP_H__
#define __METER_APP_H__

#ifdef __KERNEL__
	#include <linux/types.h>
#else /*Application*/
	#include <sys/ioctl.h>
	#include <stdint.h>
	#include <stdbool.h>

	typedef uint8_t u8;
	typedef uint32_t u32;
#endif

#define MODULE_NAME "meter"

#define METER_MAGIC_NUMBER 'g'

typedef struct meter_data_X
{
	u8 sig_bits;
	int payload;
	bool is_signed;
}meter_data_t;

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
