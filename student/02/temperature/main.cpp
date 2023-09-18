#include <iostream>

using namespace std;

int main()
{
    int temperature = 0;
    double fahrenheit , celsius;
    cout << "Enter a temperature: ";
    cin >> temperature;
    fahrenheit = (temperature * 9.0 / 5) + 32;
    celsius = (temperature - 32) * 5.0 / 9;
    cout << temperature << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit  is " << celsius << " degrees Celsius" << endl;

    // Write your code here

    return 0;
}
