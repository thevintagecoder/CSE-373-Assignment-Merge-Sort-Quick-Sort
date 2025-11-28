// Nodes are scattered but dynamically connected. It is like a data structure

//Linkedlists are made of nodes 

// We need to build a new merged list with a dummy node as a start

// we will also introduce a new pointer, which will be temporary and will always point to the last node added 

//initially, the current pointer will point to the dummy node

//I am using a guest list analogy to write it better
//I learned about constructors in struct while analysing this problem, that is why I am using it 

//current is an iterator pointer that moves along the new merged list, 
//always pointing to the last node added so the next node can be attached.


//The -> operator dereferences the pointer and accesses the member.

//In a linked list, the Head is simply a pointer that holds 
//the memory address of the very first node in the list.

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node.
// This structure represents one Guest (Node)
struct ListNode {
    int val;          // The Value (val) = Guest's age
    ListNode *next;   // The Next Pointer = Points to the next Guest
    
    // Constructors for easy creation
    ListNode() : val(0), next(nullptr) {} //This creates a node with value 0 and no next node
    ListNode(int x) : val(x), next(nullptr) {} //This creates a node with the value but no next node
    ListNode(int x, ListNode *next) : val(x), next(next) {} //has both value with a node and the address of the next one 
};

class Solution {
public:
    // The core logic to merge the two sorted lists
    //this function points to the head of two lists

    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
    // Base Cases: If either list is empty, return the other list.
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }

    // Recursive Step
    if (list1->val <= list2->val) {
        // list1 is the smaller head. The result's next node
        // is the merge of list1's tail and the full list2.
        list1->next = mergeTwoListsRecursive(list1->next, list2);
        return list1; // Return the chosen head
    } else {
        // list2 is the smaller head. The result's next node
        // is the merge of the full list1 and list2's tail.
        list2->next = mergeTwoListsRecursive(list1, list2->next);
        return list2; // Returning the chosen head
    }
}};

// --- Helper functions for testing ---

ListNode* createList(const vector<int>& v) {
    if (v.empty()) return nullptr;
    ListNode* head = new ListNode(v[0]); //head is established as the starting pointer
    ListNode* current = head; //this will move through

    for (size_t i = 1; i < v.size(); ++i) {
        current->next = new ListNode(v[i]);
        current = current->next;
    }
    return head;
}

void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        
        cout << current->val;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

int main() {
    Solution s;

    // List 1 (Your list): Sorted ages
    
    vector<int> ages1 = {22, 28, 35};
    ListNode* list1 = createList(ages1);
    
    // List 2 (Friend's list): Sorted ages
    vector<int> ages2 = {25, 30, 40, 50};
    ListNode* list2 = createList(ages2);
    
    cout << "List 1 (Your List): ";
    printList(list1);
    
    cout << "List 2 (Friend's List): ";
    printList(list2);

    // Calling the function to merge the lists
    ListNode* mergedList = s.mergeTwoListsRecursive(list1, list2);
    
    cout << "\nMerged Sorted List (The Master List): ";
    printList(mergedList);
    
  
    return 0;
}