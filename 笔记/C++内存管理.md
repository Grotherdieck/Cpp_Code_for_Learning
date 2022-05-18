&emsp;&emsp;对比一下C和C++定义类别的一些区别，以``Stack``为例子：

&emsp;&emsp;C语言定义栈无非就是定义一个结构，然后定义一些函数，它的数据和函数是分离的，在操作数据时，定义完类型后需要调用一下初始化函数，然后再每次操作栈数据时都需要传栈对象的地址，不然没法在函数中更改本来的栈数据。在我们使用结束的时候，需要手动调用``destroy``函数。

&emsp;&emsp;并且调用栈结构时，我的结构体中的数据都是不受保护的，万一大家的栈的实现细节不同，比如有的人的``top``元素标记的是栈顶的后一个元素的下标，有的人实现的``top``元素标记的是栈顶的元素的下标，盲目访问数据很有可能因为实现细节不同而访问错误。

&emsp;&emsp;所以C++的类提供而了封装的思想，不想让你调用的数据就不给你访问。

&emsp;&emsp;但是为了能够实现栈的基本功能，我在类内增加了成员函数，这些接口给你公开，你可以调接口来访问我。

&emsp;&emsp;但是还有问题没有解决，我经常忘记调用``Init``函数和``destroy``函数，这也是一层隐患。

&emsp;&emsp;所以C++提供了构造函数和析构函数，在定义和离开自己定义周期时会自动调用。

&emsp;&emsp;但是调每个成员函数总需要传对象的地址，每次传都好麻烦啊，这就引出了成员函数的``this``指针。

&emsp;&emsp;这就解释了我们前面讲解的C++的语法是怎么来的。

&emsp;&emsp;再考虑到深浅拷贝的问题，所以允许用户自己提供拷贝构造函数和``operator=``。

# 一、C/C++的内存分布

&emsp;&emsp;C/C++的程序运行起来后，进程地址空间分布如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120155147.png" style="zoom:67%;" />

&emsp;&emsp;以上是C程序在运行时的进程的虚拟内存分布,C++程序继承了C程序的这种分布。

```cpp
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
 static int staticVar = 1;
 int localVar = 1;
 
 int num1[10] = {1, 2, 3, 4};
 char char2[] = "abcd";
 //这里是开了个五个字节的数组，把a b c d \0拷贝到栈上
 //所以char2 *char2都在栈上
 const char* pChar3 = "abcd";
 //指向常量区的存的只读常量字符串"abcd"
 int* ptr1 = (int*)malloc(sizeof (int)*4);
 int* ptr2 = (int*)calloc(4, sizeof(int));
 int* ptr3 = (int*)realloc(ptr2, sizeof(int)*4);
 free (ptr1);
 free (ptr3);
}
1. 选择题：
 选项: A.栈 B.堆 C.数据段 D.代码段
 globalVar在哪里？__C__ staticGlobalVar在哪里？__C__
 staticVar在哪里？__C__ localVar在哪里？__A__
 num1 在哪里？__A__
 
 char2在哪里？__A__ *char2在哪里？__A_
 pChar3在哪里？__A__ *pChar3在哪里？__D__
 ptr1在哪里？__A__ *ptr1在哪里？__B__
```

&emsp;&emsp;C语言的堆上内存的分配方法：``malloc、calloc、realloc``.

# 二、C++的内存分配方式

## 1 new/delete处理内置类型

&emsp;&emsp;C++为什么要自己提供新的堆内存分配方法呢？

&emsp;&emsp;首先，C语言的分配方法不太好用。

```cpp
//单个int
int* p = (int*)malloc(sizeof(int));
//5个int的数组
int* p1 = (int*)malloc(5*sizeof(int));
//C++提供了一个称为new的操作符
int* p2 = new int;//单个
int* p3 = new int[5];//五个元素的数组
free(p);
free(p1);
delete p2;//单个int还给操作系统
delete[] p3;//数组还给操作系统
```

&emsp;&emsp;经测试，``malloc/free``和``new/delete``对内置类型没有本质区别，只有用法区别。

&emsp;&emsp;一个注意点：

```cpp
int* p = new int[5];//五个元素的数组
int* p2 = new int(5);//一个整形 被初始化为5
//C++98不支持new来时初始化数组
//C++11支持用大括号初始化，如下：

int main()
{
	int* p1 = new int;
	int* p2 = new int[5];
	int* p3 = new int(5);
	int* p4 = new int[5]{ 1,2,3,4,5 };
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120170436.png)

## 2 new/delete处理自定义类型

&emsp;&emsp;之所以要引入``new/delete``，真正的用处在于自定义类型，我们希望自定义类型定义出来后如果不加参数就调用默认构造函数初始化，但是``malloc`` 做不到这件事情

&emsp;&emsp;自定义类型来说，``malloc calloc realloc``都可以动态分配内存，但是它们只是开空间，不会调用该类的构造函数。

&emsp;&emsp;而C++的``new``在分配内存的同时，还会调用构造函数初始化。

&emsp;&emsp;``free``只会归还内存，并不会调用析构函数清理对象里的，创建对象时构造函数可能开辟的堆空间，而``delete``会先调用该自定义类型的析构函数，再将对象内的堆上的数据成员的内存还给堆。

&emsp;&emsp;测试如下：

```cpp
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
};

int main()
{
	A* a1 = (A*)malloc(sizeof(A));
	A* a2 = (A*)malloc(sizeof(A) * 5);
	A* a3 = new A;
	A* a4 = new A[5];
	free(a1);
	free(a2);
	delete a3;
	delete[] a4;
}
```

&emsp;&emsp;观察下图可以发现只调用了6次构造函数和析构函数，断点调试发现``malloc``不会调用自定义类型的构造函数以初始化，free不会调用自定义类型的析构函数以回收对象某些成员在构造函数中申请的堆内存。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120171600.png" style="zoom:80%;" />

&emsp;&emsp;``malloc和free,new和delete``不匹配不一定会出问题，具体情况要看编译器处理，但是尽量我们还是匹配着用比较好。

&emsp;&emsp;如果不想调用默认构造函数或者没有默认构造函数，可以这样写：

```cpp
A* a = new A(4);
A* a = new A[5]{1, 2, 3, 4, 5};
```

&emsp;&emsp;``delete[] p;``的方括号是为了知道指针p指向的空间有几个对象，这样知道要调用几次析构函数清理内存。

&emsp;&emsp;``new A[5];``和``delete[]、new A;``和``delete``要匹配使用，一个对象就用``delete a;``对象数组就用``delete[] a;``，这样``A a = new A;``一个对象，然后``delete[] a;``可能会被检查到，然后就会程序崩掉。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120173326.png" style="zoom:80%;" />

&emsp;&emsp;引入``new/delete``的原因还有一个原因：面向过程的对象，处理错误的方法是错误码；面向对象的语言，出错时让它抛异常，C++自然也希望用异常来处理错误情况，对于内存分配失败也希望抛出异常。

&emsp;&emsp;C语言中，向堆申请内存可能会失败，比如``malloc``申请失败后，会返回一个空指针，我们可以获得一个错误码：

```cpp
int main()
{
    int* p = (int*)malloc(1024 * 1024 * 1024);
    if (p == nullptr)
    {
        printf("%d\n", errno);
        //error全局变量 标记错误
        perror("malloc fail");
        //perror可以打印出符号
        exit(-1);
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120174347.png" style="zoom:80%;" />

&emsp;&emsp;但是C++并不希望通过返回``nullptr``和错误码来识别分配失败，下面将验证就算申请失败，也不会返回空：

```cpp
int main()
{
	//int* p = (int*)malloc(1024u * 1024u * 1024u* 2u);
	char* p = new char[1024u * 1024u * 1024u * 2u - 1];
	if (p == nullptr)
	{
		printf("%d\n", errno);
		perror("malloc fail");
		exit(-1);
	}
}
```

&emsp;&emsp;直接报了个错误，而不是和C一样返回空指针，然后进入``if``打印错误码处理错误。这里报的错误其实是我们没有捕获异常而出的错误。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120174805.png" style="zoom:80%;" />

&emsp;&emsp;写成异常的样式：

```cpp
int main()
{
	//int* p = (int*)malloc(1024u * 1024u * 1024u* 2u);
	char* p = nullptr;
    try
    {
        //try的意思是它会检测这里面的步骤会不会生成异常对象
        //尝试捕获异常，捕捉到调到catch
        //这里头也可以放函数 因为对象是向全局抛的
        //函数里头抛出异常也会捕获。
        p = new char[1024u * 1024u * 1024u * 2u - 1];
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}

// 这里也可以这么写

void f()
{
    char* p = new char[1024u * 1024u * 1024u * 2u - 1];
    cout << "f()" << endl;
}

int main()
{
    try
    {
        f();
    }
    // 这里在f中申请失败抛出异常后 会直接调到catch中 不会继续往下执行cou << "f()" << endl;
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120175334.png" style="zoom:80%;" />

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220120175407.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219102932.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219103008.png)

&emsp;&emsp;``new``失败了会向外抛异常，所有可能出错的地方都不用管，都会往外抛异常，然后走``catch``,是符合面向对象设计思想的。

&emsp;&emsp;总结，C++提供new/delete主要解决两个问题：

1. 自定义类型对象主动申请时，初始化和清理的问题，new/delete会调用构造函数和析构函数。

2. ``new``申请内存失败了会向外抛异常，这样才符合面向对象语言的出错处理机制

   ps:``delete、free``一般不会失败，如果失败了，都是释放空间上存在越界访问或者释放指针的位置不对（不是空间首元素地址）。

&emsp;&emsp;如使用new和delete完成一个链表节点的申请(即``buynewnode``函数)

```cpp
#include <iostream>
using namespace std;
struct ListNode
{
    int _val;
    ListNode* _prev;
    ListNode* _next;
    ListNode(int val = 0): _val(val), _prev(nullptr), _next(nullptr)
    {
        cout << "ListNode(int val)" << endl;
    }
    ~ListNode()
    {
        cout << "~ListNode" << endl;
    }
}; 
int main()
{
    auto pnode = new ListNode(1);
    cout << pnode->_val << endl;
    delete pnode;
    return 0;                                                                                            
}

```

&emsp;&emsp;我们模拟的栈，这里存在一种双重归还资源的意图。

```cpp
class Stack                                                                                               {
public:
    Stack(int capacity = 4): _top(0), _capacity(capacity)
    {
        _a = new int[_capacity];
        cout << "Stack(int)" << endl;
    }
    ~Stack()
 	{
    	 delete[] _a;
     	_a = nullptr;
     	_top = 0;
     	_capacity = 0;
     	cout << "~Stack()" << endl;
 	}
private:
    int* _a;
    int _top;
    int _capacity;
};

int main()
{
    Stack* pst = new Stack(10);
    // 先向堆申请栈的空间 然后调用栈的构造函数(给int* _a申请堆上的内存)
    delete pst;
    // 先调用栈的析构函数清理栈的资源(归还int* _a的内存) 
    // 然后把pst指向的栈对象本身的内存归还给堆内存空间
}
```

# 三、new和delete的底层原理

## 1 源码观察

&emsp;&emsp;打上断点转到反汇编看看new和delete究竟是怎么运行的，发现：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219095457.png)

&emsp;&emsp;发现new生成指令的时候调用的是``operator new``函数，我们自己也可以使用这个函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219095923.png" style="zoom: 80%;" />

&emsp;&emsp;我们来看看``operator new``的源码，发现实际上就是对``malloc``和一个申请失败抛异常的封装。

```cpp
void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
    // try to allocate size bytes
 	void *p;
    while ((p = malloc(size)) == 0)
 	if (_callnewh(size) == 0)
 	{
 		// report no memory
 		// 如果申请内存失败了，这里会抛出bad_alloc 类型异常
 		static const std::bad_alloc nomem;
 		_RAISE(nomem);
 	}
 	return (p);
}
```

&emsp;&emsp;抛异常的机制：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219100634.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219100710.png)

&emsp;&emsp;自然也有``operator delete``

```cpp
/*
operator delete: 该函数最终是通过free来释放空间的
*/
void operator delete(void *pUserData)
{
 	_CrtMemBlockHeader * pHead;
 	RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
 	if (pUserData == NULL)
		return;
 	_mlock(_HEAP_LOCK); /* block other threads */
 	__TRY
 	/* get a pointer to memory block header */
 	pHead = pHdr(pUserData);
 	/* verify block type */
 	_ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
 	_free_dbg( pUserData, pHead->nBlockUse );
 	__FINALLY
 	_munlock(_HEAP_LOCK); /* release other threads */
 	__END_TRY_FINALLY
 	return;
}
/*
free的实现
*/
#define free(p) _free_dbg(p, _NORMAL_BLOCK)
```

&emsp;&emsp;``operator delete``也是对``free``和出错抛异常的封装。

&emsp;&emsp;这样的封装都是为了使C++的内存管理方式new/delete更符合面向对象处理错误的方式(抛异常)。

&emsp;&emsp;VS2019中的new和delete的源码(转到定义)，然而我并不看的懂。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219101928.png" style="zoom: 80%;" />

```cpp
void __CRTDECL operator delete(
    void* _Block
    ) noexcept;

void __CRTDECL operator delete(
    void* _Block,
    ::std::nothrow_t const&
    ) noexcept;

void __CRTDECL operator delete[](
    void* _Block
    ) noexcept;

void __CRTDECL operator delete[](
    void* _Block,
    ::std::nothrow_t const&
    ) noexcept;

void __CRTDECL operator delete(
    void*  _Block,
    size_t _Size
    ) noexcept;

void __CRTDECL operator delete[](
    void* _Block,
    size_t _Size
    ) noexcept;
```

## 2 总结原理

&emsp;&emsp;对内置类型，new和delete和malloc和free没有区别，只是会抛异常。

&emsp;&emsp;对于自定义类型，new会先调用``operator new``申请好对象的空间，申请失败了抛异常，然后调用对象的构造函数。

&emsp;&emsp;``delete``会先调用对象的析构函数，然后调用``operator delete``.

&emsp;&emsp;对于申请对象数组，会先调用``operator new[]``(其实这个也是对``operator new``的封装)，给这些对象申请好空间，申请失败了抛异常，然后对每个对象调用构造函数。

&emsp;&emsp;``delete[]``会先调用每个对象的析构函数，然后调用``operator delete[]``归还空间。

## 3 对类重载其operator new和operator delete

&emsp;&emsp;如链表，是由一个一个结点组成的，这些结点如果每个都去找系统申请，这些内存是一块一块离散的小内存，不断申请归还速度会很慢，我们可以设计一个内存池，申请结点时，向内存池申请即可，就好像你为了用水先打水准备好一样。

&emsp;&emsp;这种技术被称为池化技术，不仅有内存池，还有线程池、链接池，道理都类似。

```cpp
struct ListNode
{
 	ListNode* _next;
 	ListNode* _prev;
 	int _data;
    ListNode(int val = 0): _data(val), _next(nullptr), _prev(nullptr)
    {}
 	void* operator new(size_t n)
 	{
        // 借助STL中的空间配置器来充当内存池
        // 这样List申请结点 归还结点时不用直接找系统 速度会相对快一点
 		void* p = nullptr;
 		p = allocator<ListNode>().allocate(1);
 		cout << "memory pool allocate" << endl;
 		return p;
 	}	
 	void operator delete(void* p)
   {
 		allocator<ListNode>().deallocate((ListNode*)p, 1);
 		cout << "memory pool deallocate" << endl;
 	}
};

// ListNode* newnode = new ListNode(1);
// 重载的那个operator new(sizeof(ListNode)) + ListNode(1)

class List
{
public:
 	List()
 	{
 		_head = new ListNode;
 		_head->_next = _head;
 		_head->_prev = _head;
 	}
 	~List()
 	{
 		ListNode* cur = _head->_next;
 		while (cur != _head)
 		{
 			ListNode* next = cur->_next;
 			delete cur;
     		cur = next;
 		}
 		delete _head;
    	_head = nullptr;
 	}
    void push_back(int val)
    {
        ListNode* newnode = new ListNode(val);
        ListNode* tail = _head->prev;
        tail->next = newnode;
        newnode->prev = tail;
        newnode->next = _head;
        _head->prev = newnode;
    }
private:
 	ListNode* _head;
};
int main()
{
    List l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    return 0;
}

```

&emsp;&emsp;可以看到这里走的``operator new``全是我们自己重载弄的内存池：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219105157.png)

## 4 定位new表达式(placement-new) 

&emsp;&emsp;假设我们已经申请了一块内存，但是我们不是使用的``new``申请的内存，并没有调用类的构造函数，能否我们对这块内存调用类的构造函数呢？答案是肯定的，虽然我们不能直接显示的调用构造函数，但是可以使用placement-new.

```cpp
// 假设已经有了一个A类
int main()
{
    A* p1 = (A*)malloc(sizeof(A));
    // 显示的调用构造函数
    new(p1)A(2);
}
```

&emsp;&emsp;如果是向内存池中申请内存，因为有很多不同类型的变量需要申请内存，所以申请完了内存肯定要自己再初始化，怎么初始化呢，placement-new即可。(new(地址)类名(构造函数参数))。

&emsp;&emsp;那怎么析构呢，可以显示的调用析构函数。

```cpp
A* p2 = new A(2);

delete p2;

//等价于

A* p3 = operator new(sizeof(A));
new(p3)A(2);

p3->~A();
operator delete(p3);
```

## 5 new/delete和malloc/free的区别

&emsp;&emsp;用法上的区别、构造函数析构函数的调用与否、一组是操作符一组是库函数、抛异常和返回空指针。

## 6 内存泄漏

&emsp;&emsp;动态内存申请后，不使用这块内存后，却不归还给系统。

&emsp;&emsp;内存泄漏的危害：

- 如果申请内存后没归还内存，也就是出现内存泄漏了，但是这个程序对应的进程正常结束了，系统会把进程的内存收回来，这时内存泄漏就造不成危害了；
- 出现内存泄漏的进程非正常结束，如僵尸进程，内存未正常回收，就会出现危害。
- 长期运行的程序，如服务器程序、后台程序等，出现内存泄漏的话危害就会很大，因为这个内存不会结束，程序如果内存泄漏，内存就会逐渐减少，然后就会变卡或者慢慢出现宕机。

&emsp;&emsp;如何防范内存泄漏呢？首先是可以使用智能指针，其次是使用一些检测工具。

- [Linux下几款C++程序中的内存泄露检查工具](https://blog.csdn.net/gatieme/article/details/51959654)
- [VS编程内存泄漏：VLD(Visual LeakDetector)内存泄露库](https://blog.csdn.net/GZrhaunt/article/details/56839765)
- [内存泄露检测工具比较](https://www.cnblogs.com/liangxiaofeng/p/4318499.html)

&emsp;&emsp;那么最多能申请多少G的堆空间呢？32位下一般申请2G(``0x7fffffff 或 1024u * 1024u * 1024u * 2 - 1``)就寄了，

&emsp;&emsp;切为64位后，进程地址空间会变得更大``2^64``个字节，就很大很够了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219115820.png" style="zoom:67%;" />

