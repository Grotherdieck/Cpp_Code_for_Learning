#define  _CRT_SECURE_NO_WARNINGS 1
//#include <stdlib.h>
//#include <stdio.h>

//namespace scu
//{
//	int rand = 1;
//	int add(int x, int y);
//	namespace ustec
//	{
//		int j = 1;
//	}
//}
//
//int scu::add(int x, int y)
//{
//	return x + y;
//}
//
//int a = 0;
//int main()
//{
//	int a = 1;
//	printf("%d\n", ::a);
//	//printf("%d", scu::rand);
//	return 0;
//}

//#include <stdlib.h>
//namespace scu
//{
//    int rand = 1;
//}
//using namespace scu;
//int main()
//{
//    printf("%d", rand);
//}

//namespace Linklist
//{
//    typedef struct NODE {
//        int val;
//        struct NODE* next;
//    }Node;
//    void listInit(Node** pphead);
//}
//
//namespace Linklist
//{
//    void listInit(Node** pphead)
//    {
//        *pphead = (Node*)malloc(sizeof(Node));
//        if (*pphead == nullptr)
//        {
//            exit(-1);
//        }
//        (*pphead)->next = nullptr;
//    }
//}
//
//using Linklist::Node;
//
//int main()
//{
//    Node* LTNode;
//    Linklist::listInit(&LTNode);
//    return 0;
//}


#include <iostream>

using std::cout;
using std::cin;

int main()
{
	int i = 1;
	double f = 1.1;
	cout << i << " " << f << std::endl;
	printf("%.3lf", f);
}