#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//class base
//{
//public:
//	base(int a = 1)
//	{
//		_a = a;
//	}
//	virtual void fun1()
//	{
//		cout << "base::fun1" << endl;
//	}
//private:
//	int _a;
//};
//
//int main()
//{
//	base b1;
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
//	void fun4()
//	{
//		cout << "child::fun4()" << endl;
//	}
//};
// void fun(void)的函数指针 void(*)()
//typedef void(*VF_Ptr)();
//
//// 打印虚函数表的函数 参数为虚函数表的指针
//void PrintVF_table(VF_Ptr* _table)
//{
//	for (int i = 0; _table[i] != nullptr; ++i)
//	{
//		printf("虚函数表中第[%d]个元素->%p\n", i, _table[i]);
//		VF_Ptr f = _table[i];
//		f();
//	}
//}
//
//
//class base1
//{
//public:
//	virtual void fun1()
//	{
//		cout << "base1::fun1()" << endl;
//	}
//	virtual void fun2()
//	{
//		cout << "base1::fun2()" << endl;
//	}
//	int b1;
//};
//
//class base2
//{
//public:
//	virtual void fun1()
//	{
//		cout << "base2::fun1()" << endl;
//	}
//	virtual void fun2()
//	{
//		cout << "base2::fun2()" << endl;
//	}
//	int b2;
//};
//
//class child : public base1, public base2
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
//	int d;
//};
//
//
//int main()
//{
//	base1 b1;
//	base2 b2;
//	child s;
////#ifdef _WIN64
////	PrintVF_table((VF_Ptr*)*(long long*)(&f));
////#else 
////	PrintVF_table((VF_Ptr*)*(int*)(&f));
////#endif // _WIN64
//
//	PrintVF_table((VF_Ptr*)*((void**)(&s)));
//	//PrintVF_table((VF_Ptr*)*((void**)((char*)&s + sizeof(base1))));
//	printf("\n");
//	base2* p = &s;
//	PrintVF_table((VF_Ptr*)*((void**)(p)));
//	return 0;
//}


