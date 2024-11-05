#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "node.h"
#include "util.h"

/**
 * @brief An array structure to act as a priority queue for the a* algorithm
 *
 * The node field for testing if a node is "lower" than another is the node_t::f_score field
 * 
 * @note The nodes stored in the array are only pointers to the actual node in the maze map and
 * should not be manipulated as value, but as references. That avoids unecessary memory allocations
 *
 * @note Fields should not be accessed directly and should only be manipulated through functions
 */
typedef struct {
    node_t** vec; // The actual array
    size_t len;   // Current amount of elements in the array
    size_t cap;   // Max capacity of the array
} array_t;

/**
 * @brief Initializes an array structure
 *
 * @param size The max size of the array
 * @return a pointer to the array created
 */
array_t* array_init(size_t size);

/**
 * @brief Frees the structure, as well as all it's fields that required memory allocation
 *
 * @param self Array to be freed
 */
void array_free(array_t* self);

/**
 * @brief Tests if an array is empty or not
 *
 * @param self Array to be tested
 * @return True if it is empty, false otherwise
 */
uint8_t array_is_empty(array_t* self);

/**
 * @brief Inserts a new element in the array
 *
 * @param self Array to insert an push into
 * @param value Value to be push
 */
void array_push(array_t* self, node_t* node);

/**
 * @brief Removes the lowest f_score node from the array and returns a pointer to it
 *
 * @param self Array to pop a value from
 * @return a pointer to a node in the maze structure that has the lowest f_score and was in the array
 */
node_t* array_pop(array_t* self);

#endif
