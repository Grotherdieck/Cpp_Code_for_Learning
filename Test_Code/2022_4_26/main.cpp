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
		cout << "ȫ����Ʊ" << endl;
		A* p = new A;
		return p;
	}
};

class Student : public Person
{
	virtual B* buyticker()
	{
		cout << "�����Ʊ" << endl;
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
//	delete p1;// �ȵ����������� �ٵ���operator delete
//	delete p2;
//	// p2->destructor + operator delete
//	// ������Ϊ�����ɶ�̬ ����ָ�����ø������������ ��������ڴ�й©
//	return 0;
//}