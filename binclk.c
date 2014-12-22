#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "mraa.h"

#define NUM_OUT 11

// My board seems to have a weird bug where using pin 7 causes the wireless to fuck up
static const uint8_t pin_map[] = {11, 10, 9, 8, 6, 5, 4, 3, 2, 1, 0, 12};

mraa_gpio_context gpio[NUM_OUT + 1];

void pr_bin(uint16_t bitmask, uint8_t num_bits)
{
	for(int i = num_bits; i--;)
	{
		if(bitmask & (1 << i)) mraa_gpio_write(gpio[i], 1);
		else mraa_gpio_write(gpio[i], 0);
	}
}

int main()
{
	mraa_init();

	for(int i = 0; i < NUM_OUT + 1; i++)
	{
		gpio[i] = mraa_gpio_init(pin_map[i]);
		mraa_gpio_dir(gpio[i], MRAA_GPIO_OUT);
	}

	int sec_pin = 0;
	while(1)
	{
		time_t raw_time; time(&raw_time);
		struct tm* ltime = localtime(&raw_time);

		pr_bin((ltime->tm_hour << 6) | (ltime->tm_min), NUM_OUT);
		mraa_gpio_write(gpio[NUM_OUT], sec_pin = !sec_pin);
		sleep(1);
	}

	return 0;
}
