#define  _CRT_SECURE_NO_WARNINGS 1

//#include <vector>
#include <iostream>
using namespace std;
//class Solution {
//    //��F(S)������ɽ��S����Ҫ�ĵ�����Ӳ����
//    //��ô��ȻF(S) = minF(S - coins[i]) + 1
//    //�������״̬ת�Ʒ���
//    //��S=0ʱ��F(S)=0
//    //��S<0ʱ,F(S)=-1��ʾ���״̬��ɲ��˽��S
//    //������dp[i]��¼֮ǰ�Ѿ�������� �����ݹ鵽�������ʱ��Ͳ���չ����
//public:
//    int coinChange(vector<int>& coins, int amount)
//    {
//        if (amount == 0)
//        {
//            return 0;
//        }
//        //dp��������¼֮ǰ�������״̬
//        vector<int> dp(amount);
//        return F(amount, dp, coins);
//    }
//    int F(int restmoney, vector<int>& dp, const vector<int>& coins)
//    {
//        if (restmoney > 0 && dp[restmoney - 1] != 0)
//        {
//            return dp[restmoney - 1];
//        }
//        int ans = 0;
//        if (restmoney == 0)
//        {
//            ans = 0;
//        }
//        else if (restmoney < 0)
//        {
//            ans = -1;
//        }
//        else
//        {
//            int curmin = INT_MAX;
//            for (auto e : coins)
//            {
//                int curret = F(restmoney - e, dp, coins);
//                if (curret != -1 && curret < curmin)
//                {
//                    curmin = curret;
//                }
//            }
//            if (curmin != INT_MAX)
//            {
//                ans = curmin + 1;
//            }
//            else
//            {
//                ans = -1;
//            }
//        }
//        dp[restmoney - 1] = ans;
//        return ans;
//    }
//};
//
//int main()
//{
//    //Solution s;
//    //vector<int> coins = { 1,2,5 };
//    long s = 2;
//    cout << sizeof(s) << endl;
//    //s.coinChange(coins, 11);
//}

//class A
//{
//public:
//    A()
//    {
//        cout << "A()" << endl;
//    }
//    A(const A& a)
//    {
//        cout << "A(const A&)" << endl;
//    }
//    ~A()
//    {
//        cout << "~A()" << endl;
//    }
//};
//A f(A a)
//{
//    return a;
//}
//int main()
//{
//    A x;
//    A y = f(x);
//}
//int main()
//{
//    A x;
//    A y;
//    y = f(x);
//}
//int cnt = 0;
//class Widget
//{
//public:
//    Widget()
//    {
//
//    }
//    Widget(const Widget&)
//    {
//        ++cnt;
//        cout << "Widget(const Widget&)" << endl;
//        x = 1;
//    }
//private:
//    int x;
//};
//
//Widget f(Widget u)
//{
//    Widget v(u);
//    Widget w = v;
//    return w;
//}
//
//int main()
//{
//    Widget x;
//    //Widget y = f(f(x));
//    f(Widget(x));
//    cout << cnt << endl;
//}

class A
{
public:
	A(int x = 1)
	{
		a = x;
	}
	~A()
	{
		cout << this->a << endl;
	}
private:
	int a;
};
A m(4);
int main()
{
	static A b(2);
	static A c(1);
}
A l(3);