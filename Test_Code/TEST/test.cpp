#define  _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int ways(int apples, int plates)
{
	//apples个完全相同的苹果放到plates个完全相同的盘子里
	//有多少种方法
	//如果苹果用完了 说明摆放结束了 返回一种摆法
	if (apples == 0) {
		return 1;
	}
	//如果plates等于0了 apples不等于0还 那么说明没有盘子用了
	//0种摆法
	if (plates == 0) {
		return 0;
	}
	//如果盘子数大于苹果数 那么多出来的盘子不论什么摆法一定空着
	//这种情况下的摆法数等于把多出来的盘子都不考虑的摆法数
	if (plates > apples) {
		return ways(apples, apples);
	}
	//当苹果数大于盘子数的时候 有两种方法
	//1) 我们把所有的盘子都使用 那么相当于先往所有盘子上都放一个苹果
	// 这种方法的方法数等于ways(apples - plates, plates)
	int a = ways(apples - plates, plates);
	//2) 我们让盘子不全都使用 那么就敲碎一个盘子 
	//剩下的盘子全用还是敲碎一个 总可能方法数用递归去讨论
	int b = ways(apples, plates - 1);
	//这两种情况显然是互斥的 所以数量可以直接加
	return a + b;
}

int _ways1(int apples, int plates, vector<vector<int>>& dp)
{
	if (dp[apples][plates] != -1) {
		return dp[apples][plates];
	}
	int ans = 0;
	if (apples == 0)
	{
		ans = 1;
	}
	else if (plates == 0)
	{
		ans = 0;
	}
	else if (apples < plates)
	{
		ans = _ways1(apples, apples, dp);
	}
	else
	{
		int a = _ways1(apples - plates, plates, dp);
		int b = _ways1(apples, plates - 1, dp);
		ans = a + b;
	}
	dp[apples][plates] = ans;
	return ans;
}

int ways1(int apples, int plates)
{
	//考虑把暴力递归过程简化为动态规划
	//暴力递归过程之所以暴力 是因为它只会通过一层层的往下展开去计算f(x,y)
	//如果这个f(x,y）已经计算过了 为什么不把它存起来呢？
	//这就是动态规划的思想
	vector<vector<int>> dp(apples + 1, vector<int>(plates + 1, -1));
	//dp[x][y] 苹果有x个 盘子有y个 摆放方法有dp[x][y]种
	//先全部搞成-1说明当前过程我们还算过
	return _ways1(apples, plates, dp);
}

int main()
{
	int begin1 = clock();
	cout << ways1(100, 20) << endl;
	int end1 = clock();
	int begin2 = clock();
	cout << ways(100, 20) << endl;
	int end2 = clock();
	cout << end1 - begin1 << endl;
	cout << end2 - begin2 << endl;
}