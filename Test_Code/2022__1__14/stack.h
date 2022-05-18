#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Stack
{
public:
	void Init();
	void Push();
	void Pop();
	virtual int top();
	
private:
	int* _a;
	int _top;
	int _capacity;
};
inline int Stack::top()
{
	return _a[_top - 1];
}