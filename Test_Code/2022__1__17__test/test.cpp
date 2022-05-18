#define  _CRT_SECURE_NO_WARNINGS 1

//#include <vector>
#include <iostream>
using namespace std;
//class Solution {
//    //设F(S)代表组成金额S所需要的的最少硬币数
//    //那么显然F(S) = minF(S - coins[i]) + 1
//    //上面的是状态转移方程
//    //且S=0时，F(S)=0
//    //当S<0时,F(S)=-1表示这个状态组成不了金额S
//    //我们用dp[i]记录之前已经计算过的 这样递归到计算过的时候就不必展开了
//public:
//    int coinChange(vector<int>& coins, int amount)
//    {
//        if (amount == 0)
//        {
//            return 0;
//        }
//        //dp数组来记录之前计算过的状态
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