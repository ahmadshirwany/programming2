#include "array_operations.hh"
#include <algorithm>

int greatest_v1(int* itemptr, int size) {
    // Using std::max_element to find the greatest element
    return *std::max_element(itemptr, itemptr + size);
}

int greatest_v2(int* itemptr, int* endptr) {
    // Using std::max_element to find the greatest element
    return *std::max_element(itemptr, endptr);
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    // Using std::copy to copy elements from itemptr to targetptr
    std::copy(itemptr, endptr, targetptr);
}

void reverse(int* leftptr, int* rightptr) {
    // Using std::reverse to reverse elements in the range [leftptr, rightptr)
    std::reverse(leftptr, rightptr);
}
