/** 
 * @brief Function prototypes for a binary tree.
 *
 * This contains all prototypes as specified by the assignment, in addition to
 * an overloading of the stream operator for easy list content output.
 *
 * @author Jennifer Teissler
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <iostream>

using std::ostream;

class BinaryTree {
    public:
        BinaryTree();
        ~BinaryTree();
        int length() const;
        void insertItem(ItemType & item);
        void deleteItem(ItemType & item);
        void retrieve(ItemType & item, bool & found) const;
        void clear();
        void preOrder() const;
        void postOrder() const;
        void inOrder() const;
        friend ostream & operator<<(ostream & stream, const BinaryTree & list);

    private:
        int count;
        Node * root;
        void insert(Node * data, Node ** node);
        void deleteRecurse(ItemType & item, Node ** node);
        Node * findMinimum(Node * node);
        void clearNode(Node * node);
        void preOrderRecurse(Node * node) const;
        void postOrderRecurse(Node * node) const;
        void inOrderRecurse(Node * node) const;
        bool retrieveRecurse(ItemType & item, Node * node) const;
        void ostreamRecurse(ostream & stream, Node * node) const;
};

#endif
