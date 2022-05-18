# 一、stack的使用与适配器模式

## 1 stack的常见接口

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322201236.png" style="zoom:80%;" />

&emsp;&emsp;发现传的第二个参数是容器，表示它是用什么容器来实现，栈是一个**适配器**。

&emsp;&emsp;常用接口：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322201347.png" style="zoom:80%;" />

&emsp;&emsp;与数据结构中学过的栈的接口都一样，就不多做介绍了。

&emsp;&emsp;为支持LIFO，栈不支持迭代器。

## 2 JZ31 栈的压入、弹出序列

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322211638.png" style="zoom:80%;" />

&emsp;&emsp;我们可以模拟这个匹配过程，用一个栈：

- 如果入栈位置的值和出栈位置的值不相等，则这个值需要先入，等后面再出栈；
- 如果入栈位置的值和出栈位置的值相等，那么先把这个值入栈，然后若栈顶元素和出栈位置元素相等，就不停弹出栈顶元素，并且移动出栈位置指针，直到栈为空或栈顶的元素和出栈序列值不匹配为止。

&emsp;&emsp;整合思路：不管怎么样先把值入栈，然后如果栈顶值和出栈序列当前值相等，就连续出栈，最后看看出栈序列指针是否走到结尾即可。

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) 
    {
        stack<int> st;
        int i = 0, j = 0, n = pushed.size();
       /* 我们的思路就是模拟这个过程
        * 1. 如果当前的入栈序列值和出栈值不同,就先入栈,后续再出栈
        * 2. 如果当前的入栈序列值和出栈值相同,先把这个值入栈,
        * 然后看这个出栈序列的值和栈顶是否相等，相等就连续出栈
        * 发现不管怎么样我们都得先入栈 所以可以把入栈放到最前面
        * 然后如果栈顶和出栈值相等 就连续出栈
        * 最后看看出栈序列是否走到了结尾就行了
        */
        while (i < n)
        {
            st.push(pushed[i++]);
            while (!st.empty() && st.top() == popped[j])
            {
                st.pop();
                ++j;
            }
        }
        return j == n;
    }
};
```

## 3 逆波兰表达式

&emsp;&emsp;后缀表达式（逆波兰表达式）是运算符在后面的表达式。

&emsp;&emsp;我们常写的表达式是中缀表达式，怎么把中缀表达式转后缀表达式呢？

19:10

&emsp;&emsp;遍历这个中缀表达式的每个东西，

- 若遇到的是数字：则直接让数字加到待输出的容器中
- 若遇到一个操作符：
- 如果栈为空或者当前栈顶的操作符的优先级比当前操作符低，就让当前操作符入栈。
- 否则如果栈顶操作符的优先级比当前的操作符运算符优先级高或相等，就循环把栈顶操作符弹出插入到待输出的容器中，知道栈为空或者栈顶的优先级比当前操作符低为止，就把当前操作符入栈。
- 最后把栈中的操作符插入到待输出的容器中。

## 4 适配器与设计模式

&emsp;&emsp;适配器是一种**设计模式**（设计模式是一套被反复使用的，多数人知晓的，经过分类编目的，**代码设计经验的总结**），该种模式是将一个类的接口转换成客户希望的另外一个接口。

&emsp;&emsp;``STL``中，stack就是一种适配器，通过给予其容器类型，就会生成不同底层的``stack``，给一个vector，就能实现数组栈，给一个list，就能实现一个链式栈：

&emsp;&emsp;对栈来说，只要你的容器支持``push_back()``和``pop_back()``和``top()``，我就能使用你这些接口适配出一个基于你底层的栈。

&emsp;&emsp;而在C++中，模板就能很好的实现这一设计模式，我们先把基础框架实现一下：

```cpp
template <class T, class Container>
class stack
{
public:
	void push(const T& x)
	{
		_con.push_back(x);
	}
	void pop()
	{
		_con.pop_back();
	}
	const T& top()
	{
		return _con.back();
	}
    bool empty()
	{
		return _con.empty();
	}
private:
	Container _con;
};
```

&emsp;&emsp;但是我们使用的时候可以不指定容器类型啊，我们可以给容器给缺省值，标准库里默认的参数是``deque<T>``，它是双端队列。

```cpp
// 适配器模式
template <class T, class Container = deque<T>>
class stack
```

&emsp;&emsp;当你的容器没有back() push_back() pop_back()接口时，编译就会报错。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220323205319.png" style="zoom:80%;" />

# 二、queue的使用与适配器模式

## 1 queue的接口

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322201717.png" style="zoom:80%;" />

&emsp;&emsp;它也是个容器适配器，看看其接口：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322201841.png" style="zoom:80%;" />

&emsp;&emsp;与数据结构中学过的队列接口都一样，就不多做介绍了。

&emsp;&emsp;为支持LIFO，队列不支持迭代器。

## 2 队列的适配器模式实现

&emsp;&emsp;push是原容器的``push_back``，pop是原容器的``pop_front()``，所以要求容器必须有这两个接口，否则会报错。

```cpp
template <class T, class Container = deque<T>>
class queue
{
public:
	void push(const T& x)
	{
		_con.push_back(x);
	}
	void pop()
	{
		_con.pop_front();
	}
	const T& front() const
	{
		return _con.front();
	}
	const T& back() const
	{
		return _con.back();
	}
	bool empty()
	{
		return _con.empty();
	}
	size_t size() const
	{
		return _con.size();
	}
private:
	Container _con;
};
```

# 三、deque容器简介

## 1 deque简介

&emsp;&emsp;``deque``是一个**双端队列**，但它并不是一个队列，它的设计初衷是为了融合list和vector的优点。

``vector``优点：

- 下标随机访问
- 尾插尾删效率高

``vector``缺点：

- 扩容代价比较大，空间存在浪费
- 头插头删效率低

``list``优点：

- 按需申请释放空间，不存在空间浪费
- 任意位置插入删除效率都是``O(1)``

``list``缺点：

- 不支持下标的随机访问。

&emsp;&emsp;我们看了``deque``的接口就知道``deque``是为了干嘛了。

&emsp;&emsp;它支持随机迭代器：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220323211103.png" style="zoom:80%;" />

&emsp;&emsp;支持任意位置的插入删除和``operator[]``:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220323211135.png" style="zoom:80%;" />

&emsp;&emsp;但是我们目前主流的数据结构中并没有主要讲``deque``，这也从侧面反映了``deque``的替代vector和list的实践失败了。

## 2 deque的设计思路

&emsp;&emsp;设计一个双链表，结点的类型是一段连续的物理空间。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220323212200.png" style="zoom:80%;" />

&emsp;&emsp;再设计一个指针数组，称为中控数组，每个元素指向一块buffer。

&emsp;&emsp;它的随机访问本质就是去每块buffer找，具体找到在哪块了以后，然后再遍历一遍buffer去找，侯捷老师曾经在《STL源码剖析中》中说：“如果你要用``deque``排序，那还不如先把``deque``的数据拷贝到``vector``中，然后``vector``排序，再拷贝回来。”

&emsp;&emsp;它的``insert``和``erase``的效率也很有问题。

&emsp;&emsp;所以它命名是``deque``，双端队列，适合头尾的插入删除。

&emsp;&emsp;但是它仍然是``STL``中``stack``和``queue``的默认生成容器，如果没有``deque``，那么栈可以使用``vector``或``list``来适配，队列可以用``list``来适配。

## 3 deque为什么可以做stack的默认适配容器

&emsp;&emsp;对于实现``stack``，``deque``比``vector``的优势在于尾插时扩容代价不大，不需要拷贝数据，浪费空间也不多，不过deque也需要扩容拷贝，中控数组满了需要扩容，但是是拷贝指针值，代价小很多。

&emsp;&emsp;对于实现``stack``,``deque``比``list``的优势在于CPU高速``cache``的命中与它不会频繁的去申请小块空间，申请和释放空间的次数少，代价更低一些。

&emsp;&emsp;对于实现``queue``，``deque``比``list``的优势也是同样的：CPU高速``cache``的命中与它不会频繁的去申请小块空间，申请和释放空间的次数少，代价更低一些。

&emsp;&emsp;所以``deque``作为栈和队列的默认容器是完胜``list``和``vector``的。

## 4 总结

&emsp;&emsp;``deque``适合头尾的插入删除，但是中间的插入、随机访问的效率都不是很好，如果需要中间插入，还是得用``list``，如果要随机访问，还得是``vector``。

&emsp;&emsp;``deque``的源码的精华在于其迭代器。

# 四、优先级队列

## 1 接触与使用

&emsp;&emsp;优先级队列也是一个容器适配器。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326144041.png" style="zoom:80%;" />

&emsp;&emsp;它的本质就是一个堆，默认情况下是一个大堆（默认是大的数优先级高）。

```cpp
void test_priority_queue()
{
	priority_queue<int> pq;
	pq.push(1);
	pq.push(3);
	pq.push(3);
	pq.push(-5);
	pq.push(9);
	pq.push(10);
	while (!pq.empty())
	{
		cout << pq.top() << ' ';
		pq.pop();
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326145549.png" style="zoom:80%;" />

&emsp;&emsp;主要接口：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326144554.png" style="zoom:80%;" />

&emsp;&emsp;如果要使该容器能够让小的数优先级高，就得最后一个参数为``greater<int>``，它在头文件``<functional>``里头，这个参数的类型被称为仿函数，或函数对象类型。

```cpp
void test_priority_queue()
{
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(1);
	pq.push(3);
	pq.push(3);
	pq.push(-5);
	pq.push(9);
	pq.push(10);
	while (!pq.empty())
	{
		cout << pq.top() << ' ';
		pq.pop();
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326145900.png" style="zoom:80%;" />

## 2 例题

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326151818.png" style="zoom:80%;" />

&emsp;&emsp;当N远大于k时，其实使用堆来解决``topK``问题比较好，建一个k个数的小堆，则堆顶就是最小元素，如果新的元素比堆顶大，则让pop掉堆顶，然后让该元素入堆，最后遍历完了堆顶就是那个第k大的元素。

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.begin() + k);
        for (int i = k; i < nums.size(); ++i)
        {
            if (nums[i] > pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
    }
};
```

&emsp;&emsp;``stl``中有很多堆相关的算法，源码中就是用这些接口实现的优先级队列：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326152457.png" style="zoom:80%;" />

## 3 模拟实现

&emsp;&emsp;考虑到``deque``的随机访问速度比较慢，而堆中要频繁的随机访问，所以我们使用``vector``作为默认适配容器。

&emsp;&emsp;大致实现如下功能，先不考虑仿函数，形成一个大堆。

```cpp
template <class T, class Container = vector<T>>
class priority_queue
{
public:
	// 用默认生成的构造去调用对应容器的默认构造函数即可
	priority_queue()
	{}
	void push(const T& x);
	void pop();
	bool empty() const;
	size_t size() const;
    const T& top();
private:
	Container _con;
};
```

&emsp;&emsp;大堆的向上调整算法：

```cpp
void adjust_up(size_t child)
{
    size_t parent = (child - 1) / 2;
	while (child > 0)
    {
		if (_con[child] > _con[parent])
        {
			swap(_con[child], _con[parent]);
		}
        else
		{
            break;
		}
		child = parent;
        parent = (child - 1) / 2;
	}
}
```

&emsp;&emsp;大堆的向下调整算法：

```cpp
void adjust_down(size_t parent)
{
    size_t child = parent * 2 + 1;
	size_t n = size();
    while (child < n)
	{
        if (child + 1 < n && _con[child + 1] > _con[child]) ++child;
		if (_con[child] > _con[parent])
        {
			swap(_con[parent], _con[child]);
		}
        else
		{
			break;
        }
		parent = child;
		child = parent * 2 + 1;
    }
}
```

&emsp;&emsp;其余的都比较简单，我们实现如下：

```cpp
template <class T, class Container = vector<T>>
class priority_queue
{
public:
	// 用默认生成的构造去调用对应容器的默认构造函数即可
	priority_queue()
	{}
	void adjust_up(size_t child)
	{
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_con[child] > _con[parent])
			{
				swap(_con[child], _con[parent]);
			}
			else
			{
				break;
			}
			child = parent;
			parent = (child - 1) / 2;
		}
	}

	void adjust_down(size_t parent)
	{
		size_t child = parent * 2 + 1;
		size_t n = size();
		while (child < n)
		{
			if (child + 1 < n && _con[child + 1] > _con[child]) ++child;
			if (_con[child] > _con[parent])
			{
				swap(_con[parent], _con[child]);
			}
			else
			{
				break;
			}
			parent = child;
			child = parent * 2 + 1;
		}
	}
	const T& top()
	{
		return _con[0];
	}
	void push(const T& x)
	{
		_con.push_back(x);
		adjust_up(_con.size() - 1);
	}
	void pop()
	{
		assert(!_con.empty());
		swap(_con[0], _con[size() - 1]);
		_con.pop_back();
		adjust_down(0);
	}
	bool empty() const
	{
		return _con.empty();
	}
	size_t size() const
	{
		return _con.size();
	}
private:
	Container _con;
};
```

&emsp;&emsp;堆这种适配器的主要作用是在原来的容器上作用一个算法。

&emsp;&emsp;我们再支持一个迭代器区间构造函数，思路就是建堆的思路，从第一个非叶子结点建堆。

```cpp
template <class InputIterator>
priority_queue(InputIterator first, InputIterator last)
    : _con(first, last)
{
	// 倒着建堆 从第一个非叶子结点建
    int n = size();
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
		adjust_down(i);
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326155757.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326155849.png" style="zoom:80%;" />

## 4 仿函数的增加

&emsp;&emsp;发现控制大堆还是小堆主要控制的地方就是``adjustup``和``adjustdown``里的大于号和小于号，并且大堆和小堆是相反的。

&emsp;&emsp;C++中为了解决这种问题，提供了一种称为仿函数的东西。

```cpp
struct Less
{
	bool operator()(int x, int y)
	{
		return x < y;
	}
};

struct greater
{
	bool operator()(int x, int y)
	{
		return x > y;
	}
};
```

&emsp;&emsp;它是一个类，其中没有任何成员变量，只有一个比较大小的成员函数，所以这个类的大小就是1，用这个类定义对象后，可以用括号操作符来调用里头的比较大小的函数：

```cpp
int main()
{
	// test_priority_queue();
	Less less;
	cout << less(1, 2) << endl;// 等价于lt.operator()(1, 2)
	greater gt;
	cout << gt(3, 2) << endl;
}
```

&emsp;&emsp;明明是一个类对象的成员函数调用，但是长得却特别像一个函数一样，可以像函数一样去使用它。

&emsp;&emsp;Less这种类型就被称为仿函数，less这种对象就被称为函数对象。

&emsp;&emsp;我们这里的比较是只针对``int``类型的，我们想让它能够针对更宽泛的类型，就想到了模板。

```cpp
template <class T>
struct Less
{
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};

// 调用
int main()
{
	
	Less<int> less;
	cout << less(1, 2) << endl;
	// 简写：
    cout << less<int>()(1, 2) << endl;
}
```

&emsp;&emsp;所以我们就要增加一个仿函数类型，通过模板参数来传：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326164133.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326163905.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326164017.png" style="zoom:80%;" />

&emsp;&emsp;STL中的sort也是，默认提供的是``less<T>()``，它会排升序，使用``greater<T>()``，会排降序。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220326165538.png" style="zoom:80%;" />

## 5 自定义类型与仿函数

&emsp;&emsp;由于仿函数的实现中，是直接拿类型进行比较的，所以如果自定义类型没有重载``operator < 和 operator >``，就会报错。

&emsp;&emsp;弥补这一漏洞，第一个方法是为自定义类型补充``operator <``和``operator >``，或者在类外搞一个友元。

&emsp;&emsp;另一种方式是自己写一个仿函数，考虑以下场景，通过日期类的指针来比较日期大小，那么就要自己实现一个仿函数，如下：

```cpp
struct DateLess
{
    bool operator()(const Date* d1, const Date* d2)
    {
        return *d1 < *d2;
    }   
};
priority_queue<Date*, vector<Date*>, DateLess> pq;
```

&emsp;&emsp;上面的实现依赖于``Date``实现了``operator <``，否则我们就在这一层自己增加逻辑即可。

&emsp;&emsp;总之，优先级队列的比较方式，是可以通过我们自己控制仿函数的逻辑，然后传参仿函数的类型就可以了。

&emsp;
