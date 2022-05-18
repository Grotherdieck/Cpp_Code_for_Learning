# 一、list的常见接口与使用

&emsp;&emsp;``list``是一个带头双向循环链表。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314121717.png" style="zoom:80%;" />

## 1 构造函数

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314122018.png" style="zoom:80%;" />

&emsp;&emsp;下面是一个简单的测试使用与遍历：

```cpp
void test_list1()
{
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    list<int>::iterator it = l.begin();
    while (it != l.end())
    {
        cout << *it << ' ';
        ++it;
    }
    cout << endl;
    for (auto num : l)
    {
        cout << num << ' ';
    }
}
```

&emsp;&emsp;因为它是双向链表，它还支持反向迭代器：

```cpp
list<int>::reverse_iterator rit = l.rbegin();
while (rit != l.rend())
{
    cout << *rit << ' ';
    ++rit;
}
```

## 2 迭代器

&emsp;&emsp;除了其他容器有的正向反向迭代器，list容器的迭代器作为双向迭代器，它还支持``next``和``prev``以获得前面和后面一个迭代器C++11。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220316184547.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220316184621.png" style="zoom:80%;" />

&emsp;&emsp;返回迭代器``it``的下一个元素的迭代器：``auto nt = next(it);``

&emsp;&emsp;返回迭代器``it``的前一个元素的迭代器：``auto pre = prev(it);``

## 2 容器修改操作

&emsp;&emsp;容器的修改操作支持：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314123017.png" style="zoom:80%;" />

&emsp;&emsp;``list``使用的比较少，因为它不支持随机访问，因此排序之类的操作会很慢，不过list还是支持sort的，但是只支持它自己的排序：

``l.sort()``，是用的一个归并排序，效率比较低下。

&emsp;&emsp;但是``list``在任意位置插入删除的效率都是``O(1)``，这才是它真正的优势。

## 3 其他成员函数

&emsp;&emsp;其他成员函数包括一下函数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314123625.png" style="zoom:80%;" />

&emsp;&emsp;``unique``去重，要求是先排序，算法是我们之前学习过的一种双指针算法。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220316184217.png" style="zoom:80%;" />

&emsp;&emsp;``remove``：根据值删除。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220316184343.png" style="zoom:80%;" />

&emsp;&emsp;``splice``：链表结合，把x链表的节点直接移动到``pos``位置之后。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314123834.png" style="zoom:80%;" />

&emsp;&emsp;看``cppreference``的``splice``使用用例：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314124044.png" style="zoom:80%;" />

# 二、list模拟实现

## 1 stl_list.h(SGI版本)框架

&emsp;&emsp;结点的框架：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314141743.png" style="zoom:80%;" />

&emsp;&emsp;``list``的类模板中的框架：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314141944.png" style="zoom:80%;" />

&emsp;&emsp;无参构造：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314142050.png" style="zoom:80%;" />

## 2 结点和list的初步框架

&emsp;&emsp;观察了原码以后，我们先把结点和``list``的初步框架敲定。

```cpp
template<class T>
struct ListNode
{
    ListNode(const T& val = T(), ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr)
    {
        _val = val;
        _prev = prev;
        _next = next;
    }
    T _val;
    ListNode<T>* _prev;
    ListNode<T>* _next;
};

template<class T>
class list
{
public:
    typedef ListNode<T> Node;
    list()
    {
        _head = new Node;
        _head->_next = _head;
        _head->_prev = _head;
    }
private:
    Node* _head;
};
```

## 3 尾插

&emsp;&emsp;这个太经典了，我们之前在学习C数据结构时就写过类似的了，实现如下：

```cpp
void push_back(const T& x)
{
    Node* tail = _head->_prev;
    Node* newnode = new Node(x);
    newnode->_next = _head;
    _head->_prev = newnode;
    newnode->_prev = tail;
    tail->_next = newnode;
}
```

&emsp;&emsp;其他都在C数据结构双向带头循环链表中弄过了，所以我们就不废大力气弄这些了，我们来重点关心没弄过的东西：**迭代器**。

## 4 迭代器

&emsp;&emsp;由于链表的结点的地址在物理上不连续，所以原生指针不做任何修改肯定无法做迭代器，为寻求思路，我们看看源码：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314150209.png" style="zoom:80%;" />

&emsp;&emsp;来看看这玩意是什么：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314150347.png" style="zoom:80%;" />

&emsp;&emsp;发现list的迭代器就是一个结点的指针，只不过使用了一个自定义类型进行了一下封装。

&emsp;&emsp;虽然结点的原生指针无法做到解引用得到结点值，++走到下一个结点，但是我们可以利用**运算符重载**。

&emsp;&emsp;依据这个初步思路，我们写出初步的``list``迭代器：

```cpp
template<class T>
struct __list_iterator
{
    typedef ListNode<T> Node;
    __list_iterator(Node* node) : _node(node)
    {}
    T& operator*()
    {
        return _node->_val;
    }
    // 前置++
    __list_iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    // 后置++
    __list_iterator operator++(int)
    {
        __list_iterator tmp(_node);
        _node = _node->_next;
        return tmp;
    }
    bool operator==(const __list_iterator<T>& it)
    {
        return it._node == _node;
    }
    bool operator!=(const __list_iterator<T>& it)
    {
        return !(*this == it);
    }
    Node* _node;
};
```

&emsp;&emsp;Node*原生指针和一个迭代器对象，它们占用的空间是一样大的，都是``4byte``，并且存的值也是一样的，但是对它们使用运算符的结果是完全不同的，这就是自定义类型运算符重载的威力。

```cpp
void f()
{
    list<int> l;
    l.push_back(1);
    Node* pnode = l.begin();
    auto it = l.begin();
    *pnode;
    ++pnode;
    
    *it;
    ++it;
}
```

&emsp;&emsp;显然迭代器的拷贝构造和赋值和析构都不需要我们自己实现，字节序拷贝就够了捏，我要的就是浅拷贝，并且也没有空间需要释放，因为迭代器是借助链表的结点的指针来访问链表，结点属于链表，不属于迭代器，释放不属于迭代器来管。

**const容器的迭代器**

&emsp;&emsp;注意，并不是我们的迭代器是``const``的，而是我们的容器是``const``的。

&emsp;&emsp;第一种方法是拷贝一份前面的迭代器结构体代码，把它弄成``const_iterator``迭代器，返回``const``引用，这个方法是可以的，但是代码冗余。

```cpp
template<class T>
struct __list_const_iterator
{
    typedef ListNode<T> Node;
    Node* _node;
    __list_const_iterator(Node* node) : _node(node)
    {}
    const T& operator*()
    {
        return _node->_val;
    }
    // ++it
    __list_const_iterator<T>& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    // it++
    __list_const_iterator<T> operator++(int)
    {
        __list_const_iterator tmp(_node);
        _node = _node->_next;
        return tmp;
    }
    
    // --it
    __list_const_iterator<T>& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    // it--
   __list_const_iterator<T> operator--(int)
   {
       __list_const_iterator tmp(_node);
       _node = _node->_prev;
       return tmp;
   }
   bool operator==(const __list_const_iterator<T>& it)
   {
       return it._node == _node;
   }
   bool operator!=(const __list_const_iterator<T>& it)
   {
       return !(*this == it);
   }
};
```

&emsp;&emsp;能否优化呢？不得不佩服STL的设计者们的思路，可以给迭代器的模板类增加一个参数，表示引用类型，普通迭代器就是``T&``,``const``容器其迭代器模板的参数就是``const T&``.

```cpp
template<class T, class Ref>
struct __list_iterator
{
    typedef ListNode<T> Node;
    
    Node* _node;
    __list_iterator(Node* node) : _node(node)
    {}
    Ref operator*()
    {
        return _node->_val;
    }
    // ++it
    __list_iterator<T, Ref>& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    // it++
    __list_iterator<T, Ref> operator++(int)
    {
        __list_iterator tmp(_node);
        _node = _node->_next;
        return tmp;
    }
    
    // --it
    __list_iterator<T, Ref>& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    // it--
    __list_iterator<T, Ref> operator--(int)
    {
        __list_iterator tmp(_node);
        _node = _node->_prev;
        return tmp;
    }
    bool operator==(const __list_iterator<T, Ref>& it)
    {
        return it._node == _node;
    }
    bool operator!=(const __list_iterator<T, Ref>& it)
    {
        return !(*this == it);
    }
};

typedef __list_iterator<T, T&> iterator;
typedef __list_iterator<T, const T&> const_iterator;
```

&emsp;&emsp;本来要实现两个类的，但是这两个类只有``operator*``的返回值类型不同，因此加一个模板参数就直接解决了这个问题。

&emsp;&emsp;我们看到``stl``源码中还传了一个指针类型作为模板参数，这是为什么呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314163545.png" style="zoom:80%;" />

&emsp;&emsp;首先，为了方便，可以把``typedef __list_iterator<T, Ref, Ptr> self;``，这样增加参数时改的少一点，下面的``->``将讲解为什么有第三个模板参数。

&emsp;&emsp;既然迭代器是像指针一样的东西，那么对于自定义类型，它要能重载``->``，我们先来看个日期类的例子。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314165544.png" style="zoom:80%;" />

&emsp;&emsp;解引用再加``.``，看着很变扭，迭代器模仿的是原生指针的行为，我们能否用像原生指针一样的：``->``,可以，运算符重载。

```cpp
T* operator->()
{
    return &(_node->_val);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314170610.png" style="zoom:80%;" />

&emsp;&emsp;这里其实并不是想象中的那么简单，``operator->``返回的是``_val``的地址，是T*类型，是一个原生指针，按理说它要访问公有类成员，应该再加上一个``->``，也就是说，这里实际上应该是``it->->_year``，但是这样可读性太差了，编译器进行了优化，省略掉了一个``->``。

&emsp;&emsp;所有类型，只要想重载``->``，都会省略一个箭头。

&emsp;&emsp;再考虑``const``容器的迭代器不能通过``->``修改自定义类型成员的值，普通迭代器可以通过``->``修改自定义类型成员的值，所以模板还要再传一个参数：``Ptr``，它用来表示``->``返回的是能修改自定义类型成员的指针和不能修改自定义成员的指针的值。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314171857.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314171934.png" style="zoom:80%;" />

&emsp;&emsp;所以不得不感叹``STL3.0``设计的精巧，三个模板参数，Ref为了决定能否通过``*``修改值，Ptr为了决定能否通过``->``修改值。

&emsp;&emsp;本质上，``vector``和``list``是优势缺陷互补的两组数据结构。

&emsp;&emsp;``vector``的缺陷：

- 连续的物理空间，是优势也是劣势：
- 优势，支持高效随机访问。
- 劣势：空间不够要增容，代价比较大；可能存在一定的空间浪费；头插头删需要挪动数据，效率较低；

&emsp;&emsp;``list``能很好地解决``vector``的问题：

- 按需申请释放空间
- ``list``支持任意位置``O(1)``的插入删除。

&emsp;&emsp;总之，如果要下标访问、频繁交换数据位置，那么``vector``更好用，如果要频繁的插入删除数据，那么``list``更好用。

## 5 insert

&emsp;&emsp;list的insert显然是不会导致迭代器失效的，因为这个位置不会出现什么意义变了之类的问题，仿照stl官方的返回值，返回一个迭代器指向插入的结点即可，其他的细节与数据结构中我们学到的双链表类似。

```cpp
iterator insert(iterator pos, const T& x)
{
    Node* prev = pos._node->_prev;
    Node* newnode = new Node(x);
    newnode->_next = pos._node;
    pos._node->_prev = newnode;
    newnode->_prev = prev;
    prev->_next = newnode;
    return iterator(newnode);
}
```

复用erase简化push_back和push_front:

```cpp
void push_back(const T& x)
{
    insert(end(), x);
}
void push_front(const T& x)
{
    insert(begin(), x);
}
```





## 6 erase与迭代器失效

&emsp;&emsp;首先删除的逻辑也与C初阶数据结构中的双链表的任意位置删除类似，并且干掉结点后，显然迭代器会失效，所以返回值一个指向删除元素后一个结点的迭代器。

```cpp
iterator erase(iterator pos)
{
    // 不能删哨兵位的头
    assert(pos != end());
    Node* prev = pos._node->_prev;
    Node* next = pos._node->_next;
    prev->_next = next;
    next->_prev = prev;
    delete pos._node;
    return iterator(next);
}
```

&emsp;&emsp;复用得到``pop_back()``和``pop_front()``。

```cpp
void pop_back()
{
    erase(--end());
}
void pop_front()
{
    erase(begin());
}
```

## 7 list的拷贝构造和赋值和析构

**析构函数**：

&emsp;&emsp;先实现一个``clear()``,清除链表中所有元素(除了哨兵位头结点)，巧妙的利用后置++就可以实现的很优雅：

```cpp
void clear()
{
    iterator it = begin();
    while (it != end())
    {
        iterator del = it++;
        delete del._node;
        // 或者复用erase：
        // erase(it++);
    }
    // 把头结点自己链接自己
    _head->_next = _head->_prev = _head;
}
```

&emsp;&emsp;析构只要调用``clear()``然后干掉头结点即可。

```cpp
~list()
{
    clear();
    delete _head;
}
```

**拷贝构造传统写法**：

&emsp;&emsp;传统写法就利用``push_back``实现即可，不过首先要先把头结点弄出来。

```cpp
// 传统写法拷贝构造 利用尾插
list(const list<T>& lt)
{
    _head = new Node;
    _head->_next = _head->_prev = _head;
    for (auto e : lt)
    {
        push_back(e);
    }
}
```

**传统的赋值运算符重载**：

&emsp;&emsp;传统写法就是利用``clear()``和``push_back()``就可以了。

```cpp
// 传统写法赋值运算符重载(深拷贝)
list<T>& operator=(const list<T>& lt)
{
    if (this != &lt)
    {
        clear();
        for (auto e : lt)
        {
            push_back(e);
        }
    }
    return *this;
}
```

**拷贝构造的现代写法**

&emsp;&emsp;与``vector``的现代写法十分类似，我们首先提供一个函数模板，它支持任意迭代器区间来构造list，构造过程中，同样的记得初始化哨兵位头结点，复用``push_back``即可。

```cpp
// 拷贝构造现代写法:利用InputIterator区间构造
template<class InputIterator>
list(InputIterator first, InputIterator last)
{
    _head = new Node;
    _head->_prev = _head->_next = _head;
    while (first != last)
    {
        push_back(*first);
        ++first;
    }
}
```

&emsp;&emsp;然后拷贝构造函数就首先让一个临时的``list``对象使用传过来的``lt``的迭代器区间构造，然后交换他们的``_head``，考虑到析构的问题，我们首先要把``this->_head``搞成哨兵位头结点，从而预防进行析构中的``clear``取``begin() = _head->_next``和``delete _head``而崩溃。

```cpp
// lt2(lt1) 现代写法 复用迭代器区间构造
list(const list<T>& lt)
{
    _head = new Node;
    _head->_next = _head->_prev = _head;
    // 利用临时对象tmp来调用迭代器区间初始化
    list<T> tmp(lt.begin(), lt.end());
    // 交换指针即可
    std::swap(_head, tmp._head);
}
```

**赋值运算符重载的现代写法**

&emsp;&emsp;赋值运算符重载的现代写法就是通过传值复用拷贝构造，然后把``this->_head``和``lt->_head``交换一下，让值对象``lt``析构时帮我把垃圾带走，不得不说，真是太巧妙了。

```cpp
// 现代版本赋值运算符重载 利用传值复用拷贝构造函数
list<T>& operator=(list<T> lt)
{
    std::swap(_head, lt._head);
    return *this;
}
```

**两个区间构造函数的冲突**

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315204651.png" style="zoom:80%;" />

&emsp;&emsp;如果``value_type``和``size_type``类型相同，迭代器区间函数模板构造函数可能就和下面的n个T类型val冲突。

```cpp
list(size_t n, const T& val = T())
{
    _head = new Node;
    _head->_next = _head->_prev = _head;
    while (n--)
    {
        push_back(val);
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315205127.png" style="zoom:80%;" />

&emsp;&emsp;是无符号n造的孽啊，一个无符号，一个int，肯定不如模板两个int合适啊，所以解决方案就是在给上面的构造函数提供一个``int n``版本。

```cpp
list(int n, const T& val = T())
{
    _head = new Node;
    _head->_next = _head->_prev = _head;
    while (n--)
    {
        push_back(val);
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315205747.png" style="zoom:80%;" />

&emsp;&emsp;利用了编译器有现成的稍微匹配一些的函数时，不会主动去进行模板推导。

## 8 反向迭代器

### I 总体框架

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315223347.png" style="zoom:80%;" />

&emsp;&emsp;可以看到stl3.0中，反向迭代器是一个模板类，参数是一个正向迭代器。反向迭代器的大体框架就是包含了一个正向迭代器，然后反向迭代器的--复用正向迭代器的++，反向迭代器的++复用正向迭代器的--。

&emsp;&emsp;但是源码中的解引用和我们想的不一样，为啥是解引用正向迭代器的前一个位置呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315211133.png" style="zoom:80%;" />

&emsp;&emsp;这是因为``rbegin()``和``rend()``的定义，我们看看``stl_list.h``中的反向迭代器定义：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315220339.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315220949.png" style="zoom:80%;" />

&emsp;&emsp;因为设计源码的大佬追求了一个对称：反向迭代器的开始是正向迭代器的结束，反向迭代器的开始是正向迭代器的结束，所以``rbegin()``和它真正应该访问的值存在一个错位，解引用访问值时需要用一个临时变量``--tmp``，然后解引用它。

### II 第一种实现方法—为反向迭代器类模板增加参数

&emsp;&emsp;在设计解引用操作符重载时发现问题，我们不知道迭代器指向的参数的类型啊，所以这里还有类型的问题，模板中的参数没有迭代器指向的参数的类型，一种方法是哪里有问题解决哪里，为反向迭代器的模板增加参数即可。

&emsp;&emsp;考虑到``->``运算符，所以直接增加两个参数，一个表明改迭代器的对象的引用类型，另一个表明改迭代器对象的指针类型。

```cpp
template <class Iterator, class Ref, class Ptr>
class reverse_iterator
{
    typedef reverse_iterator<Iterator, Ref, Ptr> self;
public:
    reverse_iterator(Iterator it) : _it(it)
    {}
    // 反向迭代器 ++复用正向迭代器的--
    self& operator++()
    {
        --_it;
        return *this;
    }
    self& operator--()
    {
        ++_it;
        return *this;
    }
    // 后置++
    self operator++(int)
    {
        self tmp = *this;
        --_it;
        return tmp;
    }
    // 后置--
    self operator--(int)
    {
        self tmp = *this;
        ++_it;
        return tmp;
    }
    // 复用正向迭代器的!=
    bool operator!=(const self& rit)
    {
        return _it != rit._it;
    }

    bool operator==(const self& rit)
    {
        return !(*this != rit);
    }
    // 因为对称问题 访问的是_it前面一个元素
    Ref operator*()
    {
        Iterator tmp = _it;
        return *(--tmp);
    }
    // 复用反向迭代器的引用 然后取地址得到指针变量
    Ptr operator->()
    {
        return &operator*();
    }
private:
    Iterator _it;
};

```

&emsp;&emsp;然后在``list``中定义反向迭代器以及``rbegin``和``rend``:

```cpp
// 定义反向迭代器
typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
typedef reverse_iterator<iterator, T&, T*> reverse_iterator;
// 定义rbegin和rend
reverse_iterator rbegin()
{
    return reverse_iterator(end());
}
reverse_iterator rend()
{
    return reverse_iterator(begin());
}
const_reverse_iterator rbegin() const
{
    return const_reverse_iterator(end());
}
const_reverse_iterator rend() const
{
    return const_reverse_iterator(begin());
}
```

&emsp;&emsp;测试一下：

```cpp
void list_test7()
{
    list<Date> lt;
    lt.push_back(Date(2022, 3, 14));
    lt.push_back(Date(2022, 3, 13));
    lt.push_back(Date(2022, 3, 12));
    list<Date>::reverse_iterator it = lt.rbegin();
    while (it != lt.rend())
    {
        // cout << (*it)._year << '/' << (*it)._month << '/' << (*it)._day << endl;
        it->_month *= 2;
        cout << it->_year << '/' << it->_month << '/' << it->_day << endl;
        ++it;
    }
    // listdateprint(lt);
}
```

&emsp;&emsp;这样设计的优异性在于**对所有容器类型通用**，只要你自己的容器实现好正向迭代器，那么反向迭代器的行为就会是正确的，下面我们为我们之前写的``vector``增加反向迭代器。

```cpp
// 反向迭代器定义
typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
typedef reverse_iterator<iterator, T&, T*> reverse_iterator;
// rbegin和rend定义

reverse_iterator rbegin()
{
    return reverse_iterator(end());
}
const_reverse_iterator rbegin() const
{
    return const_reverse_iterator(end());
}
reverse_iterator rend()
{
    return reverse_iterator(begin());
}
const_reverse_iterator rend() const
{
    return const_reverse_iterator(begin());
}

// test

int main()
{
    scu::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    scu::vector<int>::reverse_iterator  it = a.rbegin();
    while (it != a.rend())
    {
        cout << *it << ' ';
        ++it;
    }
    return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315230743.png" style="zoom:80%;" />

&emsp;&emsp;``vector``这里如果不完全对称设计，那么就会出现越界问题。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220315231324.png" style="zoom:80%;" />

&emsp;&emsp;这就是泛型模板的威力。

### III 第二种实现方式—迭代器萃取

&emsp;&emsp;另一种实现方法就是迭代器萃取、

## 9 适配器

&emsp;&emsp;我们充电时，充电器一般叫做电源适配器，本质是一个变压器，把``220v``的家庭电压转化为电子设备需要的电压。

&emsp;&emsp;适配器的语义本质是转化，反向迭代器这里的作用也是一种“转换的作用”，你把容器的正向迭代器传参传给我，我就给你生成一个反向迭代器。

## 10 迭代器萃取是什么

&emsp;&emsp;我们知道，那个迭代器明明它自己就有T&和T*的类型了，我们反向迭代器却又加了三个模板参数，我们可以通过取迭代器内的内嵌类型来减少反向迭代器的模板参数。

```cpp
//...正向迭代器内
// 把模板参数typedef成正向迭代器的内部类型
typedef Ref reference;
typedef Ptr pointer;

// 反向迭代器内：
// 加了typename的含义就是告诉编译器这是一个类型
// 你等着Iterator实例化后来获取这个类型。
typedef typename Iterator::reference Ref;
typedef typename Iterator::pointer Ptr;
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322195638.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322195659.png" style="zoom:80%;" />

&emsp;&emsp;对list正常运行：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322195859.png" style="zoom:80%;" />

&emsp;&emsp;但是这样写的缺陷就是针对``vector``和``string``时，原生指针它里头并没有任何内嵌类型，它里头可不可能嵌套这类型的，你还得自己再单独给他们造一个迭代器。

&emsp;&emsp;``STL``的源码中是使用迭代器的萃取来解决这个问题的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220322195149.png" style="zoom:80%;" />

&emsp;&emsp;思路就是对普通迭代器，使用与我们上面类似的技巧来实现，如果是一个原生指针，针对这个模板参数进行模板特化就行了。