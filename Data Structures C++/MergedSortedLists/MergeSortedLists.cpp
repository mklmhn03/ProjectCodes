#include <iostream>
#include <cassert>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    void deleteList() {
        ListNode* current = this;
        ListNode* temp;
        while (current) {
            temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) return list2;
        if (!list2) return list1;

        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};


int main() {
    Solution solution;

    // Test Case 1: Both lists are empty
    assert(solution.mergeTwoLists(nullptr, nullptr) == nullptr);

    // Test Case 2: One of the lists is empty
    ListNode* list1 = new ListNode(1);
    ListNode* result1 = solution.mergeTwoLists(list1, nullptr);
    assert(result1->val == 1);
    assert(result1->next == nullptr);

    // Test Case 3: Both lists have only one element
    ListNode* list2 = new ListNode(2);
    ListNode* result2 = solution.mergeTwoLists(list1, list2);
    assert(result2->val == 1);
    assert(result2->next->val == 2);
    assert(result2->next->next == nullptr);

    // Test Case 4: One list is longer
    list1 = new ListNode(1, new ListNode(3, new ListNode(5)));
    list2 = new ListNode(2, new ListNode(4));
    ListNode* result3 = solution.mergeTwoLists(list1, list2);
    assert(result3->val == 1);
    assert(result3->next->val == 2);
    assert(result3->next->next->val == 3);
    assert(result3->next->next->next->val == 4);
    assert(result3->next->next->next->next->val == 5);
    assert(result3->next->next->next->next->next == nullptr);

    // Test Case 5: Both lists have the same values
    list1 = new ListNode(1, new ListNode(1, new ListNode(1)));
    list2 = new ListNode(1, new ListNode(1, new ListNode(1)));
    ListNode* result4 = solution.mergeTwoLists(list1, list2);
    assert(result4->val == 1);
    assert(result4->next->val == 1);
    assert(result4->next->next->val == 1);
    assert(result4->next->next->next->val == 1);
    assert(result4->next->next->next->next->val == 1);
    assert(result4->next->next->next->next->next->val == 1);
    assert(result4->next->next->next->next->next->next == nullptr);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}