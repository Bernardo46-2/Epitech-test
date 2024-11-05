#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdlib.h>

#include "util.h"
#include "node.h"

// If HEAP_SET was defined, use a heap structure as a priority queue for the a* algorithm
// Use an array, otherwise
#ifdef HEAP_SET
#include "heap.h"
#else
#include "array.h"
#endif

// Min dimension of the maze
#define MIN_DIM 1

// Max dimension of the maze
#define MAX_DIM 10000

/**
 * @brief The structure to represent the maze
 *
 * @note The a* alrotithm is ran here, so the maze has a priority queue that
 * can either be an array of a heap, which will be decided as a compilation flag
 * and is stored in the open_set field below
 *
 * @note Fields should not be accessed directly and should only be manipulated through functions
 */
typedef struct {
    node_t** map;      // A matrix to hold the maze map
    size_t width;      // The width of the maze
    size_t height;     // The height of the maze

#ifdef HEAP_SET
    heap_t* open_set;  // The heap priority queue
#else
    array_t* open_set; // The array priority queue
#endif
} maze_t;

/**
 * @brief Constructs a maze struct from a maze written in a file
 *
 * @param path The path to the file where the maze is written
 * @return a pointer to the maze created
 */
maze_t* maze_read(char* path);

/**
 * @brief A function to print the maze
 *
 * @param self Maze to be printed
 */
void maze_print(maze_t* self);

/**
 * @brief Frees the structure, as well as all it's fields that required memory allocation
 *
 * @param Maze to be freed
 */
void maze_free(maze_t* self);

/**
 * @brief Runs the a* algorithm on the maze in order to find the best path through
 * nodes (0, 0) and (height-1, width-1)
 *
 * @param self Maze to apply the search
 *
 * @note This function traces the path on the nodes and modifies their node_t::symbol
 * field in place
 */
void maze_a_star(maze_t* self);

#endif
