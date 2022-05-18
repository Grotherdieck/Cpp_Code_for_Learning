#pragma once
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
//K->key
template <class K>
struct BSTreeNode
{
	BSTreeNode(K key = K())
		: _left(nullptr), _right(nullptr), _val(key)
	{}
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _val;
};

template <class K>
class BSTree
{
public:
	typedef BSTreeNode<K> Node;
	BSTree() : _root(nullptr)
	{}

	// 插入 如果重了就返回false
	bool insert(const K& key)
	{
		if (_root == nullptr) {
			_root = new Node(key);
			break;
		}
		Node* parent = nullptr, *cur = _root;
		while (cur)
		{
			if (cur->_val > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_val < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else return false;
		}
		if (parent->_val > key)
		{
			parent->_left = new Node(key);
		}
		else
		{
			parent->_right = new Node(key);
		}
		return true;
	}
	// 中序遍历
	void Inorder()
	{
		_Inorder(_root);
	}
	void _Inorder(Node* root)
	{
		if (root == nullptr) return;
		_Inorder(root->_left);
		cout << root->_val << ' ';
		_Inorder(root->_right);
	}
	Node* find(const K& key);
private:
	Node* _root;
};