# AdventOfCode2017

This is my repository for the [2017 Advent of Code Challenge](http://adventofcode.com/2017/). I had no desire to go crazy with the optimization as I chose to write all of these scripts in C as a refresher for myself (the last time I really wrote C was several years ago in college--I'm mainly a JavaScript girl now). I played around a lot with pointers and memory allocation, so even in cases where it seems like overkill or less efficient, I did this as an exercise.


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

Misc
-----
When I first started the challenge, I solved days 1-3 before deciding I'd like to post this to github and pretty it up a bit. I was experimenting with different file loading structures, and ended up browsing the [AdventOfCode subreddit](http://reddit.com/r/adventofcode), where I came across this amazing [post by askalski](https://www.reddit.com/r/adventofcode/comments/7q6s80/2017_optimized_solutions_in_c_195_ms_total/).  I really liked his clean solution of loading individual files for each day, so I took it a step further, allowing the user to choose whether they wanted to print the answers for all days, or just one. I also have print statements available in many of individual day files in order to print out special grids and structures that helped me solve the problem. I might add another param to allow you to toggle these on and off easily. We'll see ;)