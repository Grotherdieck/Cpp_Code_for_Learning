#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

//double division(int a, int b)
//{
//	if (b == 0)
//	{
//		string str("division by zero!");
//		throw str;
//	}
//	// 没有捕获的错误
//	if (b == 3)
//	{
//		throw 3.3;
//	}
//	return (double)a / (double)b;
//}
//
//void func()
//{
//	int a, b;
//	cin >> a >> b;
//	cout << division(a, b) << endl;
//}
//
//int main()
//{
//	try
//	{
//		func();
//	}
//	// 通过catch来捕获指定类型的异常
//	catch (const string& errmsg)
//	{
//		cout << errmsg << endl;
//	}
//	/*catch (...)
//	{
//		cout << "unknow error" << endl;
//	}*/
//	return 0;
//}
//double division(int a, int b) throw(string)
//{
//	if (b == 0)
//	{
//		string str("division by zero!");
//		throw str;
//	}
//	
//	return (double)a / (double)b;
//}
//
//void func() throw(string)
//{
//	int* array = new int[10];
//	try
//	{
//		int a, b;
//		cin >> a >> b;
//		cout << division(a, b) << endl;
//	}
//	catch (...)
//	{
//		// 第一次捕获 处理内存泄漏
//		cout << "delete[] arr" << endl;
//		delete[] array;
//		// 再次抛出 给外层处理
//		throw;
//	}
//	// ... other works
//	cout << "delete[] arr" << endl;
//	delete[] array;
//}
//
//int main()
//{
//	try
//	{
//		func();
//	}
//	catch (const string& str)
//	{
//		cout << str << endl;
//	}
//	return 0;
//}

// 服务器开发中通常使用的异常继承体系
class Exception
{
public:
    Exception(const string& errmsg, int id) : _errmsg(errmsg), _id(id) {}
    virtual string what() const
    {
        return _errmsg;
    }
protected:
    string _errmsg;
    int _id;
    // ...
};
// 数据库错误
class SqlException : public Exception
{
public:
    SqlException(const string& errmsg, int id) : Exception(errmsg, id) {}
    virtual string what() const override
    {
          return "数据库错误:" + _errmsg;
    }
};
// 缓存层错误
class CacheException : public Exception
{
public:
    CacheException(const string& errmsg, int id) : Exception(errmsg, id) {}
    virtual string what() const override
    {
        return "缓存层错误:" + _errmsg;
    }
};
// HTTP错误
class HttpServerException : public Exception
{
public:
    HttpServerException(const string& errmsg, int id, int state)
        : Exception(errmsg, id), _state(state) {}
    virtual string what() const override
    {
        return "HTTP层错误:" + _errmsg + ' ' + to_string(_id) + ' ' + to_string(_state);
    }
protected:
    int _state;
};

void sqlwork()
{
    int p = rand();
    if (p % 5 == 0)
    {
        throw SqlException("数据库插入错误!", 3);
    }
}

void cachework()
{
    // ... do sth.
    int p = rand();
    if (p % 7 == 0)
    {
        throw CacheException("缓存层空间不足!", 4);
    }
    sqlwork();
}

void httpwork()
{
    cachework();
    int p = rand();
    if (p % 3 == 0)
    {
        throw HttpServerException("权限不足", 1, 0);
    }
    else if (p % 7 == 0)
    {
        throw HttpServerException("网络连接错误", 2, 1);
    }
}

void Severstart()
{
    srand(unsigned int(time(nullptr)));
    while (1)
    {
        try
        {
            httpwork();
        }
        catch (const Exception& e) // 这里捕获父类对象就可以
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "Unkown Exception" << endl;
        }
        // system("sleep 1");
        Sleep(1000);
    }
}

int main()
{
    Severstart();
    return 0;
}





