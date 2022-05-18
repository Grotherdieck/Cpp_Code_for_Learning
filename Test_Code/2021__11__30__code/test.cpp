#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//int main()
//{
//	int x1 = 2;
//	int x2 = 3;
//	//int& a = x1 + x2;
//	const int& a = x1 + x2;
//	printf("%p\n", &a);
//}

//void f1(int* p)
//{
//	*p = 10;
//}
//
//void f2(int& p)
//{
//	p = 10;
//}
//
//int main()
//{
//	f1(NULL);
//	f1(0);
//	f2(NULL);
//	f2(0);
//}
//#include "../Stack/Stack.h"
//bool isValid(char* s)
//{
//    //思路：遇到左括号 入栈
//    //遇到右括号 出栈匹配
//    //最后看看栈是否为空
//    //如果一上来就遇到右括号 也就是说一上来就想出栈 栈为空
//    //那就return false
//    Stack st;
//    StackInit(&st);
//    while (*s)
//    {
//        if (*s == '(' || *s == '[' || *s == '{')
//        {
//            StackPush(&st, *s);
//            s++;
//        }
//        if (*s == '}' || *s == ')' || *s == ']')
//        {
//            if (StackEmpty(&st) == true)
//            {
//                Stackdestroy(&st);
//                return false;
//            }
//            StackDataType x = StackTop(&st);
//            StackPop(&st);
//            if ((*s == '}' && x != '{') || (*s == ']' && x != '[') || (*s == ')' && x != '('))
//            {
//                Stackdestroy(&st);
//                return false;
//            }
//            s++;
//        }
//    }
//    if (StackEmpty(&st) == true)
//    {
//        Stackdestroy(&st);
//        return true;
//    }
//    else
//    {
//        Stackdestroy(&st);
//        return false;
//    }
//}
//
//int main()
//{
//    char str1[] = "{[]}";
//    //cout << isValid(str1) << endl;
//    printf("%d\n", isValid(str1));
//    char str2[] = "(()]}";
//    printf("%d\n", isValid(str2));
//    //cout << isValid(str2) << endl;
//}
template <typename T>
inline T Add(T a, T b)
{
	return a + b;
}

//#define add(x,y) ((x) + (y))

int main()
{
	int ret2 = Add<int>(1, 4);
	int ret = Add(1, 3);
	cout << ret << endl;
}

void swap(int& a, int& b)
{
	if (a == b)
		return;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}