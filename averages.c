#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
 
int main(void)
{
	uint32_t x = 5;
	uint32_t y = 10;
	
	/* Compute averages of two unsigned integers without overflow
	   These can be done the same way for signed integers. */
	
	// floor average: floor((x + y) / 2)
	uint32_t avg = (x & y) + ((x ^ y) >> 1);
	printf("Floor average of 5 and 10: %"PRIu32"\n", avg );
	
	// ceiling average: ceil((x + y) / 2)
	avg = (x | y) - ((x ^ y) >> 1);
	printf("Ceiling average of 5 and 10: %"PRIu32"\n", avg );
	
	
	/* Average on two signed ints with division by 2 rounded toward
	   zero. (truncated average) No overflow. */
	   
	int32_t a = 5;
	int32_t b = -10;
	
	// first get the floor average
	int32_t tavg = (a & b) + ((a ^ b) >> 1);
	
	// correct by adding 1 iff a + b is negative AND odd
	// a + b negative => prev value of t was negative
	// odd => a ^ b has a 1 in the 0th bit
	tavg += ((uint32_t) tavg >> 31) & (a ^ b);
	printf("Truncated average of 5 and -10: %d\n", tavg );
	
	/* Suppose we know a and be are non-negative. Then we can do even better. */
	a = 5;
	b = 10;
	tavg = (uint32_t)(a + b) >> 1; // shift unsigned to move overflow to the correct position
	printf("Truncated average of 5 and 10: %d\n", tavg );
	
	/* If a <= b (signed or unsigned) then we can get the floor average like this:*/
	int32_t favg = x + ((uint32_t)(y - x) >> 1);
	printf("Floor average of 5 and 10: %d\n", favg );
	
	return 0;
}