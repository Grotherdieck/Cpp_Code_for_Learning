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
		cout << "非法日期->";
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
	cout << _year << "年" << _month << "月" << _day << "日" << endl;
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
	//如果年数大于右操作数d的对应年数，返回true
	if (_year > d._year) {
		return true;
	}
	//否则如果年数相同左操作数的月数_month，返回true
	else if (_year == d._year && _month > d._month) {
		return true;
	}
	//否则如果年数月数都相同但是左操作数的天数_day大于有操作数的天数，返回true
	else if (_year == d._year && _month == d._month && _day > d._day) {
		return true;
	}
	else//年数大于的情况都罗列完了 其他情况都返回false就可以了
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
	//大于等于的实现就等于大于或等于！
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
			//年进位
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
	//出了作用域对象就对象生命周期就结束了 不能返回引用
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
	return *this;//返回引用 底层是返回指针 就只拷贝了一个指针变量 速度快得很
}
Date Date::operator++(int)
{
	Date ret(*this);//拷贝一次
	(*this) += 1;
	return ret;//返回值又拷贝一次
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
	static const char* str[] = { "星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期天"};
	static const Date start(1900, 1, 1);
	int gap = (*this) - start;
	cout << str[gap % 7] << endl;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
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