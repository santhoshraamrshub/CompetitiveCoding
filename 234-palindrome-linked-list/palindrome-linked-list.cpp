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
    ListNode* revList(ListNode* head){
        ListNode* p=NULL;
        ListNode* curr=head;
        ListNode* n=NULL;
        while(curr!= nullptr){
            n=curr->next;
            curr->next=p;
            p=curr;
            curr=n;
        }
        return p;
    }
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        ListNode *slow=head , *fast=head;
        while(fast -> next && fast->next->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* nhead=revList(slow->next);
        
        ListNode* c1=head;
        ListNode* c2= nhead;   
        while(c2){
            if (c1->val!=c2->val){
                slow->next=revList(nhead);
                return false;
            }
            c1=c1->next;
            c2=c2->next;
        }
        slow->next=revList(nhead);
                return true;
    }
};