#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <forward_list>
#include <utility>
using namespace std;

namespace CloseHash
{
	// ��ʶÿ��λ�õ�״̬
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

	// ȱʡ�Ĺ�ϣ
	template <class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			// ˳��Ѹ���ת�������� ��ΪC++ȡģ����ȡģ��������
			return key;
		}
	};

	// �ַ������ػ�
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
			size_t start = hf(key) % _tables.size();// ���vectorΪ�ս����ᷢ��/0����
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				if (_tables[index]._status == EXIST &&
					_tables[index]._kv.first == key) return &_tables[index];
				++i;
				// ����̽�� ����Ǵ��ھͼ���̽��
				//index = start + i;
				// ����̽��
				index = start + i * i;
				index %= _tables.size();
			}
			return nullptr;
		}
		bool insert(const pair<K, V>& kv)
		{
			HashFunc hf;
			// �ȿ����Ƿ����
			HashData<K, V>* ret = find(kv.first);
			if (ret) return false;
			// ���Ƹ�������
			// ��������ԽС ��ͻ����Խ�� Ч��Խ�� ���ǿռ��˷�Խ��
			// ���������´� ��ͻ����Խ�� Ч��Խ�� �ռ��˷�Խ��
			//if (10 * _n / _tables.size() > 7)
			if (_tables.size() == 0 || 10 * _n / 7 > _tables.size())
			{
				// ����
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				// �ɷ�ʽ
				//vector<HashData<K, V>> newTables;
				//newTables.resize(newSize);
				//// ����ԭ�� ��ԭ���е����ݰ�newSize����ӳ�䵽�±�
				//for (int i = 0; i < _tables.size(); ++i)
				//{

				//}
				//_tables.swap(newTables);

				// ֱ�ӿ�һ���µĴ�С�Ĺ�ϣ�� Ȼ������ͷ���� Ȼ�󽻻����ǵ�vector ��vector��swap
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
				// newHT�Լ�ȥ�����������ͷ���Դ�ͺ�
			}

			// ���ﲻ��ģcap ��Ϊ������Խsize����vector�Ŀռ� Ӱ��size��ͬʱ���ᱻ����
			size_t start = hf(kv.first) % _tables.size();
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				++i;
				// ����̽�� ����Ǵ��ھͼ���̽��
				//index = start + i;
				// ����̽��
				index = start + i * i;
				index %= _tables.size();
			}
			_tables[index]._kv = kv;
			_tables[index]._status = EXIST;
			++_n;// ��Ч����+1
			return true;
		}
	private:
		vector<HashData<K, V>> _tables;
		size_t _n = 0;// ��Ч���ݸ���
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
		htf.insert(make_pair("sort", "����"));
		htf.insert(make_pair("map", "��ͼ"));
		htf.insert(make_pair("stl", "��׼ģ���"));
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
	// �������ù�ϣ�� ��ϣ�������˹�ϣ�� �����˻������õ�����
	// ��һ��ǰ������
	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable;
	template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc = hash<K>>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, Ref, Ptr, T, KeyOfT, HashFunc> self;
		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;// ��һ��ָ���ϣ���ָ��

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

		// operator++ ǰ���һ����ϣ���ָ�����Ϊ�����
		// ���������ĳ��Ͱʱ��һ��Ϊ��ʱ ��ôҪ��������һ����Ϊ�յ�Ͱ
		// ������Ҫ��һ��ָ���ϣ���ָ�� �������ǰλ���ǵڼ���Ͱ ��������
		self& operator++()
		{
			if (_node->_next != nullptr)
			{
				// Ͱû���� ����һ��λ��
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
		// �ѵ�����Ū����Ԫ �����Ϳ����ڵ�������ͷ����_tables
		template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, HashFunc> self;
	public:
		typedef __HTIterator<K, T&, T*, T, KeyOfT, HashFunc> iterator;
		// ��Ϊд�˿������캯�� ���������������ɹ����� ���ǵ��Լ�д
		// Ĭ�Ϲ�������ʲô����д�߳�ʼ���б���԰��Զ������͵���Ĭ�Ϲ��캯����
		//HashTable() {}
		// C++11
		HashTable() = default;// ��ʾָ��������ȥ����Ĭ�ϵĹ��캯��
		// �������캯��
		HashTable(const HashTable<K, T, KeyOfT, HashFunc>& ht)
		{
			// Ҫ������
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

		// ��ֵ
		self& operator=(self ht)
		{
			// �ִ�д��
			_n = ht._n;
			_tables.swap(ht._tables);
			return *this;
		}

		// ��������
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
			// ����
			// �������ӵ���1ʱ����
			HashFunc hf;
			if (_n == _tables.size())
			{
				_n = 0;
				int newSize = GetnextPrime(_tables.size());
				vector<Node*> newHashTable;
				newHashTable.resize(newSize);
				// ���ﲻ����ʹ�ø���Insert �����Լ�����ԭ��ʵ�� ԭ��
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
			// ͷ��
			++_n;// ���Ӹ�������
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
		int _n = 0;// ���ڼ��㸺������
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
		htf.insert(make_pair("sort", "����"));
		htf.insert(make_pair("map", "��ͼ"));
		htf.insert(make_pair("stl", "��׼ģ���"));
		cout << htf.find("sort") << endl;
		htf.Erase("sort");
		cout << htf.find("sort") << endl;
	}*/
}

