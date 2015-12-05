#ifndef __GPIO_H__
#define __GPIO_H__

#include <linux/types.h>

typedef u8 gpio_t;

#define NUM_GPIO 41

_Static_assert(sizeof(gpio_t)*256 > NUM_GPIO, "GPIO_TYPE too small!");

typedef enum gpio_function_X
{
        GPIO_INPUT = 0,
        GPIO_OUTPUT = 1,
        GPIO_ALT_FUNC_0 = 4,
        GPIO_ALT_FUNC_1 = 5,
        GPIO_ALT_FUNC_2 = 6,
        GPIO_ALT_FUNC_3 = 7,
        GPIO_ALT_FUNC_4 = 3,
        GPIO_ALT_FUNC_5 = 2,
}gpio_function_t;

int clear_gpio_pin(gpio_t gpio_num);
int set_gpio_pin(gpio_t gpio_num);
int get_gpio_pin(gpio_t gpio_num, bool * value);
int set_gpio_function(gpio_t gpio_num, gpio_function_t func);



#endif
