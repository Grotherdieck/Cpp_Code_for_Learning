#define  _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//typedef unsigned long long ULL;
//vector<ULL> p;
//string subStrHash(string s, int power, int modulo, int k, int hashValue)
//{
//    int n = s.size();
//    p = vector<ULL>(k + 1, 1);
//    for (int i = 1; i <= k; ++i)
//    {
//        p[i] = (power * p[i - 1]);
//    }
//    // ÏÈÔ¤¼ÆËãh(n - k, p, m)
//    int h = 0;
//    int cnt = 0;
//    for (int i = n - k; i <= n - 1; ++i)
//    {
//        h = (h + ((s[i] - 'a' + 1) * p[cnt++]) % modulo) % modulo;
//    }
//    int pos = 0;
//    if (h == hashValue) pos = n - k;
//    for (int i = n - k - 1; i >= 0; --i)
//    {
//        h = (((long long)power * h) % modulo + (s[i] - 'a' + 1) % modulo - ((s[i + k] - 'a' + 1) * p[k]) % modulo + modulo) % modulo;
//        if (h == hashValue) pos = i;
//    }
//    return s.substr(pos, k);
//}
//
//int main()
//{
//    cout << subStrHash("leetcode", 7, 20, 2, 0) << endl;
//}

int addAB(int A, int B)
{
    if (B == 0) return A;
    return addAB(A + 1, B - 1);
}

int main()
{
    cout << addAB(1, 2) << endl;
}