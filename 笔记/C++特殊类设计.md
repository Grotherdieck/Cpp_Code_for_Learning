# 一、设计一个类 只能在堆上创建对象

&emsp;&emsp;正常一个类对象，既可以在堆上，也可以在栈上，还可以在静态区，我们这里的思路就是把正常创建对象的渠道给封掉。

&emsp;&emsp;首先把构造函数给私有化，这样你在类外没法直接构造对象了，然后专门提供一个public的函数去在堆上构造对象，为了让它和对象没有关系，我们把这个函数设为静态的：

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

&emsp;&emsp;但是我们当前的设计仍然还没有把所有的路都给堵死，构造函数没法创建对象了，还有拷贝构造啊，也得堵死：

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

# 二、设计一个类 只能在栈上创建对象

&emsp;&emsp;和之前的思路一样，把构造函数搞成私有，然后提供 ``CreateObj``函数去在堆上创建对象即可：

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

&emsp;&emsp;但是这样写还是有隐患：我们利用拷贝构造函数配合new还是能创建出堆上的对象：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713172659.png)

&emsp;&emsp;这种情况我们无法删掉拷贝构造，因为创建对象那里一定是传值返回，

&emsp;&emsp;有人可能会说，啊呀，那封掉拷贝构造增加移动构造不就行了嘛，但是我还可以通过 ``std::move``让new去创建堆对象：

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

&emsp;&emsp;所以这时，我们应该要去屏蔽new，注意到我们之间讲过一个类可以去定制它专属的 ``operator new``和 ``operator delete``，如果没定义的话会去调用全局的，那么我们把这俩玩意禁了不就好了：

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

# 三、设计一个类 不能被拷贝

&emsp;&emsp;如果是在C++98语法的限制下，我们可以把赋值运算符重载和拷贝构造都只声明不实现，并且为了防止类外补上实现，我们声明为私有：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713175323.png)

&emsp;&emsp;C++11直接delete掉拷贝构造和赋值运算符重载就行了：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713175458.png)

# 四、设计一个类 不能被继承

* C++98方式

&emsp;&emsp;因为派生类继承后，对于父类的部分，会调用父类的构造函数、析构、拷贝构造、赋值，所以我们把父类的构造函数搞成私有，因为私有成员对于继承的子类来说是不可见的，调不动父类的构造函数自然就没法继承了：

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

* C++11方式

&emsp;&emsp;直接给类后面加final关键字表明它无法被继承即可：

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

# 五、设计一个类 只能创建一个对象

**设计模式**：

&emsp;&emsp;设计模式（Design Pattern）是一套被反复使用、多数人知晓的、经过分类的、代码设计经验的总结。为什么会产生设计模式这样的东西呢？就像人类历史发展会产生兵法。最开始部落之间打仗时都是人拼人的对砍。后来春秋战国时期，七国之间经常打仗，就发现打仗也是有套路的，后来孙子就总结出了《孙子兵法》。孙子兵法也是类似。

&emsp;&emsp;使用设计模式的目的：为了代码可重用性、让代码更容易被他人理解、保证代码可靠性。 设计模式使代码编写真正工程化；设计模式是软件工程的基石脉络，如同大厦的结构一样。

&emsp;&emsp;比如迭代器模式也是一种设计模式，很多数据结构我们不希望提供底层结构给使用者，一来访问不方便，需要去熟悉底层的结构，二来这样很可能出现一些访问错误，为了解决这些问题，就有了迭代器模式。

&emsp;&emsp;迭代器模式的方法是以同一方式封装访问结构，不暴露地层结构，并且我们使用统一的方式去轻松访问容器，使用者不必关心底层数据结构具体是怎么实现的，比如我们用STL使用迭代器，如果熟悉了一个容器的迭代器的使用，大部分容器的迭代器其实都差不太多。

&emsp;&emsp;适配器模式我们也已经学习过了，在学习stack、queue、priority_queue的设计时，我们通过模板参数给这些容器提供底层结构，它给我们转化为我们希望的结构，其实反向迭代器reverse_iterator也是一种适配器模式，把迭代器给它，它给我们生成出适配器。

**单例模式:**

&emsp;&emsp;一个类只能创建一个对象，即单例模式，该模式可以保证系统中该类只有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。比如在某个服务器程序中，该服务器的配置信息存放在一个文件中，这些配置数据由一个单例对象统一读取，然后服务进程中的其他对象再通过这个单例对象获取这些配置信息，这种方式简化了在复杂环境下的配置管理。

&emsp;&emsp;如果我们想要创建一个对象，它是多个.cpp文件全局可见的，它的用途比如统计一个递归函数被调用了多少次，除了用extern在头文件中声明然后在某个文件中定义，有没有什么别的好的解决方法呢？

&emsp;&emsp;我们可以考虑设计一个单例模式来解决这个问题：

```cpp
// 目标 得知记忆化搜索的fib函数的递归函数_fib调用了多少次
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
	// 防止拷贝
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// 声明
	static CallCnt _inst;
};


int fib(int n);

int _fib(int n, vector<int>& f);


// singleton.cpp
#include "Singleton.h"

// 定义
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
		cout << fib(i) << ' ' << "记忆化搜索递归函数调用次数:";
		cout << CallCnt::GetInstance().GetCnt() << endl;
	}
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713193625.png)

&emsp;&emsp;这样就不存在我们前面可能多个文件里cnt冲突这个问题，不必去非常麻烦的搞extern和定义，并且可以把多个东西给封装起来，并且单例模式保证了只有整个进程中只有一份单例对象。

## 1 饿汉模式与懒汉模式

&emsp;&emsp;饿汉模式的意思是我们饥饿，希望你提前准备好，我随时都准备吃，如我们前面写的那个单例计数器，它在main函数之前就创建好了单例对象，程序随时都可以访问这个单例对象。

&emsp;&emsp;懒汉模式的意思就是我很懒，我不提前准备，你第一次想吃的时候我给你做饭，放到程序语言中就是我的程序第一次访问你的单例对象时我去创建这个单例对象。

&emsp;&emsp;懒汉模式我们可以通过指针来做到，一开始指针是空，如果第一次要获取单例时，我们再给它利用new申请。

```cpp
// 懒汉模式
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
	// 防止拷贝
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
	void destroy()
	{
		delete _pinst;
		cout << "单例模式资源已释放" << endl;
	}
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// 声明
	static CallCnt* _pinst;
};
// 初始化的地方：
// 定义
CallCnt* CallCnt::_pinst = nullptr;
```

## 2 懒汉模式的多线程问题

&emsp;&emsp;但是这个懒汉模式存在多线程安全问题，当多个线程同时进入GetInstance函数时，一个线程还没申请完内存时，另一个线程进来了，另个一线程同时进来了，就回申请出来两个单例，就bug了。

&emsp;&emsp;这里为了保证我们在申请好单例后能够并行的访问单例，我们增加一个双判定并且加一把锁就好咯：

```cpp
// 懒汉模式
class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		// 申请好后在外面，没有锁限制，可以并行的访问这个单例
		if (_pinst == nullptr)
		{
			// 假如第一次申请时多个线程同时进来 就会有一个线程抢到锁
			// 然后它出去后_pinst就不是Nullptr了
			// 他们直接走到下面去了
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
	// 防止拷贝
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// 声明
	static CallCnt* _pinst;
	static std::mutex mtx;
};

// 定义
CallCnt* CallCnt::_pinst = nullptr;
mutex CallCnt::mtx;
```

&emsp;&emsp;这种方式叫**双检查加锁**，如果我们直接把锁加在最外面，那么获取单例就变成了串行而非并行，如果我们把锁加在判空里面，那么另一个线程醒了以后还是会去再次new覆盖掉原单例，我们这种写在第一个if里面，醒了以后还要再次判断指针是否为空防止重复new覆盖原单例，并且创建好单例后，直接第一个if都不会进去，锁不会影响创建好单例后并行好获取单例的效率。

## 3 单例对象的释放问题

&emsp;&emsp;通常单例对象不需要释放，因为就一份嘛，等着main函数结束了OS释放进程资源时会帮我们释放掉就可以，如果一定想自己释放，比如希望析构时不仅释放资源，我还想写个日志啥的，那么就可以自己提供单例对象的释放，第一种方式可以提供一个destroy函数，记得要加锁，第二种方式是提供一个**内部类来做释放器。**

```cpp
class CGarbo
{
public:
	~CGarbo()
	{
		if (CallCnt::_pinst != nullptr)
		{
			delete CallCnt::_pinst;
			cout << "内部类CGarbo已完成垃圾回收" << endl;
		}
	}
};
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220713204106.png)

&emsp;&emsp;总测试代码：

```cpp
// Singleton.h

// 懒汉模式
class CallCnt
{
public:
	static CallCnt& GetInstance()
	{
		// 申请好后在外面，没有锁限制，可以并行的访问这个单例
		if (_pinst == nullptr)
		{
			// 假如第一次申请时多个线程同时进来 就会有一个线程抢到锁
			// 然后它出去后_pinst就不是Nullptr了
			// 他们直接走到下面去了
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
	// 防止拷贝
	CallCnt(const CallCnt& cc) = delete;
	CallCnt& operator=(const CallCnt& cc) = delete;
	// 自己写释放函数
	void destroy()
	{
		lock_guard<mutex> lg(mtx);
		delete _pinst;
		cout << "单例模式资源已释放" << endl;
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
				cout << "内部类CGarbo已完成垃圾回收" << endl;
			}
		}
	};
private:
	CallCnt() : _cnt(0) {}
	int _cnt;
	// 声明
	static CallCnt* _pinst;
	static std::mutex mtx;
	static CGarbo gc;
};


int fib(int n);

int _fib(int n, vector<int>& f);


// singleton.cpp
#include "Singleton.h"

// 定义
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

## 4 饿汉和懒汉的区别

&emsp;&emsp;饿汉的优点：简单、并且饿汉的单例在main函数之前就准备好了，没有线程安全问题。

&emsp;&emsp;饿汉的缺点：如果有两个单例，A的单例要求先创建，B的单例再创建，饿汉无法控制全局static单例对象的初始化顺序；另外，如果单例对象的初始化很消耗时间，会导致程序启动较慢，就好像程序卡死了一样。

&emsp;&emsp;懒汉模式的优点可以对应解决饿汉模式的缺点。

&emsp;&emsp;懒汉模式的缺点：相对复杂，尤其是它还要去控制线程安全问题。

&emsp;&emsp;另外，饿汉模式还可以通过static局部变量来实现，但是这种写法在C++98中会有多线程的线程安全问题，C++11优化了这一点。

```cpp
static CallCnt& GetInstance()
{
	static CallCnt cc;
	return cc;
}
```
