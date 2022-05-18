#define  _CRT_SECURE_NO_WARNINGS 1
#include "Genetic.h"

double f(Individual& x)
{
	double x1 = x.code1.decode();
	double x2 = x.code2.decode();
	return 100 * (x1 * x1 - x2) * (x1 * x1 - x2) + (1 - x1) * (1 - x1);
}



int main()
{
	probabilityinit();
	// 500个个体的种群
	vector<Individual> population(500);
	thebest best;
	// 获取随机生成的初始种群的最佳值
	getbest(population, best);
	// 跑500轮
	int cnt = 500;
	// 把(2.048, 2.048)单独拿出来
	thebest execp(2.048, 2.048);
	// 获取某一个点是2.048(编码表示不了的)的最小值
	getexecpbest(execp);
	cout << "遗传算法已经开始，初始解为:" << endl;
	cout << "x1 = " << best.x1 << endl;
	cout << "x2 = " << best.x2 << endl;
	cout << "f(x1, x2) = " << best.val << endl;
	while (cnt--)
	{
		// 1.获得当前种群适应度 以进行选择操作
		population = select(population);
		// 2.交叉操作 利用cross
		for (int i = 0; i < 500; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				double r = rand() % N / (double)N;
				if (r < Pc)
				{
					Cross(population[i], population[j]);
				}
			}
		}
		// 3.变异操作
		for (int i = 0; i < 500; ++i)
		{
			double r = rand() % N / (double)N;
			if (r < Pm)
			{
				int who = rand() % 2;
				if (who == 0) population[i].code1.variation();
				else population[i].code2.variation();
			}
		}
		// 4.获得当前最优解
		getbest(population, best);
		int mytime = 500 - cnt;
		if (mytime % 100 == 0)
		{
			cout << "不要着急，已经运行了" << mytime << "轮了" << endl;
		}
		// 学习曲线
		cout << "第" << 500 - cnt << "轮" << endl;
		cout << "x1 = " << best.x1 << endl;
		cout << "x2 = " << best.x2 << endl;
		cout << "f(x1, x2) = " << best.val << endl;
	}
	// 如果例外情况更好 则更新best
	if (best.val > execp.val)
	{
		best = execp;
	}
	cout << "500个个体的种群，进行500轮遗传算法，得到的最优解为" << endl;
	cout << "x1 = " << best.x1 << endl;
	cout << "x2 = " << best.x2 << endl;
	cout << "f(x1, x2) = " << best.val << endl;
	return 0;
}
