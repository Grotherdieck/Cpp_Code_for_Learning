#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
#include <utility>
using namespace std;

namespace CloseHash
{
	// 标识每个位置的状态
	enum Status
	{
		EXIST,
		EMPTY,
		DELETE
	};

	template <class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		Status _status = EMPTY;
	};

	// 缺省的哈希
	template <class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			// 顺便把负数转成整数了 因为C++取模负数取模出来负数
			return key;
		}
	};

	// 字符串的特化
	template<>
	struct Hash<string>
	{
		size_t operator()(const string& str)
		{
			size_t ret = 0;
			for (char ch : str) ret *= 31, ret += ch;
			return ret;
		}
	};



	template <class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{
	public:
		bool Erase(const K& key)
		{
			HashData<K, V>* ret = find(key);
			if (ret == nullptr) return false;
			ret->_status = DELETE;
			--_n;
			return true;
		}
		HashData<K, V>* find(const K& key)
		{
			HashFunc hf;
			if (_tables.size() == 0) return nullptr;
			size_t start = hf(key) % _tables.size();// 如果vector为空进来会发生/0错误
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				if (_tables[index]._status == EXIST &&
					_tables[index]._kv.first == key) return &_tables[index];
				++i;
				// 线性探测 如果是存在就继续探测
				//index = start + i;
				// 二次探测
				index = start + i * i;
				index %= _tables.size();
			}
			return nullptr;
		}
		bool insert(const pair<K, V>& kv)
		{
			HashFunc hf;
			// 先看看是否存在
			HashData<K, V>* ret = find(kv.first);
			if (ret) return false;
			// 控制负载因子
			// 负载因子越小 冲突概率越低 效率越高 但是空间浪费越多
			// 负载因子月大 冲突概率越大 效率越低 空间浪费越少
			//if (10 * _n / _tables.size() > 7)
			if (_tables.size() == 0 || 10 * _n / 7 > _tables.size())
			{
				// 扩容
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				// 旧方式
				//vector<HashData<K, V>> newTables;
				//newTables.resize(newSize);
				//// 遍历原表 把原表中的数据按newSize重新映射到新表
				//for (int i = 0; i < _tables.size(); ++i)
				//{

				//}
				//_tables.swap(newTables);

				// 直接开一个新的大小的哈希表 然后往里头插入 然后交换他们的vector 用vector的swap
				HashTable<K, V, HashFunc> newHT;
				newHT._tables.resize(newSize);
				for (int i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._status == EXIST)
					{
						newHT.insert(_tables[i]._kv);
					}
				}
				_tables.swap(newHT._tables);
				// newHT自己去走析构函数释放资源就好
			}

			// 这里不能模cap 因为这样会越size访问vector的空间 影响size的同时还会被拿下
			size_t start = hf(kv.first) % _tables.size();
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				++i;
				// 线性探测 如果是存在就继续探测
				//index = start + i;
				// 二次探测
				index = start + i * i;
				index %= _tables.size();
			}
			_tables[index]._kv = kv;
			_tables[index]._status = EXIST;
			++_n;// 有效数字+1
			return true;
		}
	private:
		vector<HashData<K, V>> _tables;
		size_t _n = 0;// 有效数据个数
	};

	void test_hash1()
	{
		HashTable<int, int, Hash<int>> ht;
		int a[] = { 2, 3, 12, -4, -5, 6, 9 , 7, 11, 29, 37, 47, 55 };
		for (auto e : a)
		{
			ht.insert(make_pair(e, e));
		}
		cout << ht.find(12) << endl;
		ht.Erase(12);
		cout << ht.find(12) << endl;
	}

	void test_hash2()
	{
		HashTable<string, string> htf;
		htf.insert(make_pair("sort", "排序"));
		htf.insert(make_pair("map", "地图"));
		htf.insert(make_pair("stl", "标准模板库"));
	}
}

namespace LinkHash
{
	/*template <class K, class V>
	struct HashData
	{
		forward_list<pair<K, V>> list;
	};*/
	template <class K, class V>
	struct HashNode
	{
		pair<K, V> _val;
		HashNode<K, V>* _next;
		HashNode(const pair<K, V>& val) : _val(val), _next(nullptr) {}
	};
	template <class K, class V, class HashFunc = hash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		bool insert(const pair<K, V>& kv)
		{
			Node* it = find(kv.first);
			if (it != nullptr) return false;
			// 增容
			// 负载因子等于1时扩容
			HashFunc hf;
			if (_n == _tables.size())
			{
				_n = 0;
				int newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
				vector<Node*> newHashTable;
				newHashTable.resize(newSize);
				// 这里不建议使用复用Insert 建议自己遍历原表实现 原因？
				for (int i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur != nullptr)
					{
						Node* next = cur->_next;
						int index = hf(cur->_val.first) % newHashTable.size();
						cur->_next = newHashTable[index];
						newHashTable[index] = cur;
						++_n;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newHashTable);
			}
			size_t index = hf(kv.first) % _tables.size();
			// 头插
			++_n;// 增加负载因子
			Node* newnode = new Node(kv);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			return true;
		}
		Node* find(const K& key)
		{
			if (_n == 0) return nullptr;
			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur != nullptr && cur->_val.first != key) cur = cur->_next;
			return cur;
		}
		bool Erase(const K& key)
		{
			Node* del = find(key);
			if (del == nullptr) return false;
			--_n;
			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			if (cur == del)
			{
				_tables[index] = cur->_next;
				delete del;
				return true;
			}
			else
			{
				while (cur->_next != del) cur = cur->_next;
				cur->_next = del->_next;
				delete del;
				return true;
			}
		}
	private:
		vector<Node*> _tables;
		int _n = 0;// 用于计算负载因子
	};
	void test_hash1()
	{
		HashTable<int, int> ht;
		int a[] = { 2, 3, 12, -4, -5, 6, 9 , 7, 11, 29, 37, 47, 55 };
		for (auto e : a)
		{
			ht.insert(make_pair(e, e));
		}
		cout << ht.find(12) << endl;
		ht.Erase(12);
		cout << ht.find(12) << endl;
	}

	void test_hash2()
	{
		HashTable<string, string> htf;
		htf.insert(make_pair("sort", "排序"));
		htf.insert(make_pair("map", "地图"));
		htf.insert(make_pair("stl", "标准模板库"));
		cout << htf.find("sort") << endl;
		htf.Erase("sort");
		cout << htf.find("sort") << endl;
	}
}

