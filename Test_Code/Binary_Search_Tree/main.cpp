#define  _CRT_SECURE_NO_WARNINGS 1

#include "BinarySearchTree.h"

void test1()
{
	int a[] = { 1, 32, 4329, 392, 9, -5, -111 };
	BSTree<int> mytree;
	for (int p : a)
	{
		mytree.insertR(p);
	}
	mytree.Inorder();
	cout << endl;
	for (int p : a)
	{
		mytree.eraseR(p);
		mytree.Inorder();
		cout << endl;
	}
}

int main()
{
	//test1();
	// string b = to_string(1111);
	KV::test1();
	return 0;
}

//#include<iostream>
//using namespace std;
//class A {
//public:
//	A(const char* s) { cout << s << endl; }
//	~A() {}
//};
//class B :virtual public A
//{
//public:
//	B(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
//};
//class C :virtual public A
//{
//public:
//	C(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
//};
//class D :public B, public C
//{
//public:
//	D(const char* s1, const char* s2, const char* s3, const char* s4) :B(s1, s2), C(s1, s3), A(s1)
//	{
//		cout << s4 << endl;
//	}
//};
//int main() {
//	D* p = new D("class A", "class B", "class C", "class D");
//	delete p;
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//class B : public A
//{
//public:
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	return 0;
//}
