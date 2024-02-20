#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Function to check if parentheses are balanced
bool areParanthesisBalanced(string expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        }
        else {
            if (s.empty()) return false;
            
            char top = s.top();
            if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{')) {
                s.pop();
            }
            else return false;
        }
    }
    return s.empty();
}

int main() {
    vector<string> parans = {"{()}[]", "[[", "))", "{[()]}", "({[])}"};
    for (auto expr : parans) {
        if (areParanthesisBalanced(expr))
            cout << "Balanced" << endl;
        else
            cout << "Not Balanced" << endl;
    }
    return 0;
}
