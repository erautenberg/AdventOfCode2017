#include "../adventofcode.h"

typedef struct {
    int** gridArr;
    int inputX;
    int inputY;
} grid_t;

static int getNextOddSquareRoot(int input);
static int calcDistMath(int input, int sqrt);
static int findSide(int c, int sqrt, int side);
static int getOnesPos(int dimensions);
static grid_t makeGrid(int input, int length);
static void printGrid(int** grid, int dimensions);
static int calcDistGrid(int x, int y, int one);

void day03(input_t input)
{
	printf("  DAY 03\n");

	int num = my_atoi(input.str);
	int dimensions = getNextOddSquareRoot(num);

	int mathAnswer = calcDistMath(num, dimensions);

    grid_t grid = makeGrid(num, dimensions);
    // printGrid(grid.gridArr, dimensions);
    int gridAnswer = calcDistGrid(grid.inputX, grid.inputY, getOnesPos(dimensions));

	printf("    Part 1 (solved via formula): %d\n", mathAnswer);
	printf("    Part 1 (solved via grid): %d\n", gridAnswer);
	// printf("    Part 2 (solved via grid): %d\n", );
}

/*
 * Function: getNextOddSquareRoot
 * --------------------------
 *   Uses the sqaure root of the input to find the closest odd whole numbered square
 *   in order to build a perfect square grid
 *
 *   int input: the number we need to find within the spiral square
 *
 *   Returns: next closest odd whole numbered square to the input's square root
 */
static int getNextOddSquareRoot(int input)
{
    int squareroot = ceil(sqrt(input));
    if (squareroot % 2 == 0)
    {
        squareroot++;
    }

	return squareroot;
}

/*
 * Function: calcDistMath
 * --------------------------
 *   Calculates the distance in steps from the input number back to 1 in a spiral square
 *
 *   int input: the number we need to find within the spiral square
 *   int sqrt: next closest odd whole numbered square to the input's square root (height/width of the square)
 *
 *   Returns: distance in steps from the input number back to 1 in a spiral square
 */
static int calcDistMath(int input, int sqrt)
{
    int y = sqrt * sqrt;            // total number (perfect square)
    int c = y - (floor(sqrt / 2));  // where C is the center point lined up with the number "1" (min distance to 1)

    int b0 = findSide(c, sqrt, 0);  // bias meaning "skewed to one side"
    int b1 = findSide(c, sqrt, 1);  // finding these biases calculates the distance between b0 and bn
    int b2 = findSide(c, sqrt, 2);  // which is length of the side - 1 multiplied by the side number
    int b3 = findSide(c, sqrt, 3);  // in order to always move in a clockwise direction (reverse numerical order)

    int b0Dist = abs(b0 - input);   // substracting the initially requested number will yield
    int b1Dist = abs(b1 - input);   // how far from bn the requested number is
    int b2Dist = abs(b2 - input);   // use absolute value because the bias might eventually yield negatives
    int b3Dist = abs(b3 - input);   // (as you subtract between sides), but distance is absolute

    int min = b0Dist;				// finding the minimum of all the biases yields
    if (b1Dist < min)				// the lowest number of steps to the closest side center point
        min = b1Dist;
    if (b2Dist < min)
        min = b2Dist;
    if (b3Dist < min)
        min = b3Dist;

    return (floor(sqrt/2) + min);	// distance from outermost
}

/*
 * Function: findSide
 * --------------------------
 *   Calculates the distance from each side to the requested number
 *
 *   int c: center point of a side (length of side / 2, rounded down)
 *   int sqrt: next closest odd whole numbered square to the input's square root
 *   int side: 0-3 (4 sides to a square), 0 = bottom edge, 1 = left, 2, = top, 3 = right
 *
 *   Returns: 
 */
static int findSide(int c, int sqrt, int side)
{
    return c - side * (sqrt - 1);
}

/*
 * Function: getOnesPos
 * --------------------------
 *   Calculates the x/y position of 1 in a perfect spiral square
 *   (1 will always be in the middle, so x and y are the same)
 *
 *   int dimensions: height/width of the square
 *
 *   Returns: void
 */
static int getOnesPos(int dimensions)
{
    return floor(dimensions/2);
}

/*
 * Function: calcDistMath
 * --------------------------
 *   Builds a 2D array of the spiral square and determines the input's position
 *
 *   int input: the number we need to find within the spiral square
 *   int dimensions: height/width of the square
 *
 *   Returns: Grid struct containing a 2D array of the spiral square and the
 *     X and Y coordinates of the input number in that sprial square
 */
static grid_t makeGrid(int input, int dimensions)
{
    int num = dimensions * dimensions;

    int rowBoundTop = 0;
    int rowBoundBottom = dimensions - 1;
    int colBoundLeft = 0;
    int colBoundRight = dimensions - 1;
    
    int row = rowBoundBottom;
    int col = colBoundRight;
    char direction = 'a';   // a is left, w is up, d is right, s is down

    int inputPosX = -1;
    int inputPosY = -1;

    grid_t grid;

    // create the empty grid (fill with 0s)
    int** gridArr = (int **)malloc(dimensions * sizeof(int *)); 
    for (int i=0; i<dimensions; i++)
    {
         gridArr[i] = (int *)malloc(dimensions * sizeof(int));
    }
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            gridArr[i][j] = 0;
        }
    }

    // build the grid
    while (num > 0)
    {
        if (row <= rowBoundBottom && row >= rowBoundTop && col <= colBoundRight && col >= colBoundLeft)
        {
            if (num == input) {
                inputPosX = row;
                inputPosY = col;
            }
            gridArr[row][col] = num;

            if (direction == 'a')
            {
                if (col == colBoundLeft)
                {
                    row--;
                    rowBoundBottom--;
                    direction = 'w';
                }
                else
                {
                    col--;
                }
            }
            else if (direction == 'w')
            {
                if (row == rowBoundTop)
                {
                    col++;
                    colBoundLeft++;
                    direction = 'd';
                }
                else
                {
                    row--;
                }
            }
            else if (direction == 'd')
            {
                if (col == colBoundRight)
                {
                    row++;
                    rowBoundTop++;
                    direction = 's';
                }
                else
                {
                    col++;
                }
            }
            else if (direction == 's')
            {
                if (row == rowBoundBottom)
                {
                    col--;
                    colBoundRight--;
                    direction = 'a';
                }
                else
                {
                    row++;
                }
            }
        }
        num--;
    }

    // set the grid struct
    grid.gridArr = gridArr;
    grid.inputX = inputPosX;
    grid.inputY = inputPosY;

    return grid;
}

/*
 * Function: printGrid
 * --------------------------
 *   Prints out all rows and columns of a two dimensional int arr
 *
 *   int** arr: 2D array of numbers (interpretted from the input file)
 *   int dimensions: height/width of the square
 *
 *   Returns: void
 */
static void printGrid(int** grid, int dimensions)
{
    for(int i = 0; i < dimensions; i++)
    {
        printf("    ");
        for(int j = 0; j < dimensions; j++)
        {
            printf("%d\t", grid[i][j]);
        }
        printf("\n");
    }
}

/*
 * Function: calcDistGrid
 * --------------------------
 *   Prints out all rows and columns of a two dimensional int arr
 *
 *   int xDist: distance on the X axis (row) the input is from 1
 *   int yDist: distance on the Y axis (col) the input is from 1
 *   int one: x/y position of 1 in a perfect spiral square
 *     (1 will always be in the middle, so x and y are the same)
 *
 *   Returns: void
 */
static int calcDistGrid(int x, int y, int one)
{
    int xDist = abs(x - one);
    int yDist = abs(y - one);

    return xDist + yDist;
}