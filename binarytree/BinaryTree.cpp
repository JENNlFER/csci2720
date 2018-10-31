/** 
 * @brief Function implementations for a binary tree.
 *
 * This contains all implementations of prototypes required for the assignment.
 * In addition there is a stream operator override implementation.
 * 
 * This binary tree implementation does not allow for duplicates, as per
 * the assignment specifications.
 *
 * @author Jennifer Teissler
 */

#include <cstdlib>
#include <ostream>
#include "BinaryTree.h"

using std::ostream;
using std::cout;
using std::endl;

BinaryTree::BinaryTree() {
    this->count = 0;    // initialize the list to have a size of 0
    this->root = NULL;  // initialize the root pointer to nothing
};

BinaryTree::~BinaryTree() {
   this->clear();       // call the clear function to destruct the class
};

int BinaryTree::length() const {
    return this->count; // return the number of elements in the list
};

void BinaryTree::insertItem(ItemType & item) {
    Node * node = new Node(item); // create a new node
    insert(node, &(this->root));  // recursively insert the node
};

void BinaryTree::insert(Node * data, Node ** node) { // fun with double pointers
    if (*node == NULL) {               // handle missing root node case
        *node = data;                  // store the data in the node
        this->count++;                 // increment the tree size counter 
    }
    else if (data->item.compareTo((*node)->item) == ItemType::LESSER) {
        insert(data, &(*node)->left);  // recurse down the tree to the left
    } 
    else if (data->item.compareTo((*node)->item) == ItemType::GREATER) {
        insert(data, &(*node)->right); // recurse down the tree to the right
    }
};

void BinaryTree::deleteItem(ItemType & item) {
    deleteRecurse(item, &this->root); // recursively delete the node
};

void BinaryTree::deleteRecurse(ItemType & item, Node ** node) { // more fun with double pointers
    if (*node != NULL) {                            // handle root & leaf cases
        if (item.compareTo((*node)->item) == ItemType::LESSER) {
            deleteRecurse(item, &((*node)->left));  // recurse down to left
        }
        else if (item.compareTo((*node)->item) == ItemType::GREATER) {
            deleteRecurse(item, &((*node)->right)); // recurse down to right 
        }
        else {                                      // node found
            Node * temp; // two children
            if ((*node)->left != NULL && (*node)->right != NULL) {
                Node * min = findMinimum(*node); // find minimum value node
                (*node)->item = min->item;       // swap node values
                temp = min;                      // set min node to be deleted
            }     
            else {
                temp = *node;
                if ((*node)->left != NULL) {  // one child on left branch
                    *node = (*node)->left;    // connect parent to grandchild
                }
                if ((*node)->right != NULL) { // one child on right branch
                    *node = (*node)->right;   // connect parent to grandchild
                }
                else {
                    *node = NULL;             // leaf node, just remove
                }
            }
            this->count--; // decrement node count
            delete temp;   // delete node
        }
    }
};

/**
 * Finds the minimum valued node on any given subtree.
 */
Node * BinaryTree::findMinimum(Node * node) {
    if (node->left == NULL) { // check if there is a lesser node
        return node;
    }
    else {                    // recurse to lesser node
        return findMinimum(node->left);
    }
};

void BinaryTree::retrieve(ItemType & item, bool & found) const {
    found = retrieveRecurse(item, this->root); // recursively attempt to find node
};

bool BinaryTree::retrieveRecurse(ItemType & item, Node * node) const {
    if (node != NULL) { // check if node exists
        if (item.compareTo(node->item) == ItemType::LESSER) {
            return retrieveRecurse(item, node->left);
        }               // node is greater than wanted value
        if (item.compareTo(node->item) == ItemType::GREATER) {
            return retrieveRecurse(item, node->right);
        }               // node is lesser than wanted value
        return true;    // node with value found
    }
    return false;       // null node, value does not exist in tree
};

void BinaryTree::clear() {
    clearNode(this->root); // recursively delete all nodes
    this->root = NULL;     // reset the root to null
    this->count = 0;       // specify that there are zero nodes in the tree
};

void BinaryTree::clearNode(Node * node) {
    if (node != NULL) {    // iterate down all possible branches
        clearNode(node->left);
        clearNode(node->right);
    }
    delete node;           // delete parent node
};

void BinaryTree::preOrder() const {
    preOrderRecurse(this->root); // recursively follow tree pre order
    cout << endl;
};

void BinaryTree::preOrderRecurse(Node * node) const {
    if (node != NULL) {                         // check if there is a node
        cout << node->item.getValue() << + " "; // print value of the node
        preOrderRecurse(node->left);            // recurse down left branch
        preOrderRecurse(node->right);           // recurse down right branch
    }
};

void BinaryTree::postOrder() const {
    postOrderRecurse(this->root); // recursively follow tree post order
    cout << endl;
};

void BinaryTree::postOrderRecurse(Node * node) const {
    if (node != NULL) {                         // check if there is a node
        postOrderRecurse(node->left);           // recurse down left branch
        postOrderRecurse(node->right);          // recurse down right branch
        cout << node->item.getValue() << + " "; // then print value of the node
    }
};

void BinaryTree::inOrder() const {
    inOrderRecurse(this->root); // recursively follow tree in order
    cout << endl;
};

void BinaryTree::inOrderRecurse(Node * node) const {
    if (node != NULL) {                         // check if there is a node
        inOrderRecurse(node->left);             // recurse down left branch
        cout << node->item.getValue() << + " "; // print value of the node
        inOrderRecurse(node->right);            // finally recurse down the right
    }
};

ostream & operator<<(ostream & stream, const BinaryTree & tree) {
    tree.ostreamRecurse(stream, tree.root); // request ostream of tree in order
    return stream;
};

/**
 * Same effect as the inOrderRecurse function, but produces a stream rather
 * than printing directly to cout.
 */
void BinaryTree::ostreamRecurse(ostream & stream, Node * node) const {
    if (node != NULL) {
        ostreamRecurse(stream, node->left);
        stream << node->item.getValue() << + " ";
        ostreamRecurse(stream, node->right);
    }
};
