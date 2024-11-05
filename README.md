# Maze Problem

The problem is to find a path from the start of the maze (0, 0) to the end (h-1, w-1). The specifics can be found on the pdf file.

### Usage

The program reads a maze from a text file. Examples of the formatting can be found in the pdf file.

- `make` to compile
- `make re` to recompile
- `make clean` to clean object files
- `make fclean` to clean object files and binary files
- `./solver <file>` to run, where "file" is the file containing the maze

### Notes
- I choose the A* algorithm to solve the problem
- Since the rules say you can only move in the 4 cardinal directions, the Manhattan distance was used as heuristic.
- No external libraries were used
- The A* algorithm uses a priority queue in its implementation. That queue was made in two versions: an array and a minimum heap. The array is the default one, while the heap can be selected by including the `-DHEAP_SET` flag to gcc during compilation (it should already be added in the makefile). To use each version you can just add/remove that flag from the makefile.
