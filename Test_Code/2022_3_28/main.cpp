#define  _CRT_SECURE_NO_WARNINGS 1
#include "test.h"
//int main()
//{
//	Data<int, int> d1;
//	Data<int, char> d2;
//	Data<double*, int*> d3;
//	Data<double&, int&> d4;
//	A<100> a1;
//	A<10> a2;
//	Data<double&, int*> d5;
//}

//int main()
//{
//	// cout << add(1, 2) << endl;
//	A<int>* p = nullptr;
//	// p->myval();
//	// A<int> aa;
//}

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
	friend int operator^();
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