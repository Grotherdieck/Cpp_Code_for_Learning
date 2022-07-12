#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
using namespace std;

void func1(int* x)
{
	*x += 10;
}

void func2(int& x)
{
	x += 10;
}

int main()
{
	int n1 = 0, n2 = 0;
	thread t1(func1, &n1);
	thread t2(func2, std::ref(n2));
	t1.join();
	t2.join();
	cout << n1 << ',' << n2 << endl;
	return 0;
}



//int main()
//{
//	int N = 1000000;
//	// atomic<int> x = 0;
//	mutex mtx;
//	int x = 0;
//	// int begin1 = clock();
//	atomic<int> time1 = 0;
//	atomic<int> time2 = 0;
//	int begin1, end1, begin2, end2;
//	thread t1([&] {
//		// mtx.lock();
//		begin1 = clock();
//		for (int i = 0; i < N; ++i)
//		{
//			mtx.lock();
//			++x;
//			mtx.unlock();
//		}
//		end1 = clock();
//		// mtx.unlock();
//		});
//
//	//int begin2 = clock();
//	thread t2([&] {
//		// mtx.lock();
//		begin2 = clock();
//		for (int i = 0; i < N; ++i)
//		{
//			mtx.lock();
//			++x;
//			mtx.unlock();
//		}
//		end2 = clock();
//		// mtx.unlock();
//		});
//	t1.join();
//	// int end1 = clock();
//	t2.join();
//	// int end2 = clock();
//	cout << end1 - begin1 << "ms" << endl;
//	cout << end2 - begin2 << "ms" << endl;
//	cout << end2 - begin1 << "ms" << endl;
//	cout << x << endl;
//}



//int main()
//{
//	int x = 0;
//	thread t1([&] {
//		++x;
//	});
//	t1.join();
//	cout << x << endl;
//}
