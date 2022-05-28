#pragma once
#include "HashTable.hpp"
namespace Router
{
	// 在外层指定哈希的模板参数
	template <class K, class V, class hash = std::hash<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.insert(kv);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

		iterator find(const K& key)
		{
			return iterator(_ht.find(key), &(_ht));
		}
		V& operator[](const K& key)
		{
			auto it = _ht.insert(make_pair(key, V()));
			return (it.first)->second;
		}
	private:
		LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash> _ht;
	};
}
