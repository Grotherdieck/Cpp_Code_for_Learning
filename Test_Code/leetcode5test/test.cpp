#define  _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
using namespace std;
class Solution {
public:
    string longestPalindrome(string s)
    {
        int len = s.size();
        if (len == 1)
        {
            return s;
        }
        string ret;
        int left = 0;
        int maxsize = 0;
        for (left = 0; left <= len - 1; left++)
        {
            for (int right = left; right < len; right++)
            {
                if (isParlindrome(left, right, s) == true)
                {
                    int size = right - left + 1;
                    if (size > maxsize)
                    {
                        maxsize = size;
                        ret = s.substr(left, size);
                    }
                }
            }
        }
        return ret;
    }
    bool isParlindrome(int left, int right, string& str)
    {
        while (left < right)
        {
            if (str[left] != str[right])
            {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

int main()
{
    string s1 = "babad";
    Solution s;
    string s2 = s.longestPalindrome(s1);
    cout << s2;
}