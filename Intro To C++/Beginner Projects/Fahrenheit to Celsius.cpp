//Fahrenheit to Celsius
#include <iostream>
using namespace std;

int main() {
    float f, c;
    cout << "Input degrees Farenheit\n";
    cin >> f;

    // Subtract 32, multiply by 5 and divide by 9
    c = (f - 32)*5/9;
    cout << c;
    return 0;
}