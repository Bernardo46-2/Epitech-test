#ifndef _HEAP_H_
#define _HEAP_H_

#include "node.h"

typedef struct {
    node_t** vec;
    size_t len;
    size_t cap;
    
    uint8_t* bits;
    size_t bits_len;
} heap_t;

heap_t* heap_init(size_t size);
void heap_free(heap_t* self);
uint8_t heap_is_empty(heap_t* self);
void heap_push(heap_t* self, node_t* value);
node_t* heap_pop(heap_t* self);

#endif
