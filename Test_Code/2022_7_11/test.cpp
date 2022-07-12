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
//	// û�в���Ĵ���
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
//	// ͨ��catch������ָ�����͵��쳣
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
//		// ��һ�β��� �����ڴ�й©
//		cout << "delete[] arr" << endl;
//		delete[] array;
//		// �ٴ��׳� ����㴦��
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

// ������������ͨ��ʹ�õ��쳣�̳���ϵ
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
// ���ݿ����
class SqlException : public Exception
{
public:
    SqlException(const string& errmsg, int id) : Exception(errmsg, id) {}
    virtual string what() const override
    {
          return "���ݿ����:" + _errmsg;
    }
};
// ��������
class CacheException : public Exception
{
public:
    CacheException(const string& errmsg, int id) : Exception(errmsg, id) {}
    virtual string what() const override
    {
        return "��������:" + _errmsg;
    }
};
// HTTP����
class HttpServerException : public Exception
{
public:
    HttpServerException(const string& errmsg, int id, int state)
        : Exception(errmsg, id), _state(state) {}
    virtual string what() const override
    {
        return "HTTP�����:" + _errmsg + ' ' + to_string(_id) + ' ' + to_string(_state);
    }
protected:
    int _state;
};

void sqlwork()
{
    int p = rand();
    if (p % 5 == 0)
    {
        throw SqlException("���ݿ�������!", 3);
    }
}

void cachework()
{
    // ... do sth.
    int p = rand();
    if (p % 7 == 0)
    {
        throw CacheException("�����ռ䲻��!", 4);
    }
    sqlwork();
}

void httpwork()
{
    cachework();
    int p = rand();
    if (p % 3 == 0)
    {
        throw HttpServerException("Ȩ�޲���", 1, 0);
    }
    else if (p % 7 == 0)
    {
        throw HttpServerException("�������Ӵ���", 2, 1);
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
        catch (const Exception& e) // ���ﲶ�������Ϳ���
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





