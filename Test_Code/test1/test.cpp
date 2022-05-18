#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <time.h>
#include <set>
using namespace std;
//bool check(const string& s)
//{
//    int l = 0, r = s.size() - 1;
//    while (l < r)
//    {
//        if (s[l] != s[r])
//            return false;
//        ++l;
//        --r;
//    }
//    return true;
//}
//int minMovesToMakePalindrome(string s)
//{
//    if (check(s))
//        return 0;
//    unordered_map<string, int> dist;
//    int n = s.size();
//    queue<string> q;
//    dist[s] = 0;
//    q.push(s);
//    while (!q.empty())
//    {
//        string s = q.front();
//        if (check(s))
//            return dist[s];
//        q.pop();
//        for (int i = 0; i < n - 1; ++i)
//        {
//            string tmp = s;
//            swap(tmp[i], tmp[i + 1]);
//            if (dist.find(tmp) == dist.end())
//            {
//                dist[tmp] = dist[s] + 1;
//                q.push(tmp);
//            }
//        }
//    }
//    return 0;
//}
//
//int main()
//{
//    size_t begint = clock();
//    cout << minMovesToMakePalindrome("eqvvhtcsaaqtqesvvqch") << endl;
//    size_t endt = clock();
//    cout << (endt - begint) << "ms" << endl;
//}

//long long minimalKSum(vector<int>& nums, int k)
//{
//    sort(nums.begin(), nums.end());
//    long long ret = 0;
//    if (nums[0] > k)
//    {
//        ret += (long long)k * (long long)(k + 1) / 2;
//        return ret;
//    }
//    else
//    {
//        /*for (int i = 1; i < nums[0]; ++i)
//        {
//            ret = ret + (long long)i;
//        }*/
//        ret += (long long)(nums[0] - 1) * (long long)(nums[0]) / 2;
//        k -= (nums[0] - 1);
//        int n = nums.size();
//        for (int i = 1; i < n; ++i)
//        {
//            if (nums[i] != nums[i - 1] && nums[i - 1] + 1 != nums[i])
//            {
//                int cnt = min(k, nums[i] - 1 - nums[i - 1]);
//                /*ret +=
//                ((long long)nums[i - 1] + (long long)nums[i]) * ((long long)nums[i] - (long long)nums[i - 1] - 1) / 2;*/
//                ret += (long long)cnt * (long long)(nums[i - 1] + 1) + (long long)cnt * (long long)(cnt - 1) / 2;
//                k -= cnt;
//                if (k == 0) return ret;
//            }
//        }
//        ret += (long long)k * (long long)(nums[n - 1] + 1) + (long long)k * (long long)(k - 1) / 2;
//    }
//    return ret;
//}
//
//int main()
//{
//    vector<int> c = 
//    { 96, 44, 99, 25, 61, 84, 88, 18, 19, 33, 60, 86, 52, 19, 32, 47, 35, 50, 94, 17, 29, 98, 22, 21, 72, 100, 40, 84 };
//    int k = 2;
//    minimalKSum(c, 35);
//}

//vector<int> replaceNonCoprimes(vector<int>& nums)
//{
//    set<int> ret;
//    int n = nums.size();
//    int i = 1;
//    while (i < n)
//    {
//        int a = nums[i];
//        int b = nums[i - 1];
//        if (gcd(a, b) > 1)
//        {
//            int tmp = (long long)a * (long long)b / gcd(a, b);
//            ret.insert(tmp);
//            nums[i - 1] = 0;
//            nums[i] = tmp;
//            i++;
//        }
//        else
//        {
//            ret.insert(tmp);
//            i++;
//        }
//    }
//    vector<int> res;
//    for (auto l : set)
//    {
//        res.push_back(l);
//    }
//    return res;
//}

class Solution {
public:
    typedef pair<int, int> PII;
    void Floyd(vector<vector<int>>& g)
    {
        int n = g.size();
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
    {
        vector<vector<int>> g(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; ++i) g[i][i] = 0;
        for (auto& edge : edges)
        {
            int a = edge[0], b = edge[1], c = edge[2];
            g[a][b] = c;
            g[b][a] = c;
        }
        Floyd(g);
        vector<PII> cntandmax(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (g[i][j] > 1e9 / 2) continue;
                ++cntandmax[i].first;
                cntandmax[i].second = max(cntandmax[i].second, g[i][j]);
            }
        }
        int ret = 0;
        int cnt = 1e9;
        for (int i = 0; i < n; ++i)
        {
            if (cntandmax[i].second > distanceThreshold) continue;
            if (cntandmax[i].first <= cnt)
            {
                ret = i;
                cnt = cntandmax[i].first;
            }
        }
        return ret;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> a = { {0, 1, 3},{1, 2, 1},{1, 3, 4},{2, 3, 1} };
    s.findTheCity(4, a, 4);
}