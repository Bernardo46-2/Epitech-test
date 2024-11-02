#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "node.h"
#include "util.h"

typedef struct {
    node_t** vec;
    size_t len;
    size_t cap;
} array_t;

array_t* array_init(size_t size);
void array_free(array_t* self);
uint8_t array_is_empty(array_t* self);
void array_push(array_t* self, node_t* node);
node_t* array_pop(array_t* self);

void array_print(array_t* self);

#endif
