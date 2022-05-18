#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <vector>
//class A
//{
//public:
//    A(int a)
//    {
//        _a = a;
//    }
//private:
//    int _a;
//};
//class Date
//{
//public:
//    Date(int year, int month, int day, int D, int x)
//        :_year(year),
//        _month(month),
//        _day(day),
//        _D(D),
//        _x(x),
//        a(3)
//    {}
//private:
//    int _year;
//    int _month;
//    int _day;
//    const int _D;
//    int& _x;
//    A a;
//};
//
//int main()
//{
//    int i;
//    //const int j;
//}
//class A
//{
//public:
//	A(int a = 1)
//	{
//		_a = a;
//		cout << "A(int)" << endl;
//	}
//	A& operator=(const A& a)
//	{
//		_a = a._a;
//		cout << "A& operator=" << endl;
//		return *this;
//	}
//	A(const A& a)
//	{
//		_a = a._a;
//		cout << "A(const A& a)" << endl;
//	}
//private:
//	int _a;
//};
//class D
//{
//public:
//	D(const A& aa)
//	{
//		_aa = aa;
//	}
//private:
//	A _aa;
//};
//
//int main()
//{
//	A a;
//	D d(a);
//}

//class Date
//{
//public:
//    Date(int year) :_year(year)
//    {
//        cout << "Date(int)" << endl;
//    }
//    explicit Date(const Date& d)
//    {
//        _year = d._year;
//    }
//private:
//    int _year;
//};
//
//int main()
//{
//    Date d = 2022;
//    Date d1 = d;//相当于隐式调用拷贝构造函数 被explicit禁止
//    Date(d);//隐式调用拷贝构造函数 被explicit禁止
//}

//class A
//{
//public:
//	A()
//	{
//
//	}
//private:
//	int& _x;
//
//
//};

//class A
//{
//public:
//    A(int a = 1) :_a(a)
//    {
//        ++_cnt;
//    }
//    A(const A& a) :_a(a._a)
//    {
//        ++_cnt;
//    }
//    static int Getcount()
//    {
//        return _cnt;
//    }
//private:
//    int _a;
//    static int _cnt;
//};
//
////初始化 可以不加static 但是要指明类域
//int A::_cnt = 0;
//
//int main()
//{
//    A a;
//    cout << a.Getcount() << endl;
//    cout << A::Getcount() << endl;
//}
//template <int N>
//struct sum
//{
//	static int _val = N + sum<N - 1>::_val;
//};
//template <>
//struct sum<0>
//{
//	static int _val = 0;
//};
//int main()
//{
//	cout << sum<5>::_val << endl;
//	
//}

//class sum
//{
//public:
//    sum()
//    {
//        ++_n;
//        _ret += _n;
//    }
//    static int GetRet()
//    {
//        return _ret;
//    }
//    int test()
//    {
//        cout << _ret << endl;
//    }
//private:
//    static int _n;
//    static int _ret;
//};
//int sum::_n = 0;
//int sum::_ret = 0;
//
//int main()
//{
//    int n;
//    cin >> n;
//    vector<sum>(n);
//    cout << sum::GetRet() << endl;
//
//}
//class A
//{
//public:
//    A(int a1)
//    {
//        _a1 = a1;
//    }
//private:
//    int _a1 = 0;//这里不是初始化
//    //试想，对象都没创建呢 你初始化什么空间？
//    //这里只是声明
//    //严格来说 这个 = 0给的是缺省值
//    int* _p = (int*)malloc(sizeof(int) * 4);
//    int arr[6] = { 1,2,3,4,5,6 };
//    //static int _u = 4;
//};
//
//int main()
//{
//    A a(4);
//}
//class A;
//class B
//{
//public:
//	friend class A;
//	void getA(const A& a);
//private:
//	int _b;
//};
//class A
//{
//public:
//	friend class B;
//	void getB(const B& b);
//private:
//	int _a;
//};
//
//void B::getA(const A& a)
//{
//	cout << a._a << endl;
//}
//void A::getB(const B& b)
//{
//	cout << b._b << endl;
//}
//
//int main()
//{
//	return 0;
//}

//class A
//{
//public:
//	A(int a)
//	{
//		_a = a;
//	}
//private:
//	int _a = 2;
//};
//
//int main()
//{
//	A a(3);
//}

//class A
//{
//public:
//	A(int a):_a(a)
//	{
//		_a = 3;
//		cout << "int a" << endl;
//	}
//	A(const A& a)
//	{
//		_a = a._a;
//	}
//private:
//	int _a = 1;
//};
//int main()
//{
//	A a(2);
//}

//class A
//{
//public:
//	A(int a = 1):_a(a)
//	{}
//	A(const A& a) :_a(a._a)
//	{
//		cout << "A(const A&)" << endl;
//	}
//private:
//	int _a;
//};
//class B
//{
//public:
//	B():_A(),_m(1)
//	{}
//	explicit B(const A& a, int m):_A(a),_m(m)
//	{}
//private:
//	A _A;
//	int _m;
//};
//
//int main()
//{
//	//B b;
//	A a(12);
//	B b1(a, 13);
//	B b2;
//
//	b2 = B(b1);
//}

class Date
{
public:
    Date(int year = 1) :_year(year)
    {
        cout << "Date(int)" << endl;
    }
    explicit Date(const Date& d)
    {
        _year = d._year;
    }
private:
    int _year;
};

int main()
{
    Date d = 2022;
    Date d1 = d;//相当于隐式调用拷贝构造函数 被explicit禁止
    Date e;
    e = Date(d);
}