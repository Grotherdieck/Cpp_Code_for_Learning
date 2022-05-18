#define  _CRT_SECURE_NO_WARNINGS 1

//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <unordered_set>
//#include <string>
//#include <map>
//#include <set>
//#include <tuple>
//using namespace std;
//
//typedef long long LL;
//bool check(LL num)
//{
//    string tmp = to_string(num);
//    int l = 0, r = tmp.size() - 1;
//    while (l < r)
//    {
//        if (tmp[l] != tmp[r]) return false;
//        l++, r--;
//    }
//    return true;
//}
//vector<long long> kthPalindrome(vector<int>& queries, int intLength)
//{
//    if (intLength == 1)
//    {
//        vector<LL> ans;
//        for (int q : queries)
//        {
//            if (q > 0 && q < 10)
//            {
//                ans.push_back(q);
//            }
//            else
//            {
//                ans.push_back(-1);
//            }
//        }
//        return ans;
//    }
//    vector<LL> huiwen;
//    LL low = pow(10, intLength - 1) + 1;
//    LL up = pow(10, intLength) - 1;
//    for (LL i = low; i <= up; ++i)
//    {
//        if (check(i))
//        {
//            huiwen.push_back(i);
//        }
//    }
//    int n = queries.size();
//    vector<LL> ans(n);
//    int sz = huiwen.size();
//    for (int i = 0; i < n; ++i)
//    {
//        int q = queries.size();
//        if (q > sz) ans[i] = -1;
//        else ans[i] = huiwen[queries[i] - 1];
//    }
//    return ans;
//}
//
//int main()
//{
//    /*vector<int> p = { 392015495,5,4,1,425320571,565971690,3,7,6,3,506222280,468075092,5 };
//    kthPalindrome(p, 2);*/
//    cout << sizeof(long) << endl;
//}

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
using namespace std;
typedef pair<int, int> pii;
unordered_set<int> myhash;
// const int N = 1010;
// int g[N][N];
int n, m;
int res = 0;
int dx[4] = { 0, 0, 2, -2 };
int dy[4] = { 2, -2, 0, 0 };
int dist(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void dfs(int x, int y, int curval)
{
    if (y == n) x += 1, y = 0;
    if (x == m)
    {
        if (curval > res)
        {
            res = curval;
        }
        return;
    }
    // 不在这个点放蛋糕
    dfs(x, y + 1, curval);
    // 放蛋糕
    if (myhash.count(x * n + y) == 0)
    {
        /*for (int i = x - 2; i <= x + 2; ++i)
        {
            for (int j = y - 2; j <= y + 2; ++j)
            {
                if (i >= 0 && i < m && j >= 0 && j < n && dist(x, y, i, j) == 4)
                {
                    myhash.insert(x * n + y);
                }
            }
        }*/
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n)
            {
                myhash.insert(nx * n + ny);
            }
        }
        dfs(x, y + 1, curval + 1);
        auto it = myhash.begin();
        while (it != myhash.end())
        {
            int nx = (*it) / n;
            int ny = (*it) % n;
            if (dist(x, y, nx, ny) == 4)
            {
                it = myhash.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

// m 行 n 列
int main()
{
    cin >> n >> m;
    dfs(0, 0, 0);
    cout << res << endl;
    return 0;
}