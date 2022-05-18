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
//	int _port; // �˿�
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
//// �����ļ���
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
//		// Ĭ�ϲ��������ļ���д
//		ofstream of(_filename.c_str());
//		of << info._ip << ' ' << info._port << ' ';
//		of << info._d;
//	}
//
//	void readtxt(ServerInfo& info)
//	{
//		// Ĭ�ϲ��������ļ���д
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
//	Personinfo p = { "·����", 20 };
//	ostringstream oss;
//	oss << p._name << " " << p._age << " ";
//	oss << p._d;// ����Ҫ���� ��֪��Ϊʲô
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
//	string _name = "peter"; // ����
//	int _age = 18; // ����
//};
//// �̳к����Person�ĳ�Ա����Ա����+��Ա�����������������һ���֡��������ֳ���Student��
//// Teacher������Person�ĳ�Ա����������ʹ�ü��Ӵ��ڲ鿴Student��Teacher���󣬿��Կ��������ĸ��á�
//// ����Print���Կ�����Ա�����ĸ��á�
//class Student : public Person
//{
//protected:
//	int _stuid; // ѧ��
//};
//class Teacher : public Person
//{
//protected:
//	int _jobid; // ����
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
	string _name = "·����";
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
	a = b;// �и�
	b = a;
	return 0;
}