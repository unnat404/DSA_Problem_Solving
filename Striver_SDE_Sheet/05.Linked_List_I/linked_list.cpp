// =====================================================================================================================================
/*
Question List :: Day 5 :: Linked List I
1) Leetcode 206. reverse Linked List :: https://leetcode.com/problems/reverse-linked-list/
2) Leetcode 876. Middle of the Linked List :: https://leetcode.com/problems/middle-of-the-linked-list/
3) Leetcode 21. Merge Two Sorted Lists ::  https://leetcode.com/problems/merge-two-sorted-lists/
4) Leetcode 19. Remove Nth Node From End of List :: https://leetcode.com/problems/remove-nth-node-from-end-of-list/

5) 

*/
// =====================================================================================================================================
#include <bits/stdc++.h>
using namespace std;
// =====================================================================================================================================
// 1) Leetcode 206. reverse Linked List :: https://leetcode.com/problems/reverse-linked-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *ans,*prev;
        ListNode* curr=nullptr;
        
        while(head!=NULL){
            prev=head->next;       
            head->next=curr;
            curr=head;
            head=prev;
        }
        return curr;
    }
};
// =====================================================================================================================================
// 2) Leetcode 876. Middle of the Linked List :: https://leetcode.com/problems/middle-of-the-linked-list/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // use slow-fast pointers
        ListNode *slow,*fast;
        ListNode dummy=ListNode(-1,head);//add a dummy node at start of original linked list
        slow=fast=&dummy;//initialize slow and fast pointer to dummy node
        while(fast!=NULL){
            slow=slow->next;
            if(fast->next==nullptr || fast->next->next==nullptr) break;            
            fast=fast->next->next;            
        }
        return slow;
    }
};

// Cleaner implementation of slow - fast pointers
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
// =====================================================================================================================================
// 3) Leetcode 21. Merge Two Sorted Lists ::  https://leetcode.com/problems/merge-two-sorted-lists/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// This appproach is using extr (Follow up : do in-place)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *a,*b,*ans,*head_ans;
        if(list1==nullptr) return list2;
        if(list2==nullptr) return list1;
        if(list1->val <= list2->val) head_ans=ans=list1,list1=list1->next;//
        else head_ans=ans=list2,list2=list2->next;
        while(list1 && list2){
            // cout<<ans->val<<" ";
            if(list1->val <= list2->val){
                ans->next=list1;
                list1=list1->next;
            }
            else{
                ans->next=list2;
                list2=list2->next;
            }
            ans=ans->next;
        }
        if(list1!=nullptr) ans->next=list1;
        if(list2!=nullptr) ans->next=list2;
        return head_ans;
    }
};
// Do inplace approach also(without extra liked list) :: TO DO

// =====================================================================================================================================
// 4) Leetcode 19. Remove Nth Node From End of List :: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *slow,*fast;
        ListNode dummy = ListNode();
        dummy.next=head;
        slow=fast=&dummy;
        // pointers:
        // 1. take fast pointer ahead of slow pointer by n nodes
        // 2. keep a dummy node pointing to head (otherwise, how will you delete the first node?)
        while(n--){
            fast=fast->next;
        }
        
        while(fast->next!=nullptr){
            slow=slow->next,fast=fast->next;
        }
        
        slow->next=slow->next->next; 
        
        // if(slow->next == nullptr || slow->next->next==nullptr) slow->next=nullptr;
        // else slow->next=slow->next->next;
        
        return dummy.next;
    }
};

// =====================================================================================================================================
// 5) Leetcode 2. Add Two Numbers ::  https://leetcode.com/problems/add-two-numbers
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ans;
        ListNode *head=new ListNode();
        ans=head;
        
        int curr,carry=0;
        while(carry>0 || l1!=nullptr || l2!=nullptr){
            curr=carry;
            if(l1!=nullptr){
                curr+=l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr){
                curr+=l2->val;
                l2=l2->next;
            }
            carry=curr/10;
            curr%=10;
            ListNode* tem = new ListNode(curr);
            ans->next = tem;
            ans=ans->next;
        }
        
        return head->next;
    }
};
// =====================================================================================================================================
// 6) Leetcode 237. Delete Node in a Linked List:: https://leetcode.com/problems/delete-node-in-a-linked-list/
class Solution {
public:
    void deleteNode(ListNode* node) {
        *node = *(node->next);
    }
};
// if the node should be freed, we need 3 lines:
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* temp = node->next;
        *node = *temp;
        delete temp;
    }
};
// =====================================================================================================================================
