#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        queue<ListNode*> q;
        int len = lists.size();
        for (int i = 0; i < len; i++)
        {
            q.push(lists[i]);
        }
        if (q.empty())
        {
            return nullptr;
        }
        while (q.size() != 1)
        {
            ListNode* l1 = q.front();
            ListNode* l2;
            if (q.empty())
            {
                l2 = nullptr;
            }
            else
            {
                l2 = q.front();
                q.pop();
            }
            q.push(mergetwoLists(l1, l2));
        }
        return q.front();
    }
    ListNode* mergetwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode* dummyhead = new ListNode;
        ListNode* tail = dummyhead;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                ListNode* next = l1->next;
                l1->next = tail->next;
                tail->next = l1;
                tail = l1;
                l1 = next;
            }
            else
            {
                ListNode* next = l2->next;
                l2->next = tail->next;
                tail->next = l2;
                tail = l2;
                l2 = next;
            }
        }
        tail->next = l1 ? l1 : l2;
        tail = dummyhead->next;
        delete dummyhead;
        return tail;
    }
};

int main()
{
    ListNode* head1 = new ListNode;
    head1->val = -10;
    ListNode* l12 = new ListNode;
    ListNode* l13 = new ListNode;
    ListNode* l14 = new ListNode;
    ListNode* l15 = new ListNode;
    ListNode* l16 = new ListNode;
    ListNode* l17 = new ListNode;
    head1->next = l12;
    l12->next = l13;
    l13->next = l14;
    l14->next = l15;
    l15->next = l16;
    l16->next = l17;
    l17->next = nullptr;
    l12->val = -9;
    l13->val = -9;
    l14->val = -3;
    l15->val = -1;
    l16->val = -1;
    l17->val = 0;
    vector<ListNode*> lists;
    lists.push_back(head1);
    ListNode* head2 = new ListNode;
    head2->val = -5;
    head2->next = nullptr;
    lists.push_back(head2);
    ListNode* head3 = new ListNode;
    head3->next = nullptr;
    head3->val = 4;
    lists.push_back(head3);
    ListNode* head4 = new ListNode;
    head4->val = -8;
    head4->next = nullptr;
    lists.push_back(head4);
    ListNode* head5 = nullptr;
    lists.push_back(head5);
    ListNode* head6 = new ListNode;
    head6->val = -9;
    ListNode* l62 = new ListNode;
    l62->val = -6;
    head6->next = l62;
    ListNode* l63 = new ListNode;
    l63->val = -5;
    l62->next = l63;
    ListNode* l64 = new ListNode;
    l64->val = -4;
    l63->next = l64;
    ListNode* l65 = new ListNode;
    l65->val = -2;
    l64->next = l65;
    ListNode* l66 = new ListNode;
    l66->val = 2;
    l65->next = l66;
    ListNode* l67 = new ListNode;
    l67->val = 3;
    l67->next = nullptr;
    l66->next = l67;
    lists.push_back(head6);
    Solution s;
    ListNode* ret = s.mergeKLists(lists);
    return 0;
}