#include "../adventofcode.h"
#define ROWS 550
#define WORDS 20
#define LETTERS 10

static void printArr(arr_t arr);
static arr_t parseLines(char* str, int len);
static int getValidSum(arr_t arr, bool anagramSort);
static bool isValid(char* p1, char* p2, bool anagramSort);
static char* alphaStr(char* str);

void day04(input_t input)
{
	printf("  DAY 04\n");

	arr_t arr = parseLines(input.str, input.len);
	// printArr(arr);

	int sum = getValidSum(arr, FALSE);
	printf("    Part 1: %d\n", sum);

	int anagramSum = getValidSum(arr, TRUE);
	printf("    Part 2: %d\n", anagramSum);

	// Free Allocated Memory
    for (int i = 0; i < arr.rowCount; i++)
    {
    	for (int j = 0; j < arr.rows[i].wordCount; j++)
    	{
    		free(arr.rows[i].words[j]);
    		arr.rows[i].words[j] = NULL;
    	}
    }
    free(arr.rows);
    arr.rows = NULL;
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all rows of the array input struct
 *
 *   arr_t arr: struct containing array of words (interpreted from the input file)
 *
 *   Returns: void
 */
static void printArr(arr_t arr)
{
	for (int i = 0; i < arr.rowCount; i++)
	{
		printf("    ");
		for (int j = 0; j < arr.rows[i].wordCount; j++)
		{
			printf("%s ", arr.rows[i].words[j]);
		}
		printf("\n");
	}
}

/*
 * Function: parseLines
 * --------------------------
 *   Converts an input string of phrases into 2D string array
 *
 *   char* str: string to interpret
 *   int len: length of the str
 *
 *   Returns: array struct containing all words from the input file
 */
static arr_t parseLines(char* str, int len)
{
	arr_t strArr;
	strArr.rows = (row_t *)malloc(ROWS * sizeof(row_t));
	strArr.rowCount = 0;

	row_t row;
	row.wordCount = 0;
	row.words = (char**)malloc(WORDS * sizeof(char*));
	row.words[0] = (char*)malloc(LETTERS * sizeof(char));

	int r = 0;		// row
	int w = 0;		// word
	int l = 0;		// letter
	for (int i = 0; i < len; i++)
	{
		if (str[i] != '\n')
		{
			if (str[i] != ' ')
			{
				row.words[w][l] = str[i];
				l++;
			}
			else
			{
				row.words[w][l] = '\0';
				l = 0;
				w++;
				row.wordCount++;
				row.words[w] = (char*)malloc(LETTERS * sizeof(char));
			}
		}
		else
		{
			row.wordCount++;
			strArr.rows[r] = row;

			r++;
			l = 0;
			w = 0;

			row.words = (char**)malloc(WORDS * sizeof(char*));
			row.words[0] = (char*)malloc(LETTERS * sizeof(char));

			row.wordCount = 0;
		}
	}
	strArr.rowCount = r;

	return strArr;
}

/*
 * Function: getValidSum
 * --------------------------
 *   Sums all valid phrases
 *
 *   arr_t arr: struct containing array of words (interpreted from the input file)
 *   bool anagramSort: if true, passphrases are only valid if the words
 *     aren't anagrams of each other
 *
 *   Returns: sum of all phrases that are valid
 */
static int getValidSum(arr_t arr, bool anagramSort)
{
	int sum = 0;

	char* passphrase1;
	char* passphrase2;

	for (int i = 0; i < arr.rowCount; i++)
	{
		bool cont = FALSE;
		for (int j = 0; j < arr.rows[i].wordCount; j++)
		{
			if (j + 1 < arr.rows[i].wordCount)
			{
				for (int k = j + 1; k < arr.rows[i].wordCount; k++)
				{
					cont = TRUE;
					passphrase1 = arr.rows[i].words[j];
					passphrase2 = arr.rows[i].words[k];

					if (!isValid(passphrase1, passphrase2, anagramSort))
					{
						cont = FALSE;
						break;
					}
				}
			}
			if (!cont) {
				break;
			}
		}
		if (cont) {
			sum++;
		}
	}

	return sum;
}

/*
 * Function: isValid
 * --------------------------
 *   Compares two strings and returns if they are "valid" (strings don't match)
 *     and if anagramSort is true, the two strings are both alphabatized first
 *
 *   char* str1: first string to compare
 *   char* str2: second string to compare
 *   bool anagramSort: if true, passphrases are only valid if the words
 *     aren't anagrams of each other
 *
 *   Returns: true if strings are "valid," false otherwise
 */
static bool isValid(char* str1, char* str2, bool anagramSort)
{
	if (anagramSort)
	{
		str1 = alphaStr(str1);
		str2 = alphaStr(str2);
	}

	while (*str1 == *str2)
	{
		if (*str1 == '\0' || *str2 == '\0')
		{
			break;
		}
		str1++;
		str2++;
    }

	if (*str1 == '\0' && *str2 == '\0')
	{
   		return FALSE;
	}
	else
	{
    	return TRUE;
	}
}

/*
 * Function: alphaStr
 * --------------------------
 *   Sorta a string alphabetically
 *
 *   char* str: string to sort
 *
 *   Returns: alphabetically sorted string (char *)
 */
static char* alphaStr(char* str)
{
	char temp;
	int n = my_strlen(str);

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (str[i] > str[j])
			{
				temp = str[i];
            	str[i] = str[j];
            	str[j] = temp;
         	}
      	}
   	}
   	return str;
}