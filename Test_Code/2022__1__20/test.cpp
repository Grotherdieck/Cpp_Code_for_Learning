#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
//#include <string>
//#include <vector>
using namespace std;
//int numDecodings(string s)
//{
//    if (s[0] == '0')
//    {
//        return 0;
//    }
//    int size = s.size();
//    vector<int> dp(size);
//    dp[0] = 1;
//    if (size == 1)
//    {
//        return 1;
//    }
//    if (s[1] == '0')
//    {
//        dp[1] = 1;
//    }
//    else if (s[0] == '1')
//    {
//        dp[1] = 2;
//    }
//    else if (s[0] == '2' && s[1] - '1' <= 5)
//    {
//        dp[1] = 2;
//    }
//    else if (s[0] == '2' && s[1] - '1' > 5)
//    {
//        dp[1] = 1;
//    }
//    else if (s[0] - '1' > 1)
//    {
//        dp[1] = 1;
//    }
//    for (int i = 2; i < size; ++i)
//    {
//        if (s[i] == '0' && s[i - 1] != '0')
//        {
//            dp[i] = dp[i - 2];
//        }
//        else if (s[i] == '0' && s[i - 1] == '0')
//        {
//            dp[i] = 0;
//        }
//        else if (s[i] != '0' && s[i - 1] == '0')
//        {
//            dp[i] = dp[i - 1];
//        }
//        else if ((s[i - 1] == '1' && s[i] != '0')
//            || (s[i - 1] == '2' && s[i] - '0' <= 6 && s[i] - '0' > 0))
//        {
//            dp[i] = dp[i - 1] + dp[i - 2];
//        }
//        else if (s[i - 1] - '0' >= 2 && s[i] != '0')
//        {
//            dp[i] = dp[i - 1];
//        }
//        else if (s[i - 1] - '0' >= 3 && s[i] == '0')
//        {
//            dp[i] = 0;
//        }
//    }
//    return dp[size - 1];
//}
//
//int main()
//{
//    numDecodings("227");
//}
//
//int main()
//{
//	char str[] = "sssss";
//}

//int main()
//{
//	int* p1 = new int;
//	int* p2 = new int[5];
//	int* p3 = new int(5);
//	int* p4 = new int[5]{ 1,2,3,4,5 };
//}

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		delete[] _p;
		cout << "~A()" << endl;
	}
private:
	int* _p = new int(4);
};

//int main()
//{
//	A* a1 = (A*)malloc(sizeof(A));
//	A* a2 = (A*)malloc(sizeof(A) * 5);
//	A* a3 = new A;
//	A* a4 = new A[5];
//	free(a1);
//	free(a2);
//	delete[] a3;
//	delete[] a4;
//}

//int main()
//{
//	//int* p = (int*)malloc(1024u * 1024u * 1024u* 2u);
//	char* p = new char[1024u * 1024u * 1024u * 2u - 1];
//	if (p == nullptr)
//	{
//		printf("%d\n", errno);
//		perror("malloc fail");
//		exit(-1);
//	}
//}

int main()
{
	//int* p = (int*)malloc(1024u * 1024u * 1024u* 2u);
	char* p = nullptr;
	try
	{
		p = new char[1024u * 1024u * 1024u * 2u - 1];
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}