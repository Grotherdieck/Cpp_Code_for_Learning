# 一、继承的概念

## 1 初识继承

&emsp;&emsp;继承是一种类设计上的代码复用。

&emsp;&emsp;继承(``inheritance``)机制是面向对象程序设计使代码可以复用的最重要的手段，它允许程序员在**保持原有类特性的基础上**进行扩展，**增加功能**，这样产生新的类，称派生类。继承呈现了面向对象程序设计的层次结构， 体现了由简单到复杂的认知过程。以前我们接触的复用都是函数复用，继承是类设计层次的复用。

&emsp;&emsp;比如我们的学校管理系统，不同的人有着不同的特有信息，但它们共有一些信息，可以把共有的信息设计为基类，然后继承这个基类增加特有的信息构成特别的类型：老师、学生、食堂阿姨。

&emsp;&emsp;如果不使用继承体系，每个角色都单独设计一个类，公共信息就会被重复设计，产生冗余。

&emsp;&emsp;一个简单的``public``继承体系：

```cpp
class Person
{
public:
	void print()
	{
		cout << "name:" << _name << ' ' << "age:" << _age << endl;
	}
protected:
	string _name = "路由器";
	int _age = 20;
};
// 继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。这里体现出了Student和
// Teacher复用了Person的成员。下面我们使用监视窗口查看Student和Teacher对象，可以看到变量的复用。
// 调用Print可以看到成员函数的复用。
class Student : public Person
{
protected:
	int _stuid; // 学号
};
class Teacher : public Person
{
protected:
	int _jobid; // 工号
};
int main()
{
	Student s;
	Teacher t;
	s.Print();
 	t.Print();
	return 0;
}
```

&emsp;&emsp;继承可以继承父类的全部成员，不仅仅是成员变量，成员函数也一并继承。

## 2 继承的定义

&emsp;&emsp;继承的语法含义分别如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329222220.png" style="zoom:80%;" />

## 3 继承方式和访问权限修饰符

&emsp;&emsp;C++的继承方式和它的访问权限修饰符的个数一样，有三种：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329223305.png" style="zoom:80%;" />

&emsp;&emsp;继承的方式的设计是考虑到父类的成员有三种：``publilc``、``private``、``protected``，C++的设计者考虑了这不同的三种成员在子类中的权限变化，分别给出了``public``继承、``private``继承、``protected``继承，3 * 3得到了9种不同的继承方法，相比非常复杂。

&emsp;&emsp;通常C++书籍中都会给这么一个表，如果只看表非常的难记忆难理解。

| 类成员/继承方式     | public继承            | protected继承         | private继承         |
| ------------------- | --------------------- | --------------------- | ------------------- |
| 基类的public成员    | 派生类的public成员    | 派生类的protected成员 | 派生类的private成员 |
| 基类的protected成员 | 派生类的protected成员 | 派生类的protected成员 | 派生类的private成员 |
| 基类的private成员   | 派生类中不可见        | 派生类中不可见        | 派生类中不可见      |

&emsp;&emsp;不过我们可以总结出以下规律：

- 基类的``private``成员无论是哪种继承方式，都会派生类中**不可见**，不可见的含义就是它虽然被继承了，但是在派生类内和类外都不能直接访问那个成员，不过可以通过基类的继承而来的成员函数来访问它。**所以如果父类有一个成员，不想给子类用**，就可以定义成``private``成员。
- 基类的其他成员，这个成员在子类的访问权限是继承方式和基类的访问权限中的较小者，**Min(成员在基类的访问限定符，继承方式)**，权限的大小关系是：``public > protected > private``。
- ``protected``成员和``private``成员在基类中没有区别，但是在子类中，基类的``private``成员一定是不可见的，基类的``protected``成员一定是可见的，这就是``protected``和``private``的区别，可以说，``private``成员无法被“继承”。
- C++还支持缺省方式的继承，使用关键字``class``时默认的继承方式是``private``，使用``struct``时默认的继承方式是``public``，不过**最好显示的写出继承方式**。

&emsp;&emsp;我们在实践中，通常使用的都是``public``继承，很少使用``private``和``protected``继承，我们也不提倡使用``protetced/private``继承，因为``protetced/private``继承下来的成员都只能在派生类的类里面使用，实际中扩展维护性不强。

&emsp;&emsp;所以**实践中最常用的继承方式**就是父类成员都是``public``和``protected``，子类的继承方式是**public继承**。

# 二、 基类和派生类对象的赋值转换（切割）

&emsp;&emsp;C++中有类型转换的概念，仿照类型转换，如果我们考虑父类对象赋值给子类对象，子类对象赋值给父类对象，会发生什么呢？

&emsp;&emsp;这被称为父类=子类的赋值兼容，或被称为切割、切片，只有共有继承支持这个操作，它不是类型转换，它是语法支持的一种天然行为。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329224221.png" style="zoom:80%;" />

&emsp;&emsp;我们不仅仅可以用对象，还可以用指针和引用：

&emsp;&emsp;让父类的指针只能看到父类自己的成员，子类的成员看不到。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329224325.png" style="zoom:80%;" />

&emsp;&emsp;引用的底层是指针，道理也是类似。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329224406.png" style="zoom:80%;" />

&emsp;&emsp;它为什么不是类型转换呢？如果是类型转换的过程中会产生临时变量，而我们的切割并不会产生临时变量，这从我们的引用不需要用临时对象的``const``引用看出。

&emsp;&emsp;为啥只有共有继承支持这个操作呢？如果是其他方式的继承，那么子类的成员在继承后权限关系会发生了变化，而在你父类指针和父类引用的视角下，我这些成员又变成了你父类成员下权限关系，权限关系变了，这肯定不合理啊。

&emsp;&emsp;子类给父类赋值的操作（切割）是合法的，但是父类对象给子类对象的赋值是非法的，因为子类可能有父类没有的成员，不可能凭空增加，哪怕强制类型转换也会报错。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329224507.png" style="zoom:80%;" />

&emsp;&emsp;但是``bug``的事情出现了，父类指针或引用可以赋值给子类的指针或引用，不过要强制类型转换。

&emsp;&emsp;但是这时非常危险，你如果用强转后的指针访问子类成员，就可能会越界访问，如果要安全的转化，需要在后续C++的类型转化中学习。

&emsp;&emsp;一点小细节，父类的私有成员，被子类不可见的拿到以后，在切割的时候还是会被赋值。

&emsp;&emsp;切片是很重要的，C++中多态的实现正是依赖于切片机制。

# 三、继承中的作用域

&emsp;&emsp;在继承体系中，父类和子类都有各自的作用域，回忆之前学习的就近原则，当局部域和全局域有同名的成员时，优先访问局部域中的成员，在继承中，这一点是类似的。

## 1 隐藏

&emsp;&emsp;假如子类中有和父类同名的成员，那么当我们访问子类的该成员时，根据就近原则，我们会访问子类的那个成员，如果我们想访问父类的那个成员，需要指定是父类的作用域。

&emsp;&emsp;子类和父类出现同名成员，这一现象被称为隐藏（隐藏了父类的成员）或重定义。

```cpp
class fathernum
{
public:
	int _num = 1;
};

class sonnum : public fathernum
{
public:
	int _num = 999;
};

int main()
{
	sonnum s;
	cout << s._num << endl;
	cout << s.fathernum::_num << endl;
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220331191120.png" style="zoom:80%;" />

有关选择题：

```cpp
class A
{
public:
    void fun()
    {
        cout << "func()" << endl;
    }
};
class B : public A
{
public:
 	void fun(int i)
 	{
		A::fun();
		cout << "func(int i)->" <<i<<endl;
    }
};
void Test()
{
    B b;
    b.fun(10);// 构成隐藏
    b.fun();// 报错
};

```

1. A和B的``func``函数构成函数重载
2. 编译报错
3. 运行报错
4. A和B的``func``构成隐藏

&emsp;&emsp;A的``fun``和B的``fun(int)``都不在一个作用域中，何谈函数重载，这种情况下构成函数隐藏，不论函数的参数是否相同，只要函数名相同，就构成隐藏。

&emsp;&emsp;``b.fun()``想调用A作用域的``fun()``的函数，被隐藏了，无法被调用，如果想调用得指定作用域，想调用得``b.A::fun()``。

&emsp;&emsp;继承体系中不建议定义同名成员，不过语法上没有限制死，还是不建议使用。

# 四、派生类的默认成员函数

## 1 不显示的写

&emsp;&emsp;我们知道，如果我们不写一些成员函数，编译器会默认生成6个成员函数，那么如果我们不给子类写，它的4个默认成员函数（构造、析构、拷贝构造、赋值）生成了会干什么事情呢？如果我们要显示的写要做些什么事情比较好呢？

&emsp;&emsp;先什么都不写，看一看：

```cpp
class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;

		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	string _name; // 姓名
};

// 不写：
class Student : public Person
{
public:
protected:
	int _num; //学号
};

int main()
{
	Student s;
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401120811.png" style="zoom:80%;" />

&emsp;&emsp;我们调用了父类的构造函数和析构函数。

**构造函数和析构函数**

&emsp;&emsp;如果我们不写，默认生成的构造函数和析构会干两个事情，分两部分：

- 对从父类继承下来的，构造函数调用父类的构造函数，初始化从父类继承来的部分，析构函数调用父类的析构函数处理。
- 对自己的（内置类型和自定义类型），内置类型不处理，自定义类型调用它的对应的构造函数和析构函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401121438.png" style="zoom:80%;" />

**拷贝构造和赋值**

&emsp;&emsp;如果我们不写，

- 对于从父类继承下来的部分，调用父类的拷贝构造和赋值；
- 对于自己的成员，它普通类默认生成的这俩函数一样，对内置类型完成值拷贝，对自定义类型调用其拷贝构造和赋值运算符重载。

```cpp
int main()
{
	Student s;
	Student s1(s);
	Student s2;
	s2 = s;
 	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401122121.png" style="zoom:80%;" />

&emsp;&emsp;派生类的默认成员函数的原则：继承下来的部分调用父类的处理，自己的按照普通类成员处理。

## 2 自己写

&emsp;&emsp;什么情况下必须自己写这些默认成员函数呢，自己应该怎么写这些默认成员函数呢？

&emsp;&emsp;如果**父类的部分没有默认构造函数**，那么你在无参构造子类对象时，就会报错，需要我们显示写默认构造。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401122757.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401122823.png" style="zoom:80%;" />

&emsp;&emsp;如果**子类自己的成员有堆上的资源需要释放**，就需要自己写析构。

&emsp;&emsp;如果**子类自己的成员有浅拷贝问题**，则需要自己实现拷贝构造函数和赋值，实现深拷贝。

&emsp;&emsp;那么怎么解决呢？

&emsp;&emsp;**父类的成员要显示调用父类的默认成员函数处理**，自己的成员按普通类处理。

**构造函数**：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401124427.png" style="zoom:80%;" />

**拷贝构造**：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401124812.png" style="zoom:80%;" />

&emsp;&emsp;这里利用了切片，父类的拷贝构造参数是引用，我们传一个子类对象过去，它就会变成父类那部分的引用，也就是利用切片机制。

**赋值**：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401125600.png" style="zoom:80%;" />

&emsp;&emsp;这里记得要限制类域，由于隐藏的机制，如果不指定父类的类域，它会反复调用子类的赋值运算符重载，就寄了。

**析构**：

&emsp;&emsp;直接写不能调用：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130014.png" style="zoom:80%;" />

&emsp;&emsp;指定类域才能调用：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130046.png" style="zoom:80%;" />

&emsp;&emsp;为什么呢？因为析构函数的名字会被编译器同一处理成：``destructor``，所以子类的析构函数和父类的析构函数就构成了隐藏，指定类域才能调用。

&emsp;&emsp;析构函数为什么会被同一处理成这个名字呢，是为了配合**多态**的机制。

&emsp;&emsp;这里还有一个坑：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130350.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130418.png" style="zoom:80%;" />

&emsp;&emsp;这里为什么会调用两次析构函数呢？如果父类中有资源等待释放，调两次析构函数就会崩溃了。

&emsp;&emsp;这是因为**父类部分的析构函数不需要我们显示调用**，子类析构函数结束时，会自动调用父类的析构函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130702.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401130727.png" style="zoom:80%;" />

&emsp;&emsp;子类对象中，子类自己的成员和父类成员构造和析构的顺序如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401131254.png" style="zoom:80%;" />

&emsp;&emsp;这是因为子类对象也是像一个压栈顺序构造，出栈顺序析构的，所以为了避免顺序混淆，我们的子类的析构函数出了作用域后会自动调用父类部分的析构函数，不需要显示调用。

&emsp;&emsp;所以**自己实现子类析构函数时，不需要自己显示调用父类的析构函数**。

&emsp;&emsp;总结：子类自己的成员就按普通类的方式来处理，继承来的成员调用父类的对应默认成员函数处理（析构函数除外）。

# 五、友元关系与继承

&emsp;&emsp;**友元关系不能继承**。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401134440.png" style="zoom:80%;" />

&emsp;&emsp;但是子类中的父类部分仍然可以通过父类的友元访问：

```cpp
class Student;
class Person
{
public:
	Person(const char* str): _name(str)
	{}
	
protected:
	friend void display(const Person& p, const Student& s);
	string _name;
};



class Student : public Person
{
public:
	Student(const char* str = "haha", int num = 1)
		: Person(str), _num(num)
	{}
protected:
	int _num;
};

void display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	cout << s._name << endl;
}

int main()
{
	Person p("hahaha");
	Student s("sjfkajkf", 20);
	display(p, s);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401134616.png" style="zoom:80%;" />

# 六、静态成员和继承

&emsp;&emsp;如果基类定义了一个静态成员，那么整个继承体系都只有这一份静态成员。

&emsp;&emsp;由于这个特性，可以用来统计基类及其派生类一共创建了多少个对象：

```cpp
class Person
{
public :
	Person () {++ _count ;}
protected :
	string _name ; // 姓名
public :
	static int _count; // 统计人的个数。
};
int Person :: _count = 0;
class Student : public Person
{
protected :
    int _stuNum ; // 学号
};
class Graduate : public Student
{
protected :
    string _seminarCourse ; // 研究科目
};

int main()
{
    Person p;
    Student s;
    Graduate g;
    cout << "人数" << Person::_count << endl;
    cout << &Person::_count << endl;
    cout << &Student::_count << endl;
    cout << &Graduate::_count << endl;
    return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401135756.png" style="zoom:80%;" />

# 七、菱形继承与菱形虚拟继承

## 1 单继承和多继承

&emsp;&emsp;一个类只有一个**直接父类**，我们就称为单继承。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401140256.png" style="zoom:80%;" />

&emsp;&emsp;多继承：有两个或两个以上的直接父类。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401140703.png" style="zoom:80%;" />

&emsp;&emsp;多继承设计的初衷是好的，继承多个类不是挺好的。

&emsp;&emsp;菱形继承：由多继承构成的一种继承体系，继承关系如下。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401141226.png" style="zoom:80%;" />

&emsp;&emsp;菱形继承就会造成问题：``Assistant``会有数据冗余和二义性，它其中有两份``Person``，那你要访问的时候究竟要访问学生中的``Person``还是``Teacher``中的``Person``呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401141620.png" style="zoom:80%;" />

&emsp;&emsp;为了解决菱形继承造成的问题，C++又引入了复杂的虚拟继承，又是一个大坑。

&emsp;&emsp;总之多继承就是一个设计的坑，尽量不要用，大部分语言直接删掉了多继承。

```cpp
// 菱形继承二义性的问题
class Person
{
public:
	string _name; // 姓名
};

class Student : public Person
{
public:
	int _num; //学号
};
class Teacher : public Person
{
public:
	int _id; // 职工编号
};
class Assistant : public Student, public Teacher
{
protected:
	string _majorCourse; // 主修课程
};

int main()
{
	Assistant a;
	a._id = 1;
	a._num = 2;
	a._name = "fkdfjsk";
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401142350.png" style="zoom:80%;" />

&emsp;&emsp;我们来看看``a``的结构：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401142608.png" style="zoom:80%;" />

&emsp;&emsp;二义性可以通过指定作用域解决：

```cpp
int main()
{
	Assistant a;
	a._id = 1;
	a._num = 2;
	a.Teacher::_name = "fkdfjsk";
	a.Student::_name = "hafkaf";
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401142902.png" style="zoom:80%;" />

&emsp;&emsp;我们这样勉强解决了二义性，那数据冗余呢，如果``Person``中有个大数组，本来我们只要一份，你菱形继承框框给我整两个大数组，很浪费空间。

&emsp;&emsp;数据冗余和二义性还是要解决的。

## 2 虚继承解决数据冗余和二义性

&emsp;&emsp;在腰部的继承位置增加``virtual``关键字。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401144053.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401144202.png" style="zoom:80%;" />

&emsp;&emsp;发现A类的成员在D类中只有一份了，那么它的原理是什么呢？

## 3 虚继承的原理

&emsp;&emsp;监视窗口的对象模型是优化过的，并不能直接表明对象的结构，为了看清虚拟内存中这个对象是怎么存储的，我们去看看内存。

&emsp;&emsp;给一个更简单的继承关系，我们先看看不是虚拟继承的情况：

```cpp
class A
{
public:
	int _a;
};
class B : public A
//class B : virtual public A
{
public:
	int _b;
};
class C : public A
// class C : virtual public A
{
public:
	int _c;
};
class D : public B, public C
{
public:
	int _d;
};
int main()
{
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
	return 0;
}
```

&emsp;&emsp;打开内存窗口，调整一行为4个字节，输入``&d``找到d的位置：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401145151.png" style="zoom:80%;" />

&emsp;&emsp;配合断点调试可以看出：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401145535.png" style="zoom:80%;" />

&emsp;&emsp;先继承的在前面，后继承的在后面，最后是自己的成员。

&emsp;&emsp;现在改成虚继承看看。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401150333.png" style="zoom:80%;" />

&emsp;&emsp;只存了一份，但是B和C中新增了两个我们不认识的东西，我们的电脑是大端存储，所以它看起来可能是个地址，我们再调用一个内存窗口看看它们是什么。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401150728.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401150806.png" style="zoom:80%;" />

&emsp;&emsp;``0x14``就是20，``0x0c``就是12，这个东西其实是**偏移量**，是**B和C的公共成员A的偏移量/相对距离**。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401151429.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401151532.png" style="zoom:80%;" />

&emsp;&emsp;为什么要偏移量呢，是为了给B和C能够找到公共的成员A在哪，在虚继承中，A一般叫**虚基类**，在D中，A放到一个公共的位置，有时候B需要找A，C需要找A就需要通过**虚基表中的偏移量**来计算找到到A的位置，总结如下图：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401152735.png" style="zoom: 80%;" />

&emsp;&emsp;那为什么需要找呢，考虑一下场景：

```cpp
B b = d;
C c = d;
```

&emsp;&emsp;这时候会发生切片，为了把d中B的东西切过去，需要找到d的B中a的东西，它被放在公共区域，就需要偏移量去找，如下图：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401153344.png" style="zoom:80%;" />

&emsp;&emsp;我们也可以通过VS开发者命令行的查看对象模型命令找到对象的模型：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220401154642.png" style="zoom:80%;" />

&emsp;&emsp;首先打开``Developer Command Prompt for VS 2019``，然后``:盘名``切换盘，接着``cd 项目路径``，到达对应路径，最后，输入：``cl /d1 reportSingleClassLayout类名 文件名``即可显示对应对象模型。

## 4 虚继承的使用注意事项

&emsp;&emsp;哪个类具有数据冗余和二义性的问题，那么要在它的父类产生的时候（继承的时候）进行虚继承。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220406191129.png" style="zoom:80%;" />

# 八、关于继承的总结与反思

- C++的语法很复杂，多继承及其出现的数据冗余和二义性的问题的虚继承设计的非常复杂，而大部分面向对象的语言都没有多继承语法，这就体现了C++设计上的缺陷（目前我们知道的另一个缺陷就是C++没有垃圾回收）、
- 关于**继承和组合**，组合就是直接在某个类内定义一个其他类的成员，如：

```cpp
class A;
class B
{
private:
    A _a;
    int b;
};
```

&emsp;&emsp;也就是说，组合是一种**has-a**的关系，它也可以完成复用，而继承我们再熟悉不过了：

```cpp
class A;
class B : public A;
```

&emsp;&emsp;**每个派生类对象都是一个基类对象**，也就是说，继承是一种**is-a**关系。

&emsp;&emsp;符合**is-a**关系的就适合用**继承**，符合**has-a**关系就适合用**组合**。如人和学生的关系，适合用继承；人和人的器官，人有这些器官。

&emsp;&emsp;如果既是**is-a**关系又是**has-a**关系，优先用组合而不是继承，**除非你要用到多态的性质**。

&emsp;&emsp;在这篇文章中：[优先使用类型组合，而不是类继承](https://www.cnblogs.com/nexiyi/archive/2013/06/16/3138568.html)，分析了继承是一种**白箱复用**，即对于继承来的类来说，我们是可以看到父类的完整类成员的，而组合是一种**黑箱复用**，我们组合的类对象的私有成员和保护成员都是不可见的。

&emsp;&emsp;白箱复用某种程度上破坏了类的封装，子类中的实现与它的父类有如此紧密的依赖关系，以至于父类实现中的任何变化必然会导致子类发生变化。当你需要复用子类时，实现上的依赖性就会产生一些问题。如果继承下来的实现不适合解决新的问题，则父类必须重写或被其他更适合的类替换。这种依赖关系限制了灵活性并最终限制了复用性。

&emsp;&emsp;而在软件工程的设计中，希望类之间、模块之间满足**低耦合**、**高内聚**，即每个模块中希望只有和自己有关的东西，每个模块之间的关联关系最好越弱越好，这样设计**方便维护**。

&emsp;&emsp;组合的耦合度更低（只有公有成员与另一类有关系），而继承的耦合度更高（全部成员都和父类有关系），所以组合在面向对象设计中是更好的。

&emsp;&emsp;一般``UML``图就是来表示这些类之间的耦合等各种关系的，写项目或者了解项目一般就是先去了解模块及其关系，这样项目写出来一般比较符合设计经验，更多设计经验详见《设计模式》。
