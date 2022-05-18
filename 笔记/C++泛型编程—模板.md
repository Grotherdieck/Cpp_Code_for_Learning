# 一、泛型编程

&emsp;&emsp;泛型编程的含义就是对同类算法和数据结构，对于不同的数据类型，使用同样的接口。

&emsp;&emsp;由于C++支持函数重载，我们可以用函数重载来模拟泛型编程。

```cpp
void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(double& a, double& b)
{
    double tmp = a;
    a = b;
    b = tmp;
}
```

&emsp;&emsp;但是如果我们每个类型都得自己重载，就很麻烦，函数会越写越多。

&emsp;&emsp;观察到这些``swap``函数仅仅只有类型不同，其他细节都相同，C++提供了一种称为模板的机制，可以把类型与函数暂时分离，它的原理就是用把这些刻到板子上，用的时候印刷一下。

```cpp
template <class T>//这里也可以写 template <typename T> 模板参数列表
void Swap(T& a, T& b)// 函数参数列表
{
    T tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a = 2, b = 1;
    double c = 1.1, d = 1.2;
    char e = '1', f = '2';
    Swap(a, b);
    Swap(c, d);
    Swap(e, f);
}
```

# 二、函数模板

&emsp;&emsp;模板并不是函数，模板其实相当于一块板子，当你具体要用的时候，会根据我们参数的类型，生成对应的函数，就像板子被印刷出具体的一份一样，这个过程称为模板实例化。

&emsp;&emsp;观察反汇编发现是编译器为我们生成了参数类型对应的函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219122256.png" style="zoom:67%;" />

&emsp;&emsp;函数模板可以根据参数类型自动推理，大部分情况不需要显示的写上参数类别。

&emsp;&emsp;当类型冲突时，我们可以强转类型或显式的实例化模板。

```cpp
template <class T>
T add(const T& a, const T& b)
{
    return a + b;
}
int main()
{
    int a = 1, b = 2;
    double c = 1.0, d = 3.0;
    // 如果直接写 add(a, c);究竟是要int a变double还是double c变int呢
    // 就冲突了。
    add<int>(a, c);
    add<double>(b, d);
    add((double)a, c);
    add(a, (int)d);
}
```

&emsp;&emsp;这种情况是允许存在的：

```cpp
// 专门处理int的加法函数
int Add(int left, int right)
{
 	return left + right;
}
// 通用加法函数
template<class T>
T Add(T left, T right)
{
 	return left + right;
}
void Test()
{
 	Add(1, 2); // 与非模板函数匹配，编译器不需要特化
 	Add<int>(1, 2); // 调用编译器特化的Add版本
}
```

&emsp;&emsp;当普通函数和函数模板同时存在的时候，默认会调用普通函数，而不会实例化模板，编译器遵循懒人原则，都已经有了可以用的普通函数我干嘛要帮你实例化。

# 三、类模板

&emsp;&emsp;同理，是我们调用的时候根据指定的模板参数从模板中实例化出不同的类。

```cpp
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class Stack
{
public:
    Stack(int capacity = 4):_top(0), _capacity(capacity)
    {
        _a = new T[capacity];
    }
    ~Stack()
    {
        delete[] _a;
        _top = 0;
        _capacity = 0;
        cout << "~Stack()" << endl;
    }
    bool empty()
    {
        return _top == 0;
    }
    T& top()
    {
        assert(!this->empty());
        return _a[_top - 1];
    }
    void Push(const T& x)
    {
        _a[_top++] = x;
    }
    void Pop()
    {
        assert(!this->empty());
        --_top;
    }
private:
    T* _a;
    int _top;
    int _capacity;
};

int main()
{
    Stack<int> st(100);
    st.Push(1);
    st.Push(2);
    st.Push(3);
    st.Push(4);
    st.Push(5);
    st.Push(6);
    while (!st.empty())
    {
        cout << st.top() << ' ';
        st.Pop();
    }
    return 0;
}

```

&emsp;&emsp;如果你想把类模板的成员函数的定义与声明分开，必须这样：

```cpp
template <class T>
void Stack<T>::Push(const T& x)
{
    _a[_top++] = x;
}
```

&emsp;&emsp;对于类模板来说，Stack是类名，具体的类型是它实例化出来的东西，如``Stack<int>``.

&emsp;&emsp;注意类模板不要把成员函数和类声明放到不同的文件里中。



