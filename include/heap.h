#ifndef _HEAP_H_
#define _HEAP_H_

#include "node.h"

/**
 * A minimum heap structure to act as a priority queue for the a* algorithm.
 *
 * The node field for testing if a node is "lower" than another is the node_t::f_score field
 *
 * @note The nodes stored in the heap are only pointers to the actual node in the maze map and
 * should not be manipulated as value, but as references. That avoids unecessary memory allocations
 * 
 * @note Fields should not be accessed directly and should only be manipulated through functions
 */
typedef struct {
    node_t** vec;  // The actual heap, in array form
    size_t len;    // Current amount of elements in the heap
    size_t cap;    // Max capacity of the heap
    
    uint8_t* bits; // A boolean array for checking if a node of certain id is in the heap in O(1)
} heap_t;

/**
 * @brief Initializes a heap struct
 *
 * @param size The max size of the heap
 * @return a pointer for the heap created
 */
heap_t* heap_init(size_t size);

/**
 * @brief Frees the structure, as well as all it's fields that required memory allocation
 *
 * @param self Heap to be freed
 */
void heap_free(heap_t* self);

/**
 * @brief Tests if a heap is empty or not
 *
 * @param self Heap to be tested
 * @return True if it is empty, false otherwise
 */
uint8_t heap_is_empty(heap_t* self);

/**
 * @brief Inserts a new element in the heap
 *
 * @param self Heap to insert an push into
 * @param value Value to be push
 */
void heap_push(heap_t* self, node_t* value);

/**
 * @brief Removes the lowest f_score node from the heap and returns a pointer to it
 *
 * @param self Heap to pop a value from
 * @return a pointer to a node in the maze structure that has the lowest f_score and was in the heap
 */
node_t* heap_pop(heap_t* self);

#endif
