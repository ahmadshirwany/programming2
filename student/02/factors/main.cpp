#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a positive number: ";
    cin >> number;
    for ( int i = 3; i <= number; ++i ) {
        if (number%i == 0 && number/i < 10){
            cout << number << " = "<< number/i << " * " << i << endl ;
            break;
        }

    }

    // Write your code here

    return 0;
}
