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
     factor2 = 0;
     factor1 = number;
     int b = number/2;
     if (b>10){
         b = 10;
     }
    for ( int i = 1; i <b ; ++i ) {
        if (number%i == 0 ){
            if (number/i <= factor1){
                factor1 = number/i;
                factor2 = i;
            }
        }

    }
     cout << number << " = "<< factor2 << " * " << factor1 << endl ;

    // Write your code here
    }

    return 0;
}

