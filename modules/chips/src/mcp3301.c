#include "mcp3301.h"
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include "gpio.h"

#define CALL_EXIT_ON_ERROR(x, err, gt) \
	err = x; \
	if(err) \
		goto gt;


static inline bool read_bit(mcp3301_t * chip)
{

}

int mcp3301_read(mcp3301_t * chip, u16 * result)
{
	u16 retval = MCP3301_ERROR;
	int error = 0;

	printk(KERN_DEBUG "Initializing MCP3301 GPIO\n");

	

exit:
	//TODO: Unlock mutex
	return error;
	
}

int mcp3301_init(mcp3301_t * chip)
{
	mutex_init(&(chip->lock));
	return 0;
}
