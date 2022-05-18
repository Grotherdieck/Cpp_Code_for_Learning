#pragma once
#include <iostream>
#include <deque>
using std::cin;
using std::cout;
using std::endl;
using std::deque;

//   ≈‰∆˜ƒ£ Ω
template <class T, class Container = deque<T>>
class stack
{
public:
	void push(const T& x)
	{
		_con.push_back(x);
	}
	void pop()
	{
		_con.pop_back();
	}
	const T& top() const
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