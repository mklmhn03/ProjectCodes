#include <queue>
#include <iostream>
#include <cassert>

class MyStack {
private:
    std::queue<int> q;
    
public:
    MyStack() {}
    
    void push(int x) {
        q.push(x);
        int size = q.size();
        for (int i = 0; i < size - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int topElement = q.front();
        q.pop();
        return topElement;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

int main() {
    MyStack stack;
    
    // Test Case 1: Pushing and Popping
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.top() == 3); // Top element should be 3
    assert(stack.pop() == 3); // Pop should return 3
    assert(stack.top() == 2); // Top element should now be 2
    
    // Test Case 2: Empty Stack
    assert(!stack.empty());   // Stack should not be empty after pushes
    stack.pop();
    stack.pop();
    assert(stack.empty());    // Stack should be empty after all pops
    
    // Test Case 3: Edge Case - Pushing and Popping Zero
    stack.push(0);
    assert(stack.top() == 0); // Top element should be 0
    assert(stack.pop() == 0); // Pop should return 0
    
    // Test Case 4: Edge Case - Pushing Negative Numbers
    stack.push(-1);
    stack.push(-2);
    assert(stack.top() == -2); // Top element should be -2
    assert(stack.pop() == -2); // Pop should return -2
    
    // Test Case 5: Edge Case - Empty Stack Pop
    assert(!stack.empty());   // Stack should not be empty
    assert(stack.pop() == -1); // Pop should return -1 (default int value)
    assert(stack.empty()); // Stack should be empty

    std::cout << "All test cases passed!" << std::endl;
    
    return 0;
}