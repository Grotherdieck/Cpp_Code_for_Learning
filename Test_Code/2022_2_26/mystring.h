#pragma once
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;
namespace Router
{
	class string
	{
	public:
		// 字符串的迭代器就是指针
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		// ++ -- *解引用借助原生指针的++ -- *就可以了 不必自己再重载
		
		// 默认构造函数 用new char[1]是为了与delete[]匹配
		// 默认应该开成一个只有一个'\0'的字符串，
		/*string()
			: _str(new char[1]), _size(0), _capacity(0)
		{
			_str[0] = '\0';
		}*/
		/*错误示范
		string() : _str(nullptr), _size(0), _capacity(0)
		{}*/

		// 构造 利用str的长度开空间
		// 注意初始化列表的顺序是按声明顺序
		// 使用全缺省充当默认构造函数
		string(const char* str = "") :
			_size(strlen(str)), _capacity(_size)
		// ""里头默认有'\0' 后续等价为_size(0) _capacity(0)
		{
			// 正好开了一个长度为1的数组
			_str = new char[_capacity + 1];
			// 利用strcpy直接拷贝到_str
			// 把'\0'拷贝过来
			strcpy(_str, str);
		}
		// 拷贝构造 不能用默认的字节序拷贝 否则报错捏
		/*string(const string& s)
			: _size(s._size), _capacity(s._capacity)
		{
			_str = new char[_capacity];
			strcpy(_str, s._str);
		}*/
		string(const string& s)
			:_str(nullptr), _size(0), _capacity(0)
		{
			string tmp(s._str);
			swap(tmp);
		}
		// 析构
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
		/*string& operator=(const string& s)
		{
			// 自己赋值给自己就不要重复了 
			if (this != &s)
			{
				char* tmp = new char[strlen(s._str) + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this;
		}*/
		//string& operator=(const string& s)
		//{
		//	if (&s != this)
		//	{
		//		string tmp(s);
		//		swap(_str, tmp._str);
		//		/*tmp帮我复制s的内容 并且交换_str和tmp._str
		//		后顺便tmp析构的时候帮我本来的空间回收*/
		//		_size = s._size;
		//		_capacity = s._capacity;
		//
		//	}
		//  return *this;
		//}

		// 更简洁的赋值运算符重载现代写法
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		const char* c_str() const
		{
			return _str;
		}

		// 反正调用size不可能给你改 
		// 普通对象和const对象调用不会有什么区别
		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}
		// 普通对象遍历
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		// const对象遍历,通过const对象的this指针的常性会匹配到这个函数
		const char& operator[](size_t i) const
		{
			assert(i < _size);
			return _str[i];
		}

		// 扩容函数
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				// 容量到100 再给'\0'多开一个
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		// 增一个字符
		void push_back(const char ch)
		{
			/*if (_size == _capacity)
			{
				// 增容 插入一个字符扩2倍即可
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';*/
			insert(_size, ch);
		}
		// 增一个字符串
		void append(const char* s)
		{
			//size_t len = strlen(s);
			//if (_size + len > _capacity)
			//{
			//	reserve(_size + len);
			//}
			///*直接算好了要考到的位置 就是本来字符串的'\0'位置*/
			//strcpy(_str + _size, s);
			insert(_size, s);
		}
		// +=
		string& operator+=(const char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* s)
		{
			append(s);
			return *this;
		}

		void resize(size_t n, char ch = '\0')
		{
			if (n <= _size)
			{
				// 下标为n的位置补上'\0'
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity) reserve(n);
				// 利用memset 直接把_size往后的字符赋值为ch 赋值n - _size个
				memset(_str + _size, ch, n - _size);
				_size = n;
				_str[_size] = '\0';
			}
		}

		// 清空
		void clear()
		{
			_size = 0;
			_str[0] = '\0';
		}

		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);
			for (size_t i = 0; i < _size; ++i)
				if (_str[i] == ch) return i;
			return npos;
		}

		/*size_t find(const char* s, size_t pos = 0)
		{
			const char* p = strstr(_str + pos, s);
			if (p == nullptr) return npos;
			return p - _str;
		}*/

		size_t find(const char* s, size_t pos = 0) const
		{
			assert(pos < _size);
			int n = strlen(s);
			/*获得next数组*/
			int* next = new int[10000];
			next[0] = -1;
			if (n > 1) next[1] = 0;
			int k = 0, i = 2;
			while (i < n)
			{
				while (k != -1 && s[k] != s[i - 1]) k = next[k];
				next[i] = k + 1;
				++i;
				++k;
			}
			/*匹配*/
			i = pos;
			int j = 0;
			while (i < _size || j < n)
			{
				while (j != -1 && _str[i] != s[j]) j = next[j];
				++i;
				++j;
			}
			delete[] next;
			if (j == n) return i - j;
			return npos;
		}
		// pos位置插入字符
		string& insert(size_t pos, char c)
		{
			assert(pos <= _size);
			/*把pos下标及以后的往后挪一个位置 为了避免覆盖从尾巴开始挪动*/
			if (_capacity == _size)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			/*这个地方不要直接用无符号数 
			可能会出现无符号数和有符号数比较时的提升问题和头插时无符号数无法变到-1的问题*/
			size_t end = _size + 1;
			// 这里可能会出现头插pos等于0 end被提升为无符号数一直大于等于0死循环
			/*while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}*/
			// 可以发现错误就出在大于等于0上 我们干脆让end指向被挪动的位置 这样end结束是位置就是pos
			// 不满足end > pos 改为>即可
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			_size++;
			return *this;
		}
		// pos位置插入字符串
		string& insert(size_t pos, const char* s)
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = _size + len;
			/*挪动pos位置及其往后的字符*/
			while (end + 1 - len > pos)
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, s, len);
			_size += len;
			return *this;
		}
		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			/*如果删完了*/
			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
			}
			return *this;
		}
		// relation operators
		/*bool operator<(const string& s) const
		{
			return strcmp(_str, s._str) == -1;
		}
		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) == 1;
		}
		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}
		bool operator>=(const string& s) const
		{
			return !(*this < s);
		}
		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}*/
		// 输入
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};
	const size_t string::npos = -1;
	ostream& operator<<(ostream& out, const Router::string& s)
	{
		int sz = s.size();
		for (int i = 0; i < sz; ++i)
		{
			out << s[i];
		}
		return out;
	}
	// 利用cin.get()函数获取每个字符 
	istream& operator>>(istream& in, Router::string& s)
	{
		s.clear();
		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}


	bool operator<(const string& s1, const string& s2)
	{
		// 缺点 不能用strcmp了
		size_t i = 0, j = 0;
		size_t n1 = s1.size(), n2 = s2.size();
		while (i < n1 && j < n2)
		{
			if (s1[i] < s2[j]) return true;
			else if (s1[i] > s2[j]) return false;
			else
			{
				i++;
				j++;
			}
		}
		// 如果j到头了 那么要么是相等 要么是s2更短 这些情况都不满足s1 < s2 都是false
		// 否则就是i到头了j没到头 s1的长度短 s1 < s2
		return j == n2 ? false : true;
	}
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}
	bool operator>(const string& s1, const string& s2)
	{
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return !(s1 < s2);
	}
}

