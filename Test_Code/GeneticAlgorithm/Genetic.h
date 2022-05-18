#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <numeric>
using namespace std;
typedef unsigned long UL;

const double gap = 1e-7;
const int N = 100000;
// 交换概率
const double Pc = 0.6;
// 变异概率
const double Pm = 0.1;

// 设置概率初始化
void probabilityinit();

// 染色体
class chromosome
{
public:
	// 构造函数内进行随机生成编码
	chromosome()
	{
		for (int i = 0; i < 12; ++i)
		{
			bitcode[i] = rand() % 2;
		}
	}
	// 解码
	double decode()
	{
		UL val = bitcode.to_ulong();
		double res = -2.048 + 0.001 * val;
		return res;
	}
	// 变异操作
	void variation()
	{
		bitcode.flip(rand() % 12);
	}
	bitset<12> bitcode;
};

// 两个染色体表示x1的编码和x2的编码 表示一个个体
struct Individual
{
	chromosome code1;
	chromosome code2;
};

// 两个个体的交叉
void Cross(Individual& a, Individual& b);

// 函数f
double f(Individual& x);

// 放最优解的结构体
struct thebest
{
	thebest(double X1 = 0, double X2 = 0)
		:x1(X1), x2(X2)
	{
		val = 100 * (x1 * x1 - x2) * (x1 * x1 - x2) + (1 - x1) * (1 - x1);
	}
	thebest(double X1, double X2, double Val)
		: x1(X1), x2(X2), val(Val)
	{}
	double x1;
	double x2;
	double val;
};
// 获取种群最大值
void getbest(vector<Individual>& popu, thebest& best);
// 获取例外情况(一个点是2.048)情况的最大值
void getexecpbest(thebest& execp);
// 选择函数
vector<Individual> select(vector<Individual>& p);