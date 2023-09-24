#include <cstdlib>
#include <iostream>

// Write your swap function here.


void swap(int const& param1, int const& param2) {
    (void)(param1 * 2);
    (void)(param2 + 1.0);
}
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
