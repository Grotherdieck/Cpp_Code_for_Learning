#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;
//#include <vector>
//using namespace std;
//int minPathSum(vector<vector<int>>& grid)
//{
//    int rows = grid.size();
//    int cols = grid[0].size();
//    int ret = 0;
//    if (rows > cols)
//    {
//        vector<int> dp(cols);
//        int sum = 0;
//        for (int j = 0; j < cols; ++j)
//        {
//            sum += grid[0][j];
//            dp[j] = sum;
//        }
//        for (int i = 1; i < rows; ++i)
//        {
//            int prev = 0;
//            for (int k = 0; k <= i; ++k)
//            {
//                prev += grid[k][0];
//            }
//            for (int j = 1; j < cols; ++j)
//            {
//                dp[j] = min(prev, dp[j]) + grid[i][j];
//                prev = dp[j];
//            }
//        }
//        ret = dp[cols - 1];
//    }
//    else
//    {
//        vector<int> dp(rows);
//        int sum = 0;
//        for (int i = 0; i < rows; ++i)
//        {
//            sum += grid[i][0];
//            dp[i] = sum;
//        }
//        for (int j = 1; j < cols; ++j)
//        {
//            int prev = 0;
//            for (int k = 0; k <= j; ++k)
//            {
//                prev += grid[0][k];
//            }
//            for (int i = 1; i < rows; ++i)
//            {
//                dp[i] = min(dp[i], prev) + grid[i][j];
//                prev = dp[i];
//            }
//        }
//        ret = dp[rows - 1];
//    }
//    return ret;
//}
//
//int main()
//{
//    vector<vector<int>> grid{ {9,1,4,8 } };
//    int ret = minPathSum(grid);
//}

//struct ListNode {
//    int val;
//    ListNode* next;
//    ListNode() : val(0), next(nullptr) {}
//    ListNode(int x) : val(x), next(nullptr) {}
//    ListNode(int x, ListNode* next) : val(x), next(next) {}
//};
//
//ListNode* removeZeroSumSublists(ListNode* head)
//{
//    ListNode* dummyhead = new ListNode(0, head);
//    ListNode* cur = dummyhead;
//    int sum = 0;
//    while (cur != nullptr)
//    {
//        ListNode* search = cur->next;
//        sum = 0;
//        while (search != nullptr)
//        {
//            sum += search->val;
//            if (sum == 0)
//            {
//                ListNode* del = cur->next;
//                ListNode* end = search->next;
//                while (del != end)
//                {
//                    ListNode* next = del->next;
//                    delete del;
//                    del = next;
//                }
//                cur->next = end;
//                break;
//            }
//            search = search->next;
//        }
//        cur = cur->next;
//    }
//    return dummyhead->next;
//}
//
//void Print(ListNode* head)
//{
//    while (head != nullptr)
//    {
//        cout << head->val << endl;
//        head = head->next;
//    }
//}
//
//int main()
//{
//    ListNode* l1 = new ListNode(1, nullptr);
//    ListNode* l2 = new ListNode(3, l1);
//    ListNode* l3 = new ListNode(-3, l2);
//    ListNode* l4 = new ListNode(2, l3);
//    ListNode* l5 = new ListNode(1, l4);
//    l5 = removeZeroSumSublists(l5);
//    Print(l5);
//}

int cnt1[10010] = { 0 };/*ÆæÊý*/
int cnt2[10010] = { 0 };/*Å¼Êý*/
int minimumOperations(vector<int>& nums)
{
    int n = nums.size();
    for (int i = 0; i < n; i += 2)
    {
        ++cnt2[nums[i]];
        if (i + 1 < n) ++cnt1[nums[i + 1]];
    }
    int maxindex1 = 1;
    int maxindex2 = 0;
    int curmax1 = 0;
    int curmax2 = 0;
    for (int i = 0; i < 10001; ++i)
    {
        if (i % 2 == 0)
        {
            if (cnt2[i] > curmax2)
            {
                curmax2 = cnt2[i];
                maxindex2 = i;
            }
        }
        else
        {
            if (cnt1[i] > curmax1)
            {
                curmax1 = cnt1[i];
                maxindex1 = i;
            }
        }
    }
    int ret = 0;
    if (maxindex1 != maxindex2)
    {
        int count1 = n / 2;
        int count2 = n - count1;
        ret = count1 - curmax1 + count2 - curmax2;
    }
    return ret;
}

int main()
{
    vector<int> tmp = { 3,1,3,2,4,3 };
    minimumOperations(tmp);
}