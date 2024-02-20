#include <iostream>
#include <unordered_map>
using namespace std;

bool isAnagram(string s1, string s2) {
    if (s1.length() != s2.length() || s1.empty()) return false; // If lengths are different or empty

    unordered_map<char, int> charCount;

    // Count characters in string s1
    for (char c : s1) {
        charCount[c]++;
    }

    // Decrement character counts for string s2
    for (char c : s2) {
        if (charCount.find(c) == charCount.end() || charCount[c] == 0) {
            return false; // If character not found or count is already zero, they can't be anagrams
        }
        charCount[c]--;
    }

    return true;
}

int main() {
    string s1 = "anagram";
    string s2 = "nagaram";
    if (isAnagram(s1, s2)) cout << "True" << endl;
    else cout << "False" << endl;

    s1 = "rat";
    s2 = "car";
    if (isAnagram(s1, s2)) cout << "True" << endl;
    else cout << "False" << endl;
}
