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
// ��������
const double Pc = 0.6;
// �������
const double Pm = 0.1;

// ���ø��ʳ�ʼ��
void probabilityinit();

// Ⱦɫ��
class chromosome
{
public:
	// ���캯���ڽ���������ɱ���
	chromosome()
	{
		for (int i = 0; i < 12; ++i)
		{
			bitcode[i] = rand() % 2;
		}
	}
	// ����
	double decode()
	{
		UL val = bitcode.to_ulong();
		double res = -2.048 + 0.001 * val;
		return res;
	}
	// �������
	void variation()
	{
		bitcode.flip(rand() % 12);
	}
	bitset<12> bitcode;
};

// ����Ⱦɫ���ʾx1�ı����x2�ı��� ��ʾһ������
struct Individual
{
	chromosome code1;
	chromosome code2;
};

// ��������Ľ���
void Cross(Individual& a, Individual& b);

// ����f
double f(Individual& x);

// �����Ž�Ľṹ��
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
// ��ȡ��Ⱥ���ֵ
void getbest(vector<Individual>& popu, thebest& best);
// ��ȡ�������(һ������2.048)��������ֵ
void getexecpbest(thebest& execp);
// ѡ����
vector<Individual> select(vector<Individual>& p);