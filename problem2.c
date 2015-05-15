#include <stdint.h>
#include <stdio.h>

int main(void)
{
	uint32_t i;

	// Problem: A loop that goes from 0 ... 0xFFFFFFFF
	for (i = 0x00000000; i <= 0xFFFFFFFF; i++){
		fprintf(stdout, "%x\n", i);
	}

	return 0;
}