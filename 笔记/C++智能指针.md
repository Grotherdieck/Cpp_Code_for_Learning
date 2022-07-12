# һ��Ϊʲô��Ҫ����ָ�룿

&emsp;&emsp;C++Ϊʲô��Ҫ����ָ���أ���Python��Java����GC���Ƶ�OOP���ԣ�ͨ����û������ָ��ģ�����C++��������Ϊ�쳣��ȫ���⣬ͻȻ��Ϊ�쳣����catch�У�����new�����������Դû�б�����delete�������ͻ�����쳣��ȫ���⡣

&emsp;&emsp;����һ���쳣�У�����ͨ�����²����쳣�����������飬������û�дӸ�Դ�Ͻ��������⣬��������������²����쳣��ǰ������ж���������쳣��λ�ã��㻹Ҫͨ���ж����ĸ��쳣�����˰��Ҵ������쳣��������ط����൱���鷳�����������ʵ�����룺

```cpp
void div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0) throw exception("��0����");
	cout << a / b << endl;
}

int main()
{
	int* p1 = nullptr, *p2 = nullptr, *p3 = nullptr;
	try
	{
		p1 = new int[10000000];
		p2 = new int;
		p3 = new int;
		div();
	}
	catch (const exception& e)
	{
		// ��ΪnewҲ�������쳣 ����ô֪����p1�׵� ����p2�׵� ����p3�׵� ����div�׵�
		// �����p1�׳��쳣 ��ô����Ҫ����p2��p3
		// �����p2�׳��쳣 ��ô��Ҫdelete p1
		// �����p3�׳��쳣 ��ô��Ҫdelete p1 �� p2
		// �����div�׳��쳣 ��ô��Ҫdelete p1 p2 �� p3
		cout << e.what() << endl;
		if (p1 == nullptr)
		{

		}
		else if (p2 == nullptr)
		{
			delete p1;
		}
		else if (p3 == nullptr)
		{
			delete p1;
			delete p2;
		}
		else
		{
			delete p1;
			delete p2;
			delete p3;
		}
	}
}
```

# ������������ָ��ʵ��

&emsp;&emsp;��û��ʲô˼���ܰ����ǽ����������أ����Բο�����֮ǰд�� ``lock_guard``��д�������������뿪�����������������������������ͷ���Դ��

```cpp
template <class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr) : _ptr(ptr) {}
	~SmartPtr()
	{
		if (_ptr) delete _ptr;
		cout << "����ָ�����ͷ���Դ" << endl;
	}
private:
	T* _ptr;
};

void div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0) throw exception("��0����");
	cout << a / b << endl;
}

int main()
{
	int* p1 = nullptr, *p2 = nullptr, *p3 = nullptr;
	try
	{
		vector<int> vec;

		p1 = new int;
		SmartPtr<int> sp1(p1);
		p2 = new int;
		SmartPtr<int> sp2(p2);
		throw exception("test");
		p3 = new int;
		SmartPtr<int> sp3(p3);

		// vec.reserve(1000000000);

		div();
	}
	catch (const exception& e)
	{
		// ֱ���뿪�����򽻸�����ָ�봦��
		cout << e.what() << endl;
	}
}
```

&emsp;&emsp;����ͨ�� ``vector ``����ռ����ȥ��� ``bad_alloction``�쳣����Ȼ������������д������ָ���ܲ��ܰ����ǹ�����Դ��

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712091453.png)

&emsp;&emsp;�����Բ���Ҫp1 p2 p3��Щ��ָ�룬ֱ����new������ָ���ʼ����˳��������������أ�ʵ��һ�������ǵ�����ָ������ԭ��ָ��һ��������

```cpp
template <class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr) : _ptr(ptr) {}
	~SmartPtr()
	{
		if (_ptr) delete _ptr;
		cout << "����ָ�����ͷ���Դ" << endl;
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
private:
	T* _ptr;
};

void div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0) throw exception("��0����");
	cout << a / b << endl;
}

int main()
{
	try
	{
		vector<int> vec;

		SmartPtr<int> sp1(new int());
		SmartPtr<int> sp2(new int());
		// throw exception("test");
		SmartPtr<int> sp3(new int());
		(*sp1)++;
		// vec.reserve(1000000000);
		cout << *sp1 << ' ' << *sp2 << ' ' << *sp3 << endl;
		div();
	}
	catch (const exception& e)
	{
		// ֱ���뿪�����򽻸�����ָ�봦��
		cout << e.what() << endl;
	}
}
```

![img](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712093544.png)

# ��������ָ�����ϸԭ����ʵ��

## 3.1 RAII����

&emsp;&emsp;RAII��Resource Acquisition Is Initialization����ζ��Դ��ȡ��Ͱ�������һ����Ϊ���캯����һ������ȥ��ʼ��һ������Ȼ�����ö�����������������������Դ��

&emsp;&emsp;�ڶ�����ʱ��ȡ��Դ�����ſ��ƶ���Դ�ķ���ʹ֮�ڶ��������������ʼ�ձ�����Ч������ڶ���������
ʱ���ͷ���Դ����ˣ�����ʵ���ϰѹ���һ����Դ�������йܸ���һ��������������������ô���

* ����Ҫ��ʽ���ͷ���Դ��
* �������ַ�ʽ�������������Դ������������ʼ�ձ�����Ч��

&emsp;&emsp;����һ������������ָ���������ֻ��ƣ�RAII���ƹ�����Դ��ͨ��operator*��operator->��ָ��һ��������

## 3.2 ����ָ��ķ�չ��ʷ

&emsp;&emsp;��������������ǵ�����ָ�룬���������������ָ�룬Ĭ�Ͽ����ᰴ�ֽڿ�����Ȼ������ʱ�ͻ�delete���Σ��ͻᵼ�³��������

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712094634.png)

&emsp;&emsp;��ô����أ����ǣ����������ָ��ķ�չ��ʷ��

&emsp;&emsp;C++98���Ѿ�������ָ���ˣ��������������Ҳ�ǳ����ܣ�C++98������˹���Ȩת�Ƶ�˼�� ``auto_ptr``���뷨�ܼ򵥣���Ȼ������ָ��ͬһ��ռ������������ε����⣬��ôÿ��Ҫ������ʱ���Ҿ�ת�ƹ���Ȩ��

```cpp
auto_ptr(auto_ptr<T>& ap)
: _ptr(ap._ptr)
{
	// ��������ָ���ÿ� ��������Դ��
	ap._ptr = nullptr;
}
```

&emsp;&emsp;���������Ȼ��������������������������ұ������Ķ����ڿ�����������ˣ���������߲���Ϥ�����׾ͻᷢ����ָ������⡣

&emsp;&emsp;��һ������ͷ���� ``auto_ptr``��ʹ�ã��󲿷ֹ�˾�������ֹ ``auto_ptr``��ʹ�ã���֮��``auto_ptr``��һ��ʧ�ܵ���ơ�

&emsp;&emsp;���Ƕ�֪����C++98֮����һ����汾����C++11�����м��ѵ�C++������ָ���һֱ��ô�ã����׼���ȷʵһֱ��ô�ã�����C++��ֹ�б�׼���磬��Ϊ�����׼���µ�̫���ˣ��Ͼ�Ҫ׷��һ���ȶ����ܶ��׼����˽�����һ�����������Ǵ�����boost�⣬����̽��C++�ķ�չ����C++11֮ǰ��boost����Ѿ�����������Ϊʵ�õ�����ָ�롣

&emsp;&emsp;���Ƿֱ��ǣ�``scoped_ptr/shared_ptr/weak_ptr``��������������Ŀմ���������ָ��һ�㶼��������������C++11���º󣬰�������ָ�롰�����˹��������ְ�ʵ�ְ���΢����һ�£�������������ָ�룺``unique_ptr/shared_ptr/weak_ptr``�����Ƕ���ͷ�ļ� `<memory>`�С�

## 3.3 unique_ptr(Ψһָ��)

&emsp;&emsp;���Կ����Ĵ���ǳ��򵥴ֱ����������������㿽����Ҳ�����㸳ֵ��C++98��ͨ��ֻ������ʵ�֣�������˽�о��У�C++11�и��delete���ɡ�

```cpp
namespace scu
{
	template <class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr) : _ptr(ptr) {}
		~unique_ptr()
		{
			if (_ptr) delete _ptr, cout << "����ָ�����ͷ���Դ" << endl;
		}
		// ��ֹ���� ��ֹ��ֵ
		unique_ptr(const unique_ptr& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;
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
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712103444.png)

&emsp;&emsp;���������Ҫ�����أ��������ǾͿ����� ``shared_ptr``�ˡ�

## 3.4 shared_ptr(����ָ��)

&emsp;&emsp;shared_ptr�����˼·��**���ü�����**

&emsp;&emsp;ԭ����¼�ж��ٸ���������������Դ��ÿ����������ʱ--���������һ�������Ķ������ͷ���Դ��

&emsp;&emsp;���������������ľ�̬���ݳ�Ա���൱������ ``shared_ptr``ֻ��һ����̬��Ա��������кܶ����͵���Դ�أ�����P1 P2 P3����A���͵�ָ�룬P4��B���͵�ָ�룬���ѵ����ǹ���ͬһ��RefCount����Ȼ��������

&emsp;&emsp;����ϣ��**һ����Դ��һ�����ü�����**

&emsp;&emsp;�۲����ǵĳ������Բ�ͬ����Դ�Ĺ�������У���ĳһ����Դ��**ֻ�е�һ�ν��빹�캯��ʱ�������������Դ������������ǿ���������������캯��**��������ǿ����ڹ��캯��������һ�������������캯��ʱ������һ������Դ��ʾ���ü����������ٽ��뿽������ʱ��++������ü������ɡ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712125752.png)

&emsp;&emsp;ģ�����˼�룬����д�����Ĵ������£�

```cpp
namespace scu
{
	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr) : _ptr(ptr), _pRefCnt(new int(1)){}
		~shared_ptr()
		{
			--(*_pRefCnt);
			if ((*_pRefCnt) == 0 && _ptr)
			{
				delete _ptr;
				delete _pRefCnt;
				_ptr = nullptr;
				_pRefCnt = nullptr;
				cout << "scu::shared_ptr�ͷ��ڴ�ɹ�" << endl;
			}
		}
		shared_ptr(const shared_ptr& sp) : _ptr(sp._ptr), _pRefCnt(sp._pRefCnt)
		{
			++(*_pRefCnt);
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
	private:
		T* _ptr;
		int* _pRefCnt;
	};
}

int main()
{
	scu::shared_ptr<int> p1(new int(3));
	auto p2 = p1;
	auto p3 = p1;
	scu::shared_ptr<int> p4(new int(2));
	auto p5(p4);
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712130942.png)

&emsp;&emsp;���������ٿ���һ�¸�ֵ������ǹ����Ų�ͬ��ַ��ͬһ���͵���Դ��Ҳ�������ü����ĵ�ַ��ͬ����������������ü���Ӧ�ü�1���Ҳ����������ü���Ӧ�ü�1������������������ü�������0�ˣ���delete����

```cpp
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
		_pmtx = sp._pmtx;
		addRef();
	}
	return *this;
}
```

&emsp;&emsp;�������ǰѼ������ü��������ж������ü�����0�˾��ͷ���Դ�ŵ��˺���release�У����������ü����ŵ��˳�Ա����addRef�У�

```cpp
void release()
{
	--(*_pRefCnt);
	if ((*_pRefCnt) == 0 && _ptr)
	{
		delete _ptr;
		delete _pRefCnt;
		_ptr = nullptr;
		_pRefCnt = nullptr;
		cout << "scu::shared_ptr�ͷ��ڴ�ɹ�" << endl;
	}
}

void addRef()
{
	++(*_pRefCnt);
}
```

&emsp;&emsp;���Ƕ��߳�����£����ﻹ�б�����⣺���̳߳����£�ָ�����Դ������������ָ��ܣ��������Դ��ʹ�����Լ�ȥ����ȥ����������һ���������Ǳ���Ҫ��->**���ü������̰߳�ȫ����**��

&emsp;&emsp;������Ĵ��룺

```cpp
struct Date
{
	Date(int year = 2022, int month = 7, int day = 12) 
		: _year(year), _month(month), _day(day) 
	{}
	int _year, _month, _day;
};

void shared_ptr_func(scu::shared_ptr<Date>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		scu::shared_ptr<Date> copy(sp);
		copy->_day++;
		copy->_month++;
		copy->_year++;
	}
}

int main()
{
	scu::shared_ptr<Date> sp = new Date(2022, 7, 11);
	thread t1(shared_ptr_func, std::ref(sp), 100000);
	thread t2(shared_ptr_func, std::ref(sp), 100000);
	t1.join();
	t2.join();
	return 0;
}
```

&emsp;&emsp;�������ü������ܳ����̰߳�ȫ���⣺�����̶߳��ڿ���spʱ������˵���ü���Ӧ�ñ��3��Ȼ��ÿ��ѭ���������ü����ټ�1����������1�ص�1�������п��ܳ���ͬʱ�����Ǹ����ü�����Ȼ�󶼶�ȡ����1��Ȼ���2д�˻�ȥ��Ȼ������ʱ����������ָ�������ˣ�������0���ǲ��ͱ����𣬱��������������ʵ�飺

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712142559.png)

&emsp;&emsp;�������������Ե�������ǣ����̶߳�ͬһ������ָ�������п���������ʱ����ͬʱ++��--���ü�������ʱ���ü����ʹ����̰߳�ȫ���⡣

&emsp;&emsp;��ô����أ������£�ע�⣬������������ü�������һ��������һ����ȥ����һ�����ü�����**һ������Ӧһ����Դ**����������������Ҫ**����ָ�룬�ڼӼ����ü����ͼ������ü���ʱ��������**��

```cpp
namespace scu
{
	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr) : _ptr(ptr), _pRefCnt(new int(1)), _pmtx(new mutex) {}
		// ͬһ��--���ü��� ������ü�����ֵΪ0�˾�delete���߼��ŵ�����ȥ ͳһ��
		void release()
		{
			_pmtx->lock();
			--(*_pRefCnt);
			if ((*_pRefCnt) == 0 && _ptr)
			{
				delete _ptr;
				delete _pRefCnt;

				_ptr = nullptr;
				_pRefCnt = nullptr;

				cout << "scu::shared_ptr�ͷ��ڴ�ɹ�" << endl;
			}
			_pmtx->unlock();
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
		T* get()
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
}


struct Date
{
	Date(int year = 2022, int month = 7, int day = 12) 
		: _year(year), _month(month), _day(day) 
	{}
	int _year, _month, _day;
};

void shared_ptr_func(scu::shared_ptr<Date>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		scu::shared_ptr<Date> copy(sp);
		copy->_day++;
		copy->_month++;
		copy->_year++;
		// if (copy.getcnt() == 2) cout << copy.getcnt() << endl;
	}
}

int main()
{
	scu::shared_ptr<Date> sp = new Date(2022, 7, 11);
	int n = 100000;
	thread t1(shared_ptr_func, std::ref(sp), n);
	thread t2(shared_ptr_func, std::ref(sp), n);
	t1.join();
	t2.join();
	return 0;
}
```

&emsp;&emsp;����Ĵ��뻹��һ�����⣺ʲôʱ���ͷ�new�������ȽϺ����أ������ü���Ϊ0���ͷ���Դ���Ǹ�λ���ͷ�new�������϶����ԣ���Ϊ���滹Ҫ���������׵Ľ����������ͷ��һ�� ``flag``����Ȼ�����ͷ�new������Ӧ�������һ�����ü��������ͷţ���ô�����Ǹ��ط�flag��Ϊtrue��Ȼ��ÿ��release�Ǹ��ط����flagȥ�����ͷ������

```cpp
void release()
{
	_pmtx->lock();
	--(*_pRefCnt);
	bool flag = false;
	if ((*_pRefCnt) == 0 && _ptr)
	{
		delete _ptr;
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
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712151253.png)

&emsp;&emsp;��Ȼ����������ܹ��������ü������̰߳�ȫ�������ܷ�����ǵ���ԴҲһ��ͨ��������������أ���ϧ���ǲ����ܵģ���Ϊ������Դ�ĵط�������ָ��ʹ������ʹ�ý����ú�->�ĵط�����Щ�ط��������Ҳ�ܲ�������

&emsp;&emsp;��������ĺ������������ʶ���Դ���̰߳�ȫ������Ҫ�����Լ��ټ�һ������

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712152032.png)

&emsp;&emsp;�ٻ������������������RAII���ƣ�

```cpp
namespace scu
{
	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr) : _ptr(ptr), _pRefCnt(new int(1)), _pmtx(new mutex) {}
		// ͬһ��--���ü��� ������ü�����ֵΪ0�˾�delete���߼��ŵ�����ȥ ͳһ��
		void release()
		{
			_pmtx->lock();
			--(*_pRefCnt);
			bool flag = false;
			if ((*_pRefCnt) == 0 && _ptr)
			{
				delete _ptr;
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
		T* get()
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
}



struct Date
{
	Date(int year = 2022, int month = 7, int day = 12) 
		: _year(year), _month(month), _day(day) 
	{}
	int _year, _month, _day;
};

void shared_ptr_func(scu::shared_ptr<Date>& sp, int n, mutex& mtx)
{
	for (int i = 0; i < n; ++i)
	{
		scu::shared_ptr<Date> copy(sp);
		std::lock_guard<mutex> lg(mtx);
		copy->_day++;
		copy->_month++;
		copy->_year++;
		// mtx.unlock();
		// if (copy.getcnt() == 2) cout << copy.getcnt() << endl;
	}
}

int main()
{
	scu::shared_ptr<Date> sp = new Date(2022, 7, 11);
	int n = 100000;
	mutex mtx;
	thread t1(shared_ptr_func, std::ref(sp), n, std::ref(mtx));
	thread t2(shared_ptr_func, std::ref(sp), n, std::ref(mtx));
	t1.join();
	t2.join();
	return 0;
}
```

&emsp;&emsp;�����Ҫ����RAII��Դ�����ȣ���������һ���ֲ��򣬱�����������ӣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712153307.png)

&emsp;&emsp;���Զ�������C++�е�����ָ�����̰߳�ȫ���𣿻ش�Ӧ���������ģ�

&emsp;&emsp;C++�е�����ָ�����̰߳�ȫ�ģ���Ϊ�������ü����Ǽ����˵ģ���֤�˶��߳�����²���ͬʱ�ӼӼ�����Դ�����ü��������³������⣬��������ָ��ָ�����Դ���̰߳�ȫҪ�����Լ���֤��

## 3.5 shared_ptr��ѭ����������

&emsp;&emsp;ֻ������������ⳡ���У�shared_ptr�����һ��ѭ�����õ����⣺

&emsp;&emsp;����������һ��˫�������ǰ������������һ����Ϊ����ѧϰ������ָ������ǰ������е�ָ��ǰһ���ͺ�һ����ָ�붼���� ``shared_ptr``��������ʱҲʹ��shared_ptr����������ָ���ܰ��������������е�������㣺

```cpp
struct ListNode
{
	int _val;
	std::shared_ptr<ListNode> _next;
	std::shared_ptr<ListNode> _prev;
	ListNode() = default;
	~ListNode()
	{
		cout << "~ListNode" << endl;
	}
};

int main()
{
	shared_ptr<ListNode> n1(new ListNode);
	shared_ptr<ListNode> n2(new ListNode);
	n1->_next = n2;
	n2->_prev = n1;
	return 0;
}
```

&emsp;&emsp;���Ƿ�����ȫû����Դ�ͷţ�����ListNode�ڵ㶼ûȥ��������������

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712155901.png)

&emsp;&emsp;����Ϊɶ�أ��ο������ͼƬ���ͣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712201038.png)

&emsp;&emsp;��ͺ��������˴�ܣ���ץ�����ͷ������ץ���ҵ�ͷ����������Ҳ��������һ�������֣��Ҿ����㲻�����Ҿ�һ�������֣��������������˶�������һ���������֣������һ�������ˡ�

&emsp;&emsp;``shared_ptr``��ô�ã����Ǿ��������ѭ���������⡣���������Ҳ�Ҳ�����ô�޸�shared_ptr������������⣬��������ѡ�����ô����ѧϰʱ��ʶ��������⣬�����ṩһ�� ``weak_ptr``��Ӧ�����������

## 3.6 weak_ptr(��ָ��)

&emsp;&emsp;weak_ptr�����ǳ��������ϵ�����ָ�룬������ȥ����������ǵ���Դ������Դ����Ĺ��캯���п�������

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712163424.png)

&emsp;&emsp;������û��һ������ԭ��ָ��Ľӿڣ���Ҳ��ȥ��RAII���ƹ������ǵ���Դ��������Ҫ���ǿ��Դ� ``shared_ptr``�õ������ҿ�����һ��ָ��һ��������

&emsp;&emsp;�������ǿ��԰ѸոյĽڵ��ָ��ĳ� ``weak_ptr``��**������ȥ�������ü������������Ͳ���ȥ������Դ���ͷţ�**

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712163954.png)

&emsp;&emsp;weak_ptr����ȥ��ָ��һ��ȥ������Դ���޸�ֵ������������ȥ���ӻ�������ü���ȥ���������Щ��Դ��

&emsp;&emsp;���ǿ����Լ�дһ��weak_ptr���������ǿ��ǵ����ǵ�shared_ptrû��Ĭ�Ϲ��캯����Ϊ������һ��Ĭ�Ϲ��캯������ָ�붼�óɿյģ�Ȼ����΢�޲�һ��ϸ�ڣ�

```cpp
namespace scu
{
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
			// ��ֹ�ǿյ���ָ������������Ҹɱ��
			if (_pmtx != nullptr)
			{
				_pmtx->lock();
				--(*_pRefCnt);
				bool flag = false;
				if ((*_pRefCnt) == 0 && _ptr)
				{
					delete _ptr;
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
		T* get()
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
}
```

&emsp;&emsp;������һ�����׵�weak_ptr������ȥ�ṩ����shared_ptr������Ķ�������shared_ptr�����˶���֮��ģ�

```cpp
namespace scu
{
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
```

&emsp;&emsp;Ȼ�����ǵ�ѭ����������Ϳ������Լ�������ָ��ȥ�����������

```cpp
struct ListNode
{
	int _val = 0;
	scu::weak_ptr<ListNode> _next;
	scu::weak_ptr<ListNode> _prev;
	ListNode() = default;
	ListNode(int val) : _val(val), _next(), _prev() {}
	~ListNode()
	{
		cout << "~ListNode" << endl;
	}
};

int main()
{
	scu::shared_ptr<ListNode> n1(new ListNode(1));
	scu::shared_ptr<ListNode> n2(new ListNode(2));
	n1->_next = n2;
	n2->_prev = n1;
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712172605.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712172538.png)

## 3.7 Ϊ����ָ�붨��ɾ����

&emsp;&emsp;���ǵ���Դ��һ����new���İ���Ҳ������new[]���İ�����������malloc����fopen(�ⶼ��)�������Լ����ڴ����뺯����������ģ���������ڴ�ĺ���������ڴ�ĺ�����ƥ��ʹ�ã����п��ܻᱨ��

&emsp;&emsp;��׼���У�����ָ��ĵײ�Ĭ��ʹ��delete�������new[]������Դ���ͻ�����⣨��Ҫ�������������������������һ��������

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712173356.png)

&emsp;&emsp;�۲�unique_ptr�ı�׼���ף����ֻ���һ�������ģ�����������ɾ����

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712173518.png)

&emsp;&emsp;����ɾ������һ���ɵ��ö��������÷º���ʵ��һ������operator[]��Ĭ��ɾ������

```cpp
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

int main()
{
	unique_ptr<A, DeleteArray<A>> up(new A[10]);
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712174130.png)

&emsp;&emsp;��Ȼ��׼��Ϊ�����Ƿ���ʹ�ã�unique_ptr��shared_ptr����new[]ר���汾��

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712174639.png)

&emsp;&emsp;��������֧�������Լ���unique_ptr���Ӷ���ɾ������

```cpp
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
	scu::unique_ptr<A, DeleteArray<A>> up(new A[10]);
	scu::unique_ptr<FILE, FILEdel> up1(fopen("test.txt", "w"));
	std::shared_ptr<FILE> sp2(fopen("router.txt", "w"), FILEdel());
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712182040.png)

&emsp;&emsp;Ϊʲô˵����д������ָ�����˸�汾�أ���׼���У�shared_ptr�ȿ���ͨ��ģ�����ָ��ɾ������Ҳ����ͨ�����캯������ָ��ɾ�������������Ժ�lambda���ʽ�ܺõ���ϣ�����֮���Կ�������������Ϊ��ʵ���˺ü����汾�� ``shared_ptr``���ײ�ṹ������ȫ��ͬ�ģ���Ȼͨ��������������ô�������ɾ�����أ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712182633.png)

&emsp;&emsp;������������������ӣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220712183059.png)
