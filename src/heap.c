#include "../include/heap.h"

#include <stdlib.h>
#include <stdio.h>

heap_t* heap_init(size_t size) {
    heap_t* self = (heap_t*)malloc(sizeof(heap_t));

    if(!self) {
        fprintf(stderr, "error: couldn't allocate memory in `heap_init` function\n");
        exit(1);
    }

    self->vec = (node_t**)malloc(size * sizeof(node_t*));
    
    if(!self->vec) {
        fprintf(stderr, "error: couldn't allocate memory in `heap_init` function\n");
        exit(1);
    }

    self->len = 0;
    self->cap = size;

    self->bits = (uint8_t*)calloc((size + 7) / 8, sizeof(uint8_t));
    
    if(!self->bits) {
        fprintf(stderr, "error: couldn't allocate memory in `heap_init` function\n");
        exit(1);
    }
    
    return self;
}

void heap_free(heap_t* self) {
    if(self) {
        if(self->vec) free(self->vec);
        if(self->bits) free(self->bits);
        free(self);
    }
}

inline uint8_t heap_is_empty(heap_t* self) {
    return self->len == 0;
}

static void set_bit(uint8_t* bits, size_t id) {
    size_t byte = id / 8;
    size_t bit_idx = id % 8;
    bits[byte] |= (1 << bit_idx);
}

static void clear_bit(uint8_t* bits, size_t id) {
    size_t byte = id / 8;
    size_t bit_idx = id % 8;
    bits[byte] &= ~(1 << bit_idx);
}

static uint8_t check_bit(uint8_t* bits, uint8_t id) {
    size_t byte = id / 8;
    size_t bit_idx = id % 8;
    return (bits[byte] >> bit_idx) & 1;
}

static void min_heapify(heap_t* self, size_t idx) {
    size_t l = 2 * idx + 1;
    size_t r = 2 * idx + 2;
    size_t lowest = idx;

    if(l < self->len && self->vec[l]->f_score < self->vec[lowest]->f_score) {
        lowest = l;
    }
    
    if(r < self->len && self->vec[r]->f_score < self->vec[lowest]->f_score) {
        lowest = l;
    }

    if(lowest != idx) {
        node_t* tmp = self->vec[idx];
        self->vec[idx] = self->vec[lowest];
        self->vec[lowest] = tmp;

        min_heapify(self, lowest);
    }
}

static void build_min_heap(heap_t* self) {
    for(int64_t i = self->len / 2 - 1; i >= 0; i--) {
        min_heapify(self, i);
    }
}

void heap_push(heap_t* self, node_t* value) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `heap_push` function\n");
        exit(1);
    }

    if(self->len == self->cap) {
        fprintf(stderr, "error: can't push to heap in `heap_push` function\n");
        fprintf(stderr, "len: %zu, cap: %zu\n", self->len, self->cap);
        exit(1);
    }

    if(!check_bit(self->bits, value->id)) {
        self->vec[self->len++] = value;
        set_bit(self->bits, value->id);
        build_min_heap(self);
    }
}

node_t* heap_pop(heap_t* self) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `heap_pop` function\n");
        exit(1);
    }
    
    if(self->len == 0) {
        fprintf(stderr, "error: can't pop from empty heap in `heap_pop` function\n");
        exit(1);
    }

    node_t* n = self->vec[0];
    self->vec[0] = self->vec[--self->len];
    clear_bit(self->bits, n->id);
    
    min_heapify(self, 0);

    return n;
}
