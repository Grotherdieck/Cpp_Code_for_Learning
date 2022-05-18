#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
using namespace std;
//class Date {
//public:
//	void Init(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << '-' << _month << '-' << _year << '-';
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1;
//	Date d2;
//	d1.Init(2022, 1, 14);
//	d2.Init(2022, 1, 15);
//	d1.Print();
//	d2.Print();
//}

//class Date
//{
//public:
    //无参数的
    //Date()
    //{
    //    _year = 2022;
    //    _month = 1;
    //    _day = 1;
    //}
    ////有参数的
    //Date(int year = 2023, int month = 1, int day = 1)
    //{
    //    _year = year;
    //    _month = month;
    //    _day = day;
    //}
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    Date d1;
//    //int a = 1;
//    //cout << a << endl;
//}
//class A1
//{
//public:
//    A1(int a = 1)
//    {
//        cout << "A1(int)" << endl;
//    }
//};
//class A2
//{
//public:
//private:
//    int _a;
//    int _b;
//    A1 _A1;
//};
//int main()
//{
//    A2 a2;
//}
//class Date
//{
//public:
//    Date(int year = 2022, int month = 1, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//        cout << this << endl;
//    }
//
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    Date d1();
//}

//class Date
//{
//public:
//    ~Date()
//    {
//        cout << "~Date()" << endl;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//int main()
//{
//    Date d;
//}
//class Array
//{
//public:
//    Array(int capacity = 4)
//    {
//        _a = (int*)malloc(sizeof(int) * capacity);
//        _size = 0;
//        _capacity = capacity;
//    }
//    ~Array()
//    {
//        cout << "~Array()" << endl;
//        free(_a);
//        _a = nullptr;
//    }
//private:
//    int* _a;
//    int _size;
//    int _capacity;
//};
//
//int main()
//{
//    Array s1(4);
//    Array s2;
//}

//class A
//{
//public:
//    A()
//    {
//        cout << "A()" << endl;
//    }
//    A(const A& a)
//    {
//        cout << "A(const A&)" << endl;
//    }
//};

//class Date
//{
//public:
//    /*Date()
//    {
//        cout << "Date()" << endl;
//    }*/
//    Date(const Date& d)
//    {
//        _year = d._year;
//        //相当于d1._year 被d2._year赋值了
//        _month = d._month;
//        _day = d._day;
//    }
//    ~Date()
//    {
//        cout << "~Date()" << endl;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//    //A _aa;
//};
//
//void f(Date d)
//{
//    cout << "f(Date)" << endl;
//}
//
//int main()
//{
//    Date d1;
//    Date d2(d1);
//}

//class Date
//{
//public:
//    //无参数的
//    Date()
//    {
//        _year = 2022;
//        _month = 1;
//        _day = 1;
//    }
//    //有参数的
//    Date(int year = 2023, int month = 1, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    Date d1;
//    int a = 1;
//    cout << a << endl;
//}
//class A1
//{
//public:
//    A1(int date = 1, int m = 3)
//    {
//        _date = date;
//        _mmorpg = m;
//    }
//    virtual int getdate()
//    {
//        return _date + _mmorpg;
//    }
//protected:
//    int _mmorpg;
//private:
//    int _date;
//};
//class A2 : public A1
//{
//public:
//    A2()
//    {
//        cout << "A2()" << endl;
//    }
//    int getdate()
//    {
//        cout << "Imagine virtual function!" << endl;
//        return 1;
//        
//    }
//};
//
//void test(A1* a)
//{
//    cout << a->getdate() << endl;
//}
//
//int main()
//{
//    A2 a2;
//    test(&a2);
//    A1 a1(5,2);
//    a1 = a2;
//    test(&a1);
//}

#include <iostream>
using namespace std;

int cnt = 0;

class Widget
{
public:
    Widget()
    {
        cout << "Widget()" << endl;
    }
    Widget(const Widget& u)
    {
        cout << "Widget(const Widget&)" << endl;
        cnt++;
    }
};
Widget f(Widget u)
{
    Widget v(u);
    Widget w = v;
    return w;
}

int main()
{
    Widget x;
    Widget y = f(f(x));
    cout << cnt << endl;
}