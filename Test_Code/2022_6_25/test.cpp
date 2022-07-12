#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <functional>	
#include <algorithm>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
using namespace std;

//int main()
//{
//	int a = 3;
//	auto p = [&] {a = 4; };
//	p();
//	cout << a << endl;
//	return 0;
//}

//int f(int a, int b)
//{
//	return a + b;
//}
//
//struct func
//{
//	double operator()(double a, double b) { return a + b; };
//};
//
//class sub
//{
//public:
//	static int isub(int a, int b)
//	{
//		return a - b;
//	}
//	double fsub(double a, double b)
//	{
//		return a - b;
//	}
//};
//
//
//int main()
//{
//	// 包装函数指针
//	function<int(int, int)> f1 = f;
//	cout << f1(1, 2) << endl;
//	// 包装仿函数
//	function<double(double, double)> f2 = func();
//	cout << f2(3.0, 2.0) << endl;
//	// 包装成员函数
//	function<int(int, int)> f3 = &sub::isub;
//	cout << f3(1, 3) << endl;
//	function<double(sub, double, double)> f4 = &sub::fsub;
//	cout << f4(sub(), 9.0, 10.0) << endl;
//	// 包装lambda表达式
//	auto p = [](const int a, const int b) { return a * b; };
//	function<int(int, int)> f5 = p;
//	cout << f5(3, 2) << endl;
//
//}
// 利用bind转变a和b的参数顺序
//int sub(int a, int b)
//{
//	return a - b;
//}
//
//class A
//{
//public:
//	int sub(int a, int b)
//	{
//		return a - b;
//	}
//};
//
//int main()
//{
//	// 先绑定第二个参数 再绑定第一个参数 从而调换了sub的两个参数顺序
//	function<int(int, int)> f1 = bind(sub, placeholders::_2, placeholders::_1);
//	cout << f1(1, 2) << endl;
//	cout << sub(1, 2) << endl;
//	// 第一个参数直接绑死 这样就把它适配为了一个function<int(int, int)>的包装器
//	function<int(int, int)> f2 = bind(&A::sub, A(), placeholders::_1, placeholders::_2);
//	cout << f2(3, 5) << endl;
//}

//atomic<int> x = 0;
//void Func(int n)
//{
//	// 2
//	for (int i = 0; i < n; ++i)
//	{
//		// 1
//		++x;
//	}
//}
//int main()
//{
//	thread t1(Func, 10000000);
//	thread t2(Func, 20000000);
//	t1.join();
//	t2.join();
//	cout << x << endl;
//}

//int main()
//{
//	int N = 1000000;
//	atomic<int> x = 0;
//	mutex mtx;
//	// int x = 0;
//	// int begin1 = clock();
//	atomic<int> time1 = 0;
//	atomic<int> time2 = 0;
//	int begin1, end1, begin2, end2;
//	thread t1([&] {
//		//mtx.lock();
//		begin1 = clock();
//		for (int i = 0; i < N; ++i)
//		{
//			// mtx.lock();
//			++x;
//			// mtx.unlock();
//		}
//		end1 = clock();
//		// mtx.unlock();
//	});
//	
//	//int begin2 = clock();
//	thread t2([&] {
//		// mtx.lock();
//		begin2 = clock();
//		for (int i = 0; i < N; ++i)
//		{
//			// mtx.lock();
//			++x;
//			// mtx.unlock();
//		}
//		end2 = clock();
//		// mtx.unlock();
//	});
//	t1.join();
//	// int end1 = clock();
//	t2.join();
//	// int end2 = clock();
//	cout << end1 - begin1 << "ms" << endl;
//	cout << end2 - begin2 << "ms" << endl;
//	cout << end2 - begin1 << "ms" << endl;
//}

int main()
{
	int N, M;
	cin >> N >> M;
	vector<thread> vthds(N);
	int x = 0;
	mutex mtx;
	for (int i = 0; i < N; ++i)
	{
		vthds[i] = thread([&x, &mtx, M] {
			mtx.lock();
			for (int i = 0; i < M; ++i)
			{
				++x;
				cout << this_thread::get_id() << "->" << x << endl;
			}
			mtx.unlock();
		});
	}
	for (auto& e : vthds)
	{
		e.join();
	}
	cout << "final : " << x << endl;
}
