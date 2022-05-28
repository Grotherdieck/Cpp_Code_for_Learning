#pragma once
#include "HashTable.hpp"
namespace Router
{
	template <class K, class hash = std::hash<K>>
	class unordered_set
	{
		struct SetKeyofT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		// µü´úÆ÷ÄÃ³öÀ´
		typedef typename LinkHash::HashTable<K, K, SetKeyofT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}
		
		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.insert(key);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

		iterator find(const K& key)
		{
			return iterator(_ht.find(key), &_ht);
		}
	private:
		LinkHash::HashTable<K, K, SetKeyofT, hash> _ht;
	};
}
