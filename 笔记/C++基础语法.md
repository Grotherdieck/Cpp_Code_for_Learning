C++弥补了很多C语言没法解决缺陷。

# 一、命名空间

&emsp;&emsp;命名空间解决的是命名冲突的问题。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211123205445811.png)

&emsp;&emsp;rand和stdlib中的rand函数冲突了。

&emsp;&emsp;命名冲突问题主要有以下场景：

1. 我们自己定义的函数或变量名可能与库中的冲突。
2. 多人合作的大项目中，多人协作时命名冲突。

&emsp;&emsp;C语言没有特别好的方法去解决这个问题，它会建议你换个名字。

&emsp;&emsp;C++首先提供了一个新语法——命名空间，来解决这个问题。

```cpp
#include <stdlib.h>

namespace scu
{
	int rand = 1;
}
```

&emsp;&emsp;此时stdlib中的rand在全局范围，我定义的rand被隔离在一个“域”scu中，属于局部范围。

&emsp;&emsp;域：在C语言中我们就学习过，在不同的域中可以定义相同名字的变量。

&emsp;&emsp;编译器寻找变量，一般是现在局部找，然后在全局找，但是如果我们不加“域作用限定符”::它就不会在我们定义的命名空间找。

&emsp;&emsp;其实::符号在C语言中就有使用：

```cpp
int a = 0;
int main()
{
	int a = 1;
	printf("%d\n", ::a);
	return 0;
}
// ::前面是一个空格表明在全局域找
//这样就能打印这个全局a=0了。
```

&emsp;&emsp;命名空间的定义一定是全局的。

```cpp
//rand仍然是全局的变量 数据放在静态区
//只是被隔离起来了
//同样的我们对局部变量初始化以后没办法在命名空间中更改值
namespace scu
{
	int rand = 1;
}
```

&emsp;&emsp;**命名空间的定义**

- 命名空间中可以定义函数、变量、类型，函数定义可以和命名空间分离，可以只放定义。

```cpp
namespace scu
{
    int i = 1;
    int add(int x, int y)
    {
        return x + y;
    }
    typedef struct Node {
        int val;
        struct Node* next;
    }Node;
}

namespace scu
{
	int rand = 1;
	int add(int x, int y);
}

int scu::add(int x, int y)
{
	return x + y;
}
```

- 命名空间可以嵌套定义。

```cpp
namespace scu
{
	int rand = 1;
	int add(int x, int y);
	namespace ustec
	{
		int j = 1;
	}
}

int main()
{
    scu::rand = 2;
    scu::ustec::j = 3;
    return 0;
}
```

- 同一个工程中多个相同名称的命名空间会被编译器合并到一起。

```cpp
namespace Linklist
{
    typedef struct NODE {
      int val;
      struct NODE* next;
    }Node;
    void listInit(Node** pphead);
}

namespace Linklist
{
    void listInit(Node** pphead)
    {
        *pphead = (Node*)malloc(sizeof(Node));
        if (*pphead == nullptr)
        {
            exit(-1);
        }
        (*pphead)->next = nullptr;
    }
}
```

&emsp;&emsp;**命名空间的使用**

- 使用域作用限定符::

```cpp
scu::add(1,2);
```

&emsp;&emsp;这种方式能做到最好的命名隔离，但是使用并不方便。

- 把整个命名空间**展开**到全局：

```cpp
using namespace scu;
```

&emsp;&emsp;命名空间全部展开到全局，用起来方便，但是**隔离**效果失效了。

```cpp
#include <stdlib.h>
namespace scu
{
    int rand = 1;
}
using namespace scu;
int main()
{
    printf("%d",rand);
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211123214000781.png)

&emsp;&emsp;我们也可以单独展开某一个：

```cpp
namespace Linklist
{
    typedef struct NODE {
      int val;
      struct NODE* next;
    }Node;
    void listInit(Node** pphead);
}

namespace Linklist
{
    void listInit(Node** pphead)
    {
        *pphead = (Node*)malloc(sizeof(Node));
        if (*pphead == nullptr)
        {
            exit(-1);
        }
        (*pphead)->next = nullptr;
    }
}

using Linklist:: Node;

int main()
{
    Node* LTNode;
    Linklist::listInit(&LTNode);
    return 0;
}
```

# 二、C++的输入流和输出流

&emsp;&emsp;C++库中的函数和类的声明放在命名空间std中。

```cpp
int main()
{
    std::cout << "hello world" << std::endl;
}
```

&emsp;&emsp;cout是一个**全局**的输出流对象。

&emsp;&emsp;为了方便，我们可以把std中常用的东西给展开，比如：

```cpp
using std::cout;
using std::cin;
```

```cpp
<<
//流插入运算符，流向cout这个输出流
std::endl
//待补充
>>
//流提取运算符
```

```cpp
#include <iostream>

using std::cout;
using std::cin;

int main()
{
	int i = 1;
	double f = 1.1;
	cout << i << " " << f << std::endl;
}
```

&emsp;&emsp;cout和cin都可以自动识别类型进行输入输出，无需像printf和scanf一样需要指定好格式。

&emsp;&emsp;但有的时候我们想修改输出的小数位数，这时显然使用printf使用比较方便。

```cpp
printf("%.3lf",f);
```

```cpp
struct Student {
	char name[20];
	int age;
};

int main()
{
	Student s;
	cin >> s.name >> s.age;
	cout << s.name << " " << s.age << endl;
	return 0;
}
```

&emsp;&emsp;cin和scanf一样，在不加别的条件默认使用时，不会读取我们两个数据之间的空格。

&emsp;&emsp;所以我们应该视具体情况选择适当的输入输出运算符。

注意：

```cpp
#include <iostream.h>
//这是很古老的编译器的写法，大概VC6.0有这样写
//现代编译器中这样写是编译不过的。
```

# 三、缺省参数

&emsp;&emsp;缺省参数也叫默认参数。

&emsp;&emsp;意思就是说我们设定为缺省参数的变量，在调用函数的时候我们可以不传这个参数，编译器会拿缺省值做实参传给函数。

```cpp
void f(int a = 0)
{
    cout << a << endl;
}

int main()
{
    f(1);
    f();
}
```

&emsp;&emsp;注意：

1. **缺省参数只能写一次**，可以在声明中写了，然后在函数实现的时候就不能再写缺省参数了，否则会报错，推荐在声明中写缺省参数，这样方便在查看接口时查看。
2. 缺省值必须是常量或者是全局变量。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125192854275.png)

```cpp
void h(int x = 1, int y = 2, int z = 3)
{
    cout << x << y << z << endl;
}
//全缺省参数
```

&emsp;&emsp;半缺省：缺省部分参数且**必须从右往左缺省**，否则编译器会报错。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125193344525.png)

```cpp
void fun(int a = 10, int b = 2, int c = 1);

void fun(int a, int b, int c)
{
	cout << a << b << c << endl;
}

int main()
{
	fun(1);
	fun(1, 3);
	fun(1, 3, 4);
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125193655207.png)

&emsp;&emsp;缺省参数的简单应用：

```cpp
typedef struct Stack {
	int* a;
	int size;
	int capacity;
}Stack;

//利用缺省参数，你不传栈空间大小我就开出默认大小的栈
//你传栈空间大小就可以以你传的参数初始化，
//当然应该检查一下用户传的参数是否合法
void StackInit(Stack* st, int capacity = 4)
{
	st->a = (int*)malloc(sizeof(int) * capacity);
	st->size = 0;
	st->capacity = capacity;
}
```

# 四、函数重载

## 1 函数重载的语法

&emsp;&emsp;重载在自然语言中的意思是一词多意，函数重载的意思是对同样的函数名在某些不同情况下有不同的定义。

&emsp;&emsp;函数重载:是函数的一种特殊情况，C++允许在**同一作用域**中声明几个功能类似的**同名函数**，这些同名函数的 形参列表(**参数个数**或**类型**或**顺序**)必须不同，常用来处理实现功能类似数据类型不同的问题。

1. **类型不同**

```cpp
int add(int x, int y)
{
    return x + y;
}
double add(double x, double y)
{
    return x + y;
}
```

2. **参数个数不同**

```cpp
void h()
{
    cout << "恶作剧的对象 是你哦" << endl;
}

void h(int a)
{
    cout << a << endl;
}
```

3. **顺序不同**

```cpp
void h(int a, char b)
{
    cout << "h(int,char)" << endl;
}

void h(char b, int a)
{
    cout << "h(char,int)" << endl;
}
```

&emsp;&emsp;但是**返回值不同不能构成函数重载的条件**。

&emsp;&emsp;注意：

1. 缺省值不同，不能构成重载，因为不满足构成缺省的3个条件。

```cpp
void f(int a);
void f(int b = 1);
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125201020118.png)

2. 一些歧义情况。

```cpp
void f(int a = 1)
{
	cout << a << endl;
}

void f()
{
	cout << "f()" << endl;
}

int main()
{
	f();
}

//这两个f构成重载，编译能过就是证据。
//但是使用时会出问题
//当不传参的时候，调用存在歧义。
```

![img](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125201209305.png)

## 2 函数重载的原理—编译过程中的函数名修饰

&emsp;&emsp;这里我们用g++和gcc编译器来看，因为windows下函数重载有些怪异。

&emsp;&emsp;验证C语言不支持函数重载，以linux下gcc编译器为例。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125205900208.png)

&emsp;&emsp;这里我们用gcc编译器（就是以C的规则编译）编译这两个文件：

```shell
gcc test.c fun.c
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125205928181.png)

&emsp;&emsp;注释掉重载部分后：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125211205631.png)

&emsp;&emsp;编译通过了。

&emsp;&emsp;我们恢复重载部分，使用cpp的编译器g++重新编译：

```shell
g++ test.c fun.c
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125210440402.png)

&emsp;&emsp;可以看到编译通过了，并且执行效果和我们预期一样（这里把fun()改为了输出fun()\n，fun(int a)输出fun(int)\n）。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125211929658.png)

&emsp;&emsp;这里需要注意的是VS中是根据文件的后缀决定调用什么编译器，.c调用C的编译器，.cpp就调用C++编译器。linux下不需要管后缀，只看你用的编译器是gcc还是g++。

&emsp;&emsp;回顾一下编译器编译这个程序为可执行程序的全过程：

```cpp
fun.h fun.c test.c
```

1. 编译预处理：把编译预处理指令执行一下，如头文件展开，宏替换，条件编译，去掉注释。

   fun.i test.i
2. 编译：检查语法，生成汇编代码（指令级的语言，CPU看不懂，人能看懂的指令级语言）。（更多内容详情请见编译原理）

   fun.s test.s
3. 汇编：汇编代码转化为二进制的机器码，符号表的生成也在这一步。

   fun.o test.o
4. 链接：通过符号表把只有声明的函数、外部变量等的地址都补全，然后链接到一起，如果没有指定的时候linux下会生成a.out。

&emsp;&emsp;C语言不支持函数重载和**汇编和链接**这两个过程有关，我们为了看的懂链接过程中的.o文件我们用汇编来看（因为二进制机器代码看不懂。

&emsp;&emsp;在函数栈帧中，我们知道调用函数就是call进入函数的跳转表，然后再jmp到函数起始指令的地址，可以理解成那个地址就是函数的第一条语句存储在的地址区域。

&emsp;&emsp;所以执行函数最本质的步骤是**得到函数指令所在的地址**。

&emsp;&emsp;函数声明是不会有地址的，因为声明没有定义，地址是第一条指令（定义内容）所在的地址。

&emsp;&emsp;所以在链接以前，test.o中由于没有fun()和fun(int a)的定义，编译过程执行函数调用这一步的时候，**找不到地址我们就只能记忆名字**，链接是用函数名字去各个符号表找指令。

&emsp;&emsp;在C语言中，符号表中的函数名字就是原名，比如这里的fun函数，记忆的名字就是fun，那两个fun名字一样啊，符号表中出现歧义了就，所以在编译这一步就出错了。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125213102663.png)

&emsp;&emsp;所以C语言不支持函数重载可以解释如下：

&emsp;&emsp;在编译的时候，两个重载函数，函数名相同，在fun.o的符号表中存在歧义和冲突，其次链接时由于函数名相同，寻找函数地址也存在歧义和冲突。

&emsp;&emsp;事实胜于雄辩，我们去掉重载部分，用gcc编译后，使用objdump查看反汇编：

```shell
gcc -o ctest test.c fun.c
objdump -S ctest
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125231450270.png)

&emsp;&emsp;可以看到gcc的汇编过程的函数名就是函数原名。

&emsp;&emsp;C++的目标文件符号表中不是直接用函数名来标识和查找函数的。

&emsp;&emsp;C++引入了**函数名修饰规则**。

&emsp;&emsp;事实胜于雄辩，加上重载部分后，我们直接来看看我们a.out的汇编。

&emsp;&emsp;使用指令：

```shell
g++ test.c fun.c
objdump -S a.out
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125225002489.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125223355920.png)

&emsp;&emsp;注意到g++编译后，两个函数的名字分别是_Z3funi和\_Z3funv。

&emsp;&emsp;这里_Z是前缀，3是函数名的长度，fun是函数名，i是参数类型int的缩写，v是参数类型void的的缩写。

&emsp;&emsp;g++把编译过程执行函数调用时，修饰函数名的规则：

$$
\_Z+函数名长度+函数名+参数首字母（其实更详细的前面还要加上作用域）
$$

&emsp;&emsp;我们可以看这个函数经过修饰后的函数名：

```cpp
void test(int a, int* p);
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125230300222.png)

&emsp;&emsp;所以我们在编译过程中，我们执行到调用fun()和fun(1)的时候，就转化成汇编指令：

```cpp
call _Z3funv(?)
call _Z3funi(?)
//？代表地址未知
```

&emsp;&emsp;对于这里的汇编过程，调用函数名字填地址时，如果在当前文件有函数的定义，那么编译就填上地址了；如果在当前文件中只有函数的声明，定义在其他.cpp中，编译时没有地址，只能链接的时候去其他文件的符号表中根据函数修饰名去找，这是链接的重要工作。

&emsp;&emsp;我们这里也属于后一种情况。

&emsp;&emsp;然后fun.c会编译成如下汇编代码：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125225103245.png)

&emsp;&emsp;因为这两个函数函数名经过修饰都不同，fun.o的符号表不会冲突，且在链接过程中函数名不同所以调用也不会冲突。

&emsp;&emsp;然后在链接过程根据修饰后的函数名可以找到对应的不同的重载函数，就可以把?填上了，然后链接到一起成可执行文件。

&emsp;&emsp;所以有了C++的函数名修饰规则，只要参数不同，fun.o的符号表里面重载的函数的函数名不同，就不存在二义性和冲突了。

&emsp;&emsp;在链接的过程中，test.o中的main函数去调用两个重载的函数，由于修饰后的函数名不同，在fun.o中查找地址的时候，也是明确的。

&emsp;&emsp;windows下VS编译器也是同样的道理，只是规则比较奇怪，其实道理一样：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211125232831035.png)

&emsp;&emsp;对比linux g++的函数名修饰规则可以发现，windows下的函数名修饰规则很诡异，不过道理都是一个道理，通过函数名修饰的方法让两个重载的函数修饰后的函数名不同，这样就能调用不同的函数。

&emsp;&emsp;修饰规则是写编译器的人定的，C++标准并没有给出修饰规则的统一标准。

# 五、extern "C"

&emsp;&emsp;假如一个C程序想调用C++动态库或动态库，一个C++程序想调用我们写的C的动态库或静态库。

## 1 C++项目调用C的静态库

&emsp;&emsp;for example，有下面一个程序：

```cpp
bool isValid(char * s)
{
    //思路：遇到左括号 入栈
    //遇到右括号 出栈匹配
    //最后看看栈是否为空
    //如果一上来就遇到右括号 也就是说一上来就想出栈 栈为空
    //那就return false
    Stack st;
    StackInit(&st);
    while(*s)
    {
        if(*s == '(' || *s == '[' || *s == '{')
        {
            StackPush(&st, *s);
            s++;
        }
        if(*s == '}' || *s == ')' || *s == ']')
        {
            if(StackEmpty(&st)==true)
            {
                Stackdestroy(&st);
                return false;
            }
            StackDataType x = StackTop(&st);
            StackPop(&st);
            if((*s == '}' && x != '{') || (*s == ']' && x != '[') || (*s == ')' && x != '('))
            {
                Stackdestroy(&st);
                return false;
            }
            s++;
        }
    }
    if (StackEmpty(&st) == true)
    {
        Stackdestroy(&st);
        return true;
    }
    else
    {
        Stackdestroy(&st);
        return false;
    }
}

int main()
{
    char str1[] = "{[]}";
    cout << isValid(str1) << endl;
    char str2[] = "(()]}";
    cout << isValid(str2) << endl;
}
```

&emsp;&emsp;用到了我们在数据结构学习中实现的栈，假如我们已经把之前用C语言写的栈和队列实现成了一个静态库：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201140440125.png)

&emsp;&emsp;首先我们包一下头文件：

```cpp
#include "../Stack/Stack.h"//..是往上一层目录跳 找其他位置的头文件
```

&emsp;&emsp;然后使用一种方法链接一下我们的静态库

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141115078.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141135353.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141239864.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141316910.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141430148.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141453618.png)

&emsp;&emsp;现在就链接好了静态库了，尝试编译一下：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201141605638.png)

&emsp;&emsp;还是报了一堆链接错误。

&emsp;&emsp;回忆C++的函数重载的原理，C++的函数名修饰和C的规则不一样，C++把头文件的函数用C++的修饰后的函数名去找，然而C的静态库中C的函数的名字应该是原名，符号表中找不到修饰后的名字啊。

&emsp;&emsp;那难道C++项目就不能调C的库了吗？本标题的知识就要出场了——extern "C"。

```cpp
extern "C"
{
    #include "../Stack/Stack.h"
}
```

&emsp;&emsp;这句代码是告诉C++的编译器，这个头文件是用C的风格编译的，链接的时候用C的函数名修饰规则才能找到对应函数。

&emsp;&emsp;加上这句后，就成功了：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201142433089.png)

## 2 C项目调C++静态库

&emsp;&emsp;那么我们考虑用C来调用C++的静态库呢？

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201143605715.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201143649251.png)

&emsp;&emsp;发现链接失败，以C的函数名修饰规则找不到.lib中的函数，因为Stack现在是一个CPP静态库，函数名用C++的函数名修饰规则修饰了，C项目用它的函数名修饰规则找不到C++的函数了。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201143745362.png)

&emsp;&emsp;解决方法1：在静态库的头文件中中修改

```cpp
extern "C"
{
	void StackInit(Stack* ps);
	void StackPush(Stack* ps, StackDataType e);
	void StackPop(Stack* ps);
	StackDataType StackTop(Stack* ps);
	int StackSize(Stack* ps);
	bool StackEmpty(Stack* ps);
	void Stackdestroy(Stack* ps);
}
```

&emsp;&emsp;以下函数按照C的规则修饰了，注意也就无法重载了。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201144118653.png)

&emsp;&emsp;但是这时还是报错，因为我们包了头文件，C的编译器不识别extern "C"。

&emsp;&emsp;一个巧妙的利用编译预处理的解决方法，cpp项目都会默认定义一个宏__cplusplus，利用条件编译指令，如果是\_\_cplusplus，那就定义extern "C"和{}包起来，在我们的C项目中引这个头文件的时候就不会看到extern "C"和{}，但这里要注意，由于使用了C的函数修饰风格，被修饰的函数都不支持函数重载了。

```cpp
#ifdef __cplusplus
extern "C"
{
#endif
	void StackInit(Stack* ps);
	void StackPush(Stack* ps, StackDataType e);
	void StackPop(Stack* ps);
	StackDataType StackTop(Stack* ps);
	int StackSize(Stack* ps);
	bool StackEmpty(Stack* ps);
	void Stackdestroy(Stack* ps);
#ifdef __cplusplus
}
#endif
```

&emsp;&emsp;就成功的让C++的.lib在做库的函数的时候使用了C的编译规则，并且规避了C的编译器不识别extern "C"的问题。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201145523501.png)

&emsp;&emsp;这种是函数特别多的情况，我们也可以针对一个一个函数规定它是否使用C的函数名修饰风格：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201150049852.png)

&emsp;&emsp;在C++项目中，EXTERN_C被替换成extern "C"，告诉编译器后面的函数以C的风格来修饰函数名；在C项目中，EXTERN_C宏定义后面是个空的，会被替换成空，就什么也不会发生，绕开了C编译器不识别extern "C"的问题。

&emsp;&emsp;在linuxg++编译器下测试extern "C"如下：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201151131901.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201151059663.png)

总结：

在C++程序中调用C的库，给引的头文件加extern "C";

在C程序中调用C++的库，在C++库中的头文件里或直接针对需要按C风格编译的函数加extern “C”。

# 六、引用

## 1 引用的概念

&emsp;&emsp;引用不是新定义一个变量，而是给已经存在的变量取一个别名，编译器不会为引用变量开辟空间，它和引用的变量共用同一块内存空间。

**语法**：

```cpp
int main()
{
    int a = 10;
    int& b = a;//引用定义
    int* p = &a;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128094523612.png)

&emsp;&emsp;引用在语法层，这里没有开辟新空间，只是对原本的空间取了一个**新名称**叫做b。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128094822663.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128094839489.png)

## 2 引用的特性

1. 引用在定义时必须初始化。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128095319404.png)

&emsp;&emsp;对比指针变量，指针定义时可以不初始化。

2. 一个变量可以有多个引用(一个人可以有多个外号)。

```cpp
int main()
{
	int a = 10;
	int& b = a;
	int& c = a;
	int& d = b;
    double d = 1.1;//冲突了 d这个名字已经存在了
}
```

3. 引用一旦引用一个实体，再不能引用其他实体。

```cpp
int a = 3;
int c = 20;
int& b = a;
b = c;//报错
//这里是把c的值赋值给b，而不是让b变成c的别名。
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128100339735.png)

&emsp;&emsp;指针在没有const修饰的情况下，是可以修改自身值指向别的变量的。

&emsp;&emsp;Java的引用和C++并不相同，单用引用的话在C++中都实现不了链表。

## 3 常引用

```cpp
void TestConstRef()
{
 const int a = 10;
 //int& ra = a; // 该语句编译时会出错，a为常量
 //ra是int&，可读可写了，权限变大了，a都只是一个常量，ra居然还想改a，报错。
 //权限不变
 const int& ra = a;
 // int& b = 10; // 该语句编译时会出错，b为常量
 const int& b = 10;
 double d = 12.34;
 //int& rd = d; // 该语句编译时会出错，类型不同
 //权限缩小
 const int& rd = d;
}
```

&emsp;&emsp;作用在于如果我们传的引用只是为了提高效率，只是要用对象做一些输出，而不想给你改我的对象的权限，就可以用const引用。

## 4 使用场景

1. 做参数。

&emsp;&emsp;引用做参数其实是在传参的时候创建引用变量为形参，做实参的别名。

```cpp
//没有引用时
void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
//使用引用
void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int main()
{
    int a = 3;
    int b = 4;
    swap(a,b);
    swap(&a,&b);
}
//a作为实参传给了引用变量x，x成了a的引用
//同理y成了b的引用
//交换x和y可不就是交换原来的a和b嘛
```

&emsp;&emsp;引用在定义的时候必须初始化，在我们传参的时候就已经把引用变量x和y都初始化了。

&emsp;&emsp;C++目前我们有三种传参方式：传值、传地址、传引用，传引用和传指针都可以做到通过修改形参进而修改实参。

&emsp;&emsp;三个方式构成重载，因为是不同类型的变量，编译能过；但是当你调用的时候，swap(a, b)，调用时存在歧义，编译器不知道要调用传值还是传引用。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128103618878.png)

&emsp;&emsp;因此这样重载由于没法调用其实没有意义。

&emsp;&emsp;应用：使用引用修改不带头的单链表的尾插

```cpp
//原
void SLpushback(SLNode** pphead, Datatype x)
{
	SLNode* newnode = createListNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}
//引用版本 phead的改编就是改变SLNode*
void SLpushback(SLNode*& phead, Datatype x)
{
	SLNode* newnode = createListNode(x);
	if (phead == NULL)
	{
		phead = newnode;
	}
	else
	{
		SLNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}
//还可以再typedef
typedef struct SLNODE {
	Datatype data;
	struct SLNODE* next;
}SLNode,*SList;
//把struct SLNODE*typedef成SList
void SLpushfront(SList& phead, Datatype x)
{
	SLNode* newnode = createListNode(x);
	newnode->next = phead;
	phead = newnode;
}
```

2. 引用做返回值

&emsp;&emsp;引用返回的本质是返回一个临时变量，是一个引用变量（底层是地址），然后你用正常变量接就是通过引用找到了那个对象，然后拷贝给那个正常变量；用引用接这个返回值就是又给那个对象取了一个别名。

```cpp
//传值返回
int Add(int x, int y)
{
    int c = a + b;
    return c;
}

int main()
{
    int ret = Add(1, 2);
}
//这里返回的是c的值 c是一个临时变量
//出了作用域c这个变量就销毁了
//所以返回的是c的值 而不是c这个变量。
//并不是取c这个空间中的值给ret，而是值拷贝。
```

临时变量存在哪里：

- 如果返回值比较小（4或8个字节），一般用寄存器充当临时变量、
- 如果返回值比较大，临时变量会放在调用层的栈帧中。

所有的值返回都有一层拷贝。

引用返回的意思就是：不会生成返回值的拷贝去返回，而是直接返回一个返回值的引用。

```cpp
int& Add(int x, int y)
{
    int c = a + b;
    return c;
}
int main()
{
    int ret = Add(1, 2);
}
```

这样写代码的问题：

- 存在非法访问，因为Add(1, 2)的返回值是c的引用，相当于返回了一个int&tmp，当ret接收tmp 的时候，Add函数的栈帧已经销毁了，ret获得tmp的那块空间的值相当于重新访问到栈帧中的c，然而你离开栈帧的时候，c的空间已经销毁了还给系统了。
- 如果Add函数栈帧销毁会清理空间，那么取c值会访问到随机值，给ret的就是随机值（ps vs下销毁栈帧不会清）

比如如果有人这样写代码，就会很奇怪

```cpp
int& Add(int x, int y)
{
    int c = a + b;
    return c;
}
int main()
{
    int& ret = Add(1, 2);
    cout << ret << endl;
    Add(10, 20);
    cout << ret << endl;
}
//输出
//3 30
```

ret是Add栈帧中c的别名，所有权不在编程者，再次调用Add的时候，c那个位置的值会被改成30，ret也就被改成了30，**并没有显式的改ret，但是ret却被改变了**。

可以看到linux下g++编译器销毁栈帧也不会把栈帧初始化。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128120056098.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128120641259.png)

总而言之，不要轻易返回引用，尤其是生命周期只在这个函数里的对象的引用。

原则：**如果函数返回时，出了函数作用域，如果返回对象还未还给系统，则可以使用引用返回；如果已经还给系统了，则必须使用传值返回**。

```cpp
int& getelem(int n)
{
    int* p = (int*)malloc(sizeof(int));
    *p = n;
    return *p;
    //p是一个指针变量，是一个临时变量，出了作用域销毁了
    //但是p指向的空间，也就是一个堆上的变量 并没有销毁 可以返回引用
}
const int N = 10;
int& At(int i)
{
    static int a[N];
    return a[i];
}
//ps 这里At不能返回int 否则会编不过
//因为返回值相当于生成一个临时变量 临时变量具有常量性 也就是说 临时变量是右值
int main()
{
    for (size_t i = 0; i < N; i++)
    {
        At(i) = i + 10;
        //返回的是引用，通过At(i)修改那个静态数组中的a[i]
    }
    for (size_t i = 0; i < N; i++)
    {
        cout << At(i) << endl;
    }
}
```

## 5 传值、传引用 返回值、返回引用效率对比

&emsp;&emsp;传引用、返回引用的好处是：**不用拷贝整个对象**，当对象很大的时候，传值返回值会出现很大的效率损失。

传引用效率：

```cpp
#include <time.h>
struct A { int a[100000]; };
void TestFunc1(A a) {}
void TestFunc2(A& a) {}
void TestRefAndValue()
{
	A a;
	// 以值作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc1(a);
	size_t end1 = clock();
	// 以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc2(a);
	size_t end2 = clock();
	// 分别计算两个函数运行结束后的时间
	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
}

int main()
{
	TestRefAndValue();
}

```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128121413827.png)

返回引用 返回值效率对比：

```cpp
#include <iostream>
using namespace std;
#include <time.h>
struct A { int a[100000]; };
A a;
// 值返回
A TestFunc1() { return a; }
// 引用返回
A& TestFunc2() { return a; }
void TestReturnByRefOrValue()
{
	// 以值作为函数的返回值类型
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc1();
	size_t end1 = clock();
	// 以引用作为函数的返回值类型
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		TestFunc2();
	size_t end2 = clock();
	// 计算两个函数运算完成之后的时间
	cout << "TestFunc1 time:" << end1 - begin1 << endl;
	cout << "TestFunc2 time:" << end2 - begin2 << endl;
}

int main()
{
	TestReturnByRefOrValue();
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211128121708145.png)

总结：引用的作用主要体现在传参和传返回值

- 引用传参和传返回值，在有些场景下，可以提高性能（很大的对象、深拷贝对象）
- 引用传参和传返回值，输出型参数和输出型返回值，传引用可以形参改变实参。

## 6 有趣的小问题

```cpp
double d = 1.11;
int& a = d;//报错
const int& b = d;//正常
```

&emsp;&emsp;你在用d给a的时候，其实是创建了一个临时变量，如int a = d，创建了一个临时变量给a，这里也是同理，这个临时变量同样具有常量性，一个常量必须用常引用，下面这个也是右值引用的问题。

```cpp
int x1 = 2;
int x2 = 3;
int& a = x1 + x2;//报错
const int& a = x1 + x2;//正常
```

&emsp;&emsp;总结一句话，因为运算和类型转换产生的临时变量是右值，具有常性，不能修改。

&emsp;&emsp;const引用“通吃”，可以接收任意类型的变量，所以在传参的时候，如果传引用的参数不需要改变，那就传常引用就行了，这样传普通对象，可以接收；传const对象，可以接收；传临时变量，也可以接收。

## 7 指针和引用的区别

引用和指针的不同点:

1. 引用在定义时**必须初始化**，指针没有要求；
2. 引用在概念上是定义了一个**变量的别名**，指针是存储了一个**变量的地址**；
3. 引用在初始化时引用一个实体后，**就不能再引用其他实体**，而**指针可以在任何时候指向任何一个同类型实体**；
4. 没有**NULL引用**，**但有NULL指针**；
5. 在**sizeof**中含义不同：引用结果为**引用类型的大小**，但指针始终是地址空间所占字节个数(32位平台下占 4个字节)；
6. 引用自加即**引用的实体增加1**，指针自加即**指针向后偏移一个类型的大小**；
7. 有**多级指针**，但是没有**多级引用**；
8. 访问实体方式不同，**指针需要显式解引用，引用编译器自己处理**；
9. 引用比指针使用起来相对更**安全**；

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201134120358.png" style="zoom:80%;" />

&emsp;&emsp;f1函数的上面两种用法都会出错，然而编译器不会给我们报错，但是传引用的话，这两种用法通过都通过不了。显然指针更容易出错。

&emsp;&emsp;显然C++的引用是不能实现链表的，因为引用了一个实体后，无法让它去引用其他实体，也就不存在增删查改这些东西，但是Java的引用对这一特性有所修改，所以Java的引用可以实现链表。

## 8 引用的底层实现

&emsp;&emsp;引用的底层实现是指针，利用VS下的反汇编功能可以看清楚这一点。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201153022432.png)

&emsp;&emsp;lea的意思是取地址，mov的意识是移动，指针的实现：取a的地址放到eax里头，然后把eax的值放到变量p中；引用的实现：取b的地址放到eax寄存器中，然后把eax寄存器中的值放到一个变量c中。

**语法层**：指针和引用是完全不同的概念，指针是开空间，存储变量地址；**引用不开空间**，仅仅是对变量取别名。底层汇编实现时，变量和指针是一样的。

&emsp;&emsp;从一点就能看出引用和指针的语法层是完全不同而且会识别的，sizeof(引用变量)等于对象大小，sizeof(地址变量)等于地址大小(4/8个字节)。

```cpp
#include <iostream>
using namespace std;
int main()
{
	char a = 2;
	char* p = &a;
	char& b = a;
	cout << sizeof(p) << sizeof(b) << endl;
}
41
```



# 七、内联函数

## 1 动机

&emsp;&emsp;调用函数需要建立栈帧，栈帧中需要保存一些一些寄存器，结束后又要销毁栈帧恢复寄存器，**这些都是有消耗的，对于频繁调用的小函数，如果我们不希望他去建立栈帧以造成消耗，能否优化一下呢**？

&emsp;&emsp;C语言对此的方法是提供了宏函数，宏是一种**替换**，就没有建立栈帧的消耗了。

```cpp
int add(int a, int b)
{
	return a + b;
}

#define add(x,y) ((x) + (y))
```

&emsp;&emsp;C++提供了一种新的语法可以达到同样的效果——**内联函数**,**编译器会在声明为inline函数的地方考虑选择直接展开代码，而不是建立栈帧**。

## 2 VS下通过反汇编功能的实验

&emsp;&emsp;VS的默认设置中，debug版本不会使用inline功能，release版本虽然会使用inline功能，但是它有更多其他的优化，可能看不清楚原本的代码的汇编代码了。

&emsp;&emsp;修改一下设置：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201155849988.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201155916509.png)

&emsp;&emsp;无inline关键字的情况:

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201161208579.png)

&emsp;&emsp;有inline关键字的情况：可以从反汇编看出这里没有去call Add，而是直接在这里展开了函数的功能。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/image-20211201155957501.png)

&emsp;&emsp;g++的汇编代码并不好读，并且我试了一下，g++编译器有自己的想法。。。我不知道怎么强制告诉他必须要把我声明为inline的函数直接在调用地方展开。

&emsp;&emsp;有了内联函数，小函数的替换就不需要用C的函数宏来提升效率，并且其实C语言的函数宏非常容易出错。

&emsp;&emsp;但是函数宏还是有很多优势，比如他可以支持泛型，如果要让内联函数支持泛型需要用模板，又复杂了= =。

## 3 总结

inline函数的特性：

1. inline是一种以**空间换时间**的做法，省去调用函数额外开销。所以**代码很长或者有循环/递归的函数不适宜使用作为内联函数**。
2. inline对于编译器而言只是一个建议，编译器会自动优化，如果定义为inline的函数体内有循环/递归等等，编译器优化时会忽略掉内联。
3. inline**不建议声明和定义分离**，分离会导致链接错误。因为inline函数被展开，不是使用的call，就没有函数地址了，链接就会找不到。

```cpp
//"f.h"
#include <iostream>
using namespace std;
inline void f();
//"f.cpp"
#include "f.h"
void f()
{
    cout << "haha" << endl;
}
//"test.cpp"
#include "f.h"
int main()
{
    f();
}
```

&emsp;&emsp;在f.cpp文件中，由于引了f.h，f函数被声明为inline函数，**编译后的f.o符号表中没有f函数的地址**，当test.cpp中的main函数调用f()的时候，它拿着函数名字找就找不到了，因为f.o的符号表中没有f函数的地址，所以就报错了。

&emsp;&emsp;结论：代码长度短（大概10行以内）的、频繁调用的函数适合定义成内联函数。

# 八、auto关键字(C++11)

## 1 简介

&emsp;&emsp;在早期C/C++中auto的含义是：使用auto修饰的变量，是具有自动存储器的局部变量，离开局部的栈帧，变量就销毁，这没有意义啊，默认不加auto的变量不就是这样嘛。

&emsp;&emsp;C++11中，标准委员会赋予了auto全新的含义即：auto不再是一个存储类型指示符，而是作为一个新的类型 指示符来指示编译器，auto声明的变量必须由编译器在编译时期推导而得，即所谓的**自动推导类型**。

&emsp;&emsp;注意auto会把常量的常量性去掉。typeid(对象).name()可以知道这个类型：

```cpp
const int a = 0;
auto c = a;
auto d = 'A';
auto e = 10.11;
cout << typeid(c).name() << typeid(d).name() << typeid(e).name();
```

auto的实际价值：

```cpp
std::map<std::string, std::string> dirc = {{"Bob", "刘"}, {"Tom", "汤姆"}};
std::map<std::string, std:;string>::iterator it = dirc.begin();
//好长啊 这里可以用auto根据返回类型来自动推断
auto it = dirc.begin();
```

## 2 使用规则

1 **auto与指针和引用的结合使用**

推导指针类型时，auto和auto*都可以正确推导出，如果要声明这个变量是引用变量，则需要使用auto&.

```cpp
int main()
{
	int x = 10;
	auto a = &x;
	auto* b = &x;
	auto& c = x;//c是引用类型
	int& d = x;
	auto m = d;//m是普通的int 可以通过下面的修改m但是d的值不变证明
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;
	m = 20;
	cout << d << endl;
}
```

2 **auto会把常量的常量性去掉，但const auto的变量具有常性**

3 **auto不能做参数 auto不能识别数组**

4 **在同一行定义多个变量**

&emsp;&emsp;当在同一行声明多个变量时，这些变量必须是相同的类型，否则编译器将会报错，因为编译器实际只对 第一个类型进行推导，然后用推导出来的类型定义其他变量。

```cpp
void TestAuto()
{
 	auto a = 1, b = 2; 
 	auto c = 3, d = 4.0; // 该行代码会编译失败，因为c和d的初始化表达式类型不同
}
```

# 九、基于范围的for循环(C++11)

## 1 使用规则

```cpp
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    //传统的遍历数组的方法
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        cout << arr[i] << " ";
    }
    //C++范围for
    for (auto e : arr)
    {
        cout << e << endl;
    }
    //自动依次取数组array中的元素赋给e 并且自动检查是否到结尾
    //当然 自己写类型也行
    for (int x : arr)
    {
        cout << x << endl;
    }
    //如果想修改数组中的值 需要用auto& 不然e只是被复制的局部变量
    for (auto& e : arr)
    {
        e *= 2;
    }
}
```

经试验，数组指针的解引用也可以用范围for循环

```cpp
void func(int(*arr)[5])
{
	for (auto& e : *arr)
	{
		e = 2;
	}
}
int main()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	func(&arr);
	for (auto e : arr)
	{
		cout << e << " ";
	}
}
```

## 2 使用条件

1. **for循环迭代的范围必须是确定的** 对于**数组**而言，就是数组中第一个元素和最后一个元素的范围；对于类而言，**应该提供begin和end的 方法**，begin和end就是for循环迭代的范围。

   ```cpp
   void TestFor(int array[])
   {
    for(auto& e : array)
    cout<< e <<endl;
   }//会报错 array退化了
   ```


2. 迭代的对象要实现++和==的操作。

# 十、指针空值nullptr

&emsp;&emsp;NULL本质是用宏定义的：

```cpp
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
```

&emsp;&emsp;但是在极端的函数重载情况下，可能会有问题，如下代码

```cpp
void f(int* p)
{
    cout << "f(int*)" << endl;
}
void f(int x)
{
    cout << "f(int)" << endl;
}
int main()
{
    f(NULL);//因为NULL的定义 会匹配到f(int) 但是我想让它去的是int*啊
    f(0);
    f((int*)NULL);//要正确匹配 必须强转一下
    f(nullptr);
}
```

所以C++11引入了nullptr关键字

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220114161751.png)

注意：

- 在C++11中，nullptr是作为关键字被引入的，不需要引头文件
- 在C++11中，sizeof(nullptr)和sizeof((void)*0)所占字节数相等
- 为了规避极端情况，提高代码健壮性，空指针建议使用nullptr
