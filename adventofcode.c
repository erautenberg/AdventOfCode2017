#include "adventofcode.h"

static input_t getInputString(char* filename);

/*
 * Function: main
 * --------------------------
 *   Loops through the array of advent days/inputs and passes the day's inputs to
 *   the day's corresponding function (which prints out the result of the puzzle)
 *
 *   int argc: number of arguments user entered (should be 0 or 1)
 *   char* argv[]: array of user entered arguments
       ('./advent' or './advent X', where X is a specific day)
 *
 *   Returns: 0 if no errors, -1 if erros
 */
int main(int argc, char *argv[])
{
	int retval = 0;
	char* usage;

	asprintf(&usage, "  USE:\n"
		    "    To calculate all days:\t./advent -A\n"
		    "    To calculate specific day:\t./advent X\n"
		    "\twhere X is the number of the day between %d and %d\n", STARTDAY, ENDDAY);

	printf("\nEmily's Advent of Code 2017\n...........................\n\n");

	// if "./advent"
	if (argc == 1)
	{
		printf("%s\n", usage);
	}
	// if "./advent X" where X is a number
	else if (argc == 2){
		const adventday_t *advents = adventdays;
		bool cont = TRUE;
		char* str = argv[1];

		// if "-a" or "-A" was entered, calculate all days
		if (str[0] == '-' && (str[1] == 'a' || str[1] == 'A') && str[2] == '\0')
		{
			for (const adventday_t *advents = adventdays; (*advents).dayFunction; advents++) {
				input_t input = getInputString((*advents).inputFile);
				(*advents).dayFunction(input);
				printf("\n");
			}
		}
		else {
			// make sure a number was entered
			for (int i = 0; str[i] != 0; i++)
			{
				if (my_isdigit(str[i]) == 0)
				{
					cont = FALSE;
					retval = -1;
				}
			}

			// if there were no errors, continue
			if (cont)
			{
				int day = my_atoi(str);
				// if the request day number is within the the day limites, call it's function
				if (day >= STARTDAY && day <= ENDDAY)
				{
					day -= 1;	// the array is 0 based, so subtract 1 from the requested day
					input_t input = getInputString(advents[day].inputFile);
					advents[day].dayFunction(input);
					printf("\n");
				}
				else
				{
					retval = -1;
				}
			}
		}

	}
	else {
		retval = -1;
	}

	if (retval == -1) {
		printf("  ERROR: Invalid input entered\n\n%s\n", usage);
	}

	free(usage);

	return retval;
}

/*
 * Function: getInputString
 * --------------------------
 *   Opens the specified file and loads its contents into a string,
 *   which is returned inside of an input_t, along with the string length
 *
 *   char* filename: path and name of the input file to open
 *
 *   Returns: input_t, where the str attribute is the loaded file
 *     and the len attribute is the length of str
 */
static input_t getInputString(char* filename)
{
	input_t input;

	char* buffer = 0;
	long length;
	FILE * f = fopen (filename, "rb");

	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = malloc (length + 1);
	  if (buffer)
	  {
	    fread (buffer, 1, length, f);
	  }
	  fclose (f);
	}

	if (buffer)
	{
		buffer[length] = '\0';
		free(buffer);
	}

	input.str = buffer;
	input.len = length;

	return input;
}

/*
 * Function: my_isdigit
 * --------------------------
 *   Returns true or false if the char input is actually a number
 *
 *   char x: character to check
 *
 *   Returns: non-zero value if c is a digit, else 0 (true or false)
 */
int my_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
 * Function: my_atoi
 * --------------------------
 *   Converts a string argument to an integer
 *
 *   char* str: string representation of an integral number
 *
 *   Returns: converted integral number as an int, or 0 if no valid conversion
 */
int my_atoi(const char* str)
{
    int num = 0;

    for (int i = 0; str[i] != '\0'; ++i)
        num = num * 10 + str[i] - '0';
  
    return num;
}

int my_strlen(const char* str)
{
	const char *p = str;

    while (*p)
    	++p;

    return p - str;
}