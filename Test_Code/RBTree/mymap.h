#pragma once
#include "RBTree.h"
namespace Router
{
	template <class K, class V>
	class map
	{
	public:
		// 指定T内哪个是关键字
		struct MapKeyofT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		typedef typename RBTree<K, pair<K, V>, MapKeyofT>::iterator iterator;
		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		iterator find(const K& key)
		{
			return _t.find(key);
		}
		// operator[]
		V& operator[](const K& key)
		{
			auto it = _t.Insert(make_pair(key, V()));
			return (it.first)->second;
		}
	private:
		// 关键字 树中结点值
		RBTree<K, pair<K, V>, MapKeyofT> _t;
	};
	void test_map()
	{
		map<int, int> mymap;
		mymap.insert(make_pair(1, 1));
		mymap.insert(make_pair(3, 3));
		mymap.insert(make_pair(-5, -5));
		mymap.insert(make_pair(-8, -8)); 
		mymap.insert(make_pair(9, 9));
		mymap[2] = 3;
		mymap[999] = -2;
		for (auto& p : mymap)
		{
			cout << p.first << ':' << p.second << endl;
		}
	}
}