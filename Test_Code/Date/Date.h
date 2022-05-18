#pragma once
#include <iostream>
using namespace std;
class Date
{
public:
	//默认构造函数
	Date(int year = 2022, int month = 1, int day = 1);
	//拷贝构造函数用编译器默认生成的就行,练手还是自己实现一下
	Date(const Date& d);
	//打印
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
	//日期加日期没有意义 日期加天数才有意义
	Date operator+(int days)const;
	Date& operator+=(int days);
	Date operator-(int days)const;
	Date& operator-=(int days);
	//前置++ 后置++ 如果就正常写分不清楚

	//C++编译器做了一个处理 下面这个默认为前置++
	Date& operator++();
	//后置++为了跟前置++区别，进行区分，增加一个占位参数,跟前置++构成函数重载
	Date operator++(int);
	//调用时，前置++，即++d1被编译器转化为
	//d1.operator(&d1);
	//后置++，即d1++被编译器转化为
	//d1.operator(&d1, 0);
	//这个0其实没有任何意义，只是为了和前置++区别 匹配到正确的重载函数
	//这里规定死了 就用int 因为传0是编译器传的 如果你改成别的类型可能匹配不上了

	//自定义类型后置++要拷贝两次 一次是保存加之前的值 一次是返回时拷贝
	//而前置++甚至不用拷贝对象 因为前置++返回的值就是加了之后的对象 它并不会离开了这个函数就销毁
	//所以可以返回引用
	//速度是比前置++慢的 所以自定义类型建议使用前置++
	Date& operator--();
	Date operator--(int);
	//日期减日期返回天数
	int operator-(const Date& d)const;
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
	void PrintWeekday()const;
private:
	int _year;
	int _month;
	int _day;
};
