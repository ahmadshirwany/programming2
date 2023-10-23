#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
          int length = s.length();
              // Base case: If the string has one character or is empty, it's a palindrome.
              if (length <= 1) {
                  return true;
              }

              // Check if the first and last characters are the same.
              if (s[0] == s[length - 1]) {
                  // Recursively check the substring without the first and last characters.
                  return palindrome_recursive(s.substr(1, length - 2));
              } else {
                  return false;
              }
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
