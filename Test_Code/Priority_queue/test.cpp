#define  _CRT_SECURE_NO_WARNINGS 1
#include "my_priority_queue.h"
void test_priority_queue()
{
	priority_queue<int*, vector<int*>, Less<int*>> pq;
	pq.push(new int(1));
	pq.push(new int(-5));
	pq.push(new int(-10));
	pq.push(new int(2));
	while (!pq.empty())
	{
		cout << *pq.top() << ' ';
		pq.pop();
	}
}

//struct Less
//{
//	bool operator()(int x, int y)
//	{
//		return x < y;
//	}
//};
//
//struct greater
//{
//	bool operator()(int x, int y)
//	{
//		return x > y;
//	}
//};



int main()
{
	test_priority_queue();
	/*Less<int> less;
	cout << less(1, 2) << endl;*/
	/*greater gt;
	cout << gt(3, 2) << endl;*/
}

//const int N = 100;
//template <class T, size_t num>
//class stack
//{
//public:
//	void push(const T& x);
//private:
//	T _arr[num];
//	size_t sz;
//};
//
//int main()
//{
//	array<int, 10> a1;
//	int a2[10];
//	cout << a1[10] << endl;
//	// cout << a2[10] << endl;
//	return 0;
//}

//struct Date
//{
//	int a;
//};
//
//template <class T>
//bool objless(const T& a, const T& b)
//{
//	return a < b;
//}
//
//template<>
//bool objless<const Date*&>(const Date*& a, const Date*& b)
//{
//	return true;
//}
//
//
//int main()
//{
//
//}