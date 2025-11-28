//will use the bottom up approach here

//we can think of this as a customer queue, where each have their own priority numbers

//we start with sorted teams of size 1 (a single node is always sorted)

// we will take two teams of size 1, and create the team 2 with the lowest priority number first

//we will merge one member teams into 2 member teams (sorted)

//we will merge 2 member teams into 4 member teams and so on

//here, we will need three pointers, 

//A. get_length(head)We need to know the total length (n) 
//of the queue to determine when to stop doubling the size. This is a simple traversal.



#include <iostream>
using namespace std;


 // Definition for singly-linked list.

struct ListNode {
    int val;
    ListNode *next; //A pointer to the next node in the list. This is the link that chains the nodes together.
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    /**
     * Helper function to get the length of the linked list.
     */
    int get_length(ListNode* head) {
        int len = 0;
        ListNode* curr = head;
        while (curr != nullptr) {
            len++;
            curr = curr->next;
        }
        return len;
    }

    //Helper function for splitting, we cannot split a linked list like an array
    // for this we need to severe it from the root

    ListNode* split_and_cut(ListNode* head, int size) {
        if (!head) return nullptr;

        ListNode* curr = head;
        // Move (size - 1) steps to the tail of the first segment
        for (int i = 1; i < size && curr->next; ++i) {
            curr = curr->next;
        }

        // 'next_head' is the start of the second segment (list2)
        ListNode* next_head = curr->next;
        
        // cutting THE LINK
        curr->next = nullptr; 
        
        // Return the head of the second segment
        return next_head;
    }

    
    ListNode* merge_and_connect(ListNode* prev_tail, ListNode* l1, ListNode* l2) {
        
        // 'tail' will track the end of the currently merged list section
        ListNode* tail = prev_tail; 

        //this uses the fact that the customer with the least priority number will be placed first
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        //when the while loop finishes, at least one of the lists is empty, the rest are already sorted
        
        if (l1) {
            tail->next = l1;
        } else {
            tail->next = l2;
        }

        // Traverse to the end of the newly merged section to find the true tail
        while (tail->next) {
            tail = tail->next;
        }

        // Return the new tail (to be used as 'prev_tail' in the next merge)
        return tail;
    }


   public:
    ListNode* sortList(ListNode* head) {

        //If the list has only one node or is empty, then it will return the base case
        if (!head || !head->next) {
            return head;
        }

        //calling the helper function to get the length of the list
        int len = get_length(head);
        
        // A Dummy Head node simplifies the process of connecting merged lists
        ListNode dummy_head(0);
        dummy_head.next = head;

        //created a dummy head because it acts as a temporary node at first

        // Loop for the merge size (1, 2, 4, 8, ... up to length)
        //size*2 cuz we double up the size to even numbers till the length 

        for (int size = 1; size < len; size *= 2) {
            
            // 'tail' points to the end of the list that is already sorted/merged
            ListNode* tail = &dummy_head;
            
            // 'curr' starts at the beginning of the list to be processed
            ListNode* curr = dummy_head.next;

            // Inner loop: Traverse the list, merging adjacent sub-lists of 'size'
            while (curr) {
                // 1. Get List 1 (size 'size')
                ListNode* list1 = curr;
                ListNode* list2 = split_and_cut(list1, size); 

                // 2. Get List 2 (size 'size' or less)
                // The result of this split is the start of the remaining list (or nullptr)
                curr = split_and_cut(list2, size); 

                // 3. Merge List 1 and List 2, and connect the result to the main list
                // 'tail' is updated to the end of the newly merged section
                tail = merge_and_connect(tail, list1, list2);
            }
        }

        return dummy_head.next;
    }
};



void printList(ListNode* head) {
    ListNode* temp = head;
    while (temp) {
        cout << temp->val;
        if (temp->next) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    // Creating the unsorted list: 4 -> 2 -> 1 -> 3
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    cout << "Original List: ";
    printList(head);

    Solution solver;
    ListNode* sorted_head = solver.sortList(head);

    cout << "Sorted List:   ";
    printList(sorted_head);

    // Clean up memory
    ListNode* curr = sorted_head;
    while (curr) {
        ListNode* next = curr->next;
        delete curr;
        curr = next;
    }

    return 0;
}