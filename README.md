# AdventOfCode2017


Compiling
-----
- The Makefile is already set up, all you need to do is run
	`make`
- To wipe out all the object files and the executable, run
	`make clean`

Running
-----
- To see the use, run
	`./advent`
- To see the results of all available days, run
	`./advent -A` or `./advent -a`
- To run a specific day, run
	`./advent X`, where X is the number of the desired day
	For example: `./advent 1`

Notes
-----
- Multi-line input files are specifically formatted with a `\n` at the end. If you try to run your own input files, make sure they are formatted the same way
- In most cases, "perfect" input files are expected. For example, in Day 2, negative numbers are not expected

- Day 2
 - Set up to accept files with a row count of up to 16 and a column count of up to 16. If you have longer files, change lines 2 and 3 in `day02.c`:
 	```c
 	#define ROWS 16
	#define COLS 16
	```