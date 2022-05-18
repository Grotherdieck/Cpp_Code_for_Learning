#pragma once
#include "RBTree.h"
namespace Router
{
	template <class T>
	class set
	{
	public:
		struct SetKeyofT
		{
			const T& operator()(const T& k)
			{
				return k;
			}
		};
		typedef typename RBTree<T, T, SetKeyofT>::iterator iterator;
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		bool insert(const T& key)
		{
			return _t.Insert(key);
		}
	private:
		RBTree<T, T, SetKeyofT> _t;
	};
	void test_set()
	{
		set<int> myset;
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		for (auto c : a) myset.insert(c);
		auto it = myset.begin();
		while (it != myset.end())
		{
			cout << *it << endl;
			++it;
		}
	}
}