#include "../adventofcode.h"
#define MAXBLOCKS 20
#define ROWS 15000

typedef struct {
    int* arr;
    int len;
} instr_t;

typedef struct {
    int cycleCount;
    int loopSize;
} cycle_t;

typedef struct {
    int pos;
    bool same;
} loop_t;

static void printArr(int** arr, int rows, int cols);
static instr_t parseLines(char* str, int len);
static cycle_t calcCycles(int* arr, int len);
static int* redistribute(int* arr, int len);
static int findMax(int* arr, int len);
static loop_t compareArrays(int** combos, int* arr, int rows, int cols);

void day06(input_t input)
{
	printf("  DAY 06\n");

	instr_t instructions = parseLines(input.str, input.len);
	// printArr(instructions.arr, instructions.len);

	cycle_t cycles = calcCycles(instructions.arr, instructions.len);
	printf("    Part 1: %d\n", cycles.cycleCount);

	printf("    Part 2: %d\n", cycles.loopSize);

	// Free Allocated Memory
	free(instructions.arr);
	instructions.arr = NULL;
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all rows and columns of a two dimensional string arr
 *
 *   int*** arr: 2D array of strings or 3D array of chars (interpreted from the input file)
 *
 *   Returns: void
 */
static void printArr(int** arr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		printf("    ");
		for (int j = 0; j < cols; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
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
	int* numArr = (int *)malloc(MAXBLOCKS * sizeof(int));
	int number = 0;
	int length = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0')
		{
			number = (number * 10) + str[i] - '0';
		}
		else
		{
			numArr[length] = number;

			number = 0;
			length++;
		}
	}

	instructions.arr = numArr;
	instructions.len = length;

	return instructions;
}

/*
 * Function: calcCycles
 * --------------------------
 *   Calculates how many times redistribution occurs until a repeat sequene is created
 *
 *   int* arr: array of numbers (interpreted from the input file)
 *   int len: length of the array
 *
 *   Returns: Cycles struct containing cycle count until a loop occurs,
 *   and the size of the loop that occurs
 */
static cycle_t calcCycles(int* arr, int len)
{
	cycle_t retvals;
	loop_t loopChunk;
	loopChunk.same = FALSE;
	int cycles = 0;
	int* temp = arr;

	// create 2D array to contain all found sequences
	int** combos = (int **)malloc(ROWS * sizeof(int *));

    // while a repetitive sequence hasn't been created, keep redistributing
    while (!loopChunk.same)
    {
    	combos[cycles] = temp;
    	cycles++;
    	temp = redistribute(temp, len);
    	loopChunk = compareArrays(combos, temp, cycles, len);
    }

    // Free Allocated Memory
    free(temp);
    temp = NULL;
    free(combos);
    combos = NULL;

    // Set the return value struct
    retvals.cycleCount = cycles;
    retvals.loopSize = cycles - loopChunk.pos;

	return retvals;
}


/*
 * Function: redistribute
 * --------------------------
 *   Finds the highest value in the input array, sets it to zero, and
 *   distributes it's original value across all other elements (adds one to each element)
 *
 *   int* arr: array of numbers
 *   int len: length of the array
 *
 *   Returns: array of integers
 */
static int* redistribute(int* arr, int len)
{
	int* temp = (int *)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
	{
		temp[i] = arr[i];
	}

	int maxPos = findMax(temp, len);
    int blocks = temp[maxPos];
    temp[maxPos] = 0;
    for (int i = maxPos + 1; blocks > 0; i++, blocks--)
    {
    	if (i >= len)
    	{
    		i = 0;
    	}
    	temp[i]++;
    }

    return temp;
}

/*
 * Function: findMax
 * --------------------------
 *   Determines the position of the maximum value in a sequence of numbers
 *
 *   int* arr: array of numbers
 *   int len: length of the array
 *
 *   Returns: position of maximum int in the array
 */
static int findMax(int* arr, int len)
{
	int max = 0;
	int maxPos = 0;

	for (int i = 0; i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			maxPos = i;
		}
	}

	return maxPos;
}

/*
 * Function: compareArrays
 * --------------------------
 *   Determines if this new sequence of numbers has already occured before
 *
 *   int** combos: 2D int array of all sequences created so far
 *   int* arr: array of numbers to look for
 *   int rows: number of sequences in  the 2D array
 *   int cols: length of the sequence
 *
 *   Returns: Cycles struct containing cycle count until a loop occurs,
 *   and the size of the loop that occurs
 */
static loop_t compareArrays(int** combos, int* arr, int rows, int cols)
{
	loop_t loopChunk;
	loopChunk.pos = -1;

	bool same = TRUE;
	for (int i = 0; i < rows; i++)
	{
		same = TRUE;
		for (int j = 0; j < cols; j++)
		{
			if (combos[i][j] != arr[j])
			{
				same = FALSE;
				break;
			}
		}
		if (same)
		{
			loopChunk.pos = i;
			loopChunk.same = same;
			break;
		}
	}

	return loopChunk;
}