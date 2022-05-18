#ifndef __MYVECTOR__H__
#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
namespace lyq
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector(): _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			// 区间范围初始化 利用尾插
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector<T>& v)
			:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
			// 现代写法 复用区间构造函数
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		// 交换数据成员 
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		bool empty() const
		{
			return _start == _finish;
		}
		iterator begin()
		{
			return _start;
		}
		const_iterator begin() const
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator end() const
		{
			return _finish;
		}
		void reserve(int n)
		{
			if (n > capacity())
			{
				iterator tmp = new T[n];
				size_t sz = size();
				if (_start != nullptr)
				{
					for (int i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + sz;
				_end_of_storage = tmp + n;
			}
		}
		
		void resize(size_t n, const T& x = T())
		{
			size_t sz = size();
			size_t cp = capacity();
			if (n < sz)
			{
				_finish = _start + n;
			}
			else if (n < cp)
			{
				while (_finish != _start + n)
				{
					*_finish = x;
					++_finish;
				}
			}
			else if (n > cp)
			{
				reserve(n);
				while (_finish != _start + n)
				{
					*_finish = x;
					++_finish;
				}
			}
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(!empty());
			--_finish;
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			// st指向要移动的元素
			iterator st = _finish - 1;

			while (st != pos)
			{
				*(st + 1) = *st;
				--st;
			}
			*pos = x;
			++_finish;
			// 保证迭代器有效
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			// it指向待移动数据
			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			// 返回待删除元素后一个位置的迭代器
			return pos;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
	void test_vector1()
	{
		vector<int> a;
		for (int i = 1; i <= 4; ++i)
		{
			a.push_back(i);
		}
		vector<int>::iterator it = find(a.begin(), a.end(), 2);
		// it = a.erase(it);
		it = a.begin();
		while (it != a.end())
		{
			if (*it % 2 == 0)
			{
				it = a.erase(it);
			}
			else
			{
				++it;
			}
		}
		int sz = a.size();
		for (int i = 0; i < sz; ++i)
		{
			cout << a[i] << ' ';
		}
		/*cout << endl;
		a.resize(15);
		for (auto p : a)
		{
			cout << p << ' ';
		}*/
	}
}


#define __MYVECTOR__H__
#endif

