#define  _CRT_SECURE_NO_WARNINGS 1
#include "Genetic.h"



void probabilityinit()
{
	srand((unsigned int)time(nullptr));
}

void Cross(Individual& a, Individual& b)
{
	int j = rand() % 12;
	int who = rand() % 2;
	for (int k = j; k < 12; ++k)
	{
		if (who == 0)
		{
			bool tmp = a.code1.bitcode[k];
			a.code1.bitcode[k] = b.code1.bitcode[k];
			b.code1.bitcode[k] = tmp;
		}
		else
		{
			bool tmp = a.code2.bitcode[k];
			a.code2.bitcode[k] = b.code2.bitcode[k];
			b.code2.bitcode[k] = tmp;
		}
	}
}

void getbest(vector<Individual>& popu, thebest& best)
{
	thebest curbest;
	for (auto& p : popu)
	{
		double curval = f(p);
		if (curval < curbest.val)
		{
			double x1 = p.code1.decode();
			double x2 = p.code2.decode();
			curbest = { x1, x2, curval };
		}
	}
	if (curbest.val < best.val)
	{
		best = curbest;
	}
}

double _f(double x1, double x2)
{
	return 100 * (x1 * x1 - x2) * (x1 * x1 - x2) + (1 - x1) * (1 - x1);
}

void getexecpbest(thebest& execp)
{
	// x2固定为2.048
	for (int i = 0; i < (1 << 12); ++i)
	{
		double x2 = 2.048;
		double x1 = -2.048 + 0.001 * i;
		double curval = _f(x1, x2);
		if (curval < execp.val)
		{
			execp = { x1, x2, curval };
		}
	}
	// x1固定为2.048
	for (int i = 0; i < (1 << 12); ++i)
	{
		double x1 = 2.048;
		double x2 = -2.048 + 0.001 * i;
		double curval = _f(x1, x2);
		if (curval < execp.val)
		{
			execp = { x1, x2, curval };
		}
	}
}

vector<Individual> select(vector<Individual>& popu)
{
	vector<double> F(500);
	// 获取适应度函数
	for (int i = 0; i < 500; ++i)
	{
		double myval = f(popu[i]);
		if (fabs(myval) < 1e-9) F[i] = (double)1e10;
		else F[i] = 1 / myval;
	}
	// 计算染色体i被选择的概率
	vector<double> p(500);
	double Fsum = accumulate(F.begin(), F.end(), (double)0.0);
	for (int i = 0; i < 500; ++i)
	{
		p[i] = F[i] / Fsum;
	}
	// p数组的前缀和
	vector<double> q(500);
	q[0] = p[0];
	for (int i = 1; i < 500; ++i)
	{
		q[i] = q[i - 1] + p[i];
	}
	int cnt = 500;
	vector<Individual> res;
	// 轮盘赌博
	while (cnt--)
	{
		// 0-1的随机数
		double r = rand() % N / (double)N;
		// 使用二分查找  找到q中>=r的左边界
		int l = 0, right = 499;
		while (l < right)
		{
			int mid = (l + right) / 2;
			if (q[mid] >= r)
			{
				right = mid;
			}
			else l = mid + 1;
		}
		// 向返回数组中插入选择的染色体

		if (l >= 0 && l < 500) res.push_back(popu[l]);
		else if (l < 0) res.push_back(popu[0]);
		else if (l >= 500) res.push_back(popu[499]);
	}
	return res;
}