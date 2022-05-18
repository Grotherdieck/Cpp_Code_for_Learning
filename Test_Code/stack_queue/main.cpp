#define  _CRT_SECURE_NO_WARNINGS 1
#include "stack.h"
#include "queue.h"
#include <list>
#include <vector>
#include <forward_list>
using std::list;
using std::vector;
using std::forward_list;

int main()
{
	queue<int, list<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	while (!st.empty())
	{
		cout << st.front() << ' ';
		st.pop();
	}
	return 0;
}