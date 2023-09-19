#include <iostream>

using namespace std;

int main()
{
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    if (number > 0){
        int cube = number * number * number;
        if (cube/number/number ==  number){
            std::cout << "The cube of "<<number<<" is "<< cube <<"."<<endl;
        }
        else {
                std::cout << "Error! The cube of "<<number<<" is not "<< cube<<"." <<endl;
            }

    }
    else{
        std::cout << "The cube of "<<number<<" is "<< number<<"." <<endl;
    }
    return 0;
}
