/** 
 * @brief Function prototypes for a sorted linked list.
 *
 * This contains all prototypes as specified by the assignment, in addition to
 * an overloading of the stream operator for easy list content output.
 *
 * @author Jennifer Teissler
 */

#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include "ListNode.h"
#include <iostream>

using std::ostream;

class SortedLinkedList {
    public:
        SortedLinkedList();
        ~SortedLinkedList();
        int length() const;
        void insertItem(DataType & item);
        void deleteItem(DataType & item);
        int search(DataType & item) const;
        void clear();
        void pairwiseSwap();
        friend ostream & operator<<(ostream & stream, const SortedLinkedList & list);

    private:
        int count;
        ListNode * head;
};

#endif
