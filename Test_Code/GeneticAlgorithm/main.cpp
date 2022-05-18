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
	// 500���������Ⱥ
	vector<Individual> population(500);
	thebest best;
	// ��ȡ������ɵĳ�ʼ��Ⱥ�����ֵ
	getbest(population, best);
	// ��500��
	int cnt = 500;
	// ��(2.048, 2.048)�����ó���
	thebest execp(2.048, 2.048);
	// ��ȡĳһ������2.048(�����ʾ���˵�)����Сֵ
	getexecpbest(execp);
	cout << "�Ŵ��㷨�Ѿ���ʼ����ʼ��Ϊ:" << endl;
	cout << "x1 = " << best.x1 << endl;
	cout << "x2 = " << best.x2 << endl;
	cout << "f(x1, x2) = " << best.val << endl;
	while (cnt--)
	{
		// 1.��õ�ǰ��Ⱥ��Ӧ�� �Խ���ѡ�����
		population = select(population);
		// 2.������� ����cross
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
		// 3.�������
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
		// 4.��õ�ǰ���Ž�
		getbest(population, best);
		int mytime = 500 - cnt;
		if (mytime % 100 == 0)
		{
			cout << "��Ҫ�ż����Ѿ�������" << mytime << "����" << endl;
		}
		// ѧϰ����
		cout << "��" << 500 - cnt << "��" << endl;
		cout << "x1 = " << best.x1 << endl;
		cout << "x2 = " << best.x2 << endl;
		cout << "f(x1, x2) = " << best.val << endl;
	}
	// �������������� �����best
	if (best.val > execp.val)
	{
		best = execp;
	}
	cout << "500���������Ⱥ������500���Ŵ��㷨���õ������Ž�Ϊ" << endl;
	cout << "x1 = " << best.x1 << endl;
	cout << "x2 = " << best.x2 << endl;
	cout << "f(x1, x2) = " << best.val << endl;
	return 0;
}
