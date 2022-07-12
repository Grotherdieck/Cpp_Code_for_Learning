#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <thread>
#include <mutex>
using namespace std;

//class Person
//{
//public:
//	Person() = default;
//	Person(const Person& p) : _age(p._age), _name(p._name){}
//	Person(Person&& p) : _age(p._age)
//	{
//		_name = std::move(p._name);
//	}
//private:
//	int _age;
//	std::string _name;
//};
//
//
//int main()
//{
//	Person p1;
//}

//class A
//{
//public:
//	A() = default;
//	A* copy()
//	{
//		A* pa = new A(*this);
//		return pa;
//	}
//	A(const A& a) = delete;
//private:
//	// A(const A& a);
//	int _a;
//};
//
//int main()
//{
//	A a1;
//	// A a2 = a1;
//	A* p = a1.copy();
//	return 0;
//}

//template <class ...Args>
//void showlist(Args... args)
//{
//	std::cout << sizeof...(Args) << std::endl << std::endl;
//	/*for (size_t i = 0; i < sizeof...(args); ++i)
//	{
//		std::cout << args[i] << std::endl;
//	}*/
//}
//
//int main()
//{
//	showlist(1);
//	showlist(2, 'a');
//	showlist(3, 'c', std::string("sort"));
//}

// 递归解析它
// 要求 打印参数类型以及参数的值

//// 0个参数的递归终止函数
//template <class T>
//void showlist(const T& t)
//{
//	std::cout << typeid(t).name() << ":" << t << std::endl;
//}
//
//template<class T, class... Args>
//void showlist(T val, Args... args)
//{
//	// 第一个参数进来相当于直接传给了第一个模板参数T val
//	std::cout << typeid(val).name() << ":" << val << std::endl;
//	// 递归的把模板参数包传下去
//	showlist(args...);
//}
//
//
//int main()
//{
//	showlist(1);
//	showlist(2, 'a');
//	showlist(3, 'c', std::string("sort"));
//}

//template <class T>
//int PrintArgs(const T& t)
//{
//	std::cout << typeid(t).name() << ":" << t << std::endl;
//	return 0;
//}
//
//// 展开函数
//template <class... Args>
//void showlist(Args... args)
//{
//	int arr[] = { PrintArgs(args)... };
//	// 含义是先把参数包的第一个参数传给上面的PrintArgs函数
//	// 然后...按前面的方式依次展开
//	std::cout << std::endl;
//}
//
//int main()
//{
//	showlist(1);
//	showlist(2, 'a');
//	showlist(3, 'c', std::string("sort"));
//	return 0;
//}

//int main()
//{
//	std::vector<std::pair<int, int>> vec;
//	// 利用make_pair
//	vec.push_back(std::make_pair(1, 1));
//	// 利用成员pair的成员初始化列表
//	vec.push_back({ 2, 4 });
//	// emplace系列也支持上面的写法
//	vec.emplace_back(std::make_pair(3, 5));
//	// 利用emplace_back 无需写上面的东西
//	vec.emplace_back(3, 5);
//}

mutex mtx;

void Print(int n, int x)
{
	for (int i = 0; i < n; ++i)
	{
		mtx.lock();
		cout << i * x << endl;
		mtx.unlock();
	}
}



int main()
{
	vector<thread> vthds;
	int n = 10;
	vthds.resize(n);
	int i = 1;
	for (auto& t : vthds)
	{
		t = thread(Print, 10, i);
		// 线程不可拷贝 这里是移动赋值
		i++;
	}
	for (auto& t : vthds)
	{
		t.join();
	}
}