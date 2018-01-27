#ifndef ADVENTOFCODE_H
#define ADVENTOFCODE_H


/* LIBRARY INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


/* DEFINE BOOLEAN */
typedef int bool;
#define TRUE 1
#define FALSE 0

#define STARTDAY 1
#define ENDDAY 4


/* MY VERSIONS OF LIBRARY FUNCTIONS */
bool my_isdigit(char);
int my_atoi(const char*);
int my_strlen(const char*);


/* INPUT STRUCT
	string to load input file into
	length of the string
*/
typedef struct {
	char* str;
	int len;
} input_t;


/* ADVENT DAY STRUCT
	advent day function to trigger
	input file to pass to advent day function
*/
typedef struct {
	void (*dayFunction)(input_t);
	char* inputFile;
} adventday_t;


/* ADVENT DAY FUNCTIONS */
void day01(input_t);
void day02(input_t);
void day03(input_t);
void day04(input_t);


/* ARRAY OF ADVENT DAYS */
static const adventday_t adventdays[] = {
	{ day01, "input/day01.txt" },
	{ day02, "input/day02.txt" },
	{ day03, "input/day03.txt" },
	{ day04, "input/day04.txt" },
};


#endif
