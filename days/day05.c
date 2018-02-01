#include "../adventofcode.h"
#define MAXINSTR 1100

typedef struct {
    int* arr;
    int len;
} instr_t;

static void printArr(int* arr, int len);
static instr_t parseLines(char* str, int len);
static int getSteps(int* arr, int len, int part);
static int getSteps2(int* arr, int len);

void day05(input_t input)
{
	printf("  DAY 05\n");

	instr_t instructions = parseLines(input.str, input.len);
	// printArr(instructions.arr, instructions.len);

	int stepsP1 = getSteps(instructions.arr, instructions.len, 1);
	printf("    Part 1: %d\n", stepsP1);

	int stepsP2 = getSteps(instructions.arr, instructions.len, 2);
	printf("    Part 2: %d\n", stepsP2);

	// Free Allocated Memory
	free(instructions.arr);
	instructions.arr = NULL;
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all elements an int arr
 *
 *   int* arr: array of numbers (interpreted from the input file)
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
 *   int* arr: array of numbers (interpreted from the input file)
 *   int len: length of the array
 *   int part: 1 or 2 to determine which jump algorithm to use
 *
 *   Returns: number of steps it will take to exit the instruction list
 */
static int getSteps(int* arr, int len, int part)
{
	int steps = 0;
	int instr = 0;
	
	int temp[len];
	for (int i = 0; i < len; i++)
	{
		temp[i] = arr[i];
	}

	// Part 1
	if (part == 1)
	{
		for (int i = 0; i < len; steps++)
		{
			instr = temp[i];
	
			temp[i]++;
	
			i += instr;
		}
	}
	// Part 2
	else if (part == 2)
	{
		for (int i = 0; i < len; steps++)
		{
			instr = temp[i];

			if (instr >= 3) {
				temp[i]--;
			}
			else {
				temp[i]++;
			}

			i += instr;
		}
	}

	return steps;
}