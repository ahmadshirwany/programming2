#include <iostream>

using namespace std;

int main()
{
    int number = 0;

    cout << "Enter a positive number: ";
    cin >> number;
    if (number <1){
        cout << "Only positive numbers accepted" << endl;
    }
    else{
     int factor1, factor2;
     factor2 = number;
     factor1 = 0;
    for ( int i = 1; i <number+1 ; ++i ) {
        if (number%i == 0 ){
            if (number/i >= factor2){
                factor1 = number/i;
                factor2 = i;
            }
        }

    }
     cout << number << " = "<< factor1 << " * " << factor2 << endl ;

    // Write your code here
    }

    return 0;
}

