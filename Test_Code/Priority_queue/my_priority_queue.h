#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>
using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::swap;
using std::array;

template <class T>
struct Less
{
	bool operator()(const T& x, const T& y) const
	{
		return x < y;
	}
};

 // 特化
template <>
struct Less<int*>
{
	bool operator()(const int* x, const int* y) const
	{
		return *x < *y;
	}
};

template <class T>
struct Greater
{
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

template <class T, class Container = vector<T>, class Compare = Less<T> >
class priority_queue
{
public:
	// 用默认生成的构造去调用对应容器的默认构造函数即可
	priority_queue()
	{}
	template <class InputIterator>
	priority_queue(InputIterator first, InputIterator last)
		: _con(first, last)
	{
		// 倒着建堆 从第一个非叶子结点建
		int n = size();
		for (int i = (n - 1 - 1) / 2; i >= 0; --i)
		{
			adjust_down(i);
		}
	}
	void adjust_up(size_t child)
	{
		Compare cmp;
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			if (cmp(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
			}
			else
			{
				break;
			}
			child = parent;
			parent = (child - 1) / 2;
		}
	}

	void adjust_down(size_t parent)
	{
		size_t child = parent * 2 + 1;
		size_t n = size();
		Compare cmp;
		while (child < n)
		{
			if (child + 1 < n && cmp(_con[child], _con[child + 1])) ++child;
			// if (_con[child] > _con[parent])
			if (cmp(_con[parent], _con[child]))
			{
				swap(_con[parent], _con[child]);
			}
			else
			{
				break;
			}
			parent = child;
			child = parent * 2 + 1;
		}
	}
	const T& top()
	{
		return _con[0];
	}
	void push(const T& x)
	{
		_con.push_back(x);
		adjust_up(_con.size() - 1);
	}
	void pop()
	{
		assert(!_con.empty());
		swap(_con[0], _con[size() - 1]);
		_con.pop_back();
		adjust_down(0);
	}
	bool empty() const
	{
		return _con.empty();
	}
	size_t size() const
	{
		return _con.size();
	}
private:
	Container _con;
};