#include <cassert>
#include <unordered_map>
#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    if (!head || !head->next) {
        return false;
    }

    ListNode *slow = head;
    ListNode *fast = head->next;

    while (slow != fast) {
        if (!fast || !fast->next) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

int main() {
    // Test Case 1: Cycle starting from index 1
    ListNode *head1 = new ListNode(3);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);
    head1->next->next->next->next = head1->next; // Creating a cycle
    assert(hasCycle(head1) == true);

    // Test Case 2: Cycle starting from index 0
    ListNode *head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = head2; // Creating a cycle
    assert(hasCycle(head2) == true);

    // Test Case 3: Single node, no cycle
    ListNode *head3 = new ListNode(1);
    assert(hasCycle(head3) == false);

    // Test Case 4: Empty list
    ListNode *head4 = nullptr;
    assert(hasCycle(head4) == false);

    // Test Case 5: Large cycle
    ListNode *head5 = new ListNode(1);
    ListNode *current = head5;
    for(int i = 2; i <= 10000; i++) {
        current->next = new ListNode(i);
        current = current->next;
    }
    current->next = head5; // Creating a large cycle
    assert(hasCycle(head5) == true);

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}
