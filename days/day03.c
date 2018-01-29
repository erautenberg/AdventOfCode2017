#include "../adventofcode.h"

typedef struct {
    unsigned long** gridArr;
    int inputX;
    int inputY;
} grid_t;

static int getNextOddSquareRoot(int input);
static int calcDistMath(int input, int sqrt);
static int findSide(int c, int sqrt, int side);
static int getOnesPos(int dimensions);
static int calcDistGrid(int x, int y, int one);
static grid_t makeGrid(int input, int dimensions);
static grid_t makeGridSums(int input, int dimensions);
static void printGrid(unsigned long** grid, int dimensions);

void day03(input_t input)
{
	printf("  DAY 03\n");

	int num = my_atoi(input.str);
	int dimensions = getNextOddSquareRoot(num);

	int mathAnswer = calcDistMath(num, dimensions);
    printf("    Part 1 (solved via formula): %d\n", mathAnswer);

    grid_t grid = makeGrid(num, dimensions);
    // printGrid(grid.gridArr, dimensions);
    int gridAnswer = calcDistGrid(grid.inputX, grid.inputY, getOnesPos(dimensions));
    printf("    Part 1 (solved via grid): %d\n", gridAnswer);

    grid_t gridSums = makeGridSums(num, dimensions);
    // printGrid(gridSums.gridArr, dimensions);
    unsigned long gridSumsAnswer = gridSums.gridArr[gridSums.inputX][gridSums.inputY];
	printf("    Part 2 (solved via grid): %lu\n", gridSumsAnswer);

    // Free Allocated Memory
    for (int i = 0; i < dimensions; i++)
    {
        grid.gridArr[i] = NULL;
        free(grid.gridArr[i]);
        gridSums.gridArr[i] = NULL;
        free(gridSums.gridArr[i]);
    }
    grid.gridArr = NULL;
    free(grid.gridArr);
    gridSums.gridArr = NULL;
    free(gridSums.gridArr);
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
    int c = y - (floor(sqrt / 2));  // where C is number in the center position below "1" (min distance to 1 is 1)

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

/*
 * Function: makeGrid
 * --------------------------
 *   Builds a 2D array of the spiral square and determines the input's position
 *   This builds the grid clockwise, or from the outside in (N->1)
 *
 *   int input: the number we need to find within the spiral square
 *   int dimensions: height/width of the square
 *
 *   Returns: Grid struct containing a 2D array of the spiral square and the
 *     X and Y coordinates of the input number in that sprial square
 */
static grid_t makeGrid(int input, int dimensions)
{
    unsigned long num = dimensions * dimensions;

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
    unsigned long** gridArr = (unsigned long **)malloc(dimensions * sizeof(unsigned long *)); 
    for (int i = 0; i<dimensions; i++)
    {
         gridArr[i] = (unsigned long *)malloc(dimensions * sizeof(unsigned long));
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

            if (direction == 'a') // LEFT
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
            else if (direction == 'w') // UP
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
            else if (direction == 'd') // RIGHT
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
            else if (direction == 's') // DOWN
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
 * Function: makeGridSums
 * --------------------------
 *   Builds a 2D array of the spiral square, populating each position with
 *   the sum of the adjacent numbers that have already been placed and
 *   determines the input's position
 *   This builds the grid counter-clockwise, or from the inside out (1->N)
 *
 *   int input: the number we need to find within the spiral square
 *   int dimensions: height/width of the square
 *
 *   Returns: Grid struct containing a 2D array of the spiral square and the
 *     X and Y coordinates of the input number in that sprial square
 */
static grid_t makeGridSums(int input, int dimensions)
{
    unsigned long num = 1;
    unsigned long sum = 0;

    int onePos = getOnesPos(dimensions);
    int row = onePos;
    int col = onePos;
    char direction = 'd';   // a is left, w is up, d is right, s is down
    int rowBoundTop = onePos;
    int rowBoundBottom = onePos;
    int colBoundLeft = onePos;
    int colBoundRight = onePos;

    int nextInputX = -1;
    int nextInputY = -1;

    grid_t grid;

    // create the empty grid (fill with 0s)
    unsigned long** gridArr = (unsigned long **)malloc(dimensions * sizeof(unsigned long *)); 
    for (int i=0; i<dimensions; i++)
    {
         gridArr[i] = (unsigned long *)malloc(dimensions * sizeof(unsigned long));
    }
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            gridArr[i][j] = 0;
        }
    }

    // place 1 in the middle
    gridArr[row][col] = num;
    col++;
    num++;
    colBoundRight++;

    // build the grid
    while (num <= (dimensions * dimensions))
    {
        sum = 0;

        if (row <= rowBoundBottom && row >= rowBoundTop && col <= colBoundRight && col >= colBoundLeft)
        {
            if (col > colBoundLeft)
            {
                sum += gridArr[row][col-1];
            }
            if (col < colBoundRight)
            {
                sum += gridArr[row][col+1];
            }

            if (row > rowBoundTop)
            {
                sum += gridArr[row-1][col];
                if (col > colBoundLeft)
                {
                    sum += gridArr[row-1][col-1];
                }
                if (col < colBoundRight)
                {
                    sum += gridArr[row-1][col+1];
                }
            }

            if (row < rowBoundBottom)
            {
                sum += gridArr[row+1][col];
                if (col > colBoundLeft)
                {
                    sum += gridArr[row+1][col-1];
                }
                if (col < colBoundRight)
                {
                    sum += gridArr[row+1][col+1];
                }
            }

            gridArr[row][col] = sum;

            // get the FIRST sum larger than the input (once the variables aren't -1)
            if (sum > input && nextInputX == -1 && nextInputY == -1) {
                nextInputX = row;
                nextInputY = col;
            }

            if (direction == 'd') // RIGHT
            {
                if (col == colBoundRight)
                {
                    row--;
                    rowBoundTop--;
                    direction = 'w';
                }
                else
                {
                    col++;
                }
            }
            else if (direction == 'w')  // UP
            {
                if (row == rowBoundTop)
                {
                    col--;
                    colBoundLeft--;
                    direction = 'a';
                }
                else
                {
                    row--;
                }
            }
            else if (direction == 'a') // LEFT
            {
                if (col == colBoundLeft)
                {
                    row++;
                    rowBoundBottom++;
                    direction = 's';
                }
                else
                {
                    col--;
                }
            }
            
            else if (direction == 's') // DOWN
            {
                if (row == rowBoundBottom)
                {
                    col++;
                    colBoundRight++;
                    direction = 'd';
                }
                else
                {
                    row++;
                }
            }
        }
        num++;
    }

    // set the grid struct
    grid.gridArr = gridArr;
    grid.inputX = nextInputX;
    grid.inputY = nextInputY;

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
static void printGrid(unsigned long** grid, int dimensions)
{
    for(int i = 0; i < dimensions; i++)
    {
        printf("    ");
        for(int j = 0; j < dimensions; j++)
        {
            printf("%lu\t", grid[i][j]);
        }
        printf("\n");
    }
}