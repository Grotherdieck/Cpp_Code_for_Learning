#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

class A{};
class B : public A
{};

class Person
{
public:
	virtual A* buyticker()
	{
		cout << "全价买票" << endl;
		A* p = new A;
		return p;
	}
};

class Student : public Person
{
	virtual B* buyticker()
	{
		cout << "半价买票" << endl;
		B* p = new B;
		return p;
	}
};

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

//class Person
//{
//public:
//	~Person()
//	//virtual ~Person()
//	{
//		cout << "~Person" << endl;
//	}
//};
//
//class Student : public Person
//{
//public:
//	~Student()
//	//virtual ~Student()
//	{
//		cout << "~Student" << endl;
//	}
//};
//
//int main()
//{
//	/*Student s;
//	Person p;*/
//	Person* p1 = new Person;
//	Person* p2 = new Student;
//	delete p1;// 先调用析构函数 再调用operator delete
//	delete p2;
//	// p2->destructor + operator delete
//	// 但是因为不构成多态 父类指针会调用父类的析构函数 就造成了内存泄漏
//	return 0;
//}