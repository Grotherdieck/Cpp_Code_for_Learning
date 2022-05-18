#define  _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> a;
	cout << a.capacity() << endl;
	size_t sz = a.capacity();
	for (int i = 1; i <= 100; ++i)
	{
		a.push_back(i);
		if (a.capacity() != sz)
		{
			cout << "capacity changed :" << a.capacity() << endl;
			sz = a.capacity();
		}
	}
	return 0;
}