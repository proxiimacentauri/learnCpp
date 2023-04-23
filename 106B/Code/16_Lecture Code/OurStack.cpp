/******************************************************************************
 * File: OurStack.cpp
 *
 * Implementation (.cpp) file for OurStack.
 */

#include "OurStack.h"
#include "error.h"

/* Constant controlling the default size of our stack. */
const int kInitialSize = 4;

/* Constructor initializes the fields of the stack to
 * appropriate defaults.
 */
OurStack::OurStack() {
    logicalSize = 0;
    allocatedSize = kInitialSize;
    elems = new int[allocatedSize];
}

/* Destructor cleans up memory. */
OurStack::~OurStack() {
    delete[] elems;
}

int OurStack::size() const {
    return logicalSize;
}

bool OurStack::isEmpty() const {
    return size() == 0;
}

void OurStack::push(int value) {
    /* Out of space? */
    if (allocatedSize == logicalSize) {
        grow();
    }

    /* Add the element. */
    elems[logicalSize] = value;
    logicalSize++;
}

void OurStack::grow() {
    allocatedSize *= 2; // Double size; runs efficiently!
    int* helper = new int[allocatedSize];

    /* Copy everything over. */
    for (int i = 0; i < logicalSize; i++) {
        helper[i] = elems[i];
    }

    delete[] elems;
    elems = helper;
}

int OurStack::peek() const {
    /* Nothing here? */
    if (isEmpty()) {
        error("That which is not cannot be!");
    }

    return elems[logicalSize - 1];
}

int OurStack::pop() {
    int result = peek();
    logicalSize--;
    return result;
}
