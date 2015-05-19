#include <stdint.h>
#include <stdio.h>

#define OFF_RONE(x)        (x & (x - 1))        // turns off the rightmost 1 bit in a word
#define ON_RZERO(x)        (x | (x + 1))        // turns on the rightmost 0 bit in a word
#define OFF_TONES(x)       (x & (x + 1))        // turn off all trailing ones
#define ONLY_RZERO(x)      (~x & (x + 1))       // set only the the rightmost 0 of x to 1, everything else to 0
#define NOT_RONE(x)        (~x | (x - 1))       // turn off the rightmost 1 of x and turn everything else on
#define ONLY_TZEROS(x)     (~x & (x - 1))       // turn on x's trailing 0's and turn everything else off
#define NOT_TONES(x)       (~x | (x + 1))       // turn off x's trailing 1's and turn everything else on 
#define ISOLATE_RONE(x)    (x & (-x))           // turn off everything except for x's rightmost 1
#define RONE_SIDE(x)       (x ^ (x - 1))        // turn on everything after the rightmost 1, turns everything else off
#define RZERO_SIDE(x)      (x ^ (x + 1))        // turn on everything after the rightmost 0, turns everything else off
#define RIGHT_BLOCK_OFF(x) (((x & -x) + x) & x) // turn off the rightmost string of 1's

#define COMPLEMENT_INC(x)  (-~x)				 // x<-x+1; can be repeated to increment as much as you want
#define COMPLEMENT_DEC(x)  (~-x)				 // x<-x-1
#define SUM(x,y)           ((x | y) + (x & y))   // add x and y 
#define SUB(x,y)           ((x & ~y) - (~x & y)) // subtract y from x

/* Print the bits in an uint32_t */
void print_bits(uint32_t x)
{
	uint32_t b = 0x80000000;
	while (b != 0){
		fprintf(stdout, "%d", (b & x) ? 1 : 0);
		x ^= b; // turn off b-th bit
		b >>= 1;
	}
	fprintf(stdout,"\n");
}
 
int main(void)
{

	/** Test each of the macros up to, but not including, complement inc **/
	fprintf(stdout, "\nTesting OFF_RONE...RIGHT_BLOCK_OFF\n");
	uint32_t x = 1234;
	uint32_t x2;
 
 	fprintf(stdout, "Value of x:\n");
	print_bits(x);

	// turn off rightmost bit in a word
	fprintf(stdout, "OFF_RONE\n");
	x2 = OFF_RONE(x);
	print_bits(x2);
 
	// turn on rightmost 0 bit
	fprintf(stdout, "ON_RZERO\n");
	x2 = ON_RZERO(x);
	print_bits(x2);
 

 	fprintf(stdout, "OFF_TONES\n");
	x = 7;
	print_bits(x);
	// can check if uint is 2^n - 1, 0, or all 1's
	x2 = OFF_TONES(x);
	print_bits(x2);

	fprintf(stdout, "ONLY_RZERO\n");
	x = 1234;
	fprintf(stdout, "Value of x:\n");
	print_bits(x);
	fprintf(stdout, "Value of x2:\n");
	// x2 has a 1 at the rightmost 0 bit of x, 0's everywhere else
	x2 = ONLY_RZERO(x);
	print_bits(x2);

	fprintf(stdout, "NOT_RONE\n");
	// x2 has a 0 at the rightmost 1 bit of x, 1's everywhere else
	x2 = NOT_RONE(x);
	print_bits(x2);

	fprintf(stdout, "ONLY_TZEROS\n");
	// x2 has 1's at x's trailing zeros, 0 elsewhere
	x2 = ONLY_TZEROS(x);
	print_bits(x2);

	fprintf(stdout, "NOT_TONES\n");
	// x2 is a word with 0's wherever x has a trailing 1, 1's everywhere else
	x2 = NOT_TONES(x);
	print_bits(x2);

	fprintf(stdout, "ISOLATE_RONE\n");
	// x2's only 1 bit is the rightmost 1 bit of x
	x2 = ISOLATE_RONE(x);
	print_bits(x2);

	fprintf(stdout, "RONE_SIDE\n");
	// x2 has 1's at the rightmost 1 bit of x and the trailing 0's of x
	x2 = RONE_SIDE(x);
	print_bits(x2);

	fprintf(stdout, "RIGHT_BLOCK_FF\n");
	x2 = RIGHT_BLOCK_OFF(x);
	print_bits(x2);

	/* Test the complement increment. */
	fprintf(stdout, "\nTesting COMPLEMENT_INC\n");
	x = 0;
	while (x < 10) {
		printf("%d\n", x);
		x = COMPLEMENT_INC(x);
	}

	/* Test the complement decrement. */
	fprintf(stdout, "\nTesting COMPLEMENT_DEC\n");
	x = 10;
	while (x > 0) {
		printf("%d\n", x);
		x = COMPLEMENT_DEC(x);
	}

	fprintf(stdout, "\nTesting SUM\n");
	x = 1;
	uint32_t y = 2;
	fprintf(stdout, "%d\n", SUM(x,y));

	fprintf(stdout, "\nTesting SUB\n");
	x = 1;
	y = 2;
	fprintf(stdout, "%d\n", SUB(x,y));

	return 0;
}
