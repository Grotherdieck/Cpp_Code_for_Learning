#define  _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;

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

//
//struct ServerInfo
//{
//	char _ip[32]; // ip
//	int _port; // 端口
//	Date _d;
//};
//
//void testC_bin()
//{
//	ServerInfo info = { "127.0.0.1", 80 };
//	FILE* pf = fopen("test.bin", "wb");
//	assert(pf);
//	fwrite(&info, sizeof(info), 1, pf);
//	fclose(pf);
//}
//void testC_R_bin()
//{
//	ServerInfo info;
//	FILE* pf = fopen("test.bin", "rb");
//	assert(pf);
//	fread(&info, sizeof(info), 1, pf);
//	cout << info._ip << ' ' << info._port << endl;
//	fclose(pf);
//}
//
//void testC_W_S()
//{
//	ServerInfo info = { "127.0.0.1", 80 };
//	FILE* pf = fopen("test.txt", "w");
//	assert(pf);
//	fprintf(pf, "%s %d", info._ip, info._port);
//	fclose(pf);
//}
//
//void testC_R_S()
//{
//	ServerInfo info;
//	FILE* pf = fopen("test.txt", "r");
//	assert(pf);
//	fscanf(pf, "%s %d", info._ip, &info._port);
//	printf("%s %d\n", info._ip, info._port);
//	fclose(pf);
//}
//
//// 管理文件名
//class ConfigManager
//{
//public:
//	ConfigManager(const string& str): _filename(str)
//	{}
//	void writeBin(const ServerInfo& info)
//	{
//		ofstream of(_filename.c_str(), ios_base::binary | ios_base::out);
//		of.write((const char*)(&info), sizeof(info));
//	}
//
//	void readBin(ServerInfo& info)
//	{
//		ifstream of(_filename.c_str(), ios_base::binary | ios_base::in);
//		of.read((char*)(&info), sizeof(info));
//	}
//
//	void writetxt(ServerInfo& info)
//	{
//		// 默认参数就是文件读写
//		ofstream of(_filename.c_str());
//		of << info._ip << ' ' << info._port << ' ';
//		of << info._d;
//	}
//
//	void readtxt(ServerInfo& info)
//	{
//		// 默认参数就是文件读写
//		ifstream ifs(_filename.c_str());
//		ifs >> info._ip >> info._port;
//	}
//private:
//	string _filename;
//};
//
//void testCPPWbin()
//{
//	ServerInfo info = { "192.0.0.1", 80 };
//	ConfigManager con("myconfig.bin");
//	con.writeBin(info);
//}
//
//void testCPPRbin()
//{
//	ServerInfo info;
//	ConfigManager con("myconfig.bin");
//	con.readBin(info);
//	cout << info._ip << ' ' << info._port << endl;
//}
//
//void testCPPWtxt()
//{
//	ServerInfo info = { "191.0.0.1", 80 };
//	ConfigManager con("myconfig.txt");
//	con.writetxt(info);
//}
//
//void testCPPRtxt()
//{
//	ServerInfo info;
//	ConfigManager con("myconfig.txt");
//	con.readtxt(info);
//	cout << info._ip << ' ' << info._port << endl;
//}
//
//int main()
//{
//	//testC_bin();
//	//testC_R_bin();
//	// testC_R_S();
//	// testCPPWbin();
//	// testCPPRbin();
//	// testCPPWtxt();
//	// testCPPRtxt();
//	
//	return 0;
//}

//struct Personinfo
//{
//	string _name;
//	int _age;
//	Date _d;
//};
//
//int main()
//{
//	Personinfo p = { "路由器", 20 };
//	ostringstream oss;
//	oss << p._name << " " << p._age << " ";
//	oss << p._d;// 这里要换行 不知道为什么
//	cout << oss.str() << endl;
//	string tmp = oss.str();
//	istringstream iss(tmp);
//	Personinfo p1;
//	iss >> p1._name >> p1._age;
//	iss >> p1._d;
//	cout << p1._name << '*' << p1._age << '+' << p1._d << endl;
//}


//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//protected:
//	string _name = "peter"; // 姓名
//	int _age = 18; // 年龄
//};
//// 继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。这里体现出了Student和
//// Teacher复用了Person的成员。下面我们使用监视窗口查看Student和Teacher对象，可以看到变量的复用。
//// 调用Print可以看到成员函数的复用。
//class Student : public Person
//{
//protected:
//	int _stuid; // 学号
//};
//class Teacher : public Person
//{
//protected:
//	int _jobid; // 工号
//};
//int main()
//{
//	Student s;
//	Teacher t;
//	s.Print();
//	t.Print();
//	return 0;
//}

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

class Student : public Person
{
protected:
	int _sid = 10;
};

int main()
{
	Person a;
	a.print();
	Student b;
	a = b;// 切割
	b = a;
	return 0;
}