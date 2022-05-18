# 一、非类型模板参数

## 1 引入

&emsp;&emsp;考虑一下场景，假如我们只需要给定空间大小的栈，不需要它增容。

```cpp
// C++希望用const来替代宏
const int N = 100;
template <class T>
class stack
{
private:
	T _arr[N];
	size_t sz;
};
```

&emsp;&emsp;但是我们想通过一个模板栈来生成一个100大小的栈，一个200大小的栈，显然用宏或``const int N``都不能解决，对此，非类型模板参数就可以解决这个问题。

```cpp
template <class T, size_t num>
class stack
{
public:
	void push(const T& x);
private:
	T _arr[num];
	size_t sz;
};
```

 &emsp;&emsp;非类型模板参数使用时它必须是常量，而非变量。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326172349.png" style="zoom:80%;" />

&emsp;&emsp;C++规定：非类型模板参数必须是整形常量，不可以是其他类型，C++20疑似可以使用浮点型做非类型模板参数了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326172603.png" style="zoom:80%;" />

## 2 非类型模板参数的样例—array

&emsp;&emsp;C++11中提供了``array``使用了非类型模板参数，它在头文件``<array>``中，表示固定长度的数组容器：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326173530.png" style="zoom:80%;" />

&emsp;&emsp;它支持各种迭代器：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326173826.png" style="zoom:80%;" />

&emsp;&emsp;它和C语言中的数组没有任何区别，唯一的区别就是它是对象，灵一个是数组，连物理上它们的大小都是一样的，它的元素也在栈上，初始化也不初始化，李在干神魔？

&emsp;&emsp;``array``算是C++11中非常鸡肋的设计了，真正的价值对比数组就是它对越界的检查更加严格，不像C语言的数组检查是抽查，可能查不出来：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326174255.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326174330.png" style="zoom:80%;" />

# 二、模板特化

&emsp;&emsp;特化的含义就是针对模板的某些参数的值进行特殊化处理 。

## 1 函数模板特化

&emsp;&emsp;假设我们写了一个仿函数：

```cpp
template <class T>
bool objless(const T& a, const T& b)
{
	return a < b;
}
```

&emsp;&emsp;但是当我们比大小的时候，对于有些类型（如自定义类型的指针），我不想比较指针的大小啊，我想比较它指向的元素的大小，但是我们这里只有一个函数模板，咋整呢？

&emsp;&emsp;解决方式有两种，一种是直接再增加一个函数，利用参数的匹配来解决模板函数不合适的问题。

```cpp
bool objless(const Date* p1, const Date* p2)
{
    return *p1 < *p2;
}
```

&emsp;&emsp;另一种方式是显式实例化：

```cpp
template<>
bool objless<Date*>(Date*& a, Date*& b)
{
	return true;
}
```

&emsp;&emsp;就相当于我特地为某个模板参数实例化了一份函数，这个语法被称为函数模板特化，但是明明有第一种方式了啊，很麻烦你这不是。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326175807.png" style="zoom:80%;" />

## 2 类模板的特化

&emsp;&emsp;特化的模板参数是类型模板参数和非类型模板参数都可以的。

&emsp;&emsp;假如我们的类模板希望对某种参数类型时可以调用生成不同的副本，就可以使用这个技术，如我们前面的优先级队列，假如参数是一个整形的指针，我们希望比较能够按照它们所指的对象进行比较而不是仅仅比较指针的地址大小，对于这种情况，我们就可以利用类模板特化，这看起来没有去显示的调用不同的仿函数。

```cpp
template <class T>
struct Less
{
	bool operator()(const T& x, const T& y) const
	{
		return x < y;
	}
};

// 特化
template <>
struct Less<int*>
{
	bool operator()(const int* x, const int* y) const
	{
		return *x < *y;
	}
};

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
```

&emsp;&emsp;没加以前：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326180917.png" style="zoom:80%;" />

&emsp;&emsp;加了以后：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326181004.png" style="zoom:80%;" />

### I 全特化

&emsp;&emsp;所有模板参数都给确定的值，就被称为全特化，语法就是在类名后面加上指定的类型。

```cpp
template<class T1, class T2>
class Data
{
public:
    Data() {cout<<"Data<T1, T2>" <<endl;}
private:
	T1 _d1;
	T2 _d2;
};
// 全特化
template<>
class Data<int, char>
{
public:
	Data() {cout<<"Data<int, char>" <<endl;}
private:
	int _d1;
	char _d2;
};
```

### II 偏(半)特化

&emsp;&emsp;偏特化不仅可以将模板参数列表中的一部分参数特殊化处理，还可以针对模板参数进行更进一步的限制，比如限定参数是指针类型就走我这个模板，限定参数是引用类型就走我这个模板，限定参数是引用类型和指针类型就走我这个模板等。

```cpp
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	
};
// 偏特化指定部分参数
template<class T>
class Data<T, char>
{
public:
	Data() { cout << "Data<T, char>" << endl; }
private:
	T _d1;
	char _d2;
};

// 限制为指针
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
private:
	T1* _d1;
	T2* _d2;
};
// 限定为引用
template<class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data() { cout << "Data<T1&, T2&>" << endl; }
private:
	
};

// 一个引用 一个指针
template<class T1, class T2>
class Data<T1&, T2*>
{
public:
	Data() { cout << "Data<T1&, T2*>" << endl; }
private:

};

// 非类型模板参数的特化
template<size_t N>
class A
{
public:
	A() { cout << "A<N>" << endl; }

};

template<>
class A<10>
{
public:
	A() { cout << "A<10>" << endl; }

};

int main()
{
	Data<int, int> d1;
	Data<int, char> d2;
	Data<double*, int*> d3;
	Data<double&, int&> d4;
	A<100> a1;
	A<10> a2;
	Data<double&, int*> d5;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328193253.png" style="zoom:80%;" />

# 三、模板的分离编译问题

&emsp;&emsp;对于通常的``CPP``项目，我们通常把声明放在``.h``中，实现放在一个``.cpp``中，这就是分离编译。

&emsp;&emsp;声明和定义分离的原因是因为这样写很容易维护，我们只要看``.h``文件就能把提供的功能和框架看明白，如果要看实现细节再去``.cpp``里头找。

&emsp;&emsp;但是遗憾的是模板不支持分离编译，下面测试一下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328194117.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328194141.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328194202.png" style="zoom:80%;" />

&emsp;&emsp;报了一个链接错误：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328194231.png" style="zoom:80%;" />

## 1 原因分析

&emsp;&emsp;目前我们有``test.h``和``test.cpp``和``main.cpp``，首先会进行**预处理**，完成头文件展开、条件编译、宏的替换、去注释等，得到``test.i``和``main.i``。

&emsp;&emsp;这时那个函数模板的定义就展开在了``test.i``的前面和``main.i``的前面。

&emsp;&emsp;接下来的步骤是**编译**，会检查语法错误，如果没有问题生成汇编代码，会生成两份汇编代码``test.s``和``main.s``。

&emsp;&emsp;编译器在处理``test.s``中的模板函数时，因为我不知道T的类型，我都不知道要建多大的栈帧，且在``test.cpp``中没有显示的调用``add``，所以函数模板``add``不会被编译出来。

&emsp;&emsp;在``main.s``中，调用``add(1,2)``需要变成``call 函数地址``的指令，这里没有``add``的地址，但是编译依然可以通过，因为我们包了``test.h``，里头有声明嘛，函数模板的声明也是声明，我们可以等着链接阶段找。

&emsp;&emsp;接下来会进行**汇编**过程，把汇编代码转化成二进制机器码。

&emsp;&emsp;然后是**链接**过程，我们需要去根据符号表在其他的文件中找到那个符号对应的函数定义，获得函数的地址，但是这里出问题了，我们的``test.cpp``中``add``函数根本就没别编译，因为它咋``test.cpp``中没有被调用过，编译器根据模板的特性不会实例化它，所以链接这一步就会找不到``add()``的地址，

## 2 解决方法

&emsp;&emsp;既然是因为没有实例化``add``而导致链接错误，所以我们的第一种解决方式就是**显示实例化**：

```cpp
template
int add<int>(const int& a, const int& b);
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328202221.png" style="zoom:80%;" />

&emsp;&emsp;用一个实例化一个，不过这样就有点失去了泛型的意义。

&emsp;&emsp;另一种解决方式就是你不要把声明和定义分离，**声明和定义放在同一个文件中**，通常用``.hpp``或``.h``来放，先写声明表明接口，然后再写定义，``#include ``后我编译时就能找到``call``的入口，使用它的地方直接就有定义，不需要链接再去找地址。

&emsp;&emsp;对于类模板，分离编译时，有了类模板的声明，就可以定义指针，这说明有了声明就可以调用类型，但是利用类模板定义对象时还是会出现类模板未实例化而找不到构造函数：

&emsp;&emsp;这个指针可以定义，但是不能用这个指针调用任何函数，因为类模板尚未实例化，找不到对应函数的地址。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328211204.png" style="zoom:80%;" />

&emsp;&emsp;对象无法定义：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328211330.png" style="zoom:80%;" />

&emsp;&emsp;指针可以正常定义：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328211415.png" style="zoom:80%;" />

# 四、模板总结

&emsp;&emsp;优点：

- 模板复用了代码，能够快速的迭代开发，支持不同类型的数据结构库``STL``由此诞生。
- 增强了代码的灵活性，如模板仿函数。

&emsp;&emsp;缺点：

- 模板的多次实例化会导致代码膨胀，也会导致编译时间变得很长。
- 出现模板编译错误时，报错信息会非常混乱，难以定位。