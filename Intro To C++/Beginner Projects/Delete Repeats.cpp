#include <iostream>
#include <vector>

using namespace std;

vector<int> deleteRepeats(const vector<int>& nums); // Declaration
void print(const vector<int>& nums);

int main() {
    vector<int> nums;
    vector<int> res;
    // Test 1
    nums = {1, 2, 3, 3, 2};
    res = deleteRepeats(nums);
    print(res); // Should print 1, 2, 3
    // Test 2
    nums = {-1, 2, 4};
    res = deleteRepeats(nums); 
    print(res); // Should print -1, 2, 4
    // Test 3
    nums = {42, 42, 42,};
    res = deleteRepeats(nums); 
    print(res); // Should print 42
    // Test 4
    nums = {};
    res = deleteRepeats(nums); 
    print(res); // Should print a blank

    return 0;
}

vector<int> deleteRepeats(const vector<int>& nums) {
    vector<int> res;
    bool foundRepeat = false;
    // Your code here
    for (auto& num: nums) { //auto& automatically sets datatype
        for (auto& test: res) {
            if (num == test) foundRepeat = true;
        }
        if (!foundRepeat) {
            res.push_back(num);
            foundRepeat = false;
        }
    }
 

    return res;
}

void print(const vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    cout << endl;
}