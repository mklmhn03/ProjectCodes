// Write a function that returns a hashtable of the word count of an input string.
// For example, if the string is - "listen then repeat listen then repeat"
// Output - {then:2, repeat:2, listen:2}
// Note that the output words could be in any order


#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

unordered_map<string, int> wordCount(string& str) {
    unordered_map<string, int> si;
    stringstream ss(str);
    string temp;
    while (ss >> temp) {
        if (si.find(temp) == si.end()) si[temp] = 1;
        else si[temp]++;
	}
    return si;
}

// Test
int main() {
    string s;
    unordered_map<string, int> table;
    // Test 1
    s = "listen then repeat listen then repeat";
    table = wordCount(s);
    for (auto& ele : table)
        cout << ele.first << ":" << ele.second << " ";
    cout << endl;
    // Test 2
    s = "that that is is that that is not is not";
    table = wordCount(s);
    for (auto& ele : table)
        cout << ele.first << ":" << ele.second << " ";
    cout << endl;
    system("pause");
}