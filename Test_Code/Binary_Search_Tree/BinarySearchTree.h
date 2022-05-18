#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::swap;
using std::to_string;
using std::vector;

// ���
template <class K>
struct BSTNode
{
	BSTNode(const K& key = K())
		: _key(key), _left(nullptr), _right(nullptr)
	{}
	K _key;
	BSTNode<K>* _left;
	BSTNode<K>* _right;
};

// ��

template <class K>
class BSTree
{
public:
	typedef BSTNode<K> Node;
	BSTree()
		: _root(nullptr)
	{}
	bool insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root, * parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else return false;
		}
		if (parent->_key > key) parent->_left = new Node(key);
		else parent->_right = new Node(key);
		return true;
	}
	void Inorder() const
	{
		_Inorder(_root);
		return;
	}
	

	// �ݹ����
	bool insertR(const K& key)
	{
		return _insertR(_root, key);
	}
	// �ݹ����
	Node* findR(const K& key)
	{
		return _findR(_root, key);
	}
	// �ݹ�ɾ��
	bool eraseR(const K& key)
	{
		return _eraseR(_root, key);
	}
	// ��ͨ����
	Node* find(const K& key) const
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key == key) return cur;
			else if (cur->_key > key) cur = cur->_left;
			else cur = cur->_right;
		}
		return nullptr;
	}
	// ��ͨɾ��
	bool erase(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				// �ҵ��� ׼��ɾ��
				if (cur->_left == nullptr)
				{
					// ���и���Ϊ�յ���� ��ʱ��Ҫ�޸ĸ�
					if (parent == nullptr)
					{
						_root = cur->_right;
					}
					else
					{
						// �����ײ�Ϊ�� ��������Ǹ��׵�λ�����ж���Ҫ�������׵Ļ�����ɶ
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
					cur = nullptr;
					return true;
				}
				else if (cur->_right == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
					cur = nullptr;
					return true;
				}
				else
				{
					// ���Ҷ���Ϊ�� �滻��ɾ��
					// ��������������������
					Node* p = cur;// Ϊ��ɾ�������㱣�������ĸ���
					Node* rightmaxleft = cur->_right;
					while (rightmaxleft->_left != nullptr)
					{
						p = rightmaxleft;
						rightmaxleft = rightmaxleft->_left;
					}
					// swap(rightmaxleft->_key, cur->_key);
					// cur�����ݱ����ǳ�_key
					cur->_key = rightmaxleft->_key;
					// ���p->_right�͵���rightmaxleft
					// ��ô˵��p��û�� ��ʱ��Ҫ��p->_right����rightmaxleft->_right
					if (p->_right == rightmaxleft)
					{
						p->_right = rightmaxleft->_right;
					}
					// ���� Ҫ��p->_left����rightmaxleft��_right
					else
					{
						p->_left = rightmaxleft->_right;
					}
					delete rightmaxleft;
					rightmaxleft = nullptr;
					return true;
				}
			}
		}
		return false;
	}
private:
	void _Inorder(Node* root) const
	{
		if (root == nullptr) return;
		_Inorder(root->_left);
		cout << root->_key << ' ';
		_Inorder(root->_right);
	}
	// ����ݹ��Ӻ���
	bool _insertR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key > key)
		{
			return _insertR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _insertR(root->_right, key);
		}
		else return false;
	}
	// �ݹ�����Ӻ���
	Node* _findR(Node* root, const K& key)
	{
		if (root == nullptr) return nullptr;
		if (root->_key == key) return root;
		else if (root->_key > key) return _findR(root->_left, key);
		else return _findR(root->_right, key);
	}
	// �ݹ�ɾ��
	bool _eraseR(Node*& root, const K& key)
	{
		if (root == nullptr) return false;
		if (root->_key > key) return _eraseR(root->_left, key);
		else if (root->_key < key) return _eraseR(root->_right, key);
		// �ҵ���������
		else
		{
			Node* del = root;
			// ���������Ϊ��
			if (root->_left == nullptr) root = root->_right;
			// ������Ϊ��
			else if (root->_right == nullptr) root = root->_left;
			else
			{
				// ����Ϊ�� ����������������
				Node* rightmin = root->_right;
				while (rightmin->_left)
				{
					rightmin = rightmin->_left;
				}
				// �滻�� root��ֵ�滻Ϊrightmin��ֵ
				swap(root->_key, rightmin->_key);
				// Ȼ������������ɾ��������
				return _eraseR(root->_right, key);
				// ɾ��������	
			}
			delete del;
			return true;
		}
	}
private:
	Node* _root;
};


namespace KV
{
	// ���
	template <class K, class V>
	struct BSTNode
	{
		BSTNode(const K& key = K(), const V& val = V())
			: _key(key), _left(nullptr), _right(nullptr), _val(val)
		{}
		K _key;
		V _val;
		BSTNode<K, V>* _left;
		BSTNode<K, V>* _right;
	};

	// ��

	template <class K, class V>
	class BSTree
	{
	public:
		typedef BSTNode<K, V> Node;
		BSTree()
			: _root(nullptr)
		{}
		bool insert(const K& key, const V& val)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, val);
				return true;
			}
			Node* cur = _root, * parent = nullptr;
			while (cur)
			{
				parent = cur;
				if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else return false;
			}
			if (parent->_key > key) parent->_left = new Node(key, val);
			else parent->_right = new Node(key, val);
			return true;
		}
		void Inorder() const
		{
			_Inorder(_root);
			return;
		}


		//// �ݹ����
		//bool insertR(const K& key)
		//{
		//	return _insertR(_root, key);
		//}
		//// �ݹ����
		//Node* findR(const K& key)
		//{
		//	return _findR(_root, key);
		//}
		//// �ݹ�ɾ��
		//bool eraseR(const K& key)
		//{
		//	return _eraseR(_root, key);
		//}
		// ��ͨ����
		Node* find(const K& key) const
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key == key) return cur;
				else if (cur->_key > key) cur = cur->_left;
				else cur = cur->_right;
			}
			return nullptr;
		}
		// ��ͨɾ��
		bool erase(const K& key)
		{
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					// �ҵ��� ׼��ɾ��
					if (cur->_left == nullptr)
					{
						// ���и���Ϊ�յ���� ��ʱ��Ҫ�޸ĸ�
						if (parent == nullptr)
						{
							_root = cur->_right;
						}
						else
						{
							// �����ײ�Ϊ�� ��������Ǹ��׵�λ�����ж���Ҫ�������׵Ļ�����ɶ
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}
						delete cur;
						cur = nullptr;
						return true;
					}
					else if (cur->_right == nullptr)
					{
						if (parent == nullptr)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}
						delete cur;
						cur = nullptr;
						return true;
					}
					else
					{
						// ���Ҷ���Ϊ�� �滻��ɾ��
						// ��������������������
						Node* p = cur;// Ϊ��ɾ�������㱣�������ĸ���
						Node* rightmaxleft = cur->_right;
						while (rightmaxleft->_left != nullptr)
						{
							p = rightmaxleft;
							rightmaxleft = rightmaxleft->_left;
						}
						// swap(rightmaxleft->_key, cur->_key);
						// cur�����ݱ����ǳ�_key
						cur->_key = rightmaxleft->_key;
						// ���p->_right�͵���rightmaxleft
						// ��ô˵��p��û�� ��ʱ��Ҫ��p->_right����rightmaxleft->_right
						if (p->_right == rightmaxleft)
						{
							p->_right = rightmaxleft->_right;
						}
						// ���� Ҫ��p->_left����rightmaxleft��_right
						else
						{
							p->_left = rightmaxleft->_right;
						}
						delete rightmaxleft;
						rightmaxleft = nullptr;
						return true;
					}
				}
			}
			return false;
		}
	private:
		void _Inorder(Node* root) const
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			cout << root->_key << ' ';
			_Inorder(root->_right);
		}
		//// ����ݹ��Ӻ���
		//bool _insertR(Node*& root, const K& key)
		//{
		//	if (root == nullptr)
		//	{
		//		root = new Node(key);
		//		return true;
		//	}
		//	if (root->_key > key)
		//	{
		//		return _insertR(root->_left, key);
		//	}
		//	else if (root->_key < key)
		//	{
		//		return _insertR(root->_right, key);
		//	}
		//	else return false;
		//}
		//// �ݹ�����Ӻ���
		//Node* _findR(Node* root, const K& key)
		//{
		//	if (root == nullptr) return nullptr;
		//	if (root->_key == key) return root;
		//	else if (root->_key > key) return _findR(root->_left, key);
		//	else return _findR(root->_right, key);
		//}
		//// �ݹ�ɾ��
		//bool _eraseR(Node*& root, const K& key)
		//{
		//	if (root == nullptr) return false;
		//	if (root->_key > key) return _eraseR(root->_left, key);
		//	else if (root->_key < key) return _eraseR(root->_right, key);
		//	// �ҵ���������
		//	else
		//	{
		//		Node* del = root;
		//		// ���������Ϊ��
		//		if (root->_left == nullptr) root = root->_right;
		//		// ������Ϊ��
		//		else if (root->_right == nullptr) root = root->_left;
		//		else
		//		{
		//			// ����Ϊ�� ����������������
		//			Node* rightmin = root->_right;
		//			while (rightmin->_left)
		//			{
		//				rightmin = rightmin->_left;
		//			}
		//			// �滻�� root��ֵ�滻Ϊrightmin��ֵ
		//			swap(root->_key, rightmin->_key);
		//			// Ȼ������������ɾ��������
		//			return _eraseR(root->_right, key);
		//			// ɾ��������	
		//		}
		//		delete del;
		//		return true;
		//	}
		//}
	private:
		Node* _root;
	};

	void test1()
	{
		BSTree<string, vector<string>> dic;
		dic.insert("sort", { "����" });
		dic.insert("left", { "���" });
		dic.insert("right", { "�ұ�" });
		dic.insert("map", { "��ͼ", "ӳ��" });
		string str;
		while (1)
		{
			cout << "�����뵥�� :";
			cin >> str;
			BSTNode<string, vector<string>>* pnode = dic.find(str);
			if (pnode == nullptr) cout << "���޴˵���" << endl;
			else
			{
				cout << "����Ϊ:";
				for (const string& wd : pnode->_val)
				{
					cout << wd << ' ';
				}
				cout << endl;
			}
		}
	}
}
