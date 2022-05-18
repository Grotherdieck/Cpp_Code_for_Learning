#pragma once
#include <iostream>
using namespace std;
class Date
{
public:
	//Ĭ�Ϲ��캯��
	Date(int year = 2022, int month = 1, int day = 1);
	//�������캯���ñ�����Ĭ�����ɵľ���,���ֻ����Լ�ʵ��һ��
	Date(const Date& d);
	//��ӡ
	void Print()const;
	~Date();
	int Getmonthdays(int year, int month)const;
	bool operator>(const Date& d)const;
	bool operator>=(const Date& d)const;
	bool operator<(const Date& d)const;
	bool operator<=(const Date& d)const;
	Date& operator=(const Date& d);
	bool operator==(const Date& d)const;
	bool operator!=(const Date& d)const;
	//���ڼ�����û������ ���ڼ�������������
	Date operator+(int days)const;
	Date& operator+=(int days);
	Date operator-(int days)const;
	Date& operator-=(int days);
	//ǰ��++ ����++ ���������д�ֲ����

	//C++����������һ������ �������Ĭ��Ϊǰ��++
	Date& operator++();
	//����++Ϊ�˸�ǰ��++���𣬽������֣�����һ��ռλ����,��ǰ��++���ɺ�������
	Date operator++(int);
	//����ʱ��ǰ��++����++d1��������ת��Ϊ
	//d1.operator(&d1);
	//����++����d1++��������ת��Ϊ
	//d1.operator(&d1, 0);
	//���0��ʵû���κ����壬ֻ��Ϊ�˺�ǰ��++���� ƥ�䵽��ȷ�����غ���
	//����涨���� ����int ��Ϊ��0�Ǳ��������� �����ĳɱ�����Ϳ���ƥ�䲻����

	//�Զ������ͺ���++Ҫ�������� һ���Ǳ����֮ǰ��ֵ һ���Ƿ���ʱ����
	//��ǰ��++�������ÿ������� ��Ϊǰ��++���ص�ֵ���Ǽ���֮��Ķ��� ���������뿪���������������
	//���Կ��Է�������
	//�ٶ��Ǳ�ǰ��++���� �����Զ������ͽ���ʹ��ǰ��++
	Date& operator--();
	Date operator--(int);
	//���ڼ����ڷ�������
	int operator-(const Date& d)const;
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
	void PrintWeekday()const;
private:
	int _year;
	int _month;
	int _day;
};
