/*************************************************
 * File: LinkedLists.cpp
 *
 * Our very first program using Linked Lists! :-D
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Type: Cell
 *
 * A cell in a linked list.
 */
struct Cell {
    string value;
    Cell* next;
};

/* Creates and returns the linked list from the lecture slides:
 *
 * pudu -> quokka -> dikdik -> (nullptr)
 */
Cell* makeList() {
    Cell* list = new Cell;
    list->value = "pudu!";
    list->next = new Cell;
    list->next->value = "quokka!";
    list->next->next = new Cell;
    list->next->next->value = "dikdik!";
    list->next->next->next = nullptr;
    return list;
}

/* Recursively computes the length of a linked list. */
int lengthOf(Cell* list) {
    /* Option 1: The list could be empty. */
    if (list == nullptr) return 0;

    /* Option 2: We have one cell, followed by one. */
    return 1 + lengthOf(list->next);
}

/* Iteratively prints the contents of a linked list.
 *
 * Great exercise: Rewrite this function recursively!
 */
void printList(Cell* list) {
    while (list != nullptr) {
        cout << list->value << endl;
        list = list->next;
    }
}

/* Frees all the memory used by cells in the linked list. */
void freeList(Cell* list) {
    while (list != nullptr) {
        /* Remember where the next cell in the list is. */
        Cell* next = list->next;

        /* Free the memory for the current cell. */
        delete list;

        /* Advance to the next cell in the list, using the value
         * we stashed away earlier because we can no longer read
         * from list itself.
         */
        list = next;
    }
}

Cell* readList() {
    string text = getLine("Enter next, or RETURN to finish: ");

    /* If the user entered nothing, assume the list is done. */
    if (text == "") return nullptr;

    /* Otherwise: We know what goes in the first cell. Now we
     * ask: what comes next?
     */
    Cell* result  = new Cell;
    result->value = text;
    result->next  = readList();
    return result;
}

int main() {
    Cell* list = readList();
    cout << "This list has " << lengthOf(list) << " items." << endl;
    printList(list);
    freeList(list);
    return 0;
}





























