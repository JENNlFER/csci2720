/** 
 * @brief Defines the structure of a node in the linked list.
 * @author Jennifer Teissler
 */

#ifndef LISTNODE_H
#define LISTNODE_H

#include <cstdlib>
#include "DataType.h"

struct ListNode {
    DataType item;
    ListNode * next;                
    explicit ListNode(DataType & item) : item(item), next(NULL) {};  
};

#endif
