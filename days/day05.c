#include "../adventofcode.h"
#define MAXINSTR 1100

typedef struct {
    int* arr;
    int len;
} instr_t;

static void printArr(int* arr, int len);
static instr_t parseLines(char* str, int len);
static int getSteps(int* arr, int len);
static int getSteps2(int* arr, int len);

void day05(input_t input)
{
	printf("  DAY 05\n");

	instr_t instructions1 = parseLines(input.str, input.len);
	instr_t instructions2 = parseLines(input.str, input.len);
	// printArr(instructions1.arr, instructions1.len);
	// printArr(instructions2.arr, instructions2.len);

	int steps = getSteps(instructions1.arr, instructions1.len);
	printf("    Part 1: %d\n", steps);

	int steps2 = getSteps2(instructions2.arr, instructions2.len);
	printf("    Part 2: %d\n", steps2);

	// Free Allocated Memory
	free(instructions1.arr);
	instructions1.arr = NULL;
	free(instructions2.arr);
	instructions2.arr = NULL;
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all elements an int arr
 *
 *   int* arr: array of numbers (interpretted from the input file)
 *   int len: length of the array
 *
 *   Returns: void
 */
static void printArr(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
}

/*
 * Function: parseLines
 * --------------------------
 *   Converts an input string of numbers into an int array
 *
 *   char* str: string to interpret
 *   int len: length of the str
 *
 *   Returns: Instructions struct containing int array of all numbers
 *   from the input file and length of the array
 */
static instr_t parseLines(char* str, int len)
{
	instr_t instructions;
	int* numArr = (int *)malloc(MAXINSTR * sizeof(int));
	bool negative = FALSE;
	int number = 0;
	int length = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '-')
		{
			negative = TRUE;
		}
		else if (str[i] >= '0')
		{
			number = (number * 10) + str[i] - '0';
		}
		else if (str[i] == '\n')
		{
			if (negative) {
				number *= -1;
			}
			numArr[length] = number;

			negative = FALSE;
			number = 0;
			length++;
		}
	}

	instructions.arr = numArr;
	instructions.len = length;

	return instructions;
}

/*
 * Function: getSteps
 * --------------------------
 *   Calculates the number of steps it will take to exit the instruction array
 *   (which denotes the number of positions to jump forward or backward)
 *
 *   int* arr: array of numbers (interpretted from the input file)
 *   int len: length of the array
 *
 *   Returns: number of steps it will take to exit the instruction list
 */
static int getSteps(int* arr, int len)
{
	int steps = 0;
	int instr = 0;

	for (int i = 0; i < len; steps++)
	{
		instr = arr[i];

		arr[i]++;

		i += instr;
	}

	return steps;
}

/*
 * Function: getSteps2
 * --------------------------
 *   Calculates the number of steps it will take to exit the instruction array
 *   (which denotes the number of positions to jump forward or backward)
 *
 *   int* arr: array of numbers (interpretted from the input file)
 *   int len: length of the array
 *
 *   Returns: number of steps it will take to exit the instruction list
 */
static int getSteps2(int* arr, int len)
{
	int steps = 0;
	int instr = 0;

	for (int i = 0; i < len; steps++)
	{
		instr = arr[i];

		if (instr >= 3) {
			arr[i]--;
		}
		else {
			arr[i]++;
		}

		i += instr;
	}

	return steps;
}