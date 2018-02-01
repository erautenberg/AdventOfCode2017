/*
create an array of program structs
loop through every line of the input
	for each line,
		add a program struct to the array and do the following
			find the program name and set that as the struct's ID (used for the hash)
			find the weight and set that as the struct's weight
			find the arrow and add everything after it to a children array
			set the parent to NULL

loop back through the array
	for each element,
		check it's children array
			and for each element in the children array,
			look up that child and set it's parent to the current program

search for struct without parent (parent is still NULL) as this will be the root program
*/

#include "../adventofcode.h"

#define ROWS 1500
#define WORDS 20
#define LETTERS 10

#define HASHSIZE 4096
#define ARRSIZE HASHSIZE + 256
#define MULTIPLIER 37

typedef struct {
	char* name;
	unsigned int index;
	unsigned long weight;
	unsigned long totalWeight;
} info_t;

typedef struct {
	info_t info;
	info_t parent;
	unsigned int childCount;
	info_t* children;
} program_t;

// struct programtree_t {
// 	char* name;
// 	struct programtree_t* parent;

// 	unsigned long weight;
// 	unsigned long totalWeight;

// 	unsigned int childCount;
// 	struct programtree_t* children;
// };

static void printArr(arr_t arr);
static void printPrograms(program_t* programs);
static arr_t parseLines(char* str, int len);
static unsigned long hashFunction(char* s);
static program_t* buildProgramArray(arr_t arr);
static program_t* setParents(program_t* p);
static program_t getRoot(program_t* p);
// static bool isBalanced(program_t* p, program_t node);
// static program_t calcTotalWeights(program_t* p, int currIndex, int problemIndex);

void day07(input_t input)
{
	printf("  DAY 07\n");

	arr_t arr = parseLines(input.str, input.len);
	// printArr(arr);

	program_t* programsHash = buildProgramArray(arr);
	// printPrograms(programsHash);
	programsHash = setParents(programsHash);

	// program_t root = getRoot(programsHash);
	// printf("    Part 1: %s\n", root.info.name);

	// program_t programsTree = createTree
	// calcTotalWeights(programs, root.index, -1);
	// printf("    Part 2: %d\n", );


	// FREE ALLOCATED MEMORY

	// programs array
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (programsHash[i].childCount > 0)
		{
			free(programsHash[i].children);
			programsHash[i].children = NULL;
		}
	}
	free(programsHash);
	programsHash = NULL;
	
	// string input array
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

static void printPrograms(program_t* programs)
{
	int c = 0;
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (programs[i].info.name != NULL)
		{
			c++;
			printf("%d %s (%lu) -> ", c, programs[i].info.name, programs[i].info.weight);
			if (programs[i].childCount > 0)
			{
				for (int j = 0; j < programs[i].childCount; j++)
				{
					printf("%s, ", programs[i].children[j].name);
				}
			}
			printf("\n");
		}
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
		if (str[i] == ',' || str[i] == '(' || str[i] == ')')
		{
			continue;
		}
		else if (str[i] != '\n')
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

static unsigned long hashFunction(char* s)
{
	const char* us;
	unsigned long h = 0;

	for (us = s; *us; us++)
	{
		h = h * MULTIPLIER + *us;
	}

	return h;
}

static program_t* buildProgramArray(arr_t arr)
{
	program_t* programs = (program_t *)malloc((ARRSIZE) * sizeof(program_t));

	// create empty parent struct
	info_t parent;
	parent.name = NULL;
	parent.index = -1;
	parent.weight = 0;
	parent.totalWeight = 0;

	// create empty child struct
	info_t child;
	child.name = NULL;
	child.index = -1;
	child.weight = 0;
	child.totalWeight = 0;
	
	// create empty program (do not allocate memory for children array until necessary)
	info_t curr;
	curr.name = NULL;
	curr.index = -1;
	curr.weight = 0;
	curr.totalWeight = 0;
	program_t program;
	// program.info = current;
	program.childCount = 0;
	program.children = NULL;

	for (int i = 0; i < ARRSIZE; i++)
	{
		programs[i].info = curr;
		programs[i].childCount = 0;
		programs[i].children = NULL;
	}

	unsigned long h = 0;
	int collisionOffset = 0;
	for (int i = 0; i < arr.rowCount; i++)
	{
		curr.name = NULL;
		curr.index = -1;
		curr.weight = 0;
		curr.totalWeight = 0;
		program.info = curr;
		program.childCount = 0;
		program.children = NULL;

		child.name = NULL;
		child.index = -1;

		for (int j = 0; j < arr.rows[i].wordCount; j++)
		{
			if (j == 0)
			{
				curr.name = arr.rows[i].words[j];
			}
			else if (j == 1)
			{
				curr.weight = my_atoi(arr.rows[i].words[j]);
				curr.totalWeight = curr.weight;
			}
			else if (j >= 3)
			{
				if (program.childCount == 0)
				{
					program.children = (info_t *)malloc((WORDS) * sizeof(info_t));
				}

				child.name = arr.rows[i].words[j];

				program.children[program.childCount] = child;
				program.childCount++;
			}
		}
		if (curr.name != NULL)
		{
			h = hashFunction(curr.name) % HASHSIZE;
			// check for a collision
			if (programs[h].info.name != NULL)
			{
				h = HASHSIZE + collisionOffset;
				collisionOffset++;
			}
			curr.index = h;
			program.info = curr;
			programs[h] = program;
			h = 0;
		}
	}

	return programs;
}

static program_t* setParents(program_t* p)
{
	program_t* programs = p;

	int h = 0;
	// for (int i = 0; i < ARRSIZE; i++)
	// {
	// 	if (programs[i].info.name != NULL && programs[i].childCount > 0)
	// 	{
	// 		for (int j = 0; j < programs[i].childCount; j++)
	// 		{
	// 			h = hashFunction(programs[i].children[j].name) % HASHSIZE;

	// 			int cmp = my_strcmp(programs[h].info.name, programs[i].children[j].name);
	// 			printf("%d\n", cmp);
	// 			if (!cmp)
	// 			{
	// 			// 	for (h = HASHSIZE; h < ARRSIZE; h++)
	// 			// 	{
	// 			// 	// 	if (my_strcmp(programs[h].info.name, programs[i].children[j].name))
	// 			// 	// 	{
	// 			// 	// 		break;
	// 			// 	// 	}
	// 			// 	}
	// 			}
	// 			// programs[h].parent.name = programs[i].info.name;
	// 			// programs[h].parent.index = i;
	// 			// programs[i].children[j].index = h;
	// 		}
	// 	}
	// }

	return programs;
}

static program_t getRoot(program_t* p)
{
	program_t* programs = p;
	program_t root;

	for (int i = 0; i < ARRSIZE; i++)
	{
		if (programs[i].info.name != NULL && programs[i].parent.name == NULL)
		{
			root = programs[i];
		}
	}

	return root;
}

// // static bool isBalanced(program_t* p, program_t node)
// // {
// // 	program_t* programs = p;
// // 	bool balanced = TRUE;
// // 	int h = 0;
// // 	int weight = -1;

// // 	for (int i = 0; i < node.childCount; i++)
// // 	{
// // 		h = hashFunction(node.children[i]) % HASHSIZE;

// // 		if (!my_strcmp(programs[h].name, node.children[i]))
// // 		{
// // 			for (h = HASHSIZE; h < ARRSIZE; h++)
// // 			{
// // 				if (my_strcmp(programs[h].name, node.children[i]))
// // 				{
// // 					break;
// // 				}
// // 			}
// // 		}

// // 		if (weight == -1)
// // 		{
// // 			weight = programs[h].weight;
// // 		}
// // 		else if (weight != programs[h].weight)
// // 		{
// // 			balanced = FALSE;
// // 			break;
// // 		}
// // 		else {
// // 			balanced = isBalanced(programs, programs[h]);
// // 			if (balanced)
// // 			{
// // 				balanced = FALSE;
// // 				break;
// // 			}
// // 		}
// // 	}

// // 	return balanced;
// // }


// // // start with the root node
// // // following root all the way to the end (first child -> first child -> first, etc.)
// // // when farthest node is found, set it's totalWeight
// // // compare it's totalWeight to it's siblings
// // // if these siblings weights are balanced, update the parent's totalWeight to be the combined weight
// // //		(initial weight + combined children's weights)
// // // after updating parent's weight, repeat on sibling's children
// // // once total weights are updated, compare parent's siblings totalWeight to each other 
// // // 

// static program_t calcTotalWeights(program_t* p, int currIndex, int problemIndex)
// {
// 	program_t* programs = p;
// 	program_t program;

// 	int parentIndex = programs[currIndex].parent.index;
// 	int neededWeight = 0;
// 	int foundWeight = 0;

// 	if (programs[currIndex].childCount == 0)
// 	{
// 		programs[parentIndex].totalWeight += programs[currIndex].totalWeight;
// 	}
// 	else
// 	{
// 		for (int i = 0; i < programs[currIndex].childCount; i++)
// 		{
// 			// foundWeight = programs[programs[currIndex].children[i].index].totalWeight;
// 			// if (i == 0)
// 			// {
// 			// 	neededWeight = programs[programs[currIndex].children[i].index].totalWeight;
// 			// }
// 			// else if (neededWeight != programs[programs[currIndex].children[i].index].totalWeight)
// 			// {
// 			// 	printf("%s needed:%d, found: %d\n", programs[currIndex].name, neededWeight, foundWeight);
// 			// 	// printf("%s has:%lu\n", programs[programs[currIndex].children[0].index].name, programs[programs[currIndex].children[0].index].totalWeight);
// 			// 	// printf("%s has:%lu\n", programs[programs[currIndex].children[i].index].name, programs[programs[currIndex].children[i].index].totalWeight);
// 			// 	break;
// 			// }
// 			calcTotalWeights(programs, programs[currIndex].children[i].index, problemIndex);
// 		}

// 		if (parentIndex != -1)
// 		{
// 			programs[parentIndex].totalWeight += programs[currIndex].totalWeight;
// 		}
// 	}

// 	printf("%s: %lu\n", programs[currIndex].name, programs[currIndex].totalWeight);

// 	return program;
// }