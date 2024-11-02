#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdlib.h>

#include "util.h"
#include "node.h"

#ifdef HEAP_SET
#include "heap.h"
#else
#include "array.h"
#endif

#define MIN_DIM 1
#define MAX_DIM 10000

typedef struct {
    node_t** map;
    size_t width;
    size_t height;

#ifdef HEAP_SET
    heap_t* open_set;
#else
    array_t* open_set;
#endif
} maze_t;

maze_t* maze_read(char* path);
void maze_print(maze_t* self);
void maze_free(maze_t* self);
void maze_a_star(maze_t* self);

#endif
