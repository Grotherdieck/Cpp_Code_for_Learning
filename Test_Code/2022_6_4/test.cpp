#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <array>
#include <algorithm>

using namespace std;

//int main()
//{
//	//// 容器
//	//vector<int> b{ 1, 3, 4, 5 };// 等号可以省略掉
//
//	//// 数组
//	//int a[]{ 1, 2, 3, 4, 5 };
//	//int* a1 = new int[5]{ 1, 3, 4, 2, 4 };
//
//	//// 内置变量
//	//int x{ 3 };
//	//int y{ 3 + 4 };
//
//	//map<int, int> mp{ make_pair(1, 2), {3, 2} };
//	double b;
//	cout << typeid(b).name() << endl;
//	decltype(b) a = 1.0;
//}

int func(int a)
{
	return a;
}

//int main()
//{
//	//int(*pfunc)(int) = func;// 函数指针 非常复杂吧
//	//decltype(&func) pf1 = func;
//	//decltype(func)* pf2 = func;
//	//cout << pf1(1) << endl;
//	//cout << pf2(3) << endl;
//	map<string, string> mp;
//	auto it = mp.begin();
//	vector<decltype(it)> v;
//	v.push_back(it);
//}

//int main()
//{
//	int arr1[10];
//	array<int, 10> a;
//	arr1[14] = 1;
//	// a[14] = 1;
//}

//int mymin(int x, int y) { return x < y ? x : y; }
//
//int main()
//{
//	/*int& rx = 10;
//	int x = 1, y = 3;
//	int& sumxy = x + y;
//	int& minxy = mymin(x, y);*/
//	const int& rx = 10;
//	int x = 1, y = 3;
//	const int c = 2;
//	const int& sumxy = x + y;
//	const int& minxy = mymin(x, y);
//
//	// 右值引用能否引用左值
//	/*int&& px = x;
//	int&& py = y;*/
//
//	// 右值引用可以引用move后的左值
//	int&& px = std::move(x);
//	int&& py = std::move(y);
//	const int&& pc = std::move(c);
//	int&& a = 0;
//	int&& b = 1;
//	a = 3;
//	b = 2;
//}

//int main()
//{
//	string s("hello world");
//	string s1 = move(s);
//}
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		cout << "String构造" << endl;
	}

	String(String&& s)
		:_str(nullptr)
	{
		cout << "String&&移动构造" << endl;
		std::swap(_str, s._str);
	}

	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		cout << "const String& 拷贝构造" << endl;
		strcpy(_str, s._str);
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pTemp = new char[strlen(s._str) + 1];
			strcpy(pTemp, s._str);
			delete[] _str;
			_str = pTemp;
		}
		return *this;
	}

	String& operator=(String&& s)
	{
		// 既然你传过来的是将亡值 
		// 我们直接就把你的资源转移给我 我要析构的资源给你

		std::swap(_str, s._str);
		return *this;
	}

	String operator+(const String& s)
	{
		char* pTemp = new char[strlen(_str) + strlen(s._str) + 1];
		strcpy(pTemp, _str);
		strcpy(pTemp + strlen(_str), s._str);
		String strRet(pTemp);
		return strRet;
	}

	~String()
	{
		if (_str) delete[] _str;
		if (_str != nullptr) cout << "~String" << endl;
	}
private:
	char* _str;
};

String To_String(String& s)
{
	String ret = s;
	return ret;
}

//int main()
//{
//	String s = "hello";
//	String b = itb(s);
//	String a;
//	a = std::move(s);
//}

//int main()
//{
//	String bit;
//	String a("hlllo");
//	bit = To_String(a);
//
//	int s = 1;
//	cout << s << endl;
//}
//int main()
//{
//	list<String> l1;
//	String s("hello");
//	l1.push_back(s);
//	cout << endl;
//	l1.push_back("2222222222");
//	cout << endl;
//	l1.push_back(To_String(s));
//	cout << endl;
//	auto&& p = l1;
//}

//int main()
//{
//	auto p = [](int a, int b)->int { return a + b; };
//	decltype(p) p2 = p;
//	cout << typeid(p).name() << endl;
//	auto p1 = [&p, &p2] { p(1, 3); p2(3, 4); cout << "hello world" << endl; };
//	p1();
//	int a = 1;
//
//	return 0;
//}

//int main()
//{
//	int a = 1;
//	int b = 2;
//	auto p = [=, &a]() {};
//	vector<int> arr;
//	cout << typeid(p).name() << endl;
//}

int main()
{
	vector<pair<int, String>> vec;
	vec.push_back({ 1, "1111111111" });
	vec.push_back(make_pair(2, "222222222"));
	cout << endl;
	// vec.emplace_back(make_pair(3, "3333333333"));
	vec.emplace_back(4, String("444444444"));
}