&emsp;&emsp;string就是一个管理字符串的类。

&emsp;&emsp;常见参考文档：[cplusplus](http://www.cplusplus.com/reference/)[或官网](https://en.cppreference.com/w/)

# 一、初识string

&emsp;&emsp;我们用string不都是``string s("hello!");``这样吗，哪里体现的模板呢？我们来看看``cplusplus``里的介绍.

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219160002.png)

&emsp;&emsp;为什么会有``basic_string<char>``呢？难道还有别的类型的串吗？有，与编码有关。

&emsp;&emsp;编码就是一个二进制序列和符号的映射，表示英文的常见编码表最早是ascii编码表，我们普通英文字符串中存的其实就是ascii表。

&emsp;&emsp;但后来计算机都要全球化，不仅需要让二进制序列显示英文，希望二进制序列也可以映射到其他符号，后来就搞出了``unicode``,用来表示全世界文字符号的编码表，unicode中又包含utf-8、uft-16、utf-32.

&emsp;&emsp;中文通常是用两个字节映射到一个字节，一些生僻汉字是用三个或四个字节映射到的。

```cpp
int main()
{
    char s[] = "我是你爹";
    cout << sizeof(s) << endl;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219162045.png)

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219161926.png" style="zoom:67%;" />

&emsp;&emsp;vs也支持自己改存储的编码形式：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219162346.png)

&emsp;&emsp;``gbk``是国内自己做的汉字编码表。

&emsp;&emsp;一般Linux下默认支持``utf-8``，我们对编码一定要谨慎，不要乱改编码，不然编码对不上直接就是乱码= =。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219162650.png)

&emsp;&emsp;``unicode``中的一种字符映射方式对应的类型有``wchar_t``,不同编码也有不同的字符映射，所以需要实现``basic_string``以应对各种编码方式。

&emsp;&emsp;适应``unicode``搞出的不同string类：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219165428.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219165532.png)

# 二、string的常见接口

## 1 构造函数

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219170020.png)

&emsp;&emsp;第三个构造函数的含义是以从pos位置开始长度为len的子串初始化，后面的缺省值的意思是：npos是一个string类的静态成员变量，``npos = -1 赋值给 size_t len = 一个非常大的数``，然后就会有多少取多少。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219171446.png)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219170848.png)

&emsp;&emsp;第四个构造函数是以一个C类型的字符串取初始化。

&emsp;&emsp;第五个构造函数的含义是以字符串的前n个去初始化。

&emsp;&emsp;第6个构造函数的函数以是以n个字符c去初始化。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219171228.png" style="zoom:80%;" />

## 2 string类对象的容量操作

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219171528.png)

&emsp;&emsp;注意，这里size()和length()函数返回字符串的长度是不包含'\0'的。

&emsp;&emsp;这里同时有size()和length()都表示长度是因为后来的容器没有长度的概念，有个数的概念。

&emsp;&emsp;了解一些别的接口：

&emsp;&emsp;``max_size()``额，字符串的最大长度，其实和内存有关系，一般都设置成UINT_MAX,没什么卵用。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219171923.png)

&emsp;&emsp;``capacity()``当前容器容量。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219172017.png)

&emsp;&emsp;``clear()``:把容器元素清空，但是容量不变。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219172218.png)

&emsp;&emsp;``shrink_to_fit()``,把容量干到当前容器大小。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219171733.png)

## 3 string类的访问遍历操作

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219172421.png)

``operator[]``:返第i个位置的字符的引用。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219172557.png)

&emsp;&emsp;由于是引用返回，对``s[i]``操作可以修改第i个位置的字符，等价于``s.operator[](i)``，对``const string``对象则会调用后者，返回常引用，无法修改。

``at()``：功能同``operator[]``，返回第i个字符的引用，可读可写,同对``const``对象

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219173159.png)

&emsp;&emsp;与[]的区别是``operator []``是通过``assert``来断言报越界，``at()``处理的方法是抛出异常。

遍历并修改string的每个字符的方法：

- ``s[i]``
- ``s.at(i)``
- 迭代器：

```cpp
string::iteraotr s1 = s.begin();
while (it != s.end())
{
    cout << *it << ' ';
    ++it;
}
```

&emsp;&emsp;迭代器在这里可以初步认识为指向每个字符的指针，使用时要指明类域。

&emsp;&emsp;初识迭代器：

&emsp;&emsp;迭代器的目的是为了让所有的容器都有个同一的访问方法。

&emsp;&emsp;建议迭代器不要使用``i < s.end()``,虽然在``string``是好用的，但是别的容器的迭代器可能元素物理地址不连续，没有重载``<``

``const_iterator``:保护``const``容器内的值不被修改

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224194730.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224195258.png" style="zoom:80%;" />

C++11新增了``cbegin()``和``cend()``特指``const``迭代器

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224195459.png" style="zoom:80%;" />

``rbegin(),rend()``:反向迭代器

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224192432.png" style="zoom:80%;" />

同理也有``crbegin()``和``crend()``

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224195643.png" style="zoom:80%;" />

用法还是++:

```cpp
string::reverse_iterator i = s.rbegin();
// 或auto i = s.rbegin();
while (i != s.rend())
{
    cout << s[i] << ' ';
}
```

- 范围for，如果要更改内容需要加引用：``for (auto& ch : str)``

&emsp;&emsp;``front() back()``返回开头或结尾的字符。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219173547.png)

## 4 string类的容器插入操作

``push_back``：尾插一个字符。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219173702.png)

``append()``:英文含义为附加，尾插字符串，支持的格式如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219173800.png" style="zoom:80%;" />

``operator +=``:尾插字符或字符串，最方便的string插入用法。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219173857.png" style="zoom:80%;" />

在任何位置插入字符或字符串：``s.insert()``，时间复杂度是``O(n)``,尽量少用。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224212402.png" style="zoom:80%;" />

``operator +``不改变自己，涉及一次深拷贝。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224213048.png" style="zoom:80%;" />

## 5 string类的增容方式

MSVC的编译器，``string``增容方式大概是第一次两倍扩容，后续是1.5倍增容，它最早起源于hp版本。

我测试的Linux下的g++编译器，string的增容方式是每一次都扩容两倍，它起源于sgi版本。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224200527.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224200603.png" style="zoom:80%;" />

``s.reserve(n)``请求一个至少能储存``n``个字符的空间,可以减少增容，付出更少的代价，如果n小于当前容量，则请求无效，这个其实就是扩容函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224201143.png" style="zoom: 80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224201242.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224201313.png" style="zoom:80%;" />

``s.resize(n)``:把容器的大小控制成n且同时可以给新增的空间初始化，默认初始化为``'\0'``

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224201402.png" style="zoom:80%;" />

``s.resize(n)``相当于扩容加初始化，会把扩容的容量补上你给的字符，``s.reserve()``是只扩容。

``s.resize(n)``若n小于size，则会删除数据。

扩容通常常用``s.reserve()``，很少用``s.resize()``

``s.c_str()``返回那个字符串的C型指针，可能无法修改那个指针指向的值。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224204420.png" style="zoom: 80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224204609.png" style="zoom:80%;" />

用途：需要和C类型字符串交互时，就可以用``c_str()``,如``fopen``的第一个参数等.

## 6 string类的查找与子串构造

``size_t s.find(const string& str);``查找str作为子串在s串中第一次出现的位置，也可以查找字符。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224205105.png" style="zoom:80%;" />

如果查找不到，则返回无符号整形``size_t p = -1;``,-1用补码表示是全1，给``size_t``就是一个非常大的数，这个数是``string``中的静态变量：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224205606.png" style="zoom:80%;" />

```cpp
string s("test.txt");

if ((size_t p = s.find(".txt")) != s.npos)
{
    string suffix/*后缀*/ = s.substr(p, 4);
}
// 或

size_t p = s.find(".txt");
if (p != s.npos)
{
    string suffix = s.substr(p, s.size() - p);
}
```

``string substr (size_t pos = 0, size_t len = npos) const;``从pos位置开始去len长度的s的子串。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224210332.png" style="zoom:80%;" />

从右往左找：``s.rfind(str);``

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224210635.png" style="zoom:80%;" />

``URL``网络中的地址，即网址。

如果要解析网址，肯定要先找``:``,然后把一个子串取出来

```cpp
int main()
{
    string s = "http://www.cplusplus.com/reference/string/string/rfind/";
    size_t p1 = s.find(':');
    string protocol = s.substr(0, p1);
    cout << protocol << endl;
    size_t p2 = s.find('/', p1 + 3);// 从w开始找
    string domain = s.substr(p1 + 3, p2 - p1 - 3);// 左闭右开 长度为p2 - p1 - 3 不用减-1
    cout << domain << endl;
    string uri = s.substr(p2 + 1);// 直接到最后
    cout << uri << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224212043.png" style="zoom:80%;" />

字符串比较大小，string重载了各种比较符号，是按字典序比较的。

## 7 string类的删除操作

``s.erase(pos, len);``删尾的时间复杂度是``O(1)``,删头和中间的时间复杂度较高。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224212646.png" style="zoom:80%;" />

尾删还可以用``s.pop_back();``,注意是C++11支持的。



## 8 string转数字

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226092602.png" style="zoom:80%;" />

第二个指针参数是用来获得我们转完的数字是多少位的。

类似的 对long long和float类型都有对应的函数

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226092848.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226092941.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093007.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093030.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093043.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093059.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093113.png" style="zoom:80%;" />

## 9 数字转字符串

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093147.png" style="zoom:80%;" />

## 10 string比较大小

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226093437.png" style="zoom:80%;" />

只要有一个参数是string，另一个是c类型字符串或者string都可以，比较大小的结果是以字典序进行返回的。

##  

# 三、cin读入字符串的空格问题

&emsp;&emsp;正常情况下，``cin``读到一个空格就会停下来，如果想读入空格，则要么去用c语言的getchar(),或者用``cin.get()``,作用都是一个字符一个字符拿，然后拼成一个串

一行字符串的情况下：

```cpp
int main()
{
    string s;
    char ch = cin.get();
    while (ch != '\n')
    {
        s += ch;
        ch = cin.get();
    }
}
```

直接读一行：``getline(cin, str);``,它的原理就是y一个字符一个字符读取，到``'\n'``结束。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220224215135.png" style="zoom:80%;" />

# 四、string模拟实现

&emsp;&emsp;我们不考虑编码问题，因此我们不会实现一个模板类的``basic_string``,我们只实现一个类型为char类型的string。

&emsp;&emsp;为了防止我们的string与标准库的string冲突，我们也设置一个命名空间，就叫``Router``吧。

&emsp;&emsp;我们的总体思路是以C提供的``char*``的字符串来实现我们的``string``类，一些容易遇到的坑总结如下：

## 1 深浅拷贝问题

**拷贝构造函数**

&emsp;&emsp;如果我们不自定义一个拷贝构造函数，默认生成的拷贝构造函数会按字节序拷贝，那么``s2._str``和``s1._str``都指向同一跨空间，然后``delete[] s1._str;``后再``delete[] s2._str``后，会释放已经释放过的内存，就会报错了。

```cpp
namespace Router
{
	class string
	{
	public:
		// 构造 利用str的长度开空间
		string(const char* str) : _str(new char[strlen(str) + 1])
		{
			// 利用strcpy直接拷贝到_str
			strcpy(_str, str);
		}
		// 析构
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private:
		char* _str;
	};
}

int main()
{
	Router::string s1("hello world!");
	Router::string s2(s1);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226111338.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226111855.png" style="zoom:80%;" />

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226112336.png)

**赋值运算符重载**

&emsp;&emsp;思路就是先把原来的空间干掉，然后以要拷贝的串的长度开新的空间，然后利用``strcpy``拷贝数据过去，框架如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226115333.png" style="zoom:80%;" />

&emsp;&emsp;但要注意``s1 = s1;``这种情况，这种情况有可能发生，

&emsp;&emsp;``s1 = s1;``会出现可怕的问题，因为我们会先干掉``this->_str``,由于&s1和this是同一地址，原本的空间会被``delete[]``后，可能把原来空间的数据都给赋值成垃圾值了，那去哪里拷贝原来的数据呢？

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226114924.png)

```cpp
string& operator=(const string& s)
{
    // 自己赋值给自己就不要重复了 
    if (this != &s)
    {
        delete[] _str;
        _str = new char[strlen(s._str) + 1];
        strcpy(_str, s._str);
    }
    return *this;
}
```

&emsp;&emsp;但是上面的代码仍有风险：

&emsp;&emsp;``delete[]``只要地址正确，一般不会失败，风险不在它；

&emsp;&emsp;但是new申请空间失败可能抛出异常，我们先``delete[] _str;``把原来数据干掉了，然后申请空间失败抛出了异常，这时候应该去处理异常，保留``_str``中本来的数据等待后续，然而``_str``已经被我们干掉了,所以可以考虑先用一个``char* tmp``存储new来的空间，如果申请失败就去处理异常了；如果申请成功就把``_str``原本的数据干掉然后把tmp赋值给``_str``.

```cpp
string& operator=(const string& s)
{
    // 自己赋值给自己就不要重复了 
    if (this != &s)
    {
        char* tmp = new char[strlen(s._str) + 1];
        strcpy(tmp, s._str);
        delete[] _str;
        _str = tmp;
    }
    return *this;
}
```

&emsp;&emsp;引入size和容量，把上面已经实现的函数完善如下：

```cpp
string(const char* str) 
    : _size(strlen(str)), _capacity(_size)
{
    _str = new char[_capacity + 1];
    strcpy(_str, str);
}

string(const string& s) 
    : _size(s._size), _capacity(s._capacity)
{
	_str = new char[_capacity + 1];
    strcpy(_str, s._str);
}

string& operator=(const string& s)
{
    // 自己赋值给自己就不要重复了 
    if (this != &s)
    {
        char* tmp = new char[s._capacity + 1];
        strcpy(tmp, s._str);
        delete[] _str;
        _str = tmp;
        _size = s._size;
		_capacity = s._capacity;
    }
    return *this;
}

~string()
{
    delete[] _str;
    _str = nullptr;
    _size = 0;
    _capacity = 0;
}
```

&emsp;&emsp;发现还缺少默认构造函数。

**默认构造函数**

&emsp;&emsp;要么我们自己实现一个默认构造函数：

&emsp;&emsp;假如我们这样写：

```cpp
string() : _str(nullptr), _size(0), _capacity(0)
{}
```

&emsp;&emsp;这样是存在问题的，我们知道string通常会提供一个``c_str()``接口以返回c形式的字符串，c形式的字符串输出时是遇到``\0``才停止，那如果我这样

```cpp
int main()
{
	Router::string s1;
	cout << s1.c_str() << endl;
}
```

&emsp;&emsp;它就会发生一些未定义过的异常现象，引发崩溃：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226135517.png" style="zoom:80%;" />

&emsp;&emsp;因为根据C型字符串的格式，空字符串也应该有一个``'\0'``,所以我们标准写法如下：

```cpp
string() : _str(new char[1])// 因为后面用的是delete[] 需要匹配
{
    _str[0] = '\0';
    _size = _capacity = 0;
}
```

&emsp;&emsp;我们还可以提供全缺省的构造函数作为默认构造函数，这里的缺省值同样的不能给``nullptr``,原因如下：

```cpp
string(const char* str = nullptr) :
	_size(strlen(str)), _capacity(_size)
/*在这里传给strlen的是空指针 strlen不检查空指针 然后为了找'\0'就开始解引用 就会发生空指针的问题*/
{
    _str = new char[_capacity + 1];
	strcpy(_str, str);
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226140230.png)

&emsp;&emsp;一个聪明的缺省值给法是这样的，利用空字符串默认有``'\0'``:

```cpp
string(const char* str = "") :
	_size(strlen(str)), _capacity(_size)
// ""里头默认有'\0' 后续等价为_size(0) _capacity(0)
{
	// 正好开了一个长度为1的数组
	_str = new char[_capacity + 1];
	// 利用strcpy直接拷贝到_str
	// 把'\0'拷贝过来
	strcpy(_str, str);
}
```



## 2 string的迭代器

&emsp;&emsp;普通迭代器，string的迭代器可以用普通指针实现。

```cpp
// 字符串的迭代器就是指针
typedef char* iterator;
iterator begin()
{
    return _str;
}
iterator end()
{
    return _str + _size;
}
// ++ -- *解引用借助原生指针的++ -- *就可以了 不必自己再重载
```

``const``迭代器：

```cpp
typedef const char* const_iterator;
const_iterator begin() const
{
    return _str;
}
const_iterator end() const
{
    return _str + _size;
}
```

&emsp;&emsp;另外，范围for的原理就是替换成了迭代器。本质是由``begin()``和``end()``和迭代器支持的，这可以从我们去掉迭代器后的报错看出

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220226122917.png" style="zoom:80%;" />

```cpp
for (auto ch : s4)
{
    cout << ch << ' ';
}
//被替换成

auto i = s4.begin();
while (i != s4.end())
{
    cout << *i << ' ';
    ++i;
}
```





## 3 拷贝构造函数与赋值运算符重载的现代写法

&emsp;&emsp;本质就是去复用了``string``的``c_str``构造函数，然后把构造出来的string临时对象的地址和``this->_str``交换，这样就``_str``获得了拷贝好的``char*``,为了防止tmp析构时出错，所以一开始给``_str``赋``nullptr``.	

```cpp
string(const string& s)
	:_str(nullptr)
    //_str(nullptr)保证tmp析构时不会传一个随机值去析构 空指针delete[]不会
{
	string tmp(s._str);
    swap(_str, tmp._str);
}
```

&emsp;&emsp;赋值运算符重载：拷贝复用tmp的拷贝构造函数，delete原来的空间复用了tmp的析构

```cpp
string& operator=(const string& s)
{
    if (this != &s)
    {
    	string tmp(s);
    	swap(_str, tmp._str);
			/*tmp帮我复制s的内容 并且交换_str和tmp._str
			后顺便tmp析构的时候帮我本来的空间回收*/
    }
    return *this;
}
```

&emsp;&emsp;更简洁的现代写法：利用传参调用拷贝构造函数考内容，利用参数析构干掉本来的空间。

```cpp
string& operator=(string s)
{
    swap(_str, s._str);
    return *this;
}
```

&emsp;&emsp;所以一个简洁的string，不考虑增删查改只考虑深拷贝问题：

```cpp
namespace scu
{
    class string
    {
    public:
        string(const char* str = "") : _str(new char[strlen(str) + 1])
        {
            strcpy(_str, str);
        }
        string(const string& s) : _str(nullptr)
        {
            string tmp(s._str);
            swap(_str, tmp._str)
        }
        string& operator=(string s)
        {
            swap(_str, s._str);
            return *this;
        }
        ~string()
        {
            delete[] _str;
        }
    private:
        char* _str;
    };
}
```

&emsp;&emsp;对现代写法加上``_size``、``_capacity``，引入``Router::string::swap()``以交换``Router::string``的所有数据成员，修改如下：

```cpp
// 新增一个替换数据成员的swap函数
void swap(string& s)
{
    std::swap(_str, s._str);
    std::swap(_size, s._size);
    std::swap(_capacity, s._capacity);
}		
// 更简洁的赋值运算符重载现代写法
string& operator=(string s)
{
    swap(s);// 等价于 this->swap(s);
    return *this;
}
string(const string& s)
	:_str(nullptr), _size(0), _capacity(0)
{
	string tmp(s._str);
    swap(tmp);
}
```

&emsp;&emsp;string中也提供了交换成员变量的 ``void swap(string& s)``,我们知道std库中也有一个``std::swap``的交换函数，那么谁效率更高呢，我们看一下``std::swap``的原码：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220228194626.png)

&emsp;&emsp;可以看到首先拷贝构造了一个临时string对象c，一次深拷贝，然后b赋值给a，一次深拷贝，然后c赋值给b，又一次深拷贝，总共三次深拷贝，如果用``s.swap(s1)``只会把数据对象都交换一遍，不会有这三次深拷贝，效率更高。

&emsp;&emsp;上面的讨论仅限于C++98，C++11引入了新特性解决了swap对自定义类型的效率问题。

## 4 string的 扩容操作—reserve

&emsp;&emsp;先实现一个扩容函数``reserve(n)``，思路就是``new``开``n + 1``个字节的空间，先放tmp中，然后把原字符串内容拷贝过来，然后干掉原来的空间，然后修改容量的数值为新的容量.

```cpp
void reserve(size_t n)
{
    if (n > _capacity)
    {
        // 容量到100 再给'\0'多开一个
        char* tmp = new char[n + 1];
        strcpy(tmp, _str);
		delete[] _str;
        _str = tmp;
		_capacity = n;
    }
}
```

## 5 string的尾插操作

&emsp;&emsp;然后``push_back``和``append``就是和顺序表差不多的逻辑了，注意``push_back``要注意补充``'\0'``；``append``实现的方式就是有了足够的空间后，直接把要链接的字符串从``_str + _size``往后拷贝，``append``复用了``strcpy``，会自己处理``'\0'``.

```cpp
// 增一个字符
void push_back(const char ch)
{
    if (_size == _capacity)
    {
        // 增容 插入一个字符扩2倍即可 
        reserve(2 * _capacity);
	}
    _str[_size++] = ch;
    _str[_size] = '\0';
}

// 增一个字符串
void append(const char* s)
{
    size_t len = strlen(s);
    if (_size + len > _capacity)
    {
        reserve(_size + len);
    }
    /*直接算好了要考到的位置 就是本来字符串的'\0'位置*/
    strcpy(_str + _size, s);
}
```

&emsp;&emsp;复用push_back()和append()即可：

```cpp
// +=
string& operator+=(const char ch)
{
    push_back(ch);
    return *this;
}
string& operator+=(const char* s)
{
    append(s);
    return *this;
}
```

&emsp;&emsp;但是上面写的有一个隐含的风险，如下例：

```cpp
string s2;
s2 += 'c';
```

&emsp;&emsp;因为我们的capacity没考虑``'\0'``的空间，``""``的``_capacity``的长度为0,0*2怎么乘都是0，所以需要重新改一下``push_back``和``append``里头的扩容：

```cpp
// 增一个字符
void push_back(const char ch)
{
    if (_size == _capacity)
    {
        // 增容 插入一个字符扩2倍即可
        reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}
    _str[_size++] = ch;
    _str[_size] = '\0';
}

// 增一个字符串
void append(const char* s)
{
    size_t len = strlen(s);
    if (_size + len > _capacity)
    {
        reserve(len + _size);
    }
    /*直接算好了要考到的位置 就是本来字符串的'\0'位置*/
    strcpy(_str + _size, s);
}
```

## 6 string的扩容操作—resize

&emsp;&emsp;功能是把串重新定义成n长度，如果比原来的串长就会默认补充为ch字符，如果比原来的串短就会只保留前n个字符,逻辑也比较简单，注意如果大于容量扩容，记得补``'\0'``。

```cpp
void resize(size_t n, char ch = '\0')
{
    if (n <= _size)
    {
        // 下标为n的位置补上'\0'
        _str[n] = '\0';
		_size = n;
    }
    else
    {
        if (n > _capacity) reserve(n);
        // 利用memset 直接把_size往后的字符赋值为ch 赋值n - _size个字节
        memset(_str + _size, ch, n - _size);
		_size = n;
        // 补'\0'
        _str[_size] = '\0';
	}
}
```

## 7 string的任意位置插入—insert

&emsp;&emsp;首先是在pos位置插入字符ch的模拟，因为是要新增一个字符，所以如果``_size == _capacity``则需要扩容，然后把pos位置及其往后的位置都挪动1个字符，然后把ch插入进来：

```cpp
string& insert(size_t pos, char c)
{
    assert(pos <= _size);
    if (_size == _capacity)
    {
        reserve(_capacity == 0 ? 4 : 2 * _capacity);
    }
    /*end指向要拷贝去的空地 注意是'\0'也要拷所以是_size + 1
    如果end指向要挪动的字符 那么就会在头插时候pos = 0
    无符号数始终大于等于0而出问题*/
    size_t end = _size + 1;
    while (end > pos)
    {
        _str[end] = _str[end - 1];
        --end;
    }
    _str[pos] = ch;
    _size++;
    return *this;
}
```

&emsp;&emsp;然后是在pos位置插入一个字符串s,思路和插入一个字符类似，假设s串的长度为len，先考虑是否扩容问题，即len + _size > _capacity，然后把pos位置及其往后挪动``len``个位置，要插入的s串腾出空间，然后用``strncat``把原来的串的len个字符拷贝到``_str + pos``往后空出的位置，记得不要拷``'\0'``。

```cpp
string& insert(size_t pos, const char* s)
{
    assert(pos <= _size);
    size_t len = strlen(s);
    if (len + _size > _capacity)
    {
        reserve(len + _size);
    }
    size_t end = _size + len;
    while (end - len + 1 > pos)
    {
        _str[end] = _str[end - len];
        --end;
    }
    strncat(_str + pos, s, len);
    _size += len;
    return *this;
}
```

&emsp;&emsp;由此，``push_back``和``append``都可以复用``insert``:

```cpp
void push_back(const char ch)
{
    insert(_size, ch);
}

void append(const char* s)
{
    insert(_size, s);
}
```



## 8 string任意位置删除任意个数个字符—erase

&emsp;&emsp;原型：``string& erase(size_t pos = 0, size_t len = npos);``支持从pos位置删除``len``个字符。

&emsp;&emsp;思路如图，主要是考虑删完了以后还剩不剩字符了，如果不剩了，直接在pos处加``'\0'``，并且把``_size``赋值成``pos``即可；否则就要把剩下的串挪过来，

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220301161449.png" style="zoom:80%;" />

代码如下：

```cpp
string& erase(size_t pos = 0, size_t len = npos)
{
    assert(pos < _size);
    /*如果删完了*/
    if (len == npos || pos + len >= _size)
    {
        _str[pos] = '\0';
        _size = pos;
	}
    else
    {
        strcpy(_str + pos, _str + pos + len);
        _size -= len;
    }
    return *this;
}
```

## 9 string查找字符和子串—find

&emsp;&emsp;寻找一个字符第一次在字符串中出现的位置，遍历一遍即可：

```cpp
size_t find(char c, size_t pos = 0) const
{
    assert(pos < _size);
    for (int i = pos; i < _size; ++i)
    {
        if (_str[i] == c) return i;
    }
    return npos;
}
```

&emsp;&emsp;寻找一个字符串中一个子串第一次出现的位置，使用``kmp``算法或者复用``strstr``即可。

```cpp
// kmp
size_t find(const char* s, size_t pos = 0) const
{
    assert(pos < _size);
    int n = strlen(s);
    /*获得next数组*/
    int* next = new int[10000];
    next[0] = -1;
    if (n > 1) next[1] = 0;
    int k = 0, i = 2;
    while (i < n)
    {
        while (k != -1 && s[k] != s[i - 1]) k = next[k];
        next[i] = k + 1;
        ++i;
        ++k;
    }
    /*匹配*/
    i = pos;
    int j = 0;
    while (i < _size || j < n)
    {
        while (j != -1 && _str[i] != s[j]) j = ne[j];
        ++i;
        ++j;
    }
    delete[] next;
    if (j == n) return i - j;
    return npos;
}

// 复用strstr
size_t find(const char* s, size_t pos = 0)
{
    const char* p = strstr(_str + pos, s);
    if (p == nullptr) return npos;
    return p - _str;
}
```

## 10 关系比较操作符重载

&emsp;&emsp;关系比较操作符的重载既可以设计成类成员函数，也可以设计成全局的函数，类内的优势是可以直接访问类内的数据成员，类外的全局函数需要设计成友元。

&emsp;&emsp;STL的设计是设计成了全局的函数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220303191243.png" style="zoom:80%;" />

&emsp;&emsp;本人设计的成员函数重载，思路就是去复用``strcmp``即可:

```cpp
// relation operators
bool operator<(const string& s) const
{
    return strcmp(_str, s._str) == -1;
}
bool operator==(const string& s) const
{
    return strcmp(_str, s._str) == 0;
}
bool operator>(const string& s) const
{
    return strcmp(_str, s._str) == 1;
}
bool operator!=(const string& s) const
{
    return !(*this == s);
}
bool operator>=(const string& s) const
{
    return !(*this < s);
}
bool operator<=(const string& s) const
{
    return !(*this > s);
}
```

&emsp;&emsp;类外也可以复用``strcmp``，利用``c_str``即可，我们这里手写一下字符串比较的逻辑。

```cpp
bool operator<(const string& s1, const string& s2)
{
    // 缺点 不能用strcmp了
	size_t i = 0, j = 0;
    size_t n1 = s1.size(), n2 = s2.size();
	while (i < n1 && j < n2)
    {
        if (s1[i] < s2[j]) return true;
		else if (s1[i] > s2[j]) return false;
		else
        {
            i++;
            j++;
		}
	}
    // 如果j到头了 那么要么是相等 要么是s2更短 这些情况都不满足s1 < s2 都是false
	// 否则就是i到头了j没到头 s1的长度短 s1 < s2
    return j == n2 ? false : true;
}
// 使用c_str实现
bool operator==(const string& s1, const string& s2)
{
    return strcmp(s1.c_str(), s2.c_str()) == 0;
}
bool operator<=(const string& s1, const string& s2)
{
    return s1 < s2 || s1 == s2;
}
bool operator!=(const string& s1, const string& s2)
{
    return !(s1 == s2);
}
bool operator>(const string& s1, const string& s2)
{
    return !(s1 <= s2);
}
bool operator>=(const string& s1, const string& s2)
{
    return !(s1 < s2);
}
```

## 11 流插入和流提取操作符重载

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220303193439.png" style="zoom:80%;" />

&emsp;&emsp;注意由于运算符顺序，所以只能在类外实现这两个函数，``operator<<``可以不声明为友元，我们可以一个一个自己输出字符；``operator>>``也可以不声明为友元，我们可以用``cin.get()``一个一个的读取字符，利用``+=``插入到``string``中.

```cpp
// 因为用了operator[], 所以可以不用重载成友元
ostream& operator<<(ostream& out, const Router::string& s)
{
    int sz = s.size();
    // 利用cout输出访问到的每个char即可。
    for (int i = 0; i < sz; ++i)
	{
        out << s[i];
    }
    /*for (auto ch : s)
    {
        cout << ch;
    }*/
    //不能用下面的输出方式 这种方式不是_size多少就输出多少字符
    //是遇到'\0'才停止 假设有这样的字符串hello\0world
    // 它就不会正常输出了
    /*cout << s.c_str();*/
    
    return out;
}
// 利用cin.get()函数获取每个字符 
istream& operator>>(istream& in, Router::string& s)
{
    char ch = in.get();
	while (ch != ' ' && ch != '\n')
    {
        s += ch;
		ch = in.get();
	}
    // 也可以用一个缓冲区来优化
    return in;
}
```

&emsp;&emsp;为什么不能直接输出``c_str``的原因：

```cpp
int main()
{
	string s1("hello");
	s1 += '\0';
	s1 += "world";
	cout << s1 << endl;
	cout << s1.c_str() << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304105224.png" style="zoom:80%;" />

&emsp;&emsp;上面的流提取运算符还有一些问题，有的时候如果对象本身已经存在原来的数值了，我再提取的目的是让它更新为新的我输入的值，而不是在原来的基础上增加，所以可以用``clear()``.

```cpp
void clear()
{
    _size = 0;
    _str[0] = '\0';
}

istream& operator>>(istream& in, Router::string& s)
{
    
    char ch = in.get();
	while (ch != ' ' && ch != '\n')
    {
        s += ch;
		ch = in.get();
	}
    // 也可以用一个缓冲区来优化
    return in;
}
```



其他参数为string的一些模拟完全类似以``const char* s``的情况，因为我们可以操纵``s._str``，就不实现了。

# 五、string类的另一种实现方式—引用计数写时拷贝

&emsp;&emsp;浅拷贝的问题其实是两个：析构时会释放两次资源导致出错；对一个对象的修改会影响另一个对象。

&emsp;&emsp;使用引用计数计数与写时拷贝可以解决这个问题，降低深拷贝次数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220304121534.png" style="zoom:80%;" />

&emsp;&emsp;写时拷贝在再修改对象时观察引用计数，若引用计数不为1，则需要做深拷贝再写，否则直接写就可以，不用深拷贝，是一种延迟拷贝的思想。

&emsp;&emsp;如果我们不经常修改``string``对象，那么引用计数+写时拷贝就增加了效率。

&emsp;&emsp;但是它也存在缺陷，引用计数存在线程安全问题，需要加锁，在多线程环境需要付出代价，并且在动态库、静态库中有些情况下会存在一些问题。

# 六、VS下string的优化

&emsp;&emsp;当字符串长度小于16时，string的字符串会直接存到buffer数组中，它是属于对象本身的，是一个栈上的空间，当长度大于等于16时，它才会去堆申请空间。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314120150.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220314120040.png" style="zoom:80%;" />

&emsp;&emsp;VS下的string结构大致如下：

```cpp
class string
{
private:
    char* _Ptr;
    char _Buf[16];// 不够了则会去_Ptr在堆
    size_t _Mysize;
    size_t _Myres;
}
sizeof(std::string) 
```

