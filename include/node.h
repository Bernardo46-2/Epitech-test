#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>

#include "util.h"

typedef struct {
    size_t g_score;
    size_t h_score;
    size_t f_score;
    char symbol;
    size_t x, y;
    size_t px, py;
} node_t;

uint8_t node_is_wall(node_t* self);
uint8_t node_equals(node_t* self, node_t* other);
void node_print(node_t* self);

#endif
