#define  _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;



//void func(vector<int>& v, int n, int base, mutex& mtx)
//{
//	try
//	{
//		for (int i = 0; i < n; ++i)
//		{
//			mtx.lock();
//			// push_back失败了会抛异常
//			v.push_back(i + base);
//			if (base == 1000 && i == 88)
//				throw bad_alloc();
//			mtx.unlock();
//		}
//	}
//	catch (const exception& e)
//	{
//		// mtx.unlock();
//		cout << e.what() << endl;
//	}
//}
//
//int main()
//{
//	thread t1, t2;
//	mutex mtx;
//	vector<int> v;
//	
//	t1 = thread(func, std::ref(v), 100, 1000, std::ref(mtx));
//	t2 = thread(func, std::ref(v), 100, 2000, std::ref(mtx));
//	
//	
//	t1.join();
//	t2.join();
//}

//template <class Lock>
//class LockGuard
//{
//public:
//	LockGuard(Lock& lock) : _lock(lock)
//	{
//		_lock.lock();
//	}
//	~LockGuard()
//	{
//		_lock.unlock();
//	}
//private:
//	// 由于互斥锁不支持拷贝 这里我们加一个&
//	Lock& _lock;
//};
//
//void func(vector<int>& v, int n, int base, mutex& mtx)
//{
//	try
//	{
//		for (int i = 0; i < n; ++i)
//		{
//			lock_guard<mutex> lg(mtx);
//			// 一个叫锁守卫的类帮我们管理锁
//			// 在作用域内 构造函数时自动加锁
//			// 不论是结束这轮循环还是因为异常离开作用域 都会调用析构函数自动解锁
//			// 巧妙地利用了RAII机制
//			// push_back失败了会抛异常
//			v.push_back(i + base);
//			if (base == 1000 && i == 88)
//				throw bad_alloc();
//			// mtx.unlock();
//		}
//	}
//	catch (const exception& e)
//	{
//		// mtx.unlock();
//		cout << e.what() << endl;
//	}
//}
//
//int main()
//{
//	thread t1, t2;
//	mutex mtx;
//	vector<int> v;
//
//	t1 = thread(func, std::ref(v), 100, 1000, std::ref(mtx));
//	t2 = thread(func, std::ref(v), 100, 2000, std::ref(mtx));
//
//
//	t1.join();
//	t2.join();
//}

int main()
{
	int i = 0;
	int n = 100;
	bool flag = false;
	// 这里的flag 同时控制了能让t1先打印(因为一开始flag是false t2过不去会一直在flag下wait）
	// 而且保证了t1打印完后一定是t2打印 因为此时flag等于true了 t2从flag出来了 wait也被唤醒了 
	// 只有它打印完把wait改回false t1才能打印
	mutex mtx;
	condition_variable cv;
	thread t1([&]() {
		while (i < n)
		{
			unique_lock<mutex> ulk(mtx);
			cv.wait(ulk, [&flag] { return !flag; });
			++i;
			cout << this_thread::get_id() << ":->" << i << endl;
			flag = true;
			cv.notify_one();
		}
	});
	thread t2([&] {
		while (i < n)
		{
			unique_lock<mutex> ulk(mtx);
			cv.wait(ulk, [&flag] { return flag; });
			++i;
			cout << this_thread::get_id() << ">-" << i << endl;
			flag = false;
			cv.notify_one();
		}
	});
	t1.join();
	t2.join();
	return 0;
}