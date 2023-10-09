#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <vector>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
         if (!(word.length() <= 2)) {
             std::string mixed_word = word.substr(0, 1); // Keep the first letter

             // Generate a random permutation of the middle letters
             std::string middle = word.substr(1, word.length() - 2);
             std::random_device rd;
             std::mt19937 g(rd()); // Standard mersenne_twister_engine
             std::shuffle(middle.begin(), middle.end(), g);

             mixed_word += middle;

             mixed_word += word[word.length() - 1];

             std::cout << mixed_word << std::endl;

         }else{
	
        std::cout << word << std::endl;
         }
    }
}
