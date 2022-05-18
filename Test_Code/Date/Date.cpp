#define  _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!(_year >= 0
		&& (_month > 0 && _month < 13) &&
		(_day > 0 && _day <= Getmonthdays(_year, _month))))
	{
		cout << "�Ƿ�����->";
		Print();
	}
}

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

void Date::Print()const
{
	cout << _year << "��" << _month << "��" << _day << "��" << endl;
}

int Date::Getmonthdays(int year, int month)const
{
	static int arr[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int days = arr[month];
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			days++;
		}
	}
	return days;
}

bool Date::operator>(const Date& d)const
{
	//������������Ҳ�����d�Ķ�Ӧ����������true
	if (_year > d._year) {
		return true;
	}
	//�������������ͬ�������������_month������true
	else if (_year == d._year && _month > d._month) {
		return true;
	}
	//�������������������ͬ�����������������_day�����в�����������������true
	else if (_year == d._year && _month == d._month && _day > d._day) {
		return true;
	}
	else//�������ڵ�������������� �������������false�Ϳ�����
	{
		return false;
	}
}

bool Date::operator==(const Date& d)const
{
	return (_day == d._day) && (_month == d._month) && (_year == d._year);
}

bool Date::operator>=(const Date& d)const
{
	//���ڵ��ڵ�ʵ�־͵��ڴ��ڻ���ڣ�
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d)const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d)const
{
	return !(*this > d);
}

bool Date::operator!=(const Date& d)const
{
	return !(*this == d);
}

Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

Date& Date::operator+=(int days)
{
	if (days < 0)
	{
		return (*this) -= (-days);
	}
	_day += days;
	while (_day > Getmonthdays(_year, _month))
	{
		_day -= Getmonthdays(_year, _month);
		_month++;
		if (_month == 13)
		{
			//���λ
			_month = 1;
			_year++;
		}
	}
	return *this;
}

Date Date::operator+(int days)const
{
	Date ret(*this);
	ret += days;
	//�������������Ͷ����������ھͽ����� ���ܷ�������
	return ret;
}

Date& Date::operator-=(int days)
{
	if (days < 0)
	{
		return (*this) += (-days);
	}
	_day -= days;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_month = 12;
			--_year;
		}
		_day += Getmonthdays(_year, _month);
	}
	return *this;
}

Date Date::operator-(int days)const
{
	Date ret(*this);
	ret -= days;
	return ret;
}

Date& Date::operator++()
{
	(*this) += 1;
	return *this;//�������� �ײ��Ƿ���ָ�� ��ֻ������һ��ָ����� �ٶȿ�ú�
}
Date Date::operator++(int)
{
	Date ret(*this);//����һ��
	(*this) += 1;
	return ret;//����ֵ�ֿ���һ��
}

Date& Date::operator--()
{
	return (*this) -= 1;
}

Date Date::operator--(int)
{
	Date ret(*this);
	(*this) -= 1;
	return ret;
}

int Date::operator-(const Date& d)const
{
	Date bigdate = *this;
	Date smalldate = d;
	int flag = 1;
	if (bigdate < smalldate)
	{
		bigdate = d;
		smalldate = *this;
		flag = -1;
	}
	int ret = 0;
	while (smalldate < bigdate)
	{
		++smalldate;
		++ret;
	}
	return flag * ret;
}

//int Date::operator-(const Date& d)const
//{
//	Date bigdate = *this;
//	Date smalldate = d;
//	int flag = 1;
//	if (bigdate < smalldate)
//	{
//		bigdate = d;
//		smalldate = *this;
//		flag = -1;
//	}
//	int bigdays = bigdate._day;
//	while (bigdate._month != 1)
//	{
//		--bigdate._month;
//		bigdays += Getmonthdays(bigdate._year, bigdate._month);
//	}
//	int smalldays = smalldate._day;
//	while (smalldate._month != 1)
//	{
//		--smalldate._month;
//		smalldays += Getmonthdays(smalldate._year, smalldate._month);
//	}
//	int curyear = smalldate._year;
//	int yeargap = 0;
//	while (curyear != bigdate._year)
//	{
//		if ((curyear % 4 == 0 && curyear % 100 != 0) || curyear % 400 == 0)
//		{
//			yeargap += 366;
//		}
//		else
//		{
//			yeargap += 365;
//		}
//		curyear++;
//	}
//	int daygap = bigdays - smalldays;
//	return flag * (daygap + yeargap);
//}

void Date::PrintWeekday()const
{
	static const char* str[] = { "����һ", "���ڶ�", "������", "������", "������", "������", "������"};
	static const Date start(1900, 1, 1);
	int gap = (*this) - start;
	cout << str[gap % 7] << endl;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}

istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

Date::~Date()
{
	cout << "~Date()" << endl;
}