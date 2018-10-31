/** 
 * @brief Defines the structure of a node in the binary tree.
 * @author Jennifer Teissler
 */

#ifndef NODE_H
#define NODE_H

#include <cstdlib>
#include "ItemType.h"

struct Node {
    ItemType item;
    Node * left;
    Node * right;
    explicit Node(ItemType & item) : item(item), left(NULL), right(NULL) {};  
};

#endif
