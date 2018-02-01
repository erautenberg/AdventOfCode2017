#include "../adventofcode.h"
#define ROWS 20
#define COLS 20

static void printArr(arrInt_t arr);
static arrInt_t parseLines(char* str, int len);
static int getCheckSum(arrInt_t);
static int getQuotient(arrInt_t);

void day02(input_t input)
{
	printf("  DAY 02\n");

	arrInt_t arr = parseLines(input.str, input.len);
	// printArr(arr);

	int sum = getCheckSum(arr);
	printf("    Part 1: %d\n", sum);

	int quotient = getQuotient(arr);
	printf("    Part 2: %d\n", quotient);

	// Free Allocated Memory
	for (int i = 0; i < arr.rowCount; i++)
    {
    	free(arr.rows[i].nums);
    	arr.rows[i].nums = NULL;
    }
    free(arr.rows);
    arr.rows = NULL;
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all rows and columns of a two dimensional int arr
 *
 *   int** arr: 2D array of numbers (interpreted from the input file)
 *
 *   Returns: void
 */
static void printArr(arrInt_t arr)
{
	for (int i = 0; i < arr.rowCount; i++)
	{
		printf("    ");
		for (int j = 0; j < arr.rows[i].numCount; j++)
		{
			printf("%d ", arr.rows[i].nums[j]);
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
static arrInt_t parseLines(char* str, int len)
{
	arrInt_t numArr;
	numArr.rows = (rowInt_t *)malloc(ROWS * sizeof(rowInt_t));
	numArr.rowCount = 0;

	rowInt_t row;
	row.numCount = 0;
	row.nums = (int*)malloc(COLS * sizeof(int));

	int r = 0;
	int c = 0;
	int number = 0;
	
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
				row.nums[c] = number;
				row.numCount++;
				c++;
			}
			else
			{
				row.nums[c] = number;
				row.numCount++;

				numArr.rows[r] = row;

				r++;
				c = 0;

				row.nums = (int*)malloc(COLS * sizeof(int));
				row.numCount = 0;
			}
			number = 0;
		}
	}
	numArr.rowCount = r;

	return numArr;
}

/*
 * Function: getCheckSum
 * --------------------------
 *   Iterates over every row of the array to determine the largest difference of numbers
 *   and sums all of the row's differences together
 *
 *   int** arr: 2D array of numbers (interpreted from the input file)
 *
 *   Returns: sum of each line's maximum difference
 */
static int getCheckSum(arrInt_t arr)
{
	int sum = 0;
	int num = -1;
	int smallest = -1;
	int largest = 0;

	for (int i = 0; i < arr.rowCount; i++)
	{
		smallest = -1;
		largest = 0;
		for (int j = 0; j < arr.rows[i].numCount; j++)
		{
			num = arr.rows[i].nums[j];
			if (smallest < 0 || num < smallest)
			{
				smallest = num;
			}
			if (num > largest)
			{
				largest = num;
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
 *   int** arr: 2D array of numbers (interpreted from the input file)
 *
 *   Returns: sum of each line's whole number quotient
 */
static int getQuotient(arrInt_t arr)
{
	int sum = 0;
	int numJ = -1;
	int numK = -1;
	int quotient = 0;

	for (int i = 0; i < arr.rowCount; i++)
	{
		quotient = 0;
		for (int j = 0; j < arr.rows[i].numCount; j++)
		{
			numJ = arr.rows[i].nums[j];
			for (int k = 0; k < arr.rows[i].numCount; k++)
			{
				numK = arr.rows[i].nums[k];
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
		sum += quotient;
	}

	return sum;
}