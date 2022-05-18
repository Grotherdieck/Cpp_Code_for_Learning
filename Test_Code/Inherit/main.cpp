#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//class fathernum
//{
//public:
//	int _num = 1;
//};
//
//class sonnum : public fathernum
//{
//public:
//	int _num = 999;
//};
//
//int main()
//{
//	sonnum s;
//	cout << s._num << endl;
//	cout << s.fathernum::_num << endl;
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name)
//		: _name(name)
//	{
//		cout << "Person()" << endl;
//	}
//
//	Person(const Person& p)
//		: _name(p._name)
//	{
//		cout << "Person(const Person& p)" << endl;
//	}
//
//	Person& operator=(const Person& p)
//	{
//		cout << "Person operator=(const Person& p)" << endl;
//		if (this != &p)
//			_name = p._name;
//
//		return *this;
//	}
//
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
//
//// 自己写：
//class Student : public Person
//{
//public:
//	// 构造
//	Student(const char* name = "王五", int num = 1)
//		:Person(name), _num(num)
//	{}
//	// 拷贝构造 假设要实现深拷贝
//	Student(const Student& s)
//		: Person(s),_num(s._num) //这里会自动完成切片
//	{}
//	// 赋值
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s);// 避免隐藏 去父类类域找对应的赋值
//			_num = s._num;
//		}
//		return *this;
//	}
//	// 析构
//	~Student()
//	{
//		// Person::~Person();
//	}
//protected:
//	int _num; //学号
//};
////void Test()
////{
////	Student s1("jack", 18);
////	Student s2(s1);
////	Student s3("rose", 17);
////	s1 = s3;
////}
//
//int main()
//{
//	Student s;
//	/*Student s1(s);
//	Student s2("Jack", 20);
//	s = s2;*/
// 	return 0;
//}
//class Student;
//class Person
//{
//public:
//	Person(const char* str): _name(str)
//	{}
//	
//protected:
//	friend void display(const Person& p, const Student& s);
//	string _name;
//};
//
//
//
//class Student : public Person
//{
//public:
//	Student(const char* str = "haha", int num = 1)
//		: Person(str), _num(num)
//	{}
//protected:
//	int _num;
//};
//
//void display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._name << endl;
//}
//
//int main()
//{
//	Person p("hahaha");
//	Student s("sjfkajkf", 20);
//	display(p, s);
//}


//class Student;
//class Person
//{
//public:
//	friend void Display(const Person& p, const Student& s);
//protected:
//	string _name; // 姓名
//};
//class Student : public Person
//{
//protected:
//	int _stuNum; // 学号
//};
//void Display(const Person& p, const Student& s)
//{
//	cout << p._name << endl;
//	cout << s._stuNum << endl;
//}
//void main()
//{
//	Person p;
//	Student s;
//	Display(p, s);
//}

//class Person
//{
//public:
//    Person() { ++_count; }
//protected:
//    string _name; // 姓名
//public:
//    static int _count; // 统计人的个数。
//};
//int Person::_count = 0;
//class Student : public Person
//{
//protected:
//    int _stuNum; // 学号
//};
//class Graduate : public Student
//{
//protected:
//    string _seminarCourse; // 研究科目
//};
//
//int main()
//{
//    Person p;
//    Student s;
//    Graduate g;
//    cout << "人数" << Person::_count << endl;
//    cout << &Person::_count << endl;
//    cout << &Student::_count << endl;
//    cout << &Graduate::_count << endl;
//    return 0;
//}
// 菱形继承二义性的问题
//class Person
//{
//public:
//	string _name; // 姓名
//};
//
//class Student : virtual public Person
//{
//public:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//public:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//
//int main()
//{
//	Assistant a;
//	a._id = 1;
//	a._num = 2;
//	a.Teacher::_name = "fkdfjsk";
//	a.Student::_name = "hafkaf";
//	a._name = "Router";
//	return 0;
//}

class A
{
public:
	int _a;
};
//class B : public A
class B : virtual public A
{
public:
	int _b;
};
//class C : public A
class C : virtual public A
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
	d._a = 0;
	return 0;
}