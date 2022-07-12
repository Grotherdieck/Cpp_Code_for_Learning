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

// �ݹ������
// Ҫ�� ��ӡ���������Լ�������ֵ

//// 0�������ĵݹ���ֹ����
//template <class T>
//void showlist(const T& t)
//{
//	std::cout << typeid(t).name() << ":" << t << std::endl;
//}
//
//template<class T, class... Args>
//void showlist(T val, Args... args)
//{
//	// ��һ�����������൱��ֱ�Ӵ����˵�һ��ģ�����T val
//	std::cout << typeid(val).name() << ":" << val << std::endl;
//	// �ݹ�İ�ģ�����������ȥ
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
//// չ������
//template <class... Args>
//void showlist(Args... args)
//{
//	int arr[] = { PrintArgs(args)... };
//	// �������ȰѲ������ĵ�һ���������������PrintArgs����
//	// Ȼ��...��ǰ��ķ�ʽ����չ��
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
//	// ����make_pair
//	vec.push_back(std::make_pair(1, 1));
//	// ���ó�Աpair�ĳ�Ա��ʼ���б�
//	vec.push_back({ 2, 4 });
//	// emplaceϵ��Ҳ֧�������д��
//	vec.emplace_back(std::make_pair(3, 5));
//	// ����emplace_back ����д����Ķ���
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
		// �̲߳��ɿ��� �������ƶ���ֵ
		i++;
	}
	for (auto& t : vthds)
	{
		t.join();
	}
}