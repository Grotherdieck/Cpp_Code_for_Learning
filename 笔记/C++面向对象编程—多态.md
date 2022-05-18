# 一、多态的基本概念

&emsp;&emsp;多态多态，顾名思义，**多种形态**，具体来说就是不同类型的对象去完成同样的行为时，产生了不同状态的结果。

&emsp;&emsp;一般动态分为两种：静态的多态和动态的多态。

&emsp;&emsp;函数重载为什么是多态呢？看起来调用接口名相同的函数却可以表现出不同的行为，这就是一种多态。

&emsp;&emsp;那函数重载为什么是静态的多态呢？因为函数重载的实现是在**编译时实现的**，是在编译期通过参数类型生成不同的函数名修饰规则，找最符合函数名修饰规则的函数进行运行，编译期就确定了具体调用什么函数。

&emsp;&emsp;动态的多态：父类对象的引用或指针去调用同一个函数，如果引用或指向不同的对象，会调用不同的函数，它最大的特点是它是运行时实现的，如：

```cpp
class Person
{
public:
	virtual void buyticker()
	{
		cout << "全价买票" << endl;
	}
};

class Student : public Person
{
public:
	// 子类中满足三重(函数名、参数、返回值)的虚函数 就可以构成重写(覆盖)
	// 而不是隐藏
	// 这里虚函数和虚继承的虚没啥直接关系
	virtual void buyticker()
	{
		cout << "半价买票" << endl;
	}
};

// 这里利用父类和子类的切割机制
void Ticker(Person& p)
{
	p.buyticker();
}

int main()
{
	Person p;
	Student s;
	Ticker(p);
	Ticker(s);
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406200834.png" style="zoom:80%;" />

&emsp;&emsp;本质是不同类型的对象去做同一件事情，但是结果不同。

# 二、多态的定义与实现

## 1 多态的构成条件

- 必须通过**基类的指针或引用**去调用**虚函数**；
- 派生类必须完成了对基类的虚函数的重写，才能表现出不同的形态

&emsp;&emsp;验证第一个条件：

```cpp
void Ticker(Person p)
{
	p.buyticker();
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406204329.png" style="zoom:80%;" />

&emsp;&emsp;构成多态，传的是哪个类型的对象给引用或指针，就会调用这个类型的虚函数。

&emsp;&emsp;破坏条件不构成多态时，它调用的就是基类类型的对应函数。

## 2 虚函数

&emsp;&emsp;被``virtual``关键字修饰的非静态成员函数才能是虚函数，其他的函数都不是虚函数。

## 3 虚函数的重写

### I 条件

&emsp;&emsp;虚函数的重写（覆盖）：派生类中需要有一个和基类完全相同的虚函数（函数名相同、返回值类型相同、参数列表相同）才能够完成虚函数的重写，子类的``virtual``关键字可以不写，但是**父类要声明为虚函数的函数必须**写``virtual``关键字，这一点，其实不是很规范，建议都写上``virtual``。

&emsp;&emsp;这里若不构成虚函数，那么就只会调父类的成员，不会存在隐藏的问题，因为隐藏的问题是子类才有问题：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406205508.png" style="zoom:80%;" />

&emsp;&emsp;参数不同破坏多态验证：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406205742.png" style="zoom:80%;" />

&emsp;&emsp;构成多态失败：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406205810.png" style="zoom:80%;" />

&emsp;&emsp;返回值不同破坏多态验证：

&emsp;&emsp;VS直接编译不通过了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406210857.png" style="zoom:80%;" />

&emsp;&emsp;重写要求返回值相同的两个例外：

### II 例外条件1—协变

&emsp;&emsp;如果返回值是父子关系的指针或引用，则依然可以构成多态。

&emsp;&emsp;构成了多态：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406211656.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406211732.png" style="zoom:80%;" />

### III 例外条件2—析构函数的重写

&emsp;&emsp;父类和子类的析构函数，加上``virtual``关键字，是否构成虚函数的重写呢？

&emsp;&emsp;在继承中我们讲过，父类和子类的析构函数的函数名都会被特殊处理成``destructor``，所以它们函数名相同，参数类型相同，完全可以构成多态。

&emsp;&emsp;对于普通的父类对象和子类对象，析构函数是否构成多态，是否完成重写，都正确调用了，即先调用子类部分的析构函数，再调用父类部分的析构函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406212949.png" style="zoom:80%;" />

&emsp;&emsp;但是在我们**使用父类指针释放动态申请来的子类资源时会出问题**。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406213405.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406213538.png" style="zoom:80%;" />

&emsp;&emsp;不加``virtual``：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406213639.png" style="zoom:80%;" />

&emsp;&emsp;未能调用子类的析构函数，内存泄漏。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406213718.png" style="zoom:80%;" />

&emsp;&emsp;父类指针释放子类资源这是一个很常见的接口，常见于一些设计中，所以把继承体系中析构函数设计为虚函数是很重要的。

### IV 为什么子类可以不写virtual关键字？

&emsp;&emsp;因为子类会先继承父类的属性，就包括父类虚函数的属性，然后再完成重写。

&emsp;&emsp;这样设计的初衷就是为了防止因为子类和父类可能不是同一个人写的，如果子类的析构函数忘了写``virtual``关键字，不就出问题了？所以这样设计了，但是却带来了下面的坑。

&emsp;&emsp;子类的虚函数访问限定符和父类就算不同，而且还不写``virtual``关键字，还是能构成多态，父类指针或引用还是能调用这个函数，因为C++多态的原理是执行函数时通过虚表去找的，只要父类的那个虚函数是``public``的，它就会进虚表，子类继承时继承到虚函数的属性，一比对发现有能构成重写的虚函数，你访问限定符拦不住我，我就把它写虚表里了，然后我一定可以通过虚表完成多态。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406215316.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406215351.png" style="zoom:80%;" />

## 4 final和override—C++11

### I final

&emsp;&emsp;设计出发点是如何让一个类不能被继承呢？

&emsp;&emsp;C++98的设计方法是把这个类的构造函数设为私有，这样子类想初始化父类时，要调用父类的构造函数，而私有的父类构造函数在子类不可见，语法上强制限制了不可用，间接限制了你无法继承这个类。

&emsp;&emsp;那这样父类不也没法构造了吗？其实用单例模式挺好实现的：

```cpp
class A
{
	A(int a = 0) : _a(a)
	{}
	int _a;
public:
	static A createobj(int a = 0)
	{
		return A(a);
	}
};
```

&emsp;&emsp;这里不能设计为成员函数，因为成员函数得有对象。

&emsp;&emsp;C++98的方式：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409152129.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409152601.png" style="zoom:80%;" />

&emsp;&emsp;C++11觉得这种方式太麻烦了，C++11直接提供了一个关键字``final``就能让这个类无法被继承了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409152639.png" style="zoom:80%;" />

&emsp;&emsp;``final``加在虚函数上，可以让这个虚函数不可以被重写。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409152837.png" style="zoom:80%;" />

### II override

&emsp;&emsp;放在子类重写的虚函数的后面，检查是否完成重写，没有重写的话就会报错。

&emsp;&emsp;如果基类的虚函数忘了加``virtual``关键字，这时会构成隐藏而非覆盖：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409153015.png" style="zoom:80%;" />

&emsp;&emsp;给子类函数加上``override``关键字，立马报错。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409153114.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409153200.png" style="zoom:80%;" />

# 三、重载、覆盖（重写）、隐藏（重定义）的对比

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220412165204.png" style="zoom:80%;" />

# 四、抽象类

&emsp;&emsp;包含纯虚函数的列就是抽象类。

&emsp;&emsp;纯虚函数就是在虚函数后面加一个``=0``，纯虚函数一般只声明不实现，你实现也可以，但是**实现没有价值**。

```cpp
virtual base() = 0;
```

&emsp;&emsp;纯虚函数可以写上定义，但是你调用的时候会报错。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409155221.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409155253.png" style="zoom:80%;" />

&emsp;&emsp;这里调用纯虚函数报错的原因和虚表有关，即它和多态的原理有关。

&emsp;&emsp;抽象类的特点就是不能实例化出对象，所以其实没有调用的价值，就算调用了还因为没法实例化对象而解引用非法地址出错。

&emsp;&emsp;继承抽象类后，只有把抽象类中所有的虚函数都重写了，才能实例化出对象。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409155614.png" style="zoom:80%;" />

&emsp;&emsp;一般什么样的类设计为抽象类呢？**抽象的一种含义是在现实世界中没有对应的实物**。

&emsp;&emsp;一个类型如果一般在现实世界中没有具体的对应角色，就定义成抽象类比较好，正好它也不是实例化出对象出来了。比如学校中人就可以设计为一个抽象类，动物园中动物也可以设计为一个抽象类，人这个类型找不到实际的东西去对应。

&emsp;&emsp;抽象类强制了子类去完成虚函数的重写。

&emsp;&emsp;虚函数的继承是一种接口继承，你继承抽象类后，强制要求你必须把接口重写好，如果不想实现多态，就不要把函数定义为虚函数。

# 五、多态的原理

## 1 引入虚函数表

&emsp;&emsp;从一个简单的``sizeof``一个有虚函数的类来开始：

```cpp
class myc
{
public:
	virtual void f()
	{
		cout << "f(" << endl;
	}
private:
	int _a;
	char _c;
};

int main()
{
	cout << sizeof(myc) << endl;
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409160757.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409160906.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409161202.png" style="zoom:80%;" />

&emsp;&emsp;虚函数表指针，简称虚表指针。

&emsp;&emsp;所以前面那个调用纯虚函数的报错是因为有虚函数的类，找虚函数是通过这个指针去找的，然后需要解引用这个指针，就非法访问内存了。

## 2 虚函数表实现多态的原理

```cpp
class Person
{
public:
	virtual void buyticket()
	{
		cout << "全款买票" << endl;
	}
};

class Student : public Person
{
public:
	virtual void buyticket() override
	{
		cout << "半价买票" << endl;
	}
};

void Ticker(Person& p)
{
	p.buyticket();
}

int main()
{
	Person Bob;
	Student Jenson;
	Ticker(Bob);
	Ticker(Jenson);
}
```



<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409164222.png" style="zoom:80%;" />

&emsp;&emsp;这两个虚表指针地址不同，说明继承来的子类对象虚表和父类是不同的。

&emsp;&emsp;看看反汇编，发现虚函数的执行和普通函数的执行确实很不一样：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409164439.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409164944.png" style="zoom:80%;" />

&emsp;&emsp;但是父类对象和子类对象对应的汇编指令是相同的，子类对象被父类对象的指针指向或引用后，基类指针的视角就是这个基类成员和这个虚函数表，然后去虚函数表中找到对应的函数，进行调用。

&emsp;&emsp;下面是``Buy(Jenson)``的执行过程，发现和``Buy(Bob)``是一样的，唯一的不同是进入了不同的虚函数表后找到的地址不同而已，是你传给我的对象不同，才会去不同的虚表找到不同的虚函数，在编译器编译这个函数时，这两段指令是没有任何区别的，这是运行的时候去虚函数表中找到的虚函数实现了多态，所以虚函数的机制才被称为运行时多态。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409170212.png" style="zoom:80%;" />

&emsp;&emsp;那么为什么对象就不能完成多态呢？子类对象也可以给父类对象切片啊？

&emsp;&emsp;指针切片，我指向的是子类对象的父类部分，所以它指向的虚表指针就是子类的虚表；对象切片，会使用子类对象的父类部分调用拷贝构造函数，**它不会把子类的虚函数表指针复制过去**，不然父类对象持有子类对象的虚函数表，那还得了。。。比如拷贝过来的父类对象持有子类对象的虚表，生命周期结束时，析构函数就会调用子类对象的析构函数，这不就大错特错了吗。

&emsp;&emsp;另外，同类对象的虚表指针是相同的：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409165726.png" style="zoom:80%;" />

&emsp;&emsp;普通函数和虚函数的存储位置是一样的，都在公共代码段，只是虚函数还要把自己的地址存一份进虚表。

&emsp;&emsp;当是对象而非引用的时候，它直接就不会去虚表中找，因为就算能去虚表找，因为拷贝构造无法拷子类的虚表，找到的也是父类的虚表中对应函数，所以如果是对象本身来调用函数，我直接不会去虚表里头找，会直接在类域中找，只有在父类对象的指针或引用时，才会去虚函数表找，也才能安全的去虚表里头找。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409171004.png" style="zoom:80%;" />

&emsp;&emsp;多态调用在编译时是没法确定你调用的是那个函数的，因为单从一段函数上来说，它是不知道传给自己的对象是什么样的，只能知道自己要去虚表找而已。

```cpp
void Ticker(Person p)
{
	p.buyticket();
}
```

&emsp;&emsp;所以为啥子类的虚函数设为私有还是能实现多态呢？

&emsp;&emsp;首先``public``等这些访问限定符只是编译器的检查，但是我虚函数的调用是去虚表中找的，访问限定符管不到我，而且编译的时候不知道是谁来调用的这个函数，我只看到父类的这个函数是公有的，所以我检查不出来。

&emsp;&emsp;所以C++的``public``等修饰符也不是完全安全的，我利用虚函数机制，子类的私有成员虚函数我也能调用的到。

&emsp;&emsp;所以重写这个名词实际上是一个原理层面的名词，我子类把虚表拷贝过来后，子类重写的虚函数会在虚表中改变对应函数的地址。

&emsp;&emsp;VS下虚表存的地址是Jump指令的地址，它多做了一些手脚，这些操作有时候是必要的，比如为了找到多继承的一个基类的位置而修改``this``指针的值之类的。

```shell
g++ -fdump-class-hierarchy xxx.cpp//查看xxx.cpp的虚表
新版的g++参数为-fdump-lang-class
```

## 3 虚函数表存储在哪

&emsp;&emsp;一个小问题：虚函数表本身存在哪里呢？其实考虑到虚表严格来说不会被再修改了，可以猜到它放在常量区，我们通过一个对比的方法得到：

```cpp
int main()
{
	int a = 1;
	printf("栈区%p\n", &a);
	int* p = new int;
	printf("堆区%p\n", p);
	const char* str = "hellow";
	printf("常量区%p\n", str);
	printf("代码段%p\n", Ticker);
	Student s;
	printf("虚表%p\n", *(int*)(&s));
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409174818.png" style="zoom:80%;" />

&emsp;&emsp;离常量区最近。

&emsp;&emsp;Linux下g++编译器的验证：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409201553.png" style="zoom:80%;" />

## 4 单继承时的虚函数表

```cpp
class father
{
public:
	virtual void fun1()
	{
		cout << "father::fun1()" << endl;
	}
	virtual void fun2()
	{
		cout << "father::fun2()" << endl;
	}
};

class child : public father
{
public:
	virtual void fun1()
	{
		cout << "child::fun1()" << endl;
	}
	virtual void fun3()
	{
		cout << "child::fun3()" << endl;
	}
	virtual void fun4()
	{
		cout << "child::fun4()" << endl;
	}
};

int main()
{
	father f;
	child c;
	return 0;
}
```

&emsp;&emsp;发现虚函数表中没有找到``fun3``和``fun4``的虚函数表，咋回事呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409202234.png" style="zoom:80%;" />

&emsp;&emsp;它被隐藏了，我们通过内存来看。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409202611.png" style="zoom:80%;" />

&emsp;&emsp;这俩就是重写的``func1``和未重写的``fun2``，大胆猜测后面两个就是``fun3``和``fun4``的地址。



## 5 多继承的虚函数表

&emsp;&emsp;多继承后，如果不是虚继承，我们会有两张虚表，但是它的全部虚函数会全部放到第一个继承的类的虚表中。

```cpp
class base1
{
public:
	virtual void fun1()
	{
		cout << "base1::fun1()" << endl;
	}
	virtual void fun2()
	{
		cout << "base1::fun2()" << endl;
	}
	int b1;
};

class base2
{
public:
	virtual void fun1()
	{
		cout << "base2::fun1()" << endl;
	}
	virtual void fun2()
	{
		cout << "base2::fun2()" << endl;
	}
	int b2;
};

class child : public base1, public base2
{
public:
	virtual void fun1()
	{
		cout << "child::fun1()" << endl;
	}
	virtual void fun3()
	{
		cout << "child::fun3()" << endl;
	}
	int d;
};

int main()
{
	child d;
	base1* p1 = &d;
	base2* p2 = &d;
	p1->fun1();
	p2->fun2();
}class base1
{
public:
	virtual void fun1()
	{
		cout << "base1::fun1()" << endl;
	}
	virtual void fun2()
	{
		cout << "base1::fun2()" << endl;
	}
};

class base2
{
public:
	virtual void fun3()
	{
		cout << "base2::fun3()" << endl;
	}
	virtual void fun4()
	{
		cout << "base2::fun4()" << endl;
	}
};

class child : public base1, public base2
{
public:
	virtual void fun1()
	{
		cout << "child::fun1()" << endl;
	}
	virtual void fun3()
	{
		cout << "child::fun3()" << endl;
	}
};

int main()
{
	child d;
	base1* p1 = &d;
	base2* p2 = &d;
	p1->fun1();
	p2->fun3();
}
```

第一个问题：现在d中有多少个虚表呢？

&emsp;&emsp;想一想多继承的概念，大概有两个虚表，运行看一看。

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220409212432490.png" alt="image-20220409212432490" style="zoom:80%;" />

&emsp;&emsp;发现有重写的``fun1``和未重写的``fun2``，我们通过内存看看：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409212404.png" style="zoom:80%;" />

&emsp;&emsp;第一个虚表有三个虚函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409212455.png" style="zoom:80%;" />

&emsp;&emsp;第二个虚表只有两个函数。

&emsp;&emsp;通过反汇编看看``p1->fun1()``是怎么操作的：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409212757.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409212828.png" style="zoom:80%;" />

&emsp;&emsp;然后跳到了这个函数里：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409212857.png" style="zoom:80%;" />

&emsp;&emsp;我们通过反汇编来看看``p2->fun1()``是怎么操作的。

&emsp;&emsp;先跳到这个指令：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409211015.png" style="zoom:80%;" />

&emsp;&emsp;然后进入了一个让``ecx-8``的操作，这一步修改的是``this``：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409211142.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409211452.png" style="zoom:80%;" />

&emsp;&emsp;跳了两下，到了``child::fun1``:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409211246.png" style="zoom:80%;" />

&emsp;&emsp;多继承中，子类重写了``base1``和``base2``的虚函数``fun1``，虽然虚表中的``fun1``的地址不一样，这是因为``p2(base2*)``需要获得一个正确的视角，所以需要修正传给``this``指针的值。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409213708.png" style="zoom:80%;" />

## 6 打印虚表验证虚函数机制

&emsp;&emsp;虚表指针是在构造函数的初始化列表的时候初始化的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411190715.png" style="zoom:80%;" />

&emsp;&emsp;我们想要打印虚表，首先要把虚表取到，那么怎么取呢？

&emsp;&emsp;虚函数表，本质上来说它是一个函数指针数组，我们先对函数指针``typedef``一下，然后找到虚函数表指针，强转为4字节指针(32位下指针为4字节)然后解引用得到虚函数表，然后强转为``VF_Ptr*``传进打印虚表的函数。

```cpp
// void fun(void)的函数指针 void(*)()
typedef void(*VF_Ptr)();

// 打印虚函数表的函数 参数为虚函数表的指针
void PrintVF_table(VF_Ptr* _table)
{
    // 利用VS下虚表的结尾为0x00000000
	for (int i = 0; _table[i] != nullptr; ++i)
	{
		printf("虚函数表中第[%d]个元素->%p\n", i, _table[i]);
		VF_Ptr f = _table[i];
		f();
	}
}

int main()
{
	father f;
	child s;
    // 先取地址 然后强转为int*表示其为四字节指针 
    // 找到虚函数表指针 解引用 然后强转为VF_Ptr*
	PrintVF_table((VF_Ptr*)*((int*)(&f)));
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411192245.png" style="zoom:80%;" />

64位下怎么打印虚表呢？

&emsp;&emsp;用double会导致精度丢失，编译器不让我们转：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411193714.png" style="zoom:80%;" />

&emsp;&emsp;用``long long``或``int64``即可。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411193835.png" style="zoom:80%;" />

&emsp;&emsp;但是我们发现用``long long``，在32位下仍然可以正常运行。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411194028.png" style="zoom:80%;" />

&emsp;&emsp;原因是``VF_Ptr``截断了``long long``的前四个字节，恰好就是对应的那块位置。

&emsp;&emsp;我们更好的方法是把``long long*``换成``void**``即可，一个二级指针解引用看起长度是一个指针的长度，随32位和64位随动。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411194354.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411194434.png" style="zoom:80%;" />

&emsp;&emsp;这是一般的跨平台的得到看指针长度的方法。

&emsp;&emsp;如果坚持要用``int*``和``long long*``，可以利用windows预定义的``_WIN32``宏和``_WIN64``宏。

&emsp;&emsp;64位中，为了兼容，``_WIN32``和``_WIN64``都有定义；32位中，只定义了``_WIN32``，所以我们利用条件编译：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411195024.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411195257.png" style="zoom:80%;" />

&emsp;&emsp;再打印一下单继承的子类的虚函数表(v1和v3重写了，v2没有重写)：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411195732.png" style="zoom:80%;" />

&emsp;&emsp;我们来看看多继承的情况，看看其子类的虚表，先看看其对象模型：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411200120.png)

&emsp;&emsp;先继承的放在一起，这里就有问题，我们的虚函数放在哪里呢？是``base1``的虚表，还是``base2``的虚表呢？

&emsp;&emsp;我们之前用内存看了，C++选择了第一个父类的虚表来搞，我们先打印一下老大``base1``的虚表：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411200533.png" style="zoom:80%;" />

&emsp;&emsp;我们再试图用偏移来看看``base2``的虚表，用强转搞好步长就行：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411200859.png" style="zoom:80%;" />

&emsp;&emsp;或者我们可以利用``base2``指针切片时，指针会偏移。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220411201202.png" style="zoom:80%;" />

## 7 菱形继承与虚函数机制

&emsp;&emsp;菱形继承过于复杂，当其余虚函数结合后，会更加复杂，我们一般不建议使用。

&emsp;&emsp;如果要使用时，建议参考以下文章并且多问问百度谷歌。

[C++虚函数表解析](https://coolshell.cn/articles/12165.html)

[C++对象的内存分布](https://coolshell.cn/articles/12176.html)







