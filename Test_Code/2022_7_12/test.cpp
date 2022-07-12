#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;

//void div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0) throw exception("��0����");
//	cout << a / b << endl;
//}
//
//int main()
//{
//	int* p1 = nullptr, *p2 = nullptr, *p3 = nullptr;
//	try
//	{
//		p1 = new int[10000000];
//		p2 = new int;
//		p3 = new int;
//		div();
//	}
//	catch (const exception& e)
//	{
//		// ��ΪnewҲ�������쳣 ����ô֪����p1�׵� ����p2�׵� ����p3�׵� ����div�׵�
//		// �����p1�׳��쳣 ��ô����Ҫ����p2��p3
//		// �����p2�׳��쳣 ��ô��Ҫdelete p1
//		// �����p3�׳��쳣 ��ô��Ҫdelete p1 �� p2
//		// �����div�׳��쳣 ��ô��Ҫdelete p1 p2 �� p3
//		cout << e.what() << endl;
//		if (p1 == nullptr)
//		{
//
//		}
//		else if (p2 == nullptr)
//		{
//			delete p1;
//		}
//		else if (p3 == nullptr)
//		{
//			delete p1;
//			delete p2;
//		}
//		else
//		{
//			delete p1;
//			delete p2;
//			delete p3;
//		}
//	}
//}


//template <class T>
//class SmartPtr
//{
//public:
//	SmartPtr(T* ptr) : _ptr(ptr) {}
//	~SmartPtr()
//	{
//		if (_ptr) delete _ptr;
//		cout << "����ָ�����ͷ���Դ" << endl;
//	}
//	// ��ָ��һ��ʹ��
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};
//
//void div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0) throw exception("��0����");
//	cout << a / b << endl;
//}
//
//int main()
//{
//	try
//	{
//		vector<int> vec;
//		
//		SmartPtr<int> sp1(new int());
//		SmartPtr<int> sp2(new int());
//		// throw exception("test");
//		SmartPtr<int> sp3(new int());
//		SmartPtr<int> sp4(sp3);
//		(*sp1)++;
//		// vec.reserve(1000000000);
//		cout << *sp1 << ' ' << *sp2 << ' ' << *sp3 << endl;
//		div();
//	}
//	catch (const exception& e)
//	{
//		// ֱ���뿪�����򽻸�����ָ�봦��
//		cout << e.what() << endl;
//	}
//}

//
//namespace scu
//{
//	template <class T>
//	class auto_ptr
//	{
//	public:
//		auto_ptr(T* ptr) : _ptr(ptr) {}
//		~auto_ptr()
//		{
//			if (_ptr) delete _ptr, cout << "����ָ�����ͷ���Դ" << endl;
//		}
//		auto_ptr(auto_ptr<T>& ap)
//			: _ptr(ap._ptr)
//		{
//			// ��������ָ���ÿ� �����������
//			ap._ptr = nullptr;
//		}
//		// ��ָ��һ��ʹ��
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//	};
//}
//
//
//void div()
//{
//	int a, b;
//	cin >> a >> b;
//	if (b == 0) throw exception("��0����");
//	cout << a / b << endl;
//}
//
//int main()
//{
//	try
//	{
//		vector<int> vec;
//
//		scu::auto_ptr<int> sp1(new int());
//		scu::auto_ptr<int> sp2(new int());
//		// throw exception("test");
//		scu::auto_ptr<int> sp3(new int());
//		scu::auto_ptr<int> sp4(sp3);
//		(*sp1)++;
//		// vec.reserve(1000000000);
//		cout << *sp1 << ' ' << *sp2 << ' ' << *sp3 << endl;
//		div();
//	}
//	catch (const exception& e)
//	{
//		// ֱ���뿪�����򽻸�����ָ�봦��
//		cout << e.what() << endl;
//	}
//}

//namespace scu
//{
//	template <class T>
//	class unique_ptr
//	{
//	public:
//		unique_ptr(T* ptr) : _ptr(ptr) {}
//		~unique_ptr()
//		{
//			if (_ptr) delete _ptr, cout << "����ָ�����ͷ���Դ" << endl;
//		}
//		// ��ֹ���� ��ֹ��ֵ
//		unique_ptr(const unique_ptr& up) = delete;
//		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;
//		// ��ָ��һ��ʹ��
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//	};
//
//	template <class T>
//	class shared_ptr
//	{
//	public:
//		shared_ptr()
//			: _ptr(nullptr), _pRefCnt(nullptr), _pmtx(nullptr)
//		{}
//		shared_ptr(T* ptr) : _ptr(ptr), _pRefCnt(new int(1)), _pmtx(new mutex) {}
//		// ͬһ��--���ü��� ������ü�����ֵΪ0�˾�delete���߼��ŵ�����ȥ ͳһ��
//		void release()
//		{
//			if (_pmtx != nullptr)
//			{
//				_pmtx->lock();
//				--(*_pRefCnt);
//				bool flag = false;
//				if ((*_pRefCnt) == 0 && _ptr)
//				{
//					delete _ptr;
//					delete _pRefCnt;
//
//					_ptr = nullptr;
//					_pRefCnt = nullptr;
//					flag = true;
//					cout << "scu::shared_ptr�ͷ��ڴ�ɹ�" << endl;
//				}
//				_pmtx->unlock();
//				if (flag == true)
//				{
//					delete _pmtx;
//					_pmtx = nullptr;
//					cout << "new������ԴҲ�Ѿ��ͷ�" << endl;
//				}
//			}
//		}
//		// Ϊ����������� ��һ��addRef���� ��ʾ���ü���++
//		void addRef()
//		{
//			_pmtx->lock();
//			++(*_pRefCnt);
//			_pmtx->unlock();
//		}
//
//		~shared_ptr()
//		{
//			release();
//		}
//		shared_ptr(const shared_ptr& sp) : 
//			_ptr(sp._ptr), _pRefCnt(sp._pRefCnt), _pmtx(sp._pmtx)
//		{
//			addRef();
//		}
//		shared_ptr<T>& operator=(const shared_ptr& sp)
//		{
//			// ��ͬ��ַ��ͬ��������Դ
//			if (sp._pRefCnt != _pRefCnt)
//			// ��
//			// if (sp._ptr != _ptr)
//			{
//				release();
//				_pRefCnt = sp._pRefCnt;
//				_ptr = sp._ptr;
//				// �ǵ����ﻹҪ����
//				_pmtx = sp._pmtx;
//				addRef();
//			}
//			return *this;
//		}
//		// ��ָ��һ��ʹ��
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//		T* get() const 
//		{
//			return _ptr;
//		}
//		int getcnt() const 
//		{
//			return *_pRefCnt;
//		}
//	private:
//		T* _ptr;
//		int* _pRefCnt;
//		// ����ĳ�����ü������� ͬ���ڹ��캯�����ʼ��
//		std::mutex* _pmtx;
//	};
//	template <class T>
//	class weak_ptr
//	{
//	public:
//		weak_ptr() : _ptr(nullptr) {}
//		weak_ptr(const weak_ptr<T>& wp)
//			: _ptr(wp._ptr) {}
//		weak_ptr(const shared_ptr<T>& sp)
//			: _ptr(sp.get()) {}
//		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
//		{
//			_ptr = sp.get();
//			return *this;
//		}
//		weak_ptr<T>& operator=(const weak_ptr<T>& wp) = default;
//
//		T& operator*()
//		{
//			return *_ptr;
//		}
//
//		T* operator->()
//		{
//			return _ptr;
//		}
//	
//	private:
//		T* _ptr;
//	};
//}

//int main()
//{
//	scu::shared_ptr<int> p1(new int(3));
//	auto p2 = p1;
//	auto p3 = p1;
//	scu::shared_ptr<int> p4(new int(2));
//	auto p5(p4);
//	p5 = p1;
//	p4 = p1;
//}

//struct Date
//{
//	Date(int year = 2022, int month = 7, int day = 12) 
//		: _year(year), _month(month), _day(day) 
//	{}
//	int _year, _month, _day;
//};
//
//void shared_ptr_func(scu::shared_ptr<Date>& sp, int n, mutex& mtx)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		scu::shared_ptr<Date> copy(sp);
//		{
//			std::lock_guard<mutex> lg(mtx);
//			copy->_day++;
//			copy->_month++;
//			copy->_year++;
//		}
//		// do other thing...
//		
//		// mtx.unlock();
//		// if (copy.getcnt() == 2) cout << copy.getcnt() << endl;
//	}
//}
//
//int main()
//{
//	scu::shared_ptr<Date> sp = new Date(0, 0, 0);
//	int n = 100000;
//	mutex mtx;
//	thread t1(shared_ptr_func, std::ref(sp), n, std::ref(mtx));
//	thread t2(shared_ptr_func, std::ref(sp), n, std::ref(mtx));
//	t1.join();
//	t2.join();
//	cout << sp->_day << ' ' << sp->_month << ' ' << sp->_year << endl;
//	return 0;
//}

//struct ListNode
//{
//	int _val = 0;
//	scu::shared_ptr<ListNode> _next;
//	scu::shared_ptr<ListNode> _prev;
//	ListNode() = default;
//	ListNode(int val) : _val(val), _next(), _prev() {}
//	~ListNode()
//	{
//		cout << "~ListNode" << endl;
//	}
//};
//
//int main()
//{
//	scu::shared_ptr<ListNode> n1(new ListNode(1));
//	scu::shared_ptr<ListNode> n2(new ListNode(2));
//	n1->_next = n2;
//	n2->_prev = n1;
//	return 0;
//}


//class A
//{
//public:
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _a;
//};
//
//template <class T>
//struct DeleteArray
//{
//	void operator()(const T* ptr)
//	{
//		delete[] ptr;
//	}
//};
//
//int main()
//{
//	//unique_ptr<A, DeleteArray<A>> up(new A[10]);
//	unique_ptr<A[]> up1(new A[10]);
//	shared_ptr<A[]> sp(new A[10]);
//	return 0;
//}


namespace scu
{
	template <class T>
	struct DefaultDel
	{
		void operator()(const T* ptr)
		{
			delete ptr;
		}
	};
	template <class T, class D = DefaultDel<T>>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr) : _ptr(ptr) {}
		~unique_ptr()
		{
			if (_ptr) D()(_ptr), cout << "unique_ptr���ͷ���Դ" << endl;
		}
		// ��ֹ���� ��ֹ��ֵ
		unique_ptr(const unique_ptr& up) = delete;
		unique_ptr<T, D>& operator=(const unique_ptr<T, D>& up) = delete;
		// ��ָ��һ��ʹ��
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};

	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr()
			: _ptr(nullptr), _pRefCnt(nullptr), _pmtx(nullptr)
		{}
		shared_ptr(T* ptr) : _ptr(ptr), _pRefCnt(new int(1)), _pmtx(new mutex) {}
		// ͬһ��--���ü��� ������ü�����ֵΪ0�˾�delete���߼��ŵ�����ȥ ͳһ��
		void release()
		{
			if (_pmtx != nullptr)
			{
				_pmtx->lock();
				--(*_pRefCnt);
				bool flag = false;
				if ((*_pRefCnt) == 0 && _ptr)
				{
					delete _ptr;
					// D()(_ptr);
					delete _pRefCnt;

					_ptr = nullptr;
					_pRefCnt = nullptr;
					flag = true;
					cout << "scu::shared_ptr�ͷ��ڴ�ɹ�" << endl;
				}
				_pmtx->unlock();
				if (flag == true)
				{
					delete _pmtx;
					_pmtx = nullptr;
					cout << "new������ԴҲ�Ѿ��ͷ�" << endl;
				}
			}
		}
		// Ϊ����������� ��һ��addRef���� ��ʾ���ü���++
		void addRef()
		{
			_pmtx->lock();
			++(*_pRefCnt);
			_pmtx->unlock();
		}

		~shared_ptr()
		{
			release();
		}
		shared_ptr(const shared_ptr& sp) :
			_ptr(sp._ptr), _pRefCnt(sp._pRefCnt), _pmtx(sp._pmtx)
		{
			addRef();
		}
		shared_ptr<T>& operator=(const shared_ptr& sp)
		{
			// ��ͬ��ַ��ͬ��������Դ
			if (sp._pRefCnt != _pRefCnt)
				// ��
				// if (sp._ptr != _ptr)
			{
				release();
				_pRefCnt = sp._pRefCnt;
				_ptr = sp._ptr;
				// �ǵ����ﻹҪ����
				_pmtx = sp._pmtx;
				addRef();
			}
			return *this;
		}
		// ��ָ��һ��ʹ��
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
		T* get() const
		{
			return _ptr;
		}
		int getcnt() const
		{
			return *_pRefCnt;
		}
	private:
		T* _ptr;
		int* _pRefCnt;
		// ����ĳ�����ü������� ͬ���ڹ��캯�����ʼ��
		std::mutex* _pmtx;
	};
	template <class T>
	class weak_ptr
	{
	public:
		weak_ptr() : _ptr(nullptr) {}
		weak_ptr(const weak_ptr<T>& wp)
			: _ptr(wp._ptr) {}
		weak_ptr(const shared_ptr<T>& sp)
			: _ptr(sp.get()) {}
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
			return *this;
		}
		weak_ptr<T>& operator=(const weak_ptr<T>& wp) = default;

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

	private:
		T* _ptr;
	};
}


class A
{
public:
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};

template <class T>
struct DeleteArray
{
	void operator()(const T* ptr)
	{
		delete[] ptr;
	}
};


struct FILEdel
{
	void operator()(FILE* fp)
	{
		if (fp != nullptr) fclose(fp);
		cout << "�ļ�ָ��˳���ر�" << endl;
	}
};


int main()
{
	std::shared_ptr<FILE> sp1(fopen("router.txt", "w"), [](FILE* fp) {
		if (fp != nullptr) fclose(fp);
	});
	std::shared_ptr<FILE> sp2(fopen("test.txt", "w"), FILEdel());

	return 0;
}
