#define  _CRT_SECURE_NO_WARNINGS 1
#include "list.h"

void test1()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	/*l.pop_back();
	l.pop_back();
	list<int> l2(5, 1);
	l = l2;*/
	for (auto e : l)
	{
		cout << e << ' ';
	}
	cout << std::endl;
	list<int>::reverse_iterator rit = l.rbegin();
	while (rit != l.rend())
	{
		*rit *= 2;
		cout << *rit << ' ';
		++rit;
	}
	cout << endl;
}

int main()
{
	test1();
}