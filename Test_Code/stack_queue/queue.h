#pragma once
#include "stack.h"

template <class T, class Container = deque<T>>
class queue
{
public:
	void push(const T& x)
	{
		_con.push_back(x);
	}
	void pop()
	{
		_con.pop_front();
	}
	const T& front() const
	{
		return _con.front();
	}
	const T& back() const
	{
		return _con.back();
	}
	bool empty()
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