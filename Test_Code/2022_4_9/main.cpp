#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//class A final
//{
//public:
//	A(int a = 0) : _a(a)
//	{}
//	int _a;
//public:
//	static A createobj(int a = 0)
//	{
//		return A(a);
//	}
//};
//
////class B : public A
////{
////
////};
//
//class C
//{
//	virtual void hello()
//	{
//		cout << "hello C " << endl;
//	}
//};
//
//class D : public C
//{
//	virtual void hello() override
//	{
//		cout << "hello D " << endl;
//	}
//};
//
//int main()
//{
//	A A1 = A::createobj(10);
//	// B bb;
//}

//class A
//{
//public:
//	virtual void f1() = 0;
//	void f2()
//	{
//		cout << "f2()" << endl;
//	}
//};
//
//class B : public A
//{
//public:
//	virtual void f1() override
//	{
//		cout << "f1 in B!" << endl;
//	}
//};
//
//int main()
//{
//	B b1;
//	b1.f1();
//	return 0;
//}

//class myc
//{
//public:
//	virtual void f()
//	{
//		cout << "f(" << endl;
//	}
//private:
//	int _a;
//	char _c;
//};
//
//int main()
//{
//	cout << sizeof(myc) << endl;
//	myc a;
//	return 0;
//}

//class Person
//{
//public:
//	virtual void buyticket()
//	{
//		cout << "全款买票" << endl;
//	}
//};
//
//class Student : public Person
//{
//public:
//	virtual void buyticket() override
//	{
//		cout << "半价买票" << endl;
//	}
//};
////
//void Ticker(Person p)
//{
//	p.buyticket();
//}
////
////int main()
////{
////	Person Bob;
////	Student Jenson;
////	Student Alice;
////	Ticker(Bob);
////	Ticker(Jenson);
////}
//
//int main()
//{
//	int a = 1;
//	printf("栈区%p\n", &a);
//	int* p = new int;
//	printf("堆区%p\n", p);
//	const char* str = "hellow";
//	printf("常量区%p\n", str);
//	printf("代码段%p\n", Ticker);
//	Student s;
//	printf("虚表%p\n", *(int*)(&s));
//}

//class father
//{
//public:
//	virtual void fun1()
//	{
//		cout << "father::fun1()" << endl;
//	}
//	virtual void fun2()
//	{
//		cout << "father::fun2()" << endl;
//	}
//};
//
//class child : public father
//{
//public:
//	virtual void fun1()
//	{
//		cout << "child::fun1()" << endl;
//	}
//	virtual void fun3()
//	{
//		cout << "child::fun3()" << endl;
//	}
//	virtual void fun4()
//	{
//		cout << "child::fun4()" << endl;
//	}
//};
//
//int main()
//{
//	father f;
//	child c;
//	return 0;
//}



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
private:
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
private:
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
private:
	int d;
};

int main()
{
	child d;
	base1* p1 = &d;
	base2* p2 = &d;
	p1->fun1();
	p2->fun1();
}

//class Base1 {
//public:
//	virtual void func1() { cout << "Base1::func1" << endl; }
//	virtual void func2() { cout << "Base1::func2" << endl; }
//private:
//	int b1;
//};
//class Base2 {
//public:
//	virtual void func1() { cout << "Base2::func1" << endl; }
//	virtual void func2() { cout << "Base2::func2" << endl; }
//private:
//	int b2;
//};
//class Derive : public Base1, public Base2 {
//public:
//	virtual void func1() { cout << "Derive::func1" << endl; }
//	virtual void func3() { cout << "Derive::func3" << endl; }
//private:
//	int d1;
//};
//typedef void(*VFPTR) ();
//void PrintVTable(VFPTR vTable[])
//{
//	cout << " 虚表地址>" << vTable << endl;
//	for (int i = 0; vTable[i] != nullptr; ++i)
//	{
//		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
//		VFPTR f = vTable[i];
//		//f();
//	}
//	cout << endl;
//}
//int main()
//{
//	Derive d;
//	Ba1
//	/*VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
//	PrintVTable(vTableb1);
//	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
//	PrintVTable(vTableb2);*/
//	return 0;
//}
