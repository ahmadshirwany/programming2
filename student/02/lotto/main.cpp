#include <iostream>

using namespace std;
unsigned long int fictorial(int f){
    unsigned long int a = 1;
    for ( int i = 1; i <= f ; ++i ) {
        a = a*i;
    }
    return a;
}
unsigned long  foo(int n, int p ){
      unsigned long  x = fictorial(n)/(fictorial(n-p)* fictorial(p));
      return x;
}

int main()
{
    int a,b;
    cout<<"Enter the total number of lottery balls:";
    cin >> a;
    cout<<"Enter the number of drawn balls:";
    cin >> b;
    if(a<=0 or b <= 0 ){
        cout <<"The number of balls must be a positive number."<<endl;
        return 0;
    }
    else if (b>a){
         cout<< "the maximum number of drwan balls is the total ammount of balls."<<endl;
         return 0;
    }
    else {
    unsigned long  c = foo(a,b);
    cout<<"The probability of guessing all "<<b<<" balls correctly is 1/"<< c<<endl;


    return 0;
}
}
