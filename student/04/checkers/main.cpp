#include "gameboard.hh"
#include <iostream>
#include "gameboard.hh"
#include <sstream>
#include <limits>

using namespace std;
bool is_digits(string& str)
{
    for (char ch : str) {
         // ASCII Val converted
        if (ch == ' ') {
                    // Ignore spaces
                    continue;
                }
        if (!(ch >= 48 && ch <= 57)) {

            return false;
        }
    }

    return true;
}

int main()
{
   return 0;
}
