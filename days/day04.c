#include "../adventofcode.h"
#define ROWS 512
#define COLS 20
#define LETTERS 10

static char*** parseLines(char* str, int len);
static void printArr(char*** arr);
static int getValidSum(char*** arr, bool anagramSort);
static bool isValid(char* p1, char* p2, bool anagramSort);
static char* alphaStr(char* str);

void day04(input_t input)
{
	printf("  DAY 04\n");

	char*** arr = parseLines(input.str, input.len);
	// printArr(arr);

	int sum = getValidSum(arr, FALSE);
	printf("    Part 1: %d\n", sum);

	int anagramSum = getValidSum(arr, TRUE);
	printf("    Part 2: %d\n", anagramSum);

	// Free Allocated Memory
    for (int i = 0; i < ROWS; i++)
    {
    	for (int j = 0; j < COLS; j++)
    	{
    		if (arr[i][j] != NULL) {
    			arr[i][j] = NULL;
    			free(arr[i][j]);
    		}
    	}
        free(arr[i]);
    }
    arr = NULL;
    free(arr);
}

/*
 * Function: printArr
 * --------------------------
 *   Prints out all rows and columns of a two dimensional string arr
 *
 *   int*** arr: 2D array of strings or 3D array of chars (interpretted from the input file)
 *
 *   Returns: void
 */
static void printArr(char*** arr)
{
	for (int i = 0; arr[i] != NULL; i++)
	{
		printf("    ");
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] != NULL)
			{
				printf("%s ", arr[i][j]);
			}
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
 *   Returns: 2D string array containing all words from the input file
 */
static char*** parseLines(char* str, int len)
{
	char*** strArr = (char ***)malloc((ROWS+1) * sizeof(char **));
	strArr[0] = (char **)malloc((COLS+1) * sizeof(char*));
	strArr[0][0] = (char *)malloc((LETTERS+1) * sizeof(char));

	int r = 0;
	int c = 0;
	int l = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != '\n')
		{
			if (str[i] != ' ')
			{
				strArr[r][c][l] = str[i];
				l++;
			}
			else
			{
				strArr[r][c][l] = '\0';
				l = 0;
				c++;
				strArr[r][c] = (char *)malloc((LETTERS+1) * sizeof(char));
			}
		}
		else
		{
			strArr[r][c][l] = '\0';
			l = 0;
			c = 0;
			r++;
			strArr[r] = (char **)malloc((COLS+1) * sizeof(char*));
			strArr[r][c] = (char *)malloc((LETTERS+1) * sizeof(char));
		}
	}

	return strArr;
}

/*
 * Function: getValidSum
 * --------------------------
 *   Sums all valid phrases
 *
 *   int*** arr: 3D array of numbers (interpretted from the input file)
 *   bool anagramSort: if true, passphrases are only valid if the words
 *     aren't anagrams of each other
 *
 *   Returns: sum of all phrases that are valid
 */
static int getValidSum(char*** arr, bool anagramSort)
{
	int sum = 0;

	char* passphrase1 = (char *)malloc((LETTERS+1) * sizeof(char));
	char* passphrase2 = (char *)malloc((LETTERS+1) * sizeof(char));

	for (int i = 0; arr[i] != NULL; i++)
	{
		bool cont = FALSE;
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] != NULL && j + 1 < COLS)
			{
				for (int k = j + 1; k < COLS; k++)
				{
					cont = TRUE;
					passphrase1 = arr[i][j];
					passphrase2 = arr[i][k];
					
					if (passphrase1 != NULL && passphrase2 != NULL)
					{
						if (!isValid(passphrase1, passphrase2, anagramSort))
						{
							cont = FALSE;
							break;
						}
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