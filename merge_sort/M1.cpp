// Nodes are scattered but dynamically connected. It is like a data structure

//Linkedlists are made of nodes 

// We need to build a new merged list with a dummy node as a start

// we will also introduce a new pointer, which will be temporary and will always point to the last node added 

//initially, the current pointer will point to the dummy node

#include <iostream>
#include <vector>

// Definition for singly-linked list node.
// This structure represents one Guest (Node)
struct ListNode {
    int val;          // The Value (val) = Guest's age
    ListNode *next;   // The Next Pointer = Points to the next Guest
    
    // Constructors for easy creation
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // The core logic to merge the two sorted lists
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        // 1. Create the Dummy Head (The Clipboard)
        // Its value (0) doesn't matter. It's just a starting anchor.
        ListNode dummyHead(0); 
        
        // 'current' is the pointer (Your finger) that tracks the end of the merged list.
        ListNode* current = &dummyHead;

        // 2. Iterative Merging Loop (The Comparison Loop)
        while (list1 != nullptr && list2 != nullptr) {
            
            // Compare the Value (val) of the current Nodes
            if (list1->val <= list2->val) {
                // If list1 is smaller, attach list1's Node to 'current's next pointer
                current->next = list1;
                // Move list1 forward to the next Node in its list
                list1 = list1->next;
            } else {
                // If list2 is smaller, attach list2's Node to 'current's next pointer
                current->next = list2;
                // Move list2 forward to the next Node in its list
                list2 = list2->next;
            }
            
            // Move 'current' forward to the Node it just attached, preparing for the next attachment.
            current = current->next;
        }

        // 3. Handling Remaining Nodes (Stapling the rest)
        // Attach whichever list still has remaining nodes.
        if (list1 != nullptr) {
            current->next = list1;
        } else {
            current->next = list2;
        }

        // 4. Returning the Result
        // Return the first actual Node after the Dummy Head.
        return dummyHead.next;
    }
};

// --- Helper functions for testing ---

// Function to create a list from a vector of integers
ListNode* createList(const std::vector<int>& v) {
    if (v.empty()) return nullptr;
    ListNode* head = new ListNode(v[0]);
    ListNode* current = head;
    for (size_t i = 1; i < v.size(); ++i) {
        current->next = new ListNode(v[i]);
        current = current->next;
    }
    return head;
}

// Function to print the list
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Solution s;

    // List 1 (Your list): Sorted ages
    std::vector<int> ages1 = {22, 28, 35};
    ListNode* list1 = createList(ages1);
    
    // List 2 (Friend's list): Sorted ages
    std::vector<int> ages2 = {25, 30, 40, 50};
    ListNode* list2 = createList(ages2);
    
    std::cout << "List 1 (Your List): ";
    printList(list1);
    
    std::cout << "List 2 (Friend's List): ";
    printList(list2);

    // Call the function to merge the lists
    ListNode* mergedList = s.mergeTwoLists(list1, list2);
    
    std::cout << "\nMerged Sorted List (The Master List): ";
    printList(mergedList);
    
    // Note: In a production environment, you would need to add code
    // to deallocate (delete) all the ListNodes to prevent memory leaks.
    return 0;
}