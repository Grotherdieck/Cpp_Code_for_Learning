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
			// ����
			// �������ӵ���1ʱ����
			HashFunc hf;
			if (_n == _tables.size())
			{
				_n = 0;
				int newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
				vector<Node*> newHashTable;
				newHashTable.resize(newSize);
				// ���ﲻ����ʹ�ø���Insert �����Լ�����ԭ��ʵ�� ԭ��
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
			// ͷ��
			++_n;// ���Ӹ�������
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
		int _n = 0;// ���ڼ��㸺������
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
		htf.insert(make_pair("sort", "����"));
		htf.insert(make_pair("map", "��ͼ"));
		htf.insert(make_pair("stl", "��׼ģ���"));
		cout << htf.find("sort") << endl;
		htf.Erase("sort");
		cout << htf.find("sort") << endl;
	}
}

