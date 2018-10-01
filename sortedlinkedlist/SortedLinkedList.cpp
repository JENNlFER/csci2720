/** 
 * @brief Function implementations for a sorted linked list.
 *
 * This contains all implementations of prototypes required for the assignment.
 * In addition there is a stream operator override implementation.
 *
 * @author Jennifer Teissler
 */

#include <cstdlib>
#include "SortedLinkedList.h"

using std::ostream;

SortedLinkedList::SortedLinkedList() {
    this->count = 0;    // initialize the list to have a size of 0
    this->head = NULL;  // initialize the head pointer to nothing
};

SortedLinkedList::~SortedLinkedList() {
   this->clear();       // call the clear function to destruct the class
};

int SortedLinkedList::length() const {
    return this->count; // return the number of elements in the list
};

void SortedLinkedList::insertItem(DataType & item) {
    ListNode * node = new ListNode(item); // create new element
    ListNode * * current = &this->head;   // create a pointer to the pointer pointing to the first element
    // SEARCH
    // check that the current element is not null 
    // check if the element to insert is greater than or equal to the current
    while(*current != NULL && node->item.compareTo((**current).item) != DataType::LESSER) {
        current = &(**current).next;      // point current at the next element that it is pointing to
    }
    // INSERT
    node->next = *current;                // set the next element to point to the next item
    *current = node;                      // set the previous element to point to the new element
    this->count++;                        // increment list size by 1
};

void SortedLinkedList::deleteItem(DataType & item) {
    ListNode * * current = &this->head;   // create a pointer to the pointer pointing to the first element
    // SEARCH
    // check that the current element is not null 
    // check whether the element to delete has been found
    while(*current != NULL && (**current).item.compareTo(item) != DataType::EQUAL) {
        current = &(**current).next;      // point current at the next element that it is pointing to
    }
    // DELETE
    if (*current != NULL) {               // check that the element to delete is actually in the list
        ListNode * temp = *current;       // store the element to delete
        *current = temp->next;            // point the previous element at the next element
        this->count--;                    // decrement the list size by 1
        delete temp;                      // delete the element from memory
    } 
};

int SortedLinkedList::search(DataType & item) const {
    ListNode * current = this->head;        // store a pointer to the first item in the list

    for (int i = 0; i < this->count; ++i) { // iterate through the list until a match is found
        if (current->item.compareTo(item) == DataType::EQUAL) {
            return i;                       // return index of the value if found in the list
        }
        current = current->next;
    }
    return -1;                              // return -1 if the value is not found in the list
};

void SortedLinkedList::clear() {
    ListNode * current;                // create a temporary pointer 

    while (this->head != NULL) {       // iterate until the end of the list
        current = this->head;          // store the current item for deletion
        this->head = this->head->next; // move to the next item
        delete current;                // delete the current item
    }
    this->count = 0;                   // reset the list size to zero
};      

void SortedLinkedList::pairwiseSwap() {
    if (this->count < 2) {                  // the swap doesn't apply here
        return;
    }

    ListNode * a = this->head;              // point a at the first element
    ListNode * b = this->head->next;        // point b at the second element 
    ListNode * c = NULL;                    // set c to NULL for now
    this->head = b;                         // swap the head to the second element

    while (true) {                          // begin iterating over the list
        c = b->next;                        // point c at the element after b
        b->next = a;                        // swap b's element's next pointer

        if (c == NULL || c->next == NULL) { // if the end of the list has been reached
            a->next = c;                    // swap a's element's next pointer
            break;                          // stop iterating
        }

        a->next = c->next;                  // swap a's element's next pointer to be c's next
        a = c;                              // set a to c's value to set up the next loop
        b = a->next;                        // store a's next pointer in b
    }
};

ostream & operator<<(ostream & stream, const SortedLinkedList & list) {
    ListNode * current = list.head;                // start at the first element

    while (current != NULL) {                      // iterate until the end of the list
        stream << current->item.getValue() << " "; // send current value into stream
        current = current->next;                   // advance to next element
    }
    return stream;                                 // return the modified stream
};
