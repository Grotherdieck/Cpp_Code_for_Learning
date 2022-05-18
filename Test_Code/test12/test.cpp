#define  _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
using namespace std;
//bool canPermutePalindrome(string s)
//{
//    //位运算 用一个8个int的数组
//    //每一字符 生成一个右移到它ascii码位置的int
//    //然后让这个数组对应的位置去异或上这个int
//    //回文序列保证最后整个数组里头最多有一个1
//    int arr[8] = { 0 };
//    for (auto e : s)
//    {
//        //一个int32位 先整除32到达它在哪个数组里
//        //然后右移取余32位就是对应为位置
//        arr[e / 32] ^= (1 << (e % 32));
//    }
//    int cnt = 0;
//    for (auto e : arr)
//    {
//        while (e != 0)
//        {
//            e &= (e - 1);
//            cnt++;
//        }
//    }
//    return cnt < 2;
//}
//
//int main()
//{
//    canPermutePalindrome("as");
//}

//struct ListNode {
//    int val;
//    ListNode* next;
//    ListNode() : val(0), next(nullptr) {}
//    ListNode(int x) : val(x), next(nullptr) {}
//    ListNode(int x, ListNode* next) : val(x), next(next) {}
//};
//
//class Solution {
//public:
//    Solution(ListNode* head)
//    {
//        _head = head;
//        while (head != nullptr)
//        {
//            _sz++;
//            head = head->next;
//        }
//    }
//
//    int getRandom()
//    {
//        ListNode* cur = _head;
//        int walks = rand() % _sz;
//        while (walks != 0)
//        {
//            if (cur != nullptr)
//            {
//                cur = cur->next;
//            }
//            walks--;
//        }
//        return cur->val;
//    }
//private:
//    ListNode* _head;
//    int _sz;
//};
//
//int main()
//{
//    ListNode l1(3, nullptr);
//    ListNode l2(2);
//    ListNode l3(1);
//    l3.next = &l2;
//    l2.next = &l1;
//    Solution s1(&l3);
//    int ret = s1.getRandom();
//}

class Date
{
public:
	Date(int year = 2022, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		cout << "拷贝构造" << endl;
	}
	bool operator>(const Date& d2)
	{
		cout << "类内！" << endl;
		if (this->_year > d2._year)
		{
			return true;
		}
		else if (this->_year == d2._year && this->_month > d2._month)
		{
			return true;
		}
		else if (this->_year == d2._year && this->_month == d2._month && this->_day > d2._day)
		{
			return true;
		}
		return false;
	}
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
private:
	int _year;
	int _month;
	int _day;
};

bool operator>(const Date& d1, const Date& d2)
{
	cout << "全局！" << endl;
	return true;
}


int main()
{
	Date d1(2022, 1, 16);
	Date d2(2022, 1, 31);
	bool f = d2 > d1;//比较日期哪个大？
	//int day = d2 - d1;//看看两个日期相差多少天
	Date d3;
	d3 = d2 = d1;
}