#include "../adventofcode.h"
#define ROWS 16
#define COLS 16

static void printArr(int** arr);
static int** parseLines(char* str, int len);
static int getCheckSum(int** arr);
static int getQuotient(int** arr);

void day02(input_t input)
{
	printf("  DAY 02\n");

	int** arr = parseLines(input.str, input.len);
	// printArr(arr);

	int sum = getCheckSum(arr);
	printf("    Part 1: %d\n", sum);

	int quotient = getQuotient(arr);
	printf("    Part 2: %d\n", quotient);

	// Free Allocated Memory
	for (int i = 0; i < ROWS; i++)
	{
		arr[i] = NULL;
		free(arr[i]);
	}
	arr = NULL;
	free(arr);
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all rows and columns of a two dimensional int arr
 *
 *   int** arr: 2D array of numbers (interpretted from the input file)
 *
 *   Returns: void
 */
static void printArr(int** arr)
{
	for (int i = 0; arr[i] != NULL; i++)
	{
		printf("    ");
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] != -1)
			{
				printf("%d ", arr[i][j]);
			}
		}
		printf("\n");
	}
}

/*
 * Function: parseLines
 * --------------------------
 *   Converts an input string of numbers into a 2D int array
 *
 *   char* str: string to interpret
 *   int len: length of the str
 *
 *   Returns: 2D int array containing all numbers from the input file
 */
static int** parseLines(char* str, int len)
{
	int r = 0;
	int c = 0;
	int number = 0;

	int** numArr = (int **)malloc((ROWS+1) * sizeof(int *));
	numArr[0] = (int *)malloc((COLS+1) * sizeof(int));
	for (int i = 0; i < len; i++)
	{ 
		if (str[i] >= '0')
		{
			number = (number * 10) + str[i] - '0';
		}
		else
		{
			if (str[i] != '\n')
			{
				numArr[r][c] = number;
				c++;
			}
			else
			{
				numArr[r][c] = number;

				// if there are less numbers in a row than COLS defines
				// populate the rest of the row with -1's to show no input
				// (just in case 0's are in the input file)
				c++;
				if (c < COLS)
				{
					for (int j = c; j <= COLS; j++)
					{
						numArr[r][j] = -1;
					}
				}
				c = 0;

				// if the input has less rows than ROWS defines
				// prevent an extra row from being allocated
				if (i < len - 1){
					r++;
					numArr[r] = (int *)malloc((COLS+1) * sizeof(int));
				}
			}
			number = 0;
		}
	}

	return numArr;
}

/*
 * Function: getCheckSum
 * --------------------------
 *   Iterates over every row of the array to determine the largest difference of numbers
 *   and sums all of the row's differences together
 *
 *   int** arr: 2D array of numbers (interpretted from the input file)
 *
 *   Returns: sum of each line's maximum difference
 */
static int getCheckSum(int** arr)
{
	int sum = 0;
	int num = -1;
	int smallest = -1;
	int largest = 0;

	for (int i = 0; arr[i] != NULL; i++)
	{
		smallest = -1;
		largest = 0;
		for (int j = 0; j < COLS; j++)
		{
			num = arr[i][j];
			if (num != -1)
			{
				if (smallest < 0 || num < smallest)
				{
					smallest = num;
				}
				if (num > largest)
				{
					largest = num;
				}
			}
		}
		if (smallest != -1)
		{
			sum += (largest - smallest);
		}
	}

	return sum;
}

/*
 * Function: getCheckSum
 * --------------------------
 *   Iterates over every row of the array to determine the only whole numbered quotient
 *   and sums all of the row's quotients together
 *
 *   int** arr: 2D array of numbers (interpretted from the input file)
 *
 *   Returns: sum of each line's whole number quotient
 */
static int getQuotient(int** arr)
{
	int sum = 0;
	int numJ = -1;
	int numK = -1;
	int quotient = 0;

	for (int i = 0; arr[i] != NULL; i++)
	{
		quotient = 0;
		for (int j = 0; j < COLS; j++)
		{
			numJ = arr[i][j];
			if (numJ != -1)
			{
				for (int k = 0; k < COLS; k++)
				{
					numK = arr[i][k];
					if (numK != -1 && k != j)
					{
						if (numJ % numK == 0)
						{
							quotient = numJ / numK;
						}
						else if (numK % numJ == 0)
						{
							quotient = numK / numJ;
						}
					}
				}
			}
		}
		sum += quotient;
	}

	return sum;
}