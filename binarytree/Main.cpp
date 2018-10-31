/** 
 * @brief Main file to demonstrate the BinaryTree.
 *
 * Contains various functions to neatly display and interact with the
 * tree that has been created for the assignment. In addition to single
 * commands as specified by the assignment, chained commands are also possible.
 *
 * @author Jennifer Teissler
 */

#include <cstdlib>
#include "BinaryTree.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using std::ifstream;

typedef unsigned short ushort;

void clearTree(BinaryTree &);
void deleteValue(BinaryTree &);
void listCommands();
void insertValue(BinaryTree &);
void printLength(BinaryTree &);
void printPreOrder(BinaryTree &);
void printPostOrder(BinaryTree &);
void printInOrder(BinaryTree &);
void retrieveValue(BinaryTree &);
void information();
void clearScreen();
void drawLine();
char awaitCommandInput();
int awaitValueInput();

int main(int argc, char * argv[]) {
    BinaryTree tree;        // initialize the tree
    clearScreen();          // setup screen
    drawLine();
    information();
    cout << endl;

    if (argc > 2) {         // attempt to read in elements from arguments
        for (int i = 1; i < argc; ++i) {
            try {           // just skip and silently fail any invalid inputs
                ItemType data(stoi(argv[i]));
                tree.insertItem(data);
            }
            catch(...) { }
        }                   // display loaded arguments (if any)
        cout << "TREE LOADED FROM ARGUMENTS" << endl << tree << endl;
    }
    else if (argc == 2) {   // attempt to read in elements from file
        ifstream file;
        file.open(argv[1]); // open the file

        if (file) {         // check to make sure file opened
            int input;
                            // read all elements from file
            while (file >> input) {
                ItemType data(input);
                tree.insertItem(data);
            }
        }

        file.close();       // close file and display loaded arguments (if any)
        cout << "TREE LOADED FROM FILE '" << argv[1] << "'" << endl << tree << endl;
    }
    else {                  // no preloading of arguments
        cout << "NO TREE LOADED" << endl;
    }

    cout << endl;           // setup screen
    listCommands();
    cout << endl;
    bool run = true;        // create a run flag to keep the program running
    
    while (run) {           // loop and await command input
        drawLine();
        cout << "Enter a command letter: ";
                            
        switch(awaitCommandInput()) {
            case 'c': clearTree(tree);
                      break;
            case 'd': deleteValue(tree);
                      break;
            case 'h': listCommands();
                      break;
            case 'i': insertValue(tree);
                      break;
            case 'l': printLength(tree);
                      break;
            case 'p': printPreOrder(tree);
                      break;
            case 'o': printPostOrder(tree);
                      break;
            case 'n': printInOrder(tree);
                      break;
            case 'q': run = false;
                      break;
            case 'r': retrieveValue(tree);
                      break;
            case 'z': information();
                      break;
            default:  cout << "Type 'h' for a list of commands." << endl;
        }
    }

    cout << "program exit" << endl;
    drawLine();
    return EXIT_SUCCESS;    // end program
};

/**
 * Executes the clear operation on the tree.
 */
void clearTree(BinaryTree & tree) {
    cout << "Tree Cleared" << endl;
    tree.clear();
}

/**
 * Executes the delete item operation on the tree.
 */
void deleteValue(BinaryTree & tree) {
    cout << tree << endl << "Enter a value to delete: ";
    ItemType data(awaitValueInput());
    tree.deleteItem(data);
    cout << tree << endl;
}

/**
 * Displays a help screen.
 * Lists commands, as well as providing info on chained commands.
 */
void listCommands() {
    cout << "\e[1m[COMMANDS]\e[0m" << endl;
    cout << "[c] Clear Tree" << endl;
    cout << "[d] Delete Value" << endl;
    cout << "[h] List Commands" << endl;
    cout << "[i] Insert Value" << endl;
    cout << "[l] Print Length" << endl;
    cout << "[n] Print Tree In Order" << endl;
    cout << "[o] Print Tree Post Order" << endl;
    cout << "[p] Print Tree Pre Order" << endl;
    cout << "[q] Quit Program" << endl;
    cout << "[r] Retrieve Value" << endl;
    cout << "[z] Information" << endl << endl;
    cout << "\e[1m[Note]\e[0m Commands may be chained together for complex operations." << endl;
    cout << "       While running chained commands, input sanitization and " << endl;
    cout << "       legible command output will not be maintained." << endl;
    cout << "  \e[1m[Ex]\e[0m Input 'ci1i2i3i4' results in Tree '1 2 3 4'." << endl;
}

/**
 * Executes the insert item operation on the tree.
 */
void insertValue(BinaryTree & tree) {
    cout << "Enter a value to insert: ";
    ItemType data(awaitValueInput());
    tree.insertItem(data);
    cout << tree << endl;
}

/**
 * Retrieves the length of the tree.
 */
void printLength(BinaryTree & tree) {
    cout << "Tree Length = " << tree.length() << endl;
}

/**
 * Prints the tree pre order.
 */
void printPreOrder(BinaryTree & tree) {
    tree.preOrder();
}

/**
 * Prints the tree post order.
 */
void printPostOrder(BinaryTree & tree) {
    tree.postOrder();
}

/**
 * Prints the tree in order.
 */
void printInOrder(BinaryTree & tree) {
    tree.inOrder();
}

/**
 * Searches for a specific value with the search operation,
 * and notifies the user if the value is not found.
 */
void retrieveValue(BinaryTree & tree) {
    cout << "Enter a value to search for: ";
    ItemType data(awaitValueInput());
    bool exists;
    tree.retrieve(data, exists);

    if (exists) {
        cout << "Value Found In Tree" << endl;
    }
    else {
       cout << "Value Not Found In Tree" << endl; 
    }
}

/**
 * Provides basic information about the program.
 */
void information() {
    cout << "\e[1m" << "CSCI 2720 Data Structures" << endl;
    cout << "Assignment 2 - BinaryTree" << endl;
    cout << "Author - Jennifer Teissler" << endl;
    cout << "Date - October 29, 2018" << "\e[0m" << endl;
}

/**
 * Clears the current terminal screen by printing a number of
 * newlines equal to the current height of the terminal.
 */
void clearScreen() {
    struct winsize size; 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);   // get screen height

    for (ushort i = 0; i < size.ws_row; ++i) { // clear screen
        cout << endl;
    }
}

/**
 * Draws a line across the width of the screen by outputting a
 * number of characters equal to the current width of the terminal.
 */
void drawLine() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);   // get screen width

    for (ushort i = 0; i < size.ws_col; ++i) { // draw line
        cout << "\u2505";
    }
    cout << endl;
}

/**
 * Prompts user for valid command input.
 */
char awaitCommandInput() {
    char input;
    cin >> input;  // read from input

    while (!cin) { // retry until input is valid
        cin.clear();
        cin.ignore(200, '\n');
        cin >> input;
    }
    return input;  // return valid input;
}

/**
 * Prompts user for valid integer input.
 */
int awaitValueInput() {
    int input;
    cin >> input;  // read from input

    while (!cin) { // retry until input is valid
        input = 0;
        cin.clear();
        cin.ignore(200, '\n');
        cin >> input;
    }
    return input;  // return valid input
}
