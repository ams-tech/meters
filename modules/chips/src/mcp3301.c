#include "mcp3301.h"
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include "gpio.h"

#define TIME_TOLERANCE	1.05

/* Chip select disable time, in ns */
#define T_CSH_NS	(580 * TIME_TOLERANCE)
/* Chip select setup time */
#define T_SUCS_NS	(100 * TIME_TOLERANCE)
/* Clock high time */
#define T_HI_NS		(275 * TIME_TOLERANCE)
/* Clock low time */
#define T_LO_NS		(275 * TIME_TOLERANCE)

#define GOTO_ON_ERROR(x, err, gt) \
	err = x; \
	if(err) \
		goto gt

#define SET_GPIO_PIN(pin) \
	GOTO_ON_ERROR( \
		set_gpio_pin(pin), \
		error, exit)

#define CLEAR_GPIO_PIN(pin) \
	GOTO_ON_ERROR( \
		clear_gpio_pin(pin), \
		error, exit)

static inline bool read_bit(mcp3301_t * chip)
{
	bool retval;

	set_gpio_pin(chip->gpio.clk);
	udelay(T_HI_NS);
	get_gpio_pin(chip->gpio.data, &retval);
	clear_gpio_pin(chip->gpio.clk);
	udelay(T_LO_NS);

	return retval;
}

int mcp3301_read(mcp3301_t * chip, u16 * result)
{
	u16 retval = 0;
	int x, error = 0;

	mutex_lock(&(chip->lock));

	printk(KERN_DEBUG "Initializing MCP3301 GPIO\n");

	/* data */
	GOTO_ON_ERROR(
		set_gpio_function(chip->gpio.data, GPIO_INPUT),
		error, exit);

	/* clock */
	CLEAR_GPIO_PIN(chip->gpio.clk);
	GOTO_ON_ERROR(
		set_gpio_function(chip->gpio.clk, GPIO_OUTPUT),
		error, exit);

	/* chip select */
	SET_GPIO_PIN(chip->gpio.enable);
	GOTO_ON_ERROR(
		 set_gpio_function(chip->gpio.enable, GPIO_OUTPUT),
		 error, exit);

	ndelay(T_CSH_NS);

	printk(KERN_DEBUG "Init complete, lowering chip enable\n");

	CLEAR_GPIO_PIN(chip->gpio.enable);

	ndelay(T_SUCS_NS);

	printk(KERN_DEBUG "Read two blank bits\n");

	read_bit(chip);
	read_bit(chip);

	printk(KERN_DEBUG "Reading null bit\n");

	if(read_bit(chip))
	{
		error = -EFAULT;
		goto exit;
	}

	printk(KERN_DEBUG "Reading %d result bits\n", RESULT_BITS);

	for(x = (RESULT_BITS - 1); x >= 0; x--)
	{
		printk(KERN_DEBUG "Reading bit number %d\n", x);

		if(read_bit(chip))
			retval |= 1 << (x);
	}

	printk(KERN_DEBUG "Read complete, setting chip select\n");

	SET_GPIO_PIN(chip->gpio.enable);

exit:
	printk(KERN_DEBUG "Freeing mutex and exiting MCP3301 read\n");
	mutex_unlock(&(chip->lock));
	return error;
	
}

int mcp3301_init(mcp3301_t * chip)
{
	mutex_init(&(chip->lock));
	return 0;
}
