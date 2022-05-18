#define  _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"
#include "mymap.h"
#include "myset.h"

void RBTreetest1()
{
	RBTree<int, int> rbt1;
	// int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	// int a[] = { 1, 2, 3, 4, 5 };
	const int N = 100000000;
	/*for (auto e : a)
	{
		rbt1.Insert(make_pair(e, e));
		cout << e << ':' << rbt1.isbalance() << endl;
	}*/
	auto t1 = clock();
	for (int i = 0; i < N; ++i) rbt1.Insert(make_pair(i, i));
	auto t2 = clock();
	cout << rbt1.height() << endl;
	cout << t2 - t1 << "ms" << endl;
}

int main()
{
	//RBTreetest1();
	Router::test_set();
	Router::test_map();
}