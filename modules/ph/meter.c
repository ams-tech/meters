#include "meter_dev.h"
#include "meter_mod.h"
#include "meter_app.h"
#include <linux/mutex.h>
#include "mcp3301.h"

#define PH_POWER_PIN	22
#define MAX_SAMPLES	5000

static mcp3301_t chip_phy = 
{
	.gpio = 
	{
		.clk = 7,
		.data = 5,
		.enable = 3
	}
};

static int ph_meter_read(meter_dev_t * dev, 
		unsigned int samples, meter_data_t * result);
static int ph_meter_init(meter_dev_t * dev);
static void ph_meter_exit(meter_dev_t * dev);

static int ph_meter_read(meter_dev_t * dev,
		unsigned int samples, meter_data_t * result)
{
	int error, i;
	int count = 0;

	if((samples > MAX_SAMPLES) || (!samples))
		return -EINVAL;

	/* Take the power lock, the device lock and turn the device on */
	mutex_lock(&module_power_lock);
	mutex_lock(&(dev->lock));

	SET_GPIO_PIN(PH_POWER_PIN);

	for(i = 0; i < samples; i++)
	{
		int temp;
		/* the MCP3301 returns a 13-bit signed result.  
		 * Keep a running average
		 */
		error = mcp3301_read(&chip_phy, &temp);
		if(error)
			goto powerdown;
		count += temp;
	}

	count /= samples;
	
	result->sig_bits = RESULT_BITS;
	result->payload = count;
	result->is_signed = true;	

powerdown:	
	CLEAR_GPIO_PIN(PH_POWER_PIN);
exit:
	mutex_unlock(&(dev->lock));
	mutex_unlock(&module_power_lock);
	return error;
}

static int ph_meter_init(meter_dev_t * dev)
{
	return mcp3301_init(&chip_phy);
}

static void ph_meter_exit(meter_dev_t * dev)
{
	
}

static meter_interface_t interface =
{
	.read = ph_meter_read,
	.init = ph_meter_init,
	.exit = ph_meter_exit,
};

meter_dev_t ph_meter_dev = 
{
	.name = "pH",
	.phy_interface = &interface,
};
