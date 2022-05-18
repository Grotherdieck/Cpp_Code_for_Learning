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

// 结点
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

// 树

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
	

	// 递归插入
	bool insertR(const K& key)
	{
		return _insertR(_root, key);
	}
	// 递归查找
	Node* findR(const K& key)
	{
		return _findR(_root, key);
	}
	// 递归删除
	bool eraseR(const K& key)
	{
		return _eraseR(_root, key);
	}
	// 普通查找
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
	// 普通删除
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
				// 找到了 准备删除
				if (cur->_left == nullptr)
				{
					// 特判父亲为空的情况 这时需要修改根
					if (parent == nullptr)
					{
						_root = cur->_right;
					}
					else
					{
						// 若父亲不为空 则根据我是父亲的位置来判断我要交给父亲的还是是啥
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
					// 左右都不为空 替换法删除
					// 假设找右子树的最左结点
					Node* p = cur;// 为了删除这个结点保留的它的父亲
					Node* rightmaxleft = cur->_right;
					while (rightmaxleft->_left != nullptr)
					{
						p = rightmaxleft;
						rightmaxleft = rightmaxleft->_left;
					}
					// swap(rightmaxleft->_key, cur->_key);
					// cur的数据被覆盖成_key
					cur->_key = rightmaxleft->_key;
					// 如果p->_right就等于rightmaxleft
					// 那么说明p就没动 这时候要把p->_right连到rightmaxleft->_right
					if (p->_right == rightmaxleft)
					{
						p->_right = rightmaxleft->_right;
					}
					// 否则 要把p->_left连到rightmaxleft的_right
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
	// 插入递归子函数
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
	// 递归查找子函数
	Node* _findR(Node* root, const K& key)
	{
		if (root == nullptr) return nullptr;
		if (root->_key == key) return root;
		else if (root->_key > key) return _findR(root->_left, key);
		else return _findR(root->_right, key);
	}
	// 递归删除
	bool _eraseR(Node*& root, const K& key)
	{
		if (root == nullptr) return false;
		if (root->_key > key) return _eraseR(root->_left, key);
		else if (root->_key < key) return _eraseR(root->_right, key);
		// 找到了这个结点
		else
		{
			Node* del = root;
			// 如果左子树为空
			if (root->_left == nullptr) root = root->_right;
			// 右子树为空
			else if (root->_right == nullptr) root = root->_left;
			else
			{
				// 都不为空 找右子树的最左结点
				Node* rightmin = root->_right;
				while (rightmin->_left)
				{
					rightmin = rightmin->_left;
				}
				// 替换法 root的值替换为rightmin的值
				swap(root->_key, rightmin->_key);
				// 然后在右子树中删除这个结点
				return _eraseR(root->_right, key);
				// 删除这个结点	
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
	// 结点
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

	// 树

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


		//// 递归插入
		//bool insertR(const K& key)
		//{
		//	return _insertR(_root, key);
		//}
		//// 递归查找
		//Node* findR(const K& key)
		//{
		//	return _findR(_root, key);
		//}
		//// 递归删除
		//bool eraseR(const K& key)
		//{
		//	return _eraseR(_root, key);
		//}
		// 普通查找
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
		// 普通删除
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
					// 找到了 准备删除
					if (cur->_left == nullptr)
					{
						// 特判父亲为空的情况 这时需要修改根
						if (parent == nullptr)
						{
							_root = cur->_right;
						}
						else
						{
							// 若父亲不为空 则根据我是父亲的位置来判断我要交给父亲的还是是啥
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
						// 左右都不为空 替换法删除
						// 假设找右子树的最左结点
						Node* p = cur;// 为了删除这个结点保留的它的父亲
						Node* rightmaxleft = cur->_right;
						while (rightmaxleft->_left != nullptr)
						{
							p = rightmaxleft;
							rightmaxleft = rightmaxleft->_left;
						}
						// swap(rightmaxleft->_key, cur->_key);
						// cur的数据被覆盖成_key
						cur->_key = rightmaxleft->_key;
						// 如果p->_right就等于rightmaxleft
						// 那么说明p就没动 这时候要把p->_right连到rightmaxleft->_right
						if (p->_right == rightmaxleft)
						{
							p->_right = rightmaxleft->_right;
						}
						// 否则 要把p->_left连到rightmaxleft的_right
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
		//// 插入递归子函数
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
		//// 递归查找子函数
		//Node* _findR(Node* root, const K& key)
		//{
		//	if (root == nullptr) return nullptr;
		//	if (root->_key == key) return root;
		//	else if (root->_key > key) return _findR(root->_left, key);
		//	else return _findR(root->_right, key);
		//}
		//// 递归删除
		//bool _eraseR(Node*& root, const K& key)
		//{
		//	if (root == nullptr) return false;
		//	if (root->_key > key) return _eraseR(root->_left, key);
		//	else if (root->_key < key) return _eraseR(root->_right, key);
		//	// 找到了这个结点
		//	else
		//	{
		//		Node* del = root;
		//		// 如果左子树为空
		//		if (root->_left == nullptr) root = root->_right;
		//		// 右子树为空
		//		else if (root->_right == nullptr) root = root->_left;
		//		else
		//		{
		//			// 都不为空 找右子树的最左结点
		//			Node* rightmin = root->_right;
		//			while (rightmin->_left)
		//			{
		//				rightmin = rightmin->_left;
		//			}
		//			// 替换法 root的值替换为rightmin的值
		//			swap(root->_key, rightmin->_key);
		//			// 然后在右子树中删除这个结点
		//			return _eraseR(root->_right, key);
		//			// 删除这个结点	
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
		dic.insert("sort", { "排序" });
		dic.insert("left", { "左边" });
		dic.insert("right", { "右边" });
		dic.insert("map", { "地图", "映射" });
		string str;
		while (1)
		{
			cout << "请输入单词 :";
			cin >> str;
			BSTNode<string, vector<string>>* pnode = dic.find(str);
			if (pnode == nullptr) cout << "查无此单词" << endl;
			else
			{
				cout << "翻译为:";
				for (const string& wd : pnode->_val)
				{
					cout << wd << ' ';
				}
				cout << endl;
			}
		}
	}
}
