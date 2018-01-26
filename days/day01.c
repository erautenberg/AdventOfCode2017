#include "../adventofcode.h"

// static int addString(char* str, int len);
static int addString(char* str, int len, int steps);


void day01(input_t input)
{
	printf("  DAY 01\n");

	int sum = addString(input.str, input.len, 1);
	printf("    Part 1: %d\n", sum);

	int sum2 = addString(input.str, input.len, ceil(input.len/2));
	printf("    Part 2: %d\n", sum2);
}

/*
 * Function: addString
 * --------------------------
 *   Returns the sum of repetitive consecutive numbers in a circular string
 *
 *   char* str: string to sum
 *   int len: length of the str
 *   int steps: number of steps ahead to look for the digit to compare
 *
 *   Returns: sum
 */
static int addString(char* str, int len, int steps)
{
	int sum = 0;

	// for each digit, check if the digit a defined number of steps ahead is the same, and if yes, add to the total
	for (int i = 0; str[i] != 0; i++)
	{
		int nextDigit = i + steps;

		// if the digit to look ahead to is greater than the length of the string,
		// loop back to the beginning (circular list)
		if (nextDigit > (len - 1))
		{
			nextDigit = nextDigit - len;
		}

		// if (i > 0) {
		if (str[i] == str[nextDigit]) {
			sum += (str[i] - '0');
			// }
		}
	}

	return sum;
}


