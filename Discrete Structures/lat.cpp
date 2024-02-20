#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Function to calculate factorial
long double facto(int n) {
    long double fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n;
    cout << "Enter the size of the grid (n >= 1): ";
    n = 20;
    cin >> n;

    //Check if input is valid
    if (n < 1) {
        cout << "Invalid input. Please enter a positive integer greater than or equal to 1." << endl;
        return 0;
    }
    long double r = facto(n*2)/(facto(n)*facto(n));

    //Calculate number of routes
    cout << "Number of routes in a " << n << "x" << n << " grid: " << r << endl;

    return 0;
}
