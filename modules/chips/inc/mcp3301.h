#ifndef __MCP3301_H__
#define __MCP3301_H__

#include <linux/types.h>
#include <linux/mutex.h>
#include "gpio.h"

#define MCP3301_ERROR 	0xFFFF
#define RESULT_BITS	13

typedef struct mcp3301_X
{
	struct mutex lock;
	struct gpio
	{
		gpio_t clk;
		gpio_t data;
		gpio_t enable;
	} gpio;
}mcp3301_t;

/* returns a signed 13 bit result extended to an int */
int mcp3301_read(mcp3301_t * chip, int * result);
int mcp3301_init(mcp3301_t * chip);

#endif
