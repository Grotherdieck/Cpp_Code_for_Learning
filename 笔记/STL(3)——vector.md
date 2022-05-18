# 一、vector的介绍与使用

&emsp;&emsp;``vector``是一个可以动态增长的用数组实现的顺序容器。

&emsp;&emsp;``vector``是一个模板类，声明如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304124239.png" style="zoom:80%;" />

&emsp;&emsp;其第二个参数的含义是一个空间分配器(即内存池)，是为了降低频繁向系统申请空间影响效率，为提升效率而设计的。

## 1 构造函数

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304125107.png" style="zoom:80%;" />

&emsp;&emsp;支持四种构造函数：无参数构造、n个val来初始化、支持一段迭代器区间初始化、支持拷贝构造初始化。

```cpp
int main()
{
	vector<int> v1;
	int n = 8;
	vector<int> v2(n, 4);
	vector<int> v3(++v2.begin(), --v2.end());
	vector<int> v4(v2);
	
	string s("hello");
	vector<char> v5(s.begin(), s.end());
}
```

&emsp;&emsp;``string``不能够被``vector<char>``替代，因为``string``支持了很多字符串的有关比较和操作，而``vector``因为支持多种类型，它没有比较操作啥的，并且它也不提供子串查找。

&emsp;&emsp;这里的``value_type()``,对于自定义类型这就是默认构造函数，对于内置类型，C++也提供了默认构造函数，即可以使用``int a = int();``或``int a = int(10);``

## 2 赋值运算符重载

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304125848.png" style="zoom:80%;" />

&emsp;&emsp;它实现的是深拷贝。

## 3 vector的遍历操作

**opeartor[]系列访问**

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304130041.png" style="zoom:80%;" />

&emsp;&emsp;与``string``类似，``operator[]``是使用``assert``判断越界，``at``是通过抛异常来判断越界

**迭代器**

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304130209.png" style="zoom:80%;" />

&emsp;&emsp;支持迭代器则支持范围for，范围for会被替换成迭代器。

## 4 容量操作

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304130542.png" style="zoom:80%;" />

&emsp;&emsp;它的``max_size``是string的``max_size``去除以对象大小获得的。

```cpp
int main()
{
	vector<int> a;
	cout << a.max_size() << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304130716.png" style="zoom:80%;" />

&emsp;&emsp;``reserve``和``resize``和``string``的比较类似，``reserve``是申请容量，``resize``如果把空间扩大时你没有给参数那么就会填上对应类型的缺省值，对于自定义类型的缺省值，C++规定整形的缺省值都是0，浮点型的缺省值也是0，char类型的缺省值是``\0``,指针类型的缺省值是空指针。

&emsp;&emsp;``resize``缩容器元素个数时，一般不会把空间干掉，不过C++标准对此并没有规定。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304131024.png" style="zoom:80%;" />

## 5 修改操作

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304131631.png" style="zoom:80%;" />

**assign**:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304131716.png" style="zoom:67%;" />

&emsp;&emsp;可以用迭代器范围或用n个val来给容器赋值，如果范围大于当前容量capacity会扩容。

## 6 查找操作

&emsp;&emsp;在``cppreference``网页中按``ctrl + f``:搜索``find``,发现``vector``容器的成员函数中没有查找：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304132034.png" style="zoom:80%;" />

&emsp;&emsp;这并不意味着``vector``不能查找，``vector``可以通过C++提供的泛型算法``find``进行查找，理由也很简单，vector和其他顺序容器都会使用迭代器来实现查找功能，所以直接把使用迭代器实现查找的功能放在``<algorithm>``中了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304132205.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304132328.png" style="zoom:80%;" />

&emsp;&emsp;``find``的使用要注意的是如果找不到，``find``会返回指向``end()``的迭代器，若找到了，则会返回指向目标元素的迭代器，每次``find``完了记得看看找没找到再进行对应操作

&emsp;&emsp;在C++中，迭代器区间对应的实际范围都是[a,b).

```cpp
int main()
{
	vector<int> a;
	for (int i = 1; i <= 5; ++i) a.push_back(i);
	vector<int>::iterator ret = find(a.begin(), a.end(), 3);
	if (ret != a.end())
	{
		cout << "I find it!" << endl;
	}
}
```

&emsp;&emsp;``string``之所以提供``find``的另一个原因是``string``的``find``还要提供查找子串的功能，这个需求明显与泛型算法实现的功能不同。

**insert**：在迭代器指向的位置之前插入元素，效率比较低。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304133008.png" style="zoom:80%;" />

**erase**：删除某个迭代器指向的值，或删除迭代器区间的值。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304133520.png" style="zoom:80%;" />

&emsp;&emsp;在删除之前一定要判断迭代器是否是合法位置，这样删除才有意义，否则可能会导致崩溃。

```cpp
int main()
{
	vector<int> a;
	for (int i = 1; i <= 5; ++i) a.push_back(i);
	vector<int>::iterator ret = find(a.begin(), a.end(), 30);
	a.erase(ret);
	for (auto e : a)
	{
		cout << e << ' ';
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304133653.png" style="zoom:80%;" />

&emsp;&emsp;并且最好不要在使用迭代器插入后立刻删除，插入操作可能会造成迭代器失效进而导致删除错误。

**clear**：清掉元素，但是空间不一定回收。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304134153.png" style="zoom:80%;" />

## 7 vector的增容方式

&emsp;&emsp;通过以下代码测试，发现VS下是1.5倍左右的增容，Linux下g++是两倍的增容，这点和``string``一样。

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> a;
	cout << a.capacity() << endl;
	size_t sz = a.capacity();
	for (int i = 1; i <= 100; ++i)
	{
		a.push_back(i);
		if (a.capacity() != sz)
		{
			cout << "capacity changed :" << a.capacity() << endl;
			sz = a.capacity();
		}
	}
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304134612.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304134952.png" style="zoom:80%;" />

## 8 vector的嵌套结构

&emsp;&emsp;两层的``vector``其实实现的是一个表装结构，外层``vector``容器其容器内元素类型是一个一个动态增容的顺序表``vector<value_type>``,内层的``vector<value_type>``容器就是一个元素类型是``value_tpye``的动态增容的顺序表。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220305205604.png" style="zoom:80%;" />

&emsp;&emsp;其余多层嵌套的结构是类似的。

# 二、vector的模拟实现

## 1 vector的主要架构

&emsp;&emsp;``vector``和``string``不同，它是一个可以指定元素类型的模板类，元素类型可以是普通类型也可以是自定义类型，并不像``string``一样拘泥于字符类型，因此我们要使用``template``技术来模拟``vector``，首先我们先参考``STL``中``vector``的源码来看看``vector``的具体架构.

&emsp;&emsp;VS中的``vector``源码可以通过直接头文件转到定义看，不过VS写的有点乱，所以我们如果要阅读``STL``源码一般不参考它。

&emsp;&emsp;一般建议参考``STL3.0``版本的源码，因为它和侯捷老师的那本书的版本是契合的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220305165622.png" style="zoom:80%;" />

&emsp;&emsp;我们可以看到框架是一个开始位置的指针start，一个finish指向结束位置后一个位置的指针，一个end_of_storage是指向空间结束的位置的指针，我们暂时不考虑空间分配器的问题，我们当前使用new申请内存。

&emsp;&emsp;这与我们使用一个指针加上``size``和``capacity``是一样的，因为我们可以通过指针的运算互相转化。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220305194628.png" style="zoom:80%;" />

&emsp;&emsp;因此我们这里采用和它一样的架构，即``_start``指向起始地址的指针，``_finish``是指向当前数组结尾位置的后一个位置的指针，``end_of_storage``是指向空间结尾位置的指针，并且注意到指针就是迭代器，为了隔离std中的vector，我们使用一个命名空间与其隔离,因此我们的架构如下：

```cpp
namespace lyq
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
}
```

## 2 默认构造函数

&emsp;&emsp;空的vector中不含任何对象，也不用像string那样设计成含有一个``'\0'``，因此我们可以直接给它赋空指针。

```cpp
vector(): _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
{}
```

## 3 容器大小和容器容量

&emsp;&emsp;正如我们在架构里头画的那样，我们可以利用指针相减来获得size和capacity。

```cpp
size_t size() const
{
    return _finish - _start;
}
size_t capacity() const
{
    return _end_of_storage - _start;
}
```

## 4 增容的实现

**reserve**

&emsp;&emsp;增容的逻辑与string中类似，如果申请的容量n大于当前capacity，那么就先用``tmp``接受一个new出来的n块空间的指针，然后如果``_start``本来指向一块地方，即``_start != nullptr``，就先把原来的空间拷贝过来，然后释放``_start``的空间，然后``_start``等于``tmp``,对应修改``_finish``和``_end_of_storage``即可。

&emsp;&emsp;需要注意的是，这里不要用``memcpy``这种字节序拷贝,因为如果T的成员中有一个数据成员是指向一块空间的地址，那么使用``memcpy``又会造成浅拷贝的问题，我们这里可以调用``operator=``,这样只要你自己的对象的``operator=``实现了深拷贝，我也就实现了深拷贝。

&emsp;&emsp;另外要注意的点是当``_start = tmp``后，后续的``size()``和``capacity()``由于实现的问题已经会不能得出正确的结果，所以要么先把``size()``存起来，要么需要先处理``_finish = tmp + size();``后再处理``_start = tmp;``.

```cpp
void reserve(int n)
{
    if (n > capacity())
    {
        iterator tmp = new T[n];
		size_t sz = size();
        if (_start != nullptr)
        {
            for (int i = 0; i < sz; ++i)
			{
                tmp[i] = _start[i];
			}
			delete[] _start;
        }
		_start = tmp;
        _finish = tmp + sz;
		_end_of_storage = tmp + n;
    }
}
```

**resize**

```cpp
void resize(size_t n, const T& x = T());
// 虽然匿名对象的声明周期只有这一行 但是当我们加了const&它的声明周期就会延长到引用变量销毁时销毁。
// VS要求你的类型要有自己写的构造函数 这是个BUG
```

&emsp;&emsp;这里的实现与string中的resize类似，都是考虑三种情况：``size() < n;size() < n < capacity(); n > capacity()``

&emsp;&emsp;第一种情况，直接把finish移动到``_start + n``的位置即可；

&emsp;&emsp;第二种情况，我们把``_start + size()``到``_start + n``都置成那个x即可，注意这里我们用移动``_finish``来完成，这样同时可以把``size()``给改变了。

&emsp;&emsp;第三种情况，我们需要扩容至n，然后把``_start + size()``到``_start + n``的位置都置成x即可。

&emsp;&emsp;那个缺省值是使用了一个匿名对象的技术，这样各种类型就可以使用它们的默认构造函数生成缺省值（C++对内置类型也有自己的默认构造函数，即``a = int();``是合法的，整形的缺省值是0，浮点型的缺省值是``0.0``,指针类型的缺省值是``nullptr``）。

```cpp
void resize(size_t n, const T& x = T())
{
    size_t sz = size();
    size_t cp = capacity();
    if (n < sz)
    {
        _finish = _start + n;
	}
    else if (n < cp)
    {
        while (_finish != _start + n)
		{
            *_finish = x;
			++_finish;
        }
	}
	else if (n > cp)
    {
        reserve(n);
		while (_finish != _start + n)
        {
            *_finish = x;
			++_finish;
        }
	}
}
```

## 5 提供遍历有关函数

&emsp;&emsp;仿照string的设计，提供``const``版本和普通版本即可，二者构成重载，这样对``const``对象和普通对象都能遍历且普通对象能通过``[]``修改值了。

```cpp
T& operator[](size_t i)
{
    assert(i < size());
    return _start[i];
}
const T& operator[](size_t i) const
{
    assert(i < size());
    return _start[i];
}
```

&emsp;&emsp;为了能够支持范围for，我们提供``begin()``和``end()``迭代器。

```cpp
iterator begin()
{
    return _start;
}
const_iterator begin() const
{
    return _start;
}
iterator end()
{
    return _finish;
}
const_iterator end() const
{
    return _finish;
}
```

## 6 容器的尾插

**push_back**

&emsp;&emsp;我们只要在``_finish``位置插入一个元素，然后``_finish``往后移动一下即可，注意若``_finish == _end_of_storage``则需要扩容。

&emsp;&emsp;由于我们使用的是模板，所以对于T类型，它可能很大，我们为了减少拷贝可以传其``const``引用。

```cpp
void push_back(const T& x)
{
    if (_finish == _end_of_storage)
    {
        reserve(capacity() == 0 ? 4 : 2 * capacity());
	}
    *_finish = x;
    ++_finish;
}
```

&emsp;&emsp;现在就可以做一个小规模测试一下了：

```cpp
void test_vector1()
{
    vector<int> a;
    for (int i = 1; i <= 10; ++i)
	{
        a.push_back(i);
	}
	int sz = a.size();
    for (int i = 0; i < sz; ++i)
	{
        cout << a[i] << ' ';
	}
	cout << endl;
    a.resize(15);
	for (auto p : a)
    {
		cout << p << ' ';
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220305203650.png" style="zoom:80%;" />

## 7 析构函数和拷贝构造函数和赋值运算符重载

**析构函数**

```cpp
~vector()
{
    if (_start != nullptr)
    {
        delete[] _start;
    }
    _start = _finish = _end_of_capacity = nullptr;
}
```

**拷贝构造函数**

&emsp;&emsp;这里不要用``memmove``，因为T类型中可能涉及深浅拷贝的问题，所以用``operator=``让T类型的赋值运算符重载自己解决这个问题。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310192153.png" style="zoom:80%;" />

&emsp;&emsp;现代写法的核心思想就是“找我已经写过的东西来替我办事“，``string``中我们可以利用构造函数完成了拷贝构造的现代写法，但是在``vector``中，我们目前没有有参数的构造函数，所以我们先实现这个构造函数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310192912.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310193052.png" style="zoom:80%;" />

&emsp;&emsp;因此现代写法可以复用这个迭代器区间的拷贝构造：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310193446.png" style="zoom:80%;" />

**赋值运算符重载**

&emsp;&emsp;利用传值会调用拷贝构造函数，就可以复用拷贝构造函数完成赋值运算符重载。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310193904.png" style="zoom:80%;" />

&emsp;&emsp;同理，这三个``swap``也可以封装到一起。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310194215.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310194412.png" style="zoom:80%;" />

&emsp;&emsp;进而简化拷贝构造和赋值：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310194506.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310194525.png" style="zoom:80%;" />

&emsp;&emsp;我们迭代器区间构造的模板函数的名字是有意义的，其意义和迭代器分类有关系。

&emsp;&emsp;迭代器分类（与容器类型有关）：

- ``input_iterator``无实际类型。
- ``output_iterator``无实际类型。
- ``forward_iterator``单向迭代器：``forward_list``单链表，``unordered_map``哈希图，``unordered_set``哈希集合，只支持++
- ``bidirectional_iterator``双向迭代器：``list``,``map``,``set``，支持++，--。
- ``randomaccess_iterator``随机迭代器：``deque``，``vector``，支持++，--，还支持``+``, ``-``.

&emsp;&emsp;这里头是有继承关系的，之间有类似“权限”的限制，如果模板库的某个函数中需要随机迭代器，你传一个双向迭代器虽然在语法上因为都是可以的，但是里头可能要用``+``和``-``，就会出错。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310201221.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310201411.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310201830.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310201800.png" style="zoom:80%;" />

&emsp;&emsp;拷贝构造和赋值运算符重载这里模板参数``<T>``都可以不写。

## 8 容器的尾删

&emsp;&emsp;注意检查容器非空即可，提供一个``empty``，另外模仿``STL``的风格，直接提供暴力的``assert``检查容器非空即可。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310204836.png" style="zoom:80%;" />

## 9 根据迭代器插入insert与扩容导致的迭代器失效

&emsp;&emsp;在``pos``位置之前插入一个x.

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310205809.png" style="zoom:80%;" />

&emsp;&emsp;但当我们容器的元素个数是4个，这调用``insert``插入20却插入了一个随机值，这就是一种迭代器失效。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310210206.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310210219.png" style="zoom:80%;" />

&emsp;&emsp;这里的分析比较简单，就是4个元素在插入的时候会扩容，然后旧空间会被释放，但是``pos``指向的是原来的位置，而那个位置已经扩容时``delete[]``还给了系统了，导致``pos``位置失效了，出现了野指针的访问问题。

&emsp;&emsp;解决的思路就是既然扩容会导致pos失效，那么就在扩容之前记录好``pos``和``_start``的相对距离``len``，扩容完后更新``pos = _start + len``.

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310210858.png" style="zoom:80%;" />

&emsp;&emsp;但此时仍可能存在迭代器失效的问题，因为我们是传值的``pos``，你尽管在函数体重修改了``pos``使其有效，但是回到调用的地方``pos``的值并不会改变，仍然使得原本的迭代器变成一个野指针了，这仍然是一种迭代器失效。

&emsp;&emsp;``STL``中是通过返回新的迭代器来预防这种情况。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310211340.png" style="zoom:80%;" />

&emsp;&emsp;这里不能通过加引用来修改迭代器，因为这个引用必然是要修改的值，如果我们传``v1.begin()``这种临时对象就会失效，如果用``const&``来弥补，就不能修改这个值，解决不了问题。

&emsp;&emsp;所以最终的代码如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310211817.png" style="zoom:80%;" />

## 10 根据迭代器删除erase与意义改变导致的迭代器失效

&emsp;&emsp;基础逻辑还是比较简单，就是直接往前移动，到``_finish``为止，然后容器大小减小1，挪动``_finish``

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310212310.png" style="zoom:80%;" />

&emsp;&emsp;不过它也存在迭代器失效的问题，假如我们要求删除所有的偶数：

1 2 3 4 5 正常

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310212923.png" style="zoom:80%;" />

1 2 3 4 崩溃

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310212947.png" style="zoom:80%;" />

1 2 4 5 出现错误

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310213045.png" style="zoom:80%;" />

&emsp;&emsp;VS下上面三个例子都会崩溃，因为它们会被断言检查出来，``g++``下上面三个例子出现的情况都一样。VS对``erase``后的迭代器进行了强制检查，当你``erase``迭代器后，vs不允许你再次访问被删除位置的迭代器。

&emsp;&emsp;情况1和情况2的分析如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310213603.png" style="zoom:80%;" />

&emsp;&emsp;其次，某些版本实现的``erase``在删除后，会使容器缩容，给予新的地址，此时it会失效称为野指针，和``insert``中类似。

&emsp;&emsp;不过一般``SGI``和``HP``版本都没有这么做。

&emsp;&emsp;接着分析1 2 3 4崩溃的原因。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310214900.png" style="zoom:80%;" />

&emsp;&emsp;无限往前走就崩了。

&emsp;&emsp;本质原因就是``erase``后it的意义变了，查看``cppreference``也是通过返回值来解决这个问题：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310215108.png" style="zoom:80%;" />

&emsp;&emsp;erase**返回刚刚删除的元素的下一个元素的迭代器**。

&emsp;&emsp;所以官方的写法应该是这样的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310215645.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220310215338.png" style="zoom:80%;" />

## 11 迭代器失效总讨论

&emsp;&emsp;迭代器失效一般都发生在``insert``和``erase``，因为这两个接口会修改迭代器并修改底层的数据结构。

&emsp;&emsp;string的``insert``和``erase``会不会导致迭代器失效呢？

&emsp;&emsp;结论：只要使用迭代器访问的容器都可能涉及迭代器失效，所以string也会发生迭代器失效，并且它失效的情况与``vector``的失效完全类似，不过string的插入删除主要使用的是下标而非迭代器，所以体现的很少。

## 12 深拷贝时不要使用memcpy

```cpp
void reserve(size_t n)
{
    size_t sz = size();
    size_t cap = capacity();
    if (n > cap)
    {
        T* tmp = new T[n];
        if (_start != nullptr)
        {
            /*for (int i = 0; i < sz; ++i)
            {
                tmp[i] = _start[i];
             }*/
             memcpy(tmp, _start, sizeof(T) * sz);
             delete[] _start;
        }
        _start = tmp;
        _finish = tmp + sz;
        _end_of_capacity = tmp + n;
    }
}
```

&emsp;&emsp;比如如果vector中是string对象，那么就会开除一块tmp指向的空间，把_start指向的空间中``string``的每个字节拷贝了过来，这样就使得tmp和``_start``都指向了同一块空间，然后``delete[] _start``就寄了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314114430.png" style="zoom:80%;" />

&emsp;&emsp;解决这里浅拷贝的问题，如果tmp的空间是``malloc``出来的，还未调用构造函数，我们可以使用``replacement new``来调用拷贝构造函数，不过tmp的空间是``new``出来的，所以我们只好调用T类的赋值运算符重载了，它会帮我们完成深拷贝。

```cpp
void reserve(size_t n)
{
    size_t sz = size();
    size_t cap = capacity();
    if (n > cap)
    {
        T* tmp = new T[n];
        if (_start != nullptr)
        {
            for (size i = 0; i < sz; ++i)
            {
                tmp[i] = _start[i];
            }
             delete[] _start;
        }
        _start = tmp;
        _finish = tmp + sz;
        _end_of_capacity = tmp + n;
    }
}
```

&emsp;&emsp;由于VS下短小的字符串会有栈上的缓冲区保存，所以使用``memcpy``浅拷贝有时候并不会导致崩溃，但是这仅仅是VS下的特性，不能一概而论。
