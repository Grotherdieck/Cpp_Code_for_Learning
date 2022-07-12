&emsp;&emsp;�����������Դ�����󼸺���ѡ�����쳣����C����ʹ�ô�������д�����ķ�ʽ��ͬ��

# һ��C���Դ�ͳ�Ĵ�����ʽ

* ��ֹ����ͨ�� ``assert``��ȱ�ݣ�ֱ����ֹ�����û����Խ��ܡ�
* ���ش����룬ȱ����ÿ�γ�������Ƕ�Ҫ�Լ�ȥ��ѯ��������Ƚ��鷳��
* C��׼���е� ``setjmp``�� ``longjmp``�����õıȽ��١�

# ����C++���쳣����

&emsp;&emsp;�쳣��һ�ִ������ķ�ʽ����һ�����������Լ��޷�������ֵĴ���ʱ�Ϳ����׳��쳣���ú�����ֱ�ӻ��ӵ�����ȥ�����������

* throw�����������ʱ������ͨ��throw�ؼ������׳�һ���쳣��
* catch��������Ҫ��������ĵط���ͨ���쳣������򲶻��쳣��ͨ��catch�ؼ�����ɣ������ж��catch���в���
* try��try���еĴ����ʶ�п��ܱ������ض����쳣��������ͨ������һ������catch�顣

```cpp
double division(int a, int b)
{
	if (b == 0)
		throw "division by zero!";
	return (double)a / (double)b;
}

void func()
{
	int a, b;
	cin >> a >> b;
	cout << division(a, b) << endl;
}

int main()
{
	try
	{
		func();
	}
	// ͨ��catch������ָ�����͵��쳣
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	catch (...)
	{
		cout << "unknow error" << endl;
	}
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220711080700.png)

&emsp;&emsp;ͨ���������Կ��Է��֣����������߼���һ���׳��쳣�󣬲������˳��ִ�г��򣬶��ǻ�ֱ����ת�������쳣�ĵط���

# �����쳣��ʹ��

## 3.1 �쳣���׳��벶��

�쳣���׳���ƥ��ԭ��

1. �쳣��**ͨ���׳������������**��**�ö�������;�����Ӧ�ü����ĸ�catch�Ĵ������**��
2. ��ѡ�еĴ��������**����������ö�������ƥ�������׳��쳣λ���������һ��**��
3. �׳��쳣�����**������һ���쳣����Ŀ���**����Ϊ�׳����쳣���������һ����ʱ�������Ի�����
   һ���������������������ʱ������ڱ�catch�Ժ����١�������Ĵ��������ں����Ĵ�ֵ���أ�

   ![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220711083015.png)
4. catch(...)���Բ����������͵��쳣��**�����ǲ�֪���쳣������ʲô**��
5. ʵ�����׳��Ͳ����ƥ��ԭ���и����⣬��������������ȫƥ�䣬**�����׳������������ʹ�û��ಶ��**�������ʵ���зǳ�ʵ�ã����Ǻ������ϸ���������

�ں������������쳣ջչ��ƥ��ԭ��

1. ���ȼ��throw�����Ƿ���try���ڲ���������ٲ���ƥ���catch��䡣�����ƥ��ģ������catch�ĵط����д���
2. **û��ƥ���catch���˳���ǰ����ջ�������ڵ��ú�����ջ�н��в���ƥ���catch**��
3. **�������main������ջ������û��ƥ��ģ�����ֹ����**������������ŵ���������ƥ���catch�Ӿ�Ĺ��̳�Ϊջչ����**����ʵ�����������Ҫ��һ��catch(...)�����������͵��쳣���������쳣û���񣬳���ͻ�ֱ����ֹ**��

   ![img](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220711083353.png)
4. �ҵ�ƥ���catch�Ӿ䲢�����Ժ�**���������catch�Ӿ�������ִ��**��Ȼ����൱���˳����������ĺ�����ջ֡��

&emsp;&emsp;��ʵ�ʳ����У��쳣ͨ������������㴦����������ǳ��Ӵ�ʱ����������Ҫ����������͵��쳣�����ҽ������Ĵ����¼����־�У���ʱ����Ҫ��һ���쳣����ȥ�涨����������㴦���쳣���˲����ܴ���Ĺ�������ô��ô�淶��������أ������ǾͿ�����ȫ����������쳣�����û��ಶ��������ˡ�

&emsp;&emsp;�������ǲ������� ``exception``�Ķ������ǿ������������������Ȼ�������������ö�̬��ͬһ��catch������쳣�Ĵ���

## 3.2 �쳣�������׳�

&emsp;&emsp;�п��ܵ�����catch������ȫ����һ���쳣���ڽ���һЩУ�������Ժ�ϣ���ٽ��������ĵ���������������catch�����ͨ�������׳����쳣���ݸ����ϲ�ĺ������д���������ɻ�����һ���ֵ�ģ�������������������ڴ�й©�ĳ���ͨ��������ɿ����ڱ��㴦���д�����ڴ�й©���⣬Ȼ���ٴ��׳��쳣���ѱ�����Ϣ����㴫��

```cpp
double division(int a, int b)
{
	if (b == 0)
	{
		string str("division by zero!");
		throw str;
	}

	return (double)a / (double)b;
}

void func()
{
	int* array = new int[10];
	try
	{
		int a, b;
		cin >> a >> b;
		cout << division(a, b) << endl;
	}
	catch (...)
	{
		// ��һ�β��� �����ڴ�й©
		cout << "delete[] arr" << endl;
		delete[] array;
		// �ٴ��׳� ����㴦��
		throw;
	}
	// ... other works
	cout << "delete[] arr" << endl;
	delete[] array;
}

int main()
{
	try
	{
		func();
	}
	catch (const string& str)
	{
		cout << str << endl;
	}
	return 0;
}
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220711202540.png)

&emsp;&emsp;����ʵ����������Ǿ���������ָ�봦��

## 3.3�쳣��ȫ

&emsp;&emsp;**���캯����ɶ���Ĺ���ͳ�ʼ������ò�Ҫ�ڹ��캯�����׳��쳣��������ܵ��¶���������û����ȫ��ʼ��**;
&emsp;&emsp;**����������Ҫ�����Դ��������ò�Ҫ�������������׳��쳣��������ܵ�����Դй©**(�ڴ�й©����
��δ�رյ�)
&emsp;&emsp;C++���쳣�����ᵼ����Դй©�����⣬������new��delete���׳����쳣�������ڴ�й©����lock��unlock֮���׳����쳣����������C++����ʹ��RAII������������⣬���ǻ�������ָ�����ｲ��RAII��

## 3.4 �쳣�淶

&emsp;&emsp;����������� ``throw(typeA, typeB, ...)``���Ը��ߺ���ʹ���ߣ�������������ܻ��׳�ʲô���͵��쳣��``throw()``��ʾ�Ҳ����׳��쳣��

&emsp;&emsp;�����Ⲣ����һ��ǿ�Ƶ����飨��ΪҪ����C���ԣ����쳣�淶��Ȼ�Ǻܺõ����飬������ʵ�����쳣�淶����ִ�С�

&emsp;&emsp;��C++11�У������˹ؼ��� ``noexcept``���ں�������ĩβ������������ߺ���ʹ����������������׳��쳣��

# �ġ��Զ����쳣��ϵ

&emsp;&emsp;ʵ��ʹ���кܶ๫˾�����Զ����Լ����쳣��ϵ���й淶���쳣������Ϊһ����Ŀ���������������쳣����ô���ĵ����߻�����û�취���ˣ�����ʵ���ж��ᶨ��һ�׼̳еĹ淶��ϵ����������׳��Ķ��Ǽ̳е���������󣬲���һ������Ϳ����ˣ����崦���쳣�������ö�̬���ƣ��ø������ĳ���麯���Ϳ���������

&emsp;&emsp;��������������һ��������������ͨ��ʹ�õ��쳣��ϵ��

```cpp
// ������������ͨ��ʹ�õ��쳣�̳���ϵ
class Exception
{
public:
    Exception(const string& errmsg, int id) : _errmsg(errmsg), _id(id) {}
protected:
    string _errmsg;
    int _id;
    // ...
};
// ���ݿ����
class SqlException : public Exception
{};
// ��������
class CacheException : public Exception
{};
// HTTP����
class HttpServerException : public Exception
{};
int main()
{
 try{
    // server.Start();
    // �׳����������������
 }
 catch (const Exception& e) // ���ﲶ�������Ϳ���
 {}
 catch (...)
 {
    cout << "Unkown Exception" << endl;
 }
     return 0;
}
```

&emsp;&emsp;�������������һ�£�������ϰ��

```cpp
// ������������ͨ��ʹ�õ��쳣�̳���ϵ
class Exception
{
public:
    Exception(const string& errmsg, int id) : _errmsg(errmsg), _id(id) {}
    string what() const
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
{};
// ��������
class CacheException : public Exception
{};
// HTTP����
class HttpServerException : public Exception
{
public:
    HttpServerException(const string& errmsg, int id, int state)
        : Exception(errmsg, id), _state(state) {}
protected:
    int _state;
};

void sqlwork()
{
    // ... do something
}

void cachework()
{
    // ... do sth.
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
    }
}

int main()
{
    Severstart();
    return 0;
}
```

&emsp;&emsp;�ټ��˵��̬��ȥ����һ�£�

```cpp
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
```

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220711213839.png)

&emsp;&emsp;��Ȼ���ױȴ�����ߵ���֪������ȥ�ˡ�

# �塢C++��׼����쳣��ϵ

```mermaid
graph LR
A[std::exception]-->B1[std::bad_alloc]
A-->B2[std::bad_cast]
A-->B3[std::bad_typeid]
A-->B4[std::bad_exception]
A-->B5[std::logic_error]
A-->B6[std::runtime_error]
B4-->C1[std::domain_error]
B4-->C2[std::invalid_argument]
B4-->C3[std::length_error]
B4-->C4[std::out_of_range]
B6-->D1[std::overflow_error]
B6-->D2[std::range_error]
B6-->D3[std::underflow_error]
```

| �쳣                  | ����                                                     |
| --------------------- | -------------------------------------------------------- |
| std::exception        | ���쳣������C++��׼���е��쳣�ĸ���                      |
| std::bad_alloc        | ���쳣����ͨ��new�׳�                                    |
| std::bad_cast         | ���쳣����ͨ��dynamic_cast�׳�                           |
| std::bad_exception    | ���ڴ���C++������Ԥ��֮����쳣�ǳ�����                  |
| std::bad_typeid       | ���쳣����ͨ��typeid�׳�                                 |
| std::logic_error      | �����Ͽ���ͨ����ȡ����������߼�����                   |
| std::domain_error     | ��ʹ����һ����Ч����ѧ��ʱ�����׳����쳣                 |
| std::invalid_argument | ��ʹ������Ч�Ĳ���ʱ�����׳����쳣                       |
| std::length_error     | ��������̫����std::stringʱ�����׳����쳣                |
| std::out_of_range     | �����±귶Χʱ���׳����쳣����vector��bitset��operator[] |
| std::runtime_error    | �����ϲ�����ͨ���Ķ���������Ĵ�����������ʱ����     |
| std::overflow_error   | ��������ѧ����ʱ�����׳����쳣                           |
| std::range_error      | �����Դ洢������Χ��ֵʱ�����׳����쳣                   |
| std::underflow_error  | ��������ѧ�����ʱ�����׳����쳣                         |

# �����쳣����ȱ��

## 6.1 C++�쳣���ŵ�

1. �쳣��������ˣ���ȴ�����ķ�ʽ��������׼ȷ��չʾ������ĸ�����Ϣ���������԰�����ջ���õ���Ϣ���������԰������õĶ�λ�����bug��
2. ���ش�����Ĵ�ͳ��ʽ�и��ܴ��������ǣ��ں����������У����ĺ��������˴�����ô���ǵò�㷵�ش������������õ�������������Ƚ������鷳��
3. �ܶ�ĵ������ⶼ�����쳣������boost��gtest��gmock�ȵȳ��õĿ⣬��ô����ʹ������Ҳ��Ҫʹ���쳣��
4. �ܶ���Կ�ܶ�ʹ���쳣�������ܸ��õ�ʹ�õ�Ԫ���ԵȽ��а׺еĲ��ԡ�
5. ���ֺ���ʹ���쳣���ô������繹�캯��û�з���ֵ��������ʹ�ô����뷽ʽ�������� ``T& operator[](size_t pos)``�����ĺ��������posԽ����ֻ��ʹ���쳣������ֹ������û�취ͨ������ֵ��ʾ����

## 6.2 C++�쳣��ȱ��

1. �쳣�ᵼ�³����ִ�������������ҷǳ��Ļ��ң�����������ʱ�������쳣�ͻ���������ᵼ�����Ǹ��ٵ���ʱ�Լ���������ʱ���Ƚ����ѣ������Ǻ���ʹ��goto��һ��������ʱ�����ܴ�ϵ�Ͳ�������ͣ�������ͳ������ˡ�
2. �쳣����һЩ���ܵĿ�������Ȼ���ִ�Ӳ���ٶȺܿ������£����Ӱ��������Բ��ơ�
3. C++û���������ջ��ƣ���Դ��Ҫ�Լ����������쳣�ǳ����׵����ڴ�й©���������쳣��ȫ���⡣�����Ҫʹ��RAII��������Դ�Ĺ������⡣ѧϰ�ɱ��ϸߡ�
4. C++��׼����쳣��ϵ����ò��ã����´�Ҹ��Զ�����Ե��쳣��ϵ���ǳ��Ļ��ҡ�
5. �쳣�����淶ʹ�ã��������������룬�������쳣����㲶����û��಻���ԡ������쳣�淶�����㣺һ���׳��쳣���Ͷ��̳���һ�����ࡣ���������Ƿ����쳣����ʲô�쳣����ʹ�� �쳣�淶func����throw();�ķ�ʽ�淶����

�ܽ᣺�쳣������ԣ������ڱף����Թ��������ǻ��ǹ���ʹ���쳣�ġ�����OO�����Ի����������쳣����
������Ҳ���Կ������Ǵ���������
