#include "../include/node.h"

#include <stdio.h>

inline uint8_t node_is_wall(node_t* self) {
    return self->symbol == 'X';
}

inline uint8_t node_equals(node_t* self, node_t* other) {
    return self->x == other->x && self->y == other->y;
}
