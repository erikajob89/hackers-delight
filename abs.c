#include <stdint.h>
#include <stdio.h>
 
int main (void)
{
	int32_t x = -20;
	int32_t y = x >> 31;
	int32_t abs_x;
	
	abs_x = x ^ y - y; // this one emits the fewest instructions
	fprintf(stdout, "Absolute value of x by method 1: %d\n", abs_x);
	
	abs_x = (x + y) ^ y;
	fprintf(stdout, "Absolute value of x by method 2: %d\n", abs_x);
	
	abs_x = x - (x * 2 & y); // this should be a shift but idk scope
	fprintf(stdout, "Absolute value of x by method 3: %d\n", abs_x);
	
	return 0;
}