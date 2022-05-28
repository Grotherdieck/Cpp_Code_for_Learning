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
	template <class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data) : _data(data), _next(nullptr) {}
	};
	// 迭代器用哈希表 哈希表定义用了哈希表 出现了互相引用的问题
	// 加一个前置声明
	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable;
	template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc = hash<K>>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, Ref, Ptr, T, KeyOfT, HashFunc> self;
		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;// 存一个指向哈希表的指针

		__HTIterator(Node* node, HashTable<K, T, KeyOfT, HashFunc>* pht) : _node(node), _pht(pht) 
		{}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &(_node->_data);
		}

		// operator++ 前面存一个哈希表的指针就是为了这个
		// 这样如果在某个桶时下一个为空时 那么要往下找下一个不为空的桶
		// 所以需要用一个指向哈希表的指针 来算出当前位置是第几个桶 好往后走
		self& operator++()
		{
			if (_node->_next != nullptr)
			{
				// 桶没走完 走下一个位置
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				HashFunc hf;
				int index = hf(kot(_node->_data)) % (_pht->_tables.size());
				++index;
				while (index < _pht->_tables.size() && _pht->_tables[index] == nullptr)
				{
					++index;
				}
				if (index == _pht->_tables.size())
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[index];
				}
			}
			return *this;
		}
		self operator++(int)
		{
			self ans = *this;
			++(*this);
			return ans;
		}
		bool operator==(const self& it)
		{
			return it._node == _node && it._pht == _pht;
		}
		bool operator!=(const self& it)
		{
			return !(*this == it);
		}
	};
	template <class K, class T, class KeyOfT, class HashFunc = hash<K>>
	class HashTable
	{
		// 把迭代器弄成友元 这样就可以在迭代器里头访问_tables
		template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, HashFunc> self;
	public:
		typedef __HTIterator<K, T&, T*, T, KeyOfT, HashFunc> iterator;
		// 因为写了拷贝构造函数 编译器不会再生成构造了 我们得自己写
		// 默认构造我们什么都不写走初始化列表可以把自定义类型调用默认构造函数了
		//HashTable() {}
		// C++11
		HashTable() = default;// 显示指定编译器去生成默认的构造函数
		// 拷贝构造函数
		HashTable(const HashTable<K, T, KeyOfT, HashFunc>& ht)
		{
			// 要完成深拷贝
			_tables.resize(ht._tables.size());
			for (int i = 0; i < _tables.size(); ++i)
			{
				Node* cur = ht._tables[i];
				while (cur != nullptr)
				{
					Node* newnode = new Node(cur->_data);
					newnode->_next = _tables[i];
					_tables[i] = newnode;
					cur = cur->_next;
				}
			}
		}

		// 赋值
		self& operator=(self ht)
		{
			// 现代写法
			_n = ht._n;
			_tables.swap(ht._tables);
			return *this;
		}

		// 析构函数
		~HashTable()
		{
			for (int i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur != nullptr)
				{
					Node* ne = cur->_next;
					delete cur;
					cur = ne;
				}
				_tables[i] = nullptr;
			}
		}

		iterator begin()
		{
			int index = 0;
			for (index = 0; index < _tables.size(); ++index)
			{
				if (_tables[index])
				{
					return iterator(_tables[index], this);
				}
			}
			return end();
			
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
		pair<iterator, bool> insert(const T& kv)
		{
			KeyOfT kot;
			Node* it = find(kot(kv));
			if (it != nullptr) return make_pair(iterator(it, this), false);
			// 增容
			// 负载因子等于1时扩容
			HashFunc hf;
			if (_n == _tables.size())
			{
				_n = 0;
				int newSize = GetnextPrime(_tables.size());
				vector<Node*> newHashTable;
				newHashTable.resize(newSize);
				// 这里不建议使用复用Insert 建议自己遍历原表实现 原因？
				for (int i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur != nullptr)
					{
						Node* next = cur->_next;
						int index = hf(kot(cur->_data)) % newHashTable.size();
						cur->_next = newHashTable[index];
						newHashTable[index] = cur;
						++_n;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newHashTable);
			}
			size_t index = hf(kot(kv)) % _tables.size();
			// 头插
			++_n;// 增加负载因子
			Node* newnode = new Node(kv);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			// return true;
			return make_pair(iterator(newnode, this), true);
		}
		Node* find(const K& key)
		{
			if (_n == 0) return nullptr;
			HashFunc hf;
			KeyOfT kot;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur != nullptr && kot(cur->_data) != key) cur = cur->_next;
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
		size_t GetnextPrime(size_t num)
		{
			static const unsigned long __stl_prime_list[28] =
			{
			  53,         97,         193,       389,       769,
			  1543,       3079,       6151,      12289,     24593,
			  49157,      98317,      196613,    393241,    786433,
			  1572869,    3145739,    6291469,   12582917,  25165843,
			  50331653,   100663319,  201326611, 402653189, 805306457,
			  1610612741, 3221225473, 4294967291
			};
			for (int i = 0; i < 28; ++i)
			{
				if (__stl_prime_list[i] > num) return __stl_prime_list[i];
			}
		}
		vector<Node*> _tables;
		int _n = 0;// 用于计算负载因子
	};
	/*void test_hash1()
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
	}*/
}

