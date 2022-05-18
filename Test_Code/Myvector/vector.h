#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;
namespace lyq
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector():_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{}
		
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _finish;
		}
		const_iterator end() const
		{
			return _finish;
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				iterator tmp = new T[n];
				size_t sz = size();
				if (_start != nullptr)
				{
					/*memcpy(tmp, _start, sizeof(T) * sz);*/
					for (int i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}
				}
				delete[] _start;
				_start = tmp;
				_finish = tmp + sz;
				_end_of_storage = tmp + n;
			}
		}
		void resize(size_t n, const T& x = T())
		{
			size_t sz = size();
			if (n < sz)
			{
				_finish = _start + n;
			}
			else if (n < capacity())
			{
				while (_finish != _start + n)
				{
					*_finish = x;
					++_finish;
				}
			}
			else if (n > capacity())
			{
				reserve(n);
				while (_finish != _start + n)
				{
					*_finish = x;
					++_finish;
				}
			}
		}
		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				//size_t newcapacity = (capacity() == 0 ? 4 : 2 * capacity());
				//iterator tmp = new T[newcapacity];
				//// 不空则需要拷贝
				//if (_start != nullptr)
				//{
				//	memcpy(tmp, _start, sizeof(T) * size());
				//}
				//_finish = tmp + size();
				//delete[] _start;
				//_start = tmp;
				//_end_of_storage = tmp + newcapacity;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = x;
			++_finish;
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
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
	void test_vector1()
	{
		vector<int> a;
		for (int i = 1; i <= 5; ++i)
		{
			a.push_back(i);
		}
		a.resize(10);
		for (auto e : a)
		{
			cout << e << ' ';
		}
	}
}

#endif