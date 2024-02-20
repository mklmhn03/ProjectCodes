#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 10;

int main() {
	
	// Static array
	int nums[SIZE]; // Array declaration

	// Write to elements of array
	for (int i = 0; i < SIZE; i++) {
		nums[i] = i*i;
	}

	// Read elements of array
	for (int i = 0; i < SIZE; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;

	// 2D arrays
	const int nRows = 3;
	const int nCols = 3;
	int grid[nRows][nCols]; 
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			if (i == j) {
				grid[i][j] = 1;
			} else {
				grid[i][j] = 0;
			}
		}
	}

	// Print 2D array
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}

	// Dynamic arrays - needed array sizes need to change at run time
	int cap = 4;
	string* names = new string[cap]; // new allocates memory on heap storage, and returns a pointer
	string n("");
	int count = 0;
	while (n.compare("Quit") != 0){
		cout << "Enter a name" << endl;
		cin >> n;
		if (n.compare("Quit") != 0) {
			if (count >= cap) { // Need to extend the array
				cout << "Extending array" << endl;
				string* oldNames = names; // Save pointer to old array
				names = new string[2*cap]; // Allocate new array
				for (int i = 0; i < cap; i++) { // Copy elements over
					names[i] = oldNames[i];
				}
				delete []oldNames; // Deallocate old array
				cap = 2*cap; // Update capacity
			}
			names[count] = n;
			count++;
		}
	}

	// Print out array
	cout << endl << "Printing Array" << endl;
	for (int i = 0; i < cap; i++) {
		cout << names[i] << endl;
	}
		

}