#include "../adventofcode.h"

static int addString(char* str);


void day01(input_t input)
{
	printf("  DAY 01\n");

	int sum = addString(input.str);
	printf("    Part 1: %d\n", sum);
}

static int addString(char* str)
{
	int sum = 0;
	int length = 0;
	for (int i = 0; str[i] != 0; i++, length++)
	{
		if (i > 0) {
			if (str[i] == str[i-1]) {
				sum += (str[i] - '0');
			}
		}
	}

	if (str[length - 1] == str[0])
	{
		sum += (str[0] - '0');
	}

	return sum;
}


