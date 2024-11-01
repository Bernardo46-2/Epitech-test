#include <stdio.h>

#include "include/maze.h"

int main(int argc, char** argv) {
    if(argc < 2) return 1;

    maze_t* m = maze_read(argv[1]);
    // maze_print(m);
    // printf("h: %zu\n", m->height);
    // printf("w: %zu\n", m->width);
    maze_a_star(m);
    maze_free(m);
    
    return 0;
}
