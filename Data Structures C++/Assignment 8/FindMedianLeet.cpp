#include <queue>
using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxHeap; // stores the smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // stores the larger half
    
public:    
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        return (maxHeap.size() > minHeap.size())? maxHeap.top() : (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

#include <iostream>
#include <cassert>

int main() {
    // Test Case 1: Adding numbers in ascending order
    MedianFinder mf1;
    mf1.addNum(1);
    mf1.addNum(2);
    mf1.addNum(3);
    assert(mf1.findMedian() == 2.0);

    // Test Case 2: Adding numbers in descending order
    MedianFinder mf2;
    mf2.addNum(3);
    mf2.addNum(2);
    mf2.addNum(1);
    assert(mf2.findMedian() == 2.0);

    // Test Case 3: Adding alternating numbers
    MedianFinder mf3;
    mf3.addNum(1);
    mf3.addNum(5);
    mf3.addNum(2);
    mf3.addNum(6);
    assert(mf3.findMedian() == 3.5);

    // Test Case 4: Adding negative numbers
    MedianFinder mf4;
    mf4.addNum(-1);
    mf4.addNum(-5);
    mf4.addNum(-2);
    mf4.addNum(-6);
    assert(mf4.findMedian() == -3.5);

    std::cout << "All test cases passed." << std::endl;

    return 0;
}
