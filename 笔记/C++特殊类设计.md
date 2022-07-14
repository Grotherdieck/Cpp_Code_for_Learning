# һ�����һ���� ֻ���ڶ��ϴ�������

&emsp;&emsp;����һ������󣬼ȿ����ڶ��ϣ�Ҳ������ջ�ϣ��������ھ�̬�������������˼·���ǰ�������������������������

&emsp;&emsp;���Ȱѹ��캯����˽�л���������������û��ֱ�ӹ�������ˣ�Ȼ��ר���ṩһ��public�ĺ���ȥ�ڶ��Ϲ������Ϊ�������Ͷ���û�й�ϵ�����ǰ����������Ϊ��̬�ģ�

```cpp
class HeapOnly
{
public:
	static HeapOnly* CreateObj(int a = 0)
	{
		return new HeapOnly(a);
	}
private:
	HeapOnly(int a = 0) : _a(a) {}
	int _a;
};


int main()
{
	HeapOnly ho;
	const HeapOnly hp;
	HeapOnly* pho = HeapOnly::CreateObj();
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713170627.png)

&emsp;&emsp;�������ǵ�ǰ�������Ȼ��û�а����е�·�������������캯��û�����������ˣ����п������찡��Ҳ�ö�����

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713171108.png)

```cpp
class HeapOnly
{
public:
	static HeapOnly* CreateObj(int a = 0)
	{
		return new HeapOnly(a);
	}

	HeapOnly(const HeapOnly& ho) = delete;

private:
	HeapOnly(int a = 0) : _a(a) {}
	int _a;
};


int main()
{
	//HeapOnly ho;
	//const HeapOnly hp;
	HeapOnly* pho = HeapOnly::CreateObj();
	HeapOnly copy(*pho);
}
```

# �������һ���� ֻ����ջ�ϴ�������

&emsp;&emsp;��֮ǰ��˼·һ�����ѹ��캯�����˽�У�Ȼ���ṩ ``CreateObj``����ȥ�ڶ��ϴ������󼴿ɣ�

```cpp
class StackOnly
{
public:
	static StackOnly CreateObj(int a)
	{
		return StackOnly(a);
	}
private:
	StackOnly(int a = 0) : _a(a) {}
	int _a;
};

int main()
{
	StackOnly so = StackOnly::CreateObj(1);
	StackOnly* ptr = new StackOnly;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713172020.png)

&emsp;&emsp;��������д�������������������ÿ������캯�����new�����ܴ��������ϵĶ���

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713172659.png)

&emsp;&emsp;������������޷�ɾ���������죬��Ϊ������������һ���Ǵ�ֵ���أ�

&emsp;&emsp;���˿��ܻ�˵����ѽ���Ƿ���������������ƶ����첻������������һ�����ͨ�� ``std::move``��newȥ�����Ѷ���

```cpp
class StackOnly
{
public:
	static StackOnly CreateObj(int a)
	{
		return StackOnly(a);
	}
	StackOnly(const StackOnly& so) = delete;
	StackOnly(StackOnly&& so) : _a(so._a) {}
private:
	StackOnly(int a = 0) : _a(a) {}
	int _a;
};

int main()
{
	StackOnly so = StackOnly::CreateObj(1);
	StackOnly* ptr = new StackOnly(std::move(so));
}
```

&emsp;&emsp;������ʱ������Ӧ��Ҫȥ����new��ע�⵽����֮�佲��һ�������ȥ������ר���� ``operator new``�� ``operator delete``�����û����Ļ���ȥ����ȫ�ֵģ���ô���ǰ�����������˲��ͺ��ˣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713174237.png)

```cpp
class StackOnly
{
public:
	static StackOnly CreateObj(int a)
	{
		return StackOnly(a);
	}
	void* operator new(size_t n) = delete;
	void operator delete(void*) = delete;
private:
	StackOnly(int a = 0) : _a(a) {}
	int _a;
};

int main()
{
	StackOnly so = StackOnly::CreateObj(1);
	StackOnly* ptr = new StackOnly(so);
}
```

# �������һ���� ���ܱ�����

&emsp;&emsp;�������C++98�﷨�������£����ǿ��԰Ѹ�ֵ��������غͿ������춼ֻ������ʵ�֣�����Ϊ�˷�ֹ���ⲹ��ʵ�֣���������Ϊ˽�У�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713175323.png)

&emsp;&emsp;C++11ֱ��delete����������͸�ֵ��������ؾ����ˣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713175458.png)

# �ġ����һ���� ���ܱ��̳�

* C++98��ʽ

&emsp;&emsp;��Ϊ������̳к󣬶��ڸ���Ĳ��֣�����ø���Ĺ��캯�����������������졢��ֵ���������ǰѸ���Ĺ��캯�����˽�У���Ϊ˽�г�Ա���ڼ̳е�������˵�ǲ��ɼ��ģ�����������Ĺ��캯����Ȼ��û���̳��ˣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713182127.png)

```cpp
class NoInherit
{
public:
private:
	NoInherit(int a = 0) : _a(a) {}
	int _a;
};


class test : public NoInherit
{
public:
	test() = default;
};


int main()
{
	test t;
}
```

* C++11��ʽ

&emsp;&emsp;ֱ�Ӹ�������final�ؼ��ֱ������޷����̳м��ɣ�

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713182248.png)

```cpp
class NoInherit final
{
public:
	NoInherit(int a = 0) : _a(a) {}
private:

	int _a;
};


class test : public NoInherit
{
public:
	test() = default;
};


int main()
{
	test t;
}
```

# �塢���һ���� ֻ�ܴ���һ������

**���ģʽ**��

&emsp;&emsp;���ģʽ��Design Pattern����һ�ױ�����ʹ�á�������֪���ġ���������ġ�������ƾ�����ܽᡣΪʲô��������ģʽ�����Ķ����أ�����������ʷ��չ������������ʼ����֮�����ʱ������ƴ�˵ĶԿ�����������ս��ʱ�ڣ��߹�֮�侭�����̣��ͷ��ִ���Ҳ������·�ģ��������Ӿ��ܽ���ˡ����ӱ����������ӱ���Ҳ�����ơ�

&emsp;&emsp;ʹ�����ģʽ��Ŀ�ģ�Ϊ�˴���������ԡ��ô�������ױ�������⡢��֤����ɿ��ԡ� ���ģʽʹ�����д�������̻������ģʽ��������̵Ļ�ʯ���磬��ͬ���õĽṹһ����

&emsp;&emsp;���������ģʽҲ��һ�����ģʽ���ܶ����ݽṹ���ǲ�ϣ���ṩ�ײ�ṹ��ʹ���ߣ�һ�����ʲ����㣬��Ҫȥ��Ϥ�ײ�Ľṹ�����������ܿ��ܳ���һЩ���ʴ���Ϊ�˽����Щ���⣬�����˵�����ģʽ��

&emsp;&emsp;������ģʽ�ķ�������ͬһ��ʽ��װ���ʽṹ������¶�ز�ṹ����������ʹ��ͳһ�ķ�ʽȥ���ɷ���������ʹ���߲��ع��ĵײ����ݽṹ��������ôʵ�ֵģ�����������STLʹ�õ������������Ϥ��һ�������ĵ�������ʹ�ã��󲿷������ĵ�������ʵ���̫�ࡣ

&emsp;&emsp;������ģʽ����Ҳ�Ѿ�ѧϰ���ˣ���ѧϰstack��queue��priority_queue�����ʱ������ͨ��ģ���������Щ�����ṩ�ײ�ṹ����������ת��Ϊ����ϣ���Ľṹ����ʵ���������reverse_iteratorҲ��һ��������ģʽ���ѵ����������������������ɳ���������

**����ģʽ:**

&emsp;&emsp;һ����ֻ�ܴ���һ�����󣬼�����ģʽ����ģʽ���Ա�֤ϵͳ�и���ֻ��һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㣬��ʵ�������г���ģ�鹲��������ĳ�������������У��÷�������������Ϣ�����һ���ļ��У���Щ����������һ����������ͳһ��ȡ��Ȼ���������е�����������ͨ��������������ȡ��Щ������Ϣ�����ַ�ʽ�����ڸ��ӻ����µ����ù���

&emsp;&emsp;���������Ҫ����һ���������Ƕ��.cpp�ļ�ȫ�ֿɼ��ģ�������;����ͳ��һ���ݹ麯���������˶��ٴΣ�������extern��ͷ�ļ�������Ȼ����ĳ���ļ��ж��壬��û��ʲô��ĺõĽ�������أ�

&emsp;&emsp;���ǿ��Կ������һ������ģʽ�����������⣺

```cpp
// Ŀ�� ��֪���仯������fib�����ĵݹ麯��_fib�����˶��ٴ�
//Singleton.h

#include <string>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;


class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		return _inst;
	}
	int operator++()
	{
		++_cnt;
		return _cnt;
	}
	int operator++(int)
	{
		return _cnt++;
	}
	int GetCnt()
	{
		return _cnt;
	}
	void reinit()
	{
		_cnt = 0;
	}
	// ��ֹ����
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// ����
	static CallCnt _inst;
};


int fib(int n);

int _fib(int n, vector<int>& f);


// singleton.cpp
#include "Singleton.h"

// ����
CallCnt CallCnt::_inst;

int fib(int n)
{
	CallCnt::GetInstance().reinit();
	vector<int> f(n);
	return _fib(n, f);
}

int _fib(int n, vector<int>& f)
{
	++CallCnt::GetInstance();
	if (n - 1 == 0) return f[0] = 1;
	else if (n - 1 == 1) return f[1] = 1;
	else
	{
		if (f[n - 1] != 0) return f[n - 1];
		else
		{
			return f[n - 1] = _fib(n - 1, f) + _fib(n - 2, f);
		}
	}
}

// test.cpp
#include "Singleton.h"
int main()
{
	for (int i = 1; i <= 100; ++i)
	{
		cout << fib(i) << ' ' << "���仯�����ݹ麯�����ô���:";
		cout << CallCnt::GetInstance().GetCnt() << endl;
	}
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713193625.png)

&emsp;&emsp;�����Ͳ���������ǰ����ܶ���ļ���cnt��ͻ������⣬����ȥ�ǳ��鷳�ĸ�extern�Ͷ��壬���ҿ��԰Ѷ����������װ���������ҵ���ģʽ��֤��ֻ������������ֻ��һ�ݵ�������

## 1 ����ģʽ������ģʽ

&emsp;&emsp;����ģʽ����˼�����Ǽ�����ϣ������ǰ׼���ã�����ʱ��׼���ԣ�������ǰ��д���Ǹ�����������������main����֮ǰ�ʹ������˵������󣬳�����ʱ�����Է��������������

&emsp;&emsp;����ģʽ����˼�����Һ������Ҳ���ǰ׼�������һ����Ե�ʱ���Ҹ����������ŵ����������о����ҵĳ����һ�η�����ĵ�������ʱ��ȥ���������������

&emsp;&emsp;����ģʽ���ǿ���ͨ��ָ����������һ��ʼָ���ǿգ������һ��Ҫ��ȡ����ʱ�������ٸ�������new���롣

```cpp
// ����ģʽ
class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		if (_pinst == nullptr)
		{
			_pinst = new CallCnt;
		}
		return *_pinst;
	}
	int operator++()
	{
		++_cnt;
		return _cnt;
	}
	int operator++(int)
	{
		return _cnt++;
	}
	int GetCnt()
	{
		return _cnt;
	}
	void reinit()
	{
		_cnt = 0;
	}
	// ��ֹ����
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
	void destroy()
	{
		delete _pinst;
		cout << "����ģʽ��Դ���ͷ�" << endl;
	}
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// ����
	static CallCnt* _pinst;
};
// ��ʼ���ĵط���
// ����
CallCnt* CallCnt::_pinst = nullptr;
```

## 2 ����ģʽ�Ķ��߳�����

&emsp;&emsp;�����������ģʽ���ڶ��̰߳�ȫ���⣬������߳�ͬʱ����GetInstance����ʱ��һ���̻߳�û�������ڴ�ʱ����һ���߳̽����ˣ����һ�߳�ͬʱ�����ˣ��ͻ��������������������bug�ˡ�

&emsp;&emsp;����Ϊ�˱�֤����������õ������ܹ����еķ��ʵ�������������һ��˫�ж����Ҽ�һ�����ͺÿ���

```cpp
// ����ģʽ
class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		// ����ú������棬û�������ƣ����Բ��еķ����������
		if (_pinst == nullptr)
		{
			// �����һ������ʱ����߳�ͬʱ���� �ͻ���һ���߳�������
			// Ȼ������ȥ��_pinst�Ͳ���Nullptr��
			// ����ֱ���ߵ�����ȥ��
			lock_guard<mutex> lg(mtx);
			if (_pinst == nullptr)
			{
				_pinst = new CallCnt;
			}
		}
		return *_pinst;
	}
	int operator++()
	{
		++_cnt;
		return _cnt;
	}
	int operator++(int)
	{
		return _cnt++;
	}
	int GetCnt()
	{
		return _cnt;
	}
	void reinit()
	{
		_cnt = 0;
	}
	// ��ֹ����
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// ����
	static CallCnt* _pinst;
	static std::mutex mtx;
};

// ����
CallCnt* CallCnt::_pinst = nullptr;
mutex CallCnt::mtx;
```

&emsp;&emsp;���ַ�ʽ��**˫������**���������ֱ�Ӱ������������棬��ô��ȡ�����ͱ���˴��ж��ǲ��У�������ǰ��������п����棬��ô��һ���߳������Ժ��ǻ�ȥ�ٴ�new���ǵ�ԭ��������������д�ڵ�һ��if���棬�����Ժ�Ҫ�ٴ��ж�ָ���Ƿ�Ϊ�շ�ֹ�ظ�new����ԭ���������Ҵ����õ�����ֱ�ӵ�һ��if�������ȥ��������Ӱ�촴���õ������кû�ȡ������Ч�ʡ�

## 3 ����������ͷ�����

&emsp;&emsp;ͨ������������Ҫ�ͷţ���Ϊ��һ�������main����������OS�ͷŽ�����Դʱ��������ͷŵ��Ϳ��ԣ����һ�����Լ��ͷţ�����ϣ������ʱ�����ͷ���Դ���һ���д����־ɶ�ģ���ô�Ϳ����Լ��ṩ����������ͷţ���һ�ַ�ʽ�����ṩһ��destroy�������ǵ�Ҫ�������ڶ��ַ�ʽ���ṩһ��**�ڲ��������ͷ�����**

```cpp
class CGarbo
{
public:
	~CGarbo()
	{
		if (CallCnt::_pinst != nullptr)
		{
			delete CallCnt::_pinst;
			cout << "�ڲ���CGarbo�������������" << endl;
		}
	}
};
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713204106.png)

&emsp;&emsp;�ܲ��Դ��룺

```cpp
// Singleton.h

// ����ģʽ
class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		// ����ú������棬û�������ƣ����Բ��еķ����������
		if (_pinst == nullptr)
		{
			// �����һ������ʱ����߳�ͬʱ���� �ͻ���һ���߳�������
			// Ȼ������ȥ��_pinst�Ͳ���Nullptr��
			// ����ֱ���ߵ�����ȥ��
			lock_guard<mutex> lg(mtx);
			if (_pinst == nullptr)
			{
				_pinst = new CallCnt;
			}
		}
		return *_pinst;
	}
	int operator++()
	{
		lock_guard<mutex> lg(mtx);
		++_cnt;
		return _cnt;
	}
	int operator++(int)
	{
		lock_guard<mutex> lg(mtx);
		return _cnt++;
	}
	int GetCnt()
	{
		return _cnt;
	}
	void reinit()
	{
		lock_guard<mutex> lg(mtx);
		_cnt = 0;
	}
	// ��ֹ����
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
	// �Լ�д�ͷź���
	void destroy()
	{
		lock_guard<mutex> lg(mtx);
		delete _pinst;
		cout << "����ģʽ��Դ���ͷ�" << endl;
		_pinst = nullptr;
	}
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (CallCnt::_pinst != nullptr)
			{
				delete CallCnt::_pinst;
				cout << "�ڲ���CGarbo�������������" << endl;
			}
		}
	};
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// ����
	static CallCnt* _pinst;
	static std::mutex mtx;
	static CGarbo gc;
};


int fib(int n);

int _fib(int n, vector<int>& f);


// singleton.cpp
#include "Singleton.h"

// ����
CallCnt* CallCnt::_pinst = nullptr;
mutex CallCnt::mtx;
CallCnt::CGarbo gc;

int fib(int n)
{
	CallCnt::GetInstance().reinit();
	vector<int> f(n);
	return _fib(n, f);
}

int _fib(int n, vector<int>& f)
{
	++CallCnt::GetInstance();
	if (f[n - 1] != 0) return f[n - 1];
	else if (n - 1 == 0)
	{
		f[0] = 1;
		return f[0];
	}
	else if (n - 1 == 1)
	{

		f[1] = 1;

		return f[1];
	}
	else
	{
		f[n - 1] = _fib(n - 1, f) + _fib(n - 2, f);
		return f[n - 1];

	}
}

// test.cpp
int main()
{
	thread t1 = thread(fib, 100);
	thread t2 = thread(fib, 100);


	Sleep(10000);
	t1.join();
	t2.join();
	cout << CallCnt::GetInstance().GetCnt() << endl;
	// CallCnt::GetInstance().destroy();
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713204406.png)

## 4 ����������������

&emsp;&emsp;�������ŵ㣺�򵥡����Ҷ����ĵ�����main����֮ǰ��׼�����ˣ�û���̰߳�ȫ���⡣

&emsp;&emsp;������ȱ�㣺���������������A�ĵ���Ҫ���ȴ�����B�ĵ����ٴ����������޷�����ȫ��static��������ĳ�ʼ��˳�����⣬�����������ĳ�ʼ��������ʱ�䣬�ᵼ�³��������������ͺ����������һ����

&emsp;&emsp;����ģʽ���ŵ���Զ�Ӧ�������ģʽ��ȱ�㡣

&emsp;&emsp;����ģʽ��ȱ�㣺��Ը��ӣ�����������Ҫȥ�����̰߳�ȫ���⡣

&emsp;&emsp;���⣬����ģʽ������ͨ��static�ֲ�������ʵ�֣���������д����C++98�л��ж��̵߳��̰߳�ȫ���⣬C++11�Ż�����һ�㡣

```cpp
static CallCnt& GetInstance()
{
	static CallCnt cc;
	return cc;
}
```
