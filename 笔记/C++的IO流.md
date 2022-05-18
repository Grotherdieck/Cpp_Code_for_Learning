# 一、C语言的输入输出

&emsp;&emsp;C语言主要使用``scanf``和``printf``与输入输出设备交互，大概是这样的：

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220328211639471.png" alt="image-20220328211639471" style="zoom:80%;" />

# 二、C++的输入输出流

## 1 流是什么

&emsp;&emsp;“流”即是流动的意思，是物质从一处向另一处流动的过程，是对一种有序连续且具有方向性的数据（ 其单位 可以是bit,byte,packet ）的抽象描述。

&emsp;&emsp; C++流是指信息从外部输入设备（如键盘）向计算机内部（如内存） 输入和从内存向外部输出设备（显示器）输出的过程。这种输入输出的过程被形象的比喻为“流”。

&emsp;&emsp;它的特性是：有序连续、具有方向性 

&emsp;&emsp;为了实现这种流动，C++定义了I/O标准类库，这些每个类都称为流/流类，用以完成某方面的功能。

## 2 C++的标准IO流

&emsp;&emsp;C++的这些``cin cout``等都是一些全局对象，关系如下，``ios``是其基类，它们之间有继承的关系。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328211729.png" style="zoom:80%;" />

&emsp;&emsp;之前我们说过，``cout``和``cin``能自动识别类型的原因是因为它们做了运算符重载，同时这些运算符有构成了函数重载。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328211916.png" style="zoom:80%;" />

&emsp;&emsp;所以自定义类型需要我们自己做函数重载才可以用。

**cin cout效率提升**

&emsp;&emsp;``ios::sync_with_stdio(false);``这条语句可以把``cin``和``scanf``、``cout``和``printf``的同步关掉，可以提升``cin``的速度，不过这时``cin``和``scanf``混用就会出错。

&emsp;&emsp;没有这条语句时，``cin cout``为了保证混用``printf``和``scanf``时文件指针不混乱做了很多工作，所以速度要慢，关掉速度就会快很多。

**读取一行**

&emsp;&emsp;C语言读取一行，可以用``fgets``，C++可以用``getline``。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328213256.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328213219.png" style="zoom:80%;" />

&emsp;&emsp;``cin cout``相比``scanf``和``printf``的优势就在于自定义类型对象在重载后可以直接使用``<<``和``>>``输入输出，不比每次都要自己用``scanf``和``printf``组合。

**多组测试用例**

&emsp;&emsp;C语言写法：

```cpp
while (scanf("", ) != EOF)
```

&emsp;&emsp;因为``scanf``会返回读取的个数，当读取的个数是0的时候，就结束了。

&emsp;&emsp;C++写法：

```cpp
while (cin >> )
```

&emsp;&emsp;这里判断的表达式是判断的``cin``这个``istream``对象，按理说不应该啊，我们之前值接触过整形和布尔值做逻辑判断，这里怎么对象也能做逻辑判断了，是因为**类型运算符重载**，当用``istream``对象进行逻辑判断时，它就会调用这个类型运算符重载，使其返回一个布尔值。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328214937.png" style="zoom:80%;" />

&emsp;&emsp;我们的一个简单测试：

```cpp
class B
{
public:
	B(int b = 0) : _b(b)
	{}
	operator bool()
	{
		return _b != 0;
	}
private:
	int _b;
};

int main()
{
	B b1(11);
	if (b1)
	{
		cout << "隐式类型转换一样的operator bool()" << endl;
	}
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220328215539.png" style="zoom:80%;" />

&emsp;&emsp;所以上面的原理就是在``istream``类内部有一个标志符，当读取结束的时候，就会给这个标志符该为``false``，然后``operator bool()``返回这个标志符作为真假性即可。

&emsp;&emsp;进一步测试：

```cpp
class B
{
public:
	B(int b = 0) : _b(b)
	{}
	operator bool()
	{
		return _b != 0;
	}
	friend istream& operator>>(istream& in, B& b);
	friend ostream& operator<<(ostream& out, B& b);
private:
	int _b;
};
istream& operator>>(istream& in, B& b)
{
	in >> b._b;
	return in;
}

ostream& operator<<(ostream& out, B& b)
{
	out << b._b;
	return out;
}

int main()
{
	B b1(11);
	while (b1)
	{
		cin >> b1;
		cout << b1 << endl;
	}
	return 0;
}
```

## 3 C++的文件IO流

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329185344.png" style="zoom:80%;" />

&emsp;&emsp;假如我们要把如下结构的对象写入文件中：

```cpp
struct ServerInfo
{
 char _ip[32]; // ip
 int _port; // 端口
};
```

&emsp;&emsp;使用C语言的话，首先我们需要用``fopen``和``fclose``打开和关闭文件，文件的读写有两种方式，二进制读写可以使用``fwrite``和``fread``作为接口，直接写出内存中你的数据是怎么二进制存储的。还有一种写字符串来读写文件，接口为``fputs``和``fgets``打印接收一行，``fprintf``和``fscanf``来格式化字符串读写。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329190509.png" style="zoom:80%;" />

写：

```cpp
void testC_bin()
{
	ServerInfo info = { "127.0.0.1", 80 };
	FILE* pf = fopen("test.bin", "wb");
	assert(pf);
	fwrite(&info, sizeof(info), 1, pf);
	fclose(pf);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329191041.png" style="zoom:80%;" />

读：

```cpp
void testC_R_bin()
{
	ServerInfo info;
	FILE* pf = fopen("test.bin", "rb");
	assert(pf);
	fread(&info, sizeof(info), 1, pf);
	cout << info._ip << ' ' << info._port << endl;
	fclose(pf);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329190947.png" style="zoom:80%;" />

&emsp;&emsp;二进制读写比较简单，但缺陷是写出去的东西文件中看不见。

&emsp;&emsp;字符型读写测试：

```cpp
void testC_W_S()
{
	ServerInfo info = { "127.0.0.1", 80 };
	FILE* pf = fopen("test.txt", "w");
	assert(pf);
	fprintf(pf, "%s %d", info._ip, info._port);
	fclose(pf);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329191429.png" style="zoom:80%;" />

```cpp
void testC_R_S()
{
	ServerInfo info;
	FILE* pf = fopen("test.txt", "r");
	assert(pf);
	fscanf(pf, "%s %d", info._ip, &info._port);
	printf("%s %d\n", info._ip, info._port);
	fclose(pf);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329191709.png" style="zoom:80%;" />

&emsp;&emsp;注意``fscanf``和``scanf``类似，对多个数据，它们都以``' '``或``\n``区分。

&emsp;&emsp;我们用C++的风格玩一下，包头文件``<fstream>``。

&emsp;&emsp;C++中，``ofstream``是写文件流的类：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329192645.png" style="zoom:80%;" />

&emsp;&emsp;构造函数中的模式类型：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329192746.png" style="zoom:80%;" />

&emsp;&emsp;这里是用比特位表示状态，和``Linux``中的系统调用状态类似，可以``|``来把状态弄到一起。

&emsp;&emsp;它的写的成员函数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329193602.png" style="zoom:80%;" />

&emsp;&emsp;框架：

```cpp
// 管理文件名
class ConfigManager
{
public:
	ConfigManager(const string& str): _filename(str)
	{}
	void writeBin(const ServerInfo& info)
	{
		ofstream of(_filename.c_str(), ios_base::binary | ios_base::out);
		of.write((const char*)(&info), sizeof(info));
	}

	void readBin(ServerInfo& info)
	{
		ifstream of(_filename.c_str(), ios_base::binary | ios_base::in);
		of.read((char*)(&info), sizeof(info));
	}

	void writetxt(const ServerInfo& info)
	{
		// 默认参数就是文件读写
		ofstream of(_filename.c_str());
		of << info._ip << ' ' << info._port;
	}

	void writetxt(ServerInfo& info)
	{
		// 默认参数就是文件读写
		ifstream ifs(_filename.c_str());
		ifs >> info._ip >> info._port;
	}
private:
	string _filename;
};
```

&emsp;&emsp;二进制写：

```cpp
void testCPPWbin()
{
	ServerInfo info = { "192.0.0.1", 80 };
	ConfigManager con("myconfig.bin");
	con.writeBin(info);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329194151.png" style="zoom:80%;" />

&emsp;&emsp;二进制读:

```cpp
void testCPPRbin()
{
	ServerInfo info;
	ConfigManager con("myconfig.bin");
	con.readBin(info);
	cout << info._ip << ' ' << info._port << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329194500.png" style="zoom:80%;" />

文本写：

```cpp
void testCPPWtxt()
{
	ServerInfo info = { "191.0.0.1", 80 };
	ConfigManager con("myconfig.txt");
	con.writetxt(info);
}

```



<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329195216.png" style="zoom:80%;" />

文本读：

```cpp
void testCPPRtxt()
{
	ServerInfo info;
	ConfigManager con("myconfig.txt");
	con.readtxt(info);
	cout << info._ip << ' ' << info._port << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329195140.png" style="zoom:80%;" />

&emsp;&emsp;二进制读写和C类似，不过文本读写可以支持``operator >> ``和``operator <<``，可以对自定义类型重载这些运算符，然后就可以像``cout``、``cin``那样进行文本读写。

&emsp;&emsp;对自定义类型，这里需要去掉``const``，不知道为啥。

```cpp
class Date
{
public:
	Date(int year = 2000, int month = 1, int day = 1)
		: _year(year), _month(month), _day(day)
	{}
	friend ofstream& operator<<(ofstream& out, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ofstream& operator<<(ofstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}

void writetxt(ServerInfo& info)
{
    // 默认参数就是文件读写
	ofstream of(_filename.c_str());
    of << info._ip << ' ' << info._port << ' ';
	of << info._d;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329200628.png" style="zoom:80%;" />

## 3 C++的字符串IO流

&emsp;&emsp;头文件``<sstream>``。

``ostringstream``：把一个自定义结构中的内容读成一个字符串，类似``sprintf``。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329201132.png" style="zoom:80%;" />

&emsp;&emsp;它支持``operator<<``，可以从结构中把内容直接转字符串，注意分割，如果要获得转成的字符串，用``.str()``即可：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329201354.png" style="zoom:80%;" />

``istringstream``：把一个字符串中的内容一部分一部分读取出来，类似``sscanf``。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329201539.png" style="zoom:80%;" />

&emsp;&emsp;它也支持``operator>>``，可以从字符串中把内容读出来，注意需要分隔符。

&emsp;&emsp;在网络编程中，可以用这两个东西来完成**序列化**和**反序列化**的任务。

&emsp;&emsp;一个测试：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329202745.png" style="zoom:80%;" />

```cpp
class Date
{
public:
	Date(int year = 2000, int month = 1, int day = 1)
		: _year(year), _month(month), _day(day)
	{}
	friend ofstream& operator<<(ofstream& out, Date& d);
	friend ostringstream& operator<<(ostringstream& out, Date& d);
	friend ostream& operator<<(ostream& out, Date& d);
	friend istringstream& operator>>(istringstream& sin, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day;
	return out;
}

ofstream& operator<<(ofstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}

ostringstream& operator<<(ostringstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}

istringstream& operator>>(istringstream& sin, Date& d)
{
	sin >> d._year >> d._month >> d._day;
	return sin;
}

struct Personinfo
{
	string _name;
	int _age;
	Date _d;
};

int main()
{
	Personinfo p = { "路由器", 20 };
	ostringstream oss;
	oss << p._name << " " << p._age << " ";
	oss << p._d;// 这里要换行 不知道为什么
	cout << oss.str() << endl;
	string tmp = oss.str();
	istringstream iss(tmp);
	Personinfo p1;
	iss >> p1._name >> p1._age;
	iss >> p1._d;
	cout << p1._name << '*' << p1._age << '+' << p1._d << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220329204309.png" style="zoom:80%;" />

## 4 秒用ostream 、istream的继承体系

&emsp;&emsp;``ofstrem`` 和``ostringstream``自定义类型和内置类型不能连续输出的原因：

&emsp;&emsp;首先，这里有一个继承体系：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409144711.png" style="zoom:80%;" />

&emsp;&emsp;``ofstream``是继承与``ostream``，它的流插入是继承于``ostream``，并且没有重写，``ofstream``的``operator<<``打开就是这个。

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220409144957.png)

&emsp;&emsp;所以先是一个内置类型的话，就会调用上面的函数，返回``ostream``类型的对象，所以它不能做我们的友元函数``ofstream& operator<<(ofstream& out, Date& d)``的左操作数（父类对象不可传给子类）。

&emsp;&emsp;原因是我们重载错了，子类对象也是父类对象，所以我们的友元函数输出的话只要重载一个

```cpp
friend ostream& operator<<(ostream& out, Date& d);
```

&emsp;&emsp;就行了。

&emsp;&emsp;这样之所以可以，因为往哪插入的决定性因素（文件指针）在父类中（``ostringstream``里头是虚拟文件，也可以看做文件指针），所以直接复用父类的``operator<<``即可，``const``的问题也一并解决了。

```cpp
class Date
{
public:
	Date(int year = 2000, int month = 1, int day = 1)
		: _year(year), _month(month), _day(day)
	{}
	//friend ofstream& operator<<(ofstream& out, Date& d);
	// friend ostringstream& operator<<(ostringstream& out, Date& d);
	friend ostream& operator<<(ostream& out, const Date& d);
	//friend istringstream& operator>>(istringstream& sin, Date& d);
	friend istream& operator>>(istream& in, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day;
	return out;
}

/*ofstream& operator<<(ofstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}

ostringstream& operator<<(ostringstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}*/

istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

struct Personinfo
{
	string _name;
	int _age;
	Date _d;
};

int main()
{
	Personinfo p = { "路由器", 20 };
	ostringstream oss;
	oss << p._name << " " << p._age << " " << p._d;// 不用换行咯
	cout << oss.str() << endl;
	string tmp = oss.str();
	istringstream iss(tmp);
	Personinfo p1;
	iss >> p1._name >> p1._age >> p1._d;
	cout << p1._name << '*' << p1._age << '+' << p1._d << endl;
}
```





