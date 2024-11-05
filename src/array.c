#include "../include/array.h"

#include <stdio.h>

array_t* array_init(size_t size) {
    array_t* self;

    self = (array_t*)malloc(sizeof(array_t));

    if(!self) {
        fprintf(stderr, "error: couldn't allocate memory in `array_init` function\n");
        exit(1);
    }
    
    self->len = 0;
    self->cap = size;
    self->vec = (node_t**)malloc(self->cap * sizeof(node_t*));

    if(!self->vec) {
        fprintf(stderr, "error: couldn't allocate memory in `array_init` function\n");
        exit(1);
    }
    
    return self;
}

void array_free(array_t* self) {
    if(self) {
        if(self->vec) free(self->vec);
        free(self);
    }
}

inline uint8_t array_is_empty(array_t* self) {
    return self->len == 0;
}

void array_push(array_t* self, node_t* node) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `array_push` function\n");
        exit(1);
    }
    
    if(self->len == self->cap) {
        fprintf(stderr, "error: can't push to array in `array_push` function\n");
        exit(1);
    }

    for(size_t i = 0; i < self->len; i++) {
        if(node_equals(self->vec[i], node)) {
            return;
        }
    }
    
    self->vec[self->len++] = node;
}

node_t* array_pop(array_t* self) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `array_pop` function\n");
        exit(1);
    }

    if(self->len == 0) {
        fprintf(stderr, "error: can't pop from empty array in `array_pop` function\n");
        exit(1);
    }

    node_t* n = self->vec[0];
    size_t idx = 0;
    
    for(size_t i = 0; i < self->len; i++) {
        if(self->vec[i]->f_score < n->f_score) {
            n = self->vec[i];
            idx = i;
        }
    }

    for(size_t i = idx; i < self->len-1; i++) {
        self->vec[i] = self->vec[i+1];
    }
    
    self->len--;

    return n;
}
