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
		// �ַ����ĵ���������ָ��
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
		// ++ -- *�����ý���ԭ��ָ���++ -- *�Ϳ����� �����Լ�������
		
		// Ĭ�Ϲ��캯�� ��new char[1]��Ϊ����delete[]ƥ��
		// Ĭ��Ӧ�ÿ���һ��ֻ��һ��'\0'���ַ�����
		/*string()
			: _str(new char[1]), _size(0), _capacity(0)
		{
			_str[0] = '\0';
		}*/
		/*����ʾ��
		string() : _str(nullptr), _size(0), _capacity(0)
		{}*/

		// ���� ����str�ĳ��ȿ��ռ�
		// ע���ʼ���б��˳���ǰ�����˳��
		// ʹ��ȫȱʡ�䵱Ĭ�Ϲ��캯��
		string(const char* str = "") :
			_size(strlen(str)), _capacity(_size)
		// ""��ͷĬ����'\0' �����ȼ�Ϊ_size(0) _capacity(0)
		{
			// ���ÿ���һ������Ϊ1������
			_str = new char[_capacity + 1];
			// ����strcpyֱ�ӿ�����_str
			// ��'\0'��������
			strcpy(_str, str);
		}
		// �������� ������Ĭ�ϵ��ֽ��򿽱� ���򱨴���
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
		// ����
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
		/*string& operator=(const string& s)
		{
			// �Լ���ֵ���Լ��Ͳ�Ҫ�ظ��� 
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
		//		/*tmp���Ҹ���s������ ���ҽ���_str��tmp._str
		//		��˳��tmp������ʱ����ұ����Ŀռ����*/
		//		_size = s._size;
		//		_capacity = s._capacity;
		//
		//	}
		//  return *this;
		//}

		// �����ĸ�ֵ����������ִ�д��
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

		// ��������size�����ܸ���� 
		// ��ͨ�����const������ò�����ʲô����
		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}
		// ��ͨ�������
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		// const�������,ͨ��const�����thisָ��ĳ��Ի�ƥ�䵽�������
		const char& operator[](size_t i) const
		{
			assert(i < _size);
			return _str[i];
		}

		// ���ݺ���
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				// ������100 �ٸ�'\0'�࿪һ��
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		// ��һ���ַ�
		void push_back(const char ch)
		{
			/*if (_size == _capacity)
			{
				// ���� ����һ���ַ���2������
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';*/
			insert(_size, ch);
		}
		// ��һ���ַ���
		void append(const char* s)
		{
			//size_t len = strlen(s);
			//if (_size + len > _capacity)
			//{
			//	reserve(_size + len);
			//}
			///*ֱ�������Ҫ������λ�� ���Ǳ����ַ�����'\0'λ��*/
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
				// �±�Ϊn��λ�ò���'\0'
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity) reserve(n);
				// ����memset ֱ�Ӱ�_size������ַ���ֵΪch ��ֵn - _size��
				memset(_str + _size, ch, n - _size);
				_size = n;
				_str[_size] = '\0';
			}
		}

		// ���
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
			/*���next����*/
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
			/*ƥ��*/
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
		// posλ�ò����ַ�
		string& insert(size_t pos, char c)
		{
			assert(pos <= _size);
			/*��pos�±꼰�Ժ������Ųһ��λ�� Ϊ�˱��⸲�Ǵ�β�Ϳ�ʼŲ��*/
			if (_capacity == _size)
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			/*����ط���Ҫֱ�����޷����� 
			���ܻ�����޷��������з������Ƚ�ʱ�����������ͷ��ʱ�޷������޷��䵽-1������*/
			size_t end = _size + 1;
			// ������ܻ����ͷ��pos����0 end������Ϊ�޷�����һֱ���ڵ���0��ѭ��
			/*while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}*/
			// ���Է��ִ���ͳ��ڴ��ڵ���0�� ���Ǹɴ���endָ��Ų����λ�� ����end������λ�þ���pos
			// ������end > pos ��Ϊ>����
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = c;
			_size++;
			return *this;
		}
		// posλ�ò����ַ���
		string& insert(size_t pos, const char* s)
		{
			assert(pos <= _size);
			size_t len = strlen(s);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = _size + len;
			/*Ų��posλ�ü���������ַ�*/
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
			/*���ɾ����*/
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
		// ����
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
	// ����cin.get()������ȡÿ���ַ� 
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
		// ȱ�� ������strcmp��
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
		// ���j��ͷ�� ��ôҪô����� Ҫô��s2���� ��Щ�����������s1 < s2 ����false
		// �������i��ͷ��jû��ͷ s1�ĳ��ȶ� s1 < s2
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

