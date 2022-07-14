# 一、C语言的类型转换

&emsp;&emsp;C++要兼容C的基础语法，不管是C的精华语法还是不太好用的语法都会拿过来使用，对于C语言的不足，C++新增了一些库和一些细节语法去补充C语言的不足，比如引用，比如函数重载，比如模板，C++还增加了标准库去让我们使用更加方便，C++还增加了很多面向对象的语法，如类和对象、继承和多态、异常等。

&emsp;&emsp;C++的类型转化是属于去解决C语言的不足而引入的，我们先来看看C语言的类型转换。

&emsp;&emsp;C++是一种强类型的语言，当不同类型的对象之间相互操作时，需要发生类型转化，只有能进行类型转化才能OK，否则会出问题，弱类型语言则不必。

&emsp;&emsp;C语言也是一种强类型语言，它的类型转换就有**隐式类型转换和强制类型转换。**

&emsp;&emsp;隐式类型转换是编译器在编译期自动进行的，能转就转，不能转就会编译失败。

&emsp;&emsp;一般相近类型都能发生隐式类型转换，比如char int long long double之间就可以互相转换，因为它们都表示大小。

&emsp;&emsp;但是不是相近类型可能就无法类型转换，比如 ``int*``与 ``int``就不能隐式类型转换。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714161252.png)

&emsp;&emsp;这种如果真的要转就要我们强制类型转换：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714161430.png)

&emsp;&emsp;但是C++设计者对这种类型转换比较不满，他觉得你这都没给我说清楚是哪一种类型转换，我怎么知道你是要怎么类型转换，因此C++给出了4种类型转换。

# 二、C++的类型转换

&emsp;&emsp;如果从语法设计的角度，应该取消隐式类型转换，但是C++要兼容以前的语法，所以不敢取消；

&emsp;&emsp;从规范类型转换方式角度，我们应当针对不同类型转换进行分类。

## 1 static_cast

&emsp;&emsp;static_cast用于非多态类型的转换（静态转换），**编译器隐式执行的任何类型转换都可用static_cast**，也就是说它只能用于相近类型的转换，但它不能用于两个不相关的类型进行转换。

&emsp;&emsp;使用时一定不要像强制类型转换那样去用，要像一个模板函数那样使用：

```cpp
int main()
{
	double d = 1.1;
	int a = static_cast<int>(d);
	// <要转去的类型>
}
```

&emsp;&emsp;那如果是那种完全不相关的类型的转换呢，可以用 ``reinterpret_cast``。

## 2 reinterpret_cast

&emsp;&emsp;reinterpret的含义有重新解释的意思，它用于完成完全不相关的类型之间的转换，往往可以完成很多很bug的事情：

```cpp
// 把void (void)类型的函数指针重命名为Func
typedef void(*Func)(void);

int sub(int a)
{
	cout << a << endl;
	return a;
}

int main()
{
	Func ptr = reinterpret_cast<Func>(sub);
	ptr();
}
```

&emsp;&emsp;可以看到把一个 ``int(*)(int)``类型的函数指针都强转成 ``void(*)(void)``的函数指针了，还是能调用，并且这个a每次不同的编译都是随机值，不得不说，很bug。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714171050.png)

## 3 const_cast

&emsp;&emsp;const修饰的意义是在语法层上不能直接修改，如果我们想去除变量的const属性，就可以用这个，之后就修改它了。它的用法如下代码（ps：本代码中存在一些bug的事情）

```cpp
int main()
{
	const int a1 = 2;
	int* p1 = (int*)&a1;
	*p1 = 3;
	cout << "a1 = " << a1 << endl;
	cout << "*p1 = " << *p1 << endl;
	const int a2 = 2;
	int* p2 = const_cast<int*>(&a2);
	*p2 = 3;
	cout << "a2 = " << a2 << endl;
	cout << "*p2 = " << *p2 << endl;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714172141.png)

&emsp;&emsp;明明我们已经修改了a2和a1啊，为啥它俩的值没变呢？

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714172355.png)

&emsp;&emsp;这是因为编译器进行了我们不想的优化，它看着a1和a2语法上是常量，因此直接在读取他们的值时直接给优化成了把a原本的值放到寄存器里头去，去读取寄存器里头的值，自然就有问题了。

&emsp;&emsp;要阻止这种优化，可以加 ``volatile``关键字：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714173538.png)

&emsp;&emsp;C++把这个单独拿出来，是为了提醒大家注意const属性被去掉后，变量可能会被修改，这和编译器的优化可能会冲突，小心提醒你这时候应该用 ``volatile``关键字。

## 4 dynamic_cast

&emsp;&emsp;它是C语言中没有的一种类型转化，它主要用于**将父类对象的指针或引用转化为子类对象的指针或引用（动态转换）。**

&emsp;&emsp;回顾继承多态那里，我们定义向上转型为子类对象的指针或引用转化为父类对象的指针或引用，这是赋值兼容的，因为一个子类对象一定是一个父类对象，属于is-a关系，不需要我们转换类型。

&emsp;&emsp;定义向下转型为将父类的指针或引用转化为子类对象的指针或引用，这个转换是不一定成功的，这里用 ``dynamic_cast``转换此时就会显得更安全一些。

PS：

* dynamic_cast**只能用于父类含有虚函数的类**。
* dynamic_cast会先检查转换是否能成功，能成功则转换，不能成功则返回0。

&emsp;&emsp;那么什么情况需要向下转换呢？如果我们有一个父类指针，它可能指向父类对象A a，也可能指向子类对象B b，那么如果我们要区分一下指向的具体是谁，并且如果是指向子类对象，则转化为子类对象，并且访问子类对象的对象：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714192837.png)

&emsp;&emsp;原因是它识别指向的父类还是子类是通过查看虚表的一些标识实现的。

&emsp;&emsp;考题：C++的四种强制类型转换是啥？分别作用是啥？

&emsp;&emsp;四种类型转换的意义：期望C++程序员，不要再用C的隐式类型转换和强制类型转换，而是全部规范使用，这样减少类型转换的坑。

&emsp;&emsp;但是实际使用中，很多人嫌麻烦，用的不规范，但是还是有些公司把这个规范写到了公司的文档规范中，强制要求大家执行，比如Google。

# 三、STL中的空间配置器简介

&emsp;&emsp;STL中的容器经常会要向堆中申请小块内存，频繁的向堆申请小块内存会有很多问题：效率问题、内存碎片。因此STL的设计者专门给STL容器设计了内存池，称为空间配置器。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714200416.png)

&emsp;&emsp;STL的空间配置器可以缓解内存碎片问题，但是没完全解决，好一点的内存池都要想办法解决这个问题，比如tc_malloc.

&emsp;&emsp;STL中把空间配置器分为一级空间配置器与二级空间配置器。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220714201307.png)

&emsp;&emsp;申请空间大于128字节就去用malloc申请内存，即一级内存配置器，小于128就去用二级内存配置器。

&emsp;&emsp;二级配置器是一个内存块的哈希表，每个结点链接着对应大小的内存块，这样归还内存时可以以O1的速度查找到这些内存块并且进行删除，如果正常申请以链表组织，那么删除时就要每次都要查找链表，效率比较低，一级内存配置器就是这样的。

&emsp;&emsp;归还内存时，小块内存直接还到哈希上面继续挂着，大块内存归还到一级配置器里。

&emsp;&emsp;具体到一个STL容器，它一般会以模板参数与typedef的方式把配置器封装起来，然后用配置器分配内存后用 ``operator new``来调用构造函数。
