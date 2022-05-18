#define  _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"

void TestAVLTree1()
{
	AVLTree<int, int> t;
	//int a[] = { 5, 4, 3, 2, 1 };
	// int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// int a[] = { 1, 2, 3, 4, 5 };
	/*int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	// int a[] = { 90, 30, 60 };
	for (auto& e : a)
	{
		t.Insert(make_pair(e, e));
		if (!t.isBalance())
		{
			cout << "插入" << e << "出问题了" << endl;
		} 
	}
	t.Inorder();
	if (!t.isBalance()) cout << "该树异常" << endl;*/
	const int N = 100000000;
	auto t1 = clock();
	for (int i = 0; i < N; ++i)
	{
		t.Insert(make_pair(i, i));
	}
	auto t2 = clock();
	int height = t.height();
	cout << height << "层" << endl;
	cout << t2 - t1 << "ms" << endl;
}

int main()
{
	TestAVLTree1();
}