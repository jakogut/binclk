#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define NUM_OUT 11

void pr_bin(uint16_t bitmask, uint8_t num_bits)
{
	int i;
	for(i = num_bits; i--;) if(bitmask & (1 << i)) printf("1"); else printf("0");
	printf("\n");
}

int main()
{
	while(1)
	{
		time_t raw_time; time(&raw_time);
		struct tm* ltime = localtime(&raw_time);

		pr_bin((ltime->tm_hour << 6) | (ltime->tm_min), NUM_OUT);
		sleep(60);
	}

	return 0;
}
