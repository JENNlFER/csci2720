/** 
 * @brief Main file to demonstrate the SortedLinkedList.
 *
 * Contains various functions to neatly display and interact with the
 * list that has been created for the assignment. In addition to single
 * commands as specified by the assignment, chained commands are also possible.
 *
 * @author Jennifer Teissler
 */

#include <cstdlib>
#include "SortedLinkedList.h"
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

void pairwiseSwap(SortedLinkedList &);
void clearList(SortedLinkedList &);
void deleteValue(SortedLinkedList &);
void listCommands();
void insertValue(SortedLinkedList &);
void printLength(SortedLinkedList &);
void printList(SortedLinkedList &);
void searchValue(SortedLinkedList &);
void information();
void clearScreen();
void drawLine();
char awaitCommandInput();
int awaitValueInput();

int main(int argc, char * argv[]) {
    SortedLinkedList list;  // initialize the list
    clearScreen();          // setup screen
    drawLine();
    information();
    cout << endl;

    if (argc > 2) {         // attempt to read in elements from arguments
        for (int i = 1; i < argc; ++i) {
            try {           // just skip and silently fail any invalid inputs
                DataType data(stoi(argv[i]));
                list.insertItem(data);
            }
            catch(...) { }
        }                   // display loaded arguments (if any)
        cout << "LIST LOADED FROM ARGUMENTS" << endl << list << endl;
    }
    else if (argc == 2) {   // attempt to read in elements from file
        ifstream file;
        file.open(argv[1]); // open the file

        if (file) {         // check to make sure file opened
            int input;
                            // read all elements from file
            while (file >> input) {
                DataType data(input);
                list.insertItem(data);
            }
        }

        file.close();       // close file and display loaded arguments (if any)
        cout << "LIST LOADED FROM FILE '" << argv[1] << "'" << endl << list << endl;
    }
    else {                  // no preloading of arguments
        cout << "NO LIST LOADED" << endl;
    }

    cout << endl;           // setup screen
    listCommands();
    cout << endl;
    bool run = true;        // create a run flag to keep the program running
    
    while (run) {           // loop and await command input
        drawLine();
        cout << "Enter a command letter: ";
                            
        switch(awaitCommandInput()) { 
            case 'b': pairwiseSwap(list);
                      break;
            case 'c': clearList(list);
                      break;
            case 'd': deleteValue(list);
                      break;
            case 'h': listCommands();
                      break;
            case 'i': insertValue(list);
                      break;
            case 'l': printLength(list);
                      break;
            case 'p': printList(list);
                      break;
            case 'q': run = false;
                      break;
            case 's': searchValue(list);
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
 * Executes the pairwise swap operation on the list.
 */
void pairwiseSwap(SortedLinkedList & list) {
    cout << "Before Swap" << endl << list << endl;
    list.pairwiseSwap();
    cout << "After Swap" << endl << list << endl;
}

/**
 * Executes the clear operation on the list.
 */
void clearList(SortedLinkedList & list) {
    cout << "List Cleared" << endl;
    list.clear();
}

/**
 * Executes the delete item operation on the list.
 */
void deleteValue(SortedLinkedList & list) {
    cout << list << endl << "Enter a value to delete: ";
    DataType data(awaitValueInput());
    list.deleteItem(data);
    cout << list << endl;
}

/**
 * Displays a help screen.
 * Lists commands, as well as providing info on chained commands.
 */
void listCommands() {
    cout << "\e[1m[COMMANDS]\e[0m" << endl;
    cout << "[b] Pairwise Swap" << endl;
    cout << "[c] Clear List" << endl;
    cout << "[d] Delete Value" << endl;
    cout << "[h] List Commands" << endl;
    cout << "[i] Insert Value" << endl;
    cout << "[l] Print Length" << endl;
    cout << "[p] Print List" << endl;
    cout << "[q] Quit Program" << endl;
    cout << "[s] Search Value" << endl;
    cout << "[z] Information" << endl << endl;
    cout << "\e[1m[Note]\e[0m Commands may be chained together for complex operations." << endl;
    cout << "       While running chained commands, input sanitization and " << endl;
    cout << "       legible command output will not be maintained." << endl;
    cout << "  \e[1m[Ex]\e[0m Input 'ci1i2i3i4b' results in list '2 1 4 3'." << endl;
}

/**
 * Executes the insert item operation on the list.
 */
void insertValue(SortedLinkedList & list) {
    cout << "Enter a value to insert: ";
    DataType data(awaitValueInput());
    list.insertItem(data);
    cout << list << endl;
}

/**
 * Retrieves the length of the list.
 */
void printLength(SortedLinkedList & list) {
    cout << "List Length = " << list.length() << endl;
}

/**
 * Prints the list.
 */
void printList(SortedLinkedList & list) {
    cout << list << endl;
}

/**
 * Searches for a specific value with the search operation,
 * and notifies the user if the value is not found.
 */
void searchValue(SortedLinkedList & list) {
    cout << "Enter a value to search for: ";
    DataType data(awaitValueInput());
    int index = list.search(data);

    if (index == -1) {
        cout << "Value Not Found" << endl;
    }
    else {
        cout << "Value At Index = " << index << endl;
    }
}

/**
 * Provides basic information about the program.
 */
void information() {
    cout << "\e[1m" << "CSCI 2720 Data Structures" << endl;
    cout << "Assignment 1 - SortedLinkedList" << endl;
    cout << "Author - Jennifer Teissler" << endl;
    cout << "Date - October 1, 2018" << "\e[0m" << endl;
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
