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
//			// push_backʧ���˻����쳣
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
//	// ���ڻ�������֧�ֿ��� �������Ǽ�һ��&
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
//			// һ������������������ǹ�����
//			// ���������� ���캯��ʱ�Զ�����
//			// �����ǽ�������ѭ��������Ϊ�쳣�뿪������ ����������������Զ�����
//			// �����������RAII����
//			// push_backʧ���˻����쳣
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
	// �����flag ͬʱ����������t1�ȴ�ӡ(��Ϊһ��ʼflag��false t2����ȥ��һֱ��flag��wait��
	// ���ұ�֤��t1��ӡ���һ����t2��ӡ ��Ϊ��ʱflag����true�� t2��flag������ waitҲ�������� 
	// ֻ������ӡ���wait�Ļ�false t1���ܴ�ӡ
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