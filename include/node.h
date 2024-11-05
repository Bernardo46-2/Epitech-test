#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>

#include "util.h"

/**
 * A node structure for representing the nodes of the maze and storing their metadata
 *
 * @note There's no constructor function as the only situation where this struct should
 * be initialized is during the criation of the maze_t struct, within it's constructor
 */
typedef struct {
    size_t id;      // node ID
    size_t g_score; // distance from this node to the start node
    size_t h_score; // distance from this node to the end node (manhattan distance)
    size_t f_score; // total cost (g_score + h_score)
    char symbol;    // symbol to be printed in the maze ('*' | 'X' | 'o')
    size_t x, y;    // xy positions in the maze matrix
    size_t px, py;  // xy positions of the parent node, selected during the a* algorithm
} node_t;

/**
 * @brief Tests whether a node is a wall of not
 * 
 * @param self Node to test if is wall
 * @return True if the node is a wall, false if it is not
 */
uint8_t node_is_wall(node_t* self);

/**
 * @brief Tests if a node is equal to another one based off xy position
 *
 * @param self, other nodes to compare
 * @return True if the nodes are equal, false if they are not
 */
uint8_t node_equals(node_t* self, node_t* other);

#endif
