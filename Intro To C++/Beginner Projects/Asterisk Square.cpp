/*
Write a function that displays at the left margin of the screen a solid square of 
asterisks whose
side is specified in integer parameter side. For example, if side is 4, the 
function displays the following
****
****
****
****
Print an invalid input message if side is negative.
*/
#include <iostream>
using namespace std;
void displaySquare(int side) {
    if (side < 0) {
        cout << "Invalid, positive integers only.";
    }
    else{
        for (int i = 0; i < side; i++) {
            for (int j = 0; j < side; j++) {
                cout << "*";
            }
            cout << endl;
        }
    }
}
int main() {
    // Test
    displaySquare(4);
    cout << endl;
    displaySquare(5);
    cout << endl;
    displaySquare(0);
    cout << endl;
    displaySquare(-4);
}