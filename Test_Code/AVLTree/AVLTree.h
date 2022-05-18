#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <cassert>
#include <functional>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::endl;
using std::max;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;// ������
	pair<K, V> _kv;

	int _bf;// ƽ������
	// ����ƽ��������Ҫ�õݹ�ʵ�� �������
	// �������ƽ������Ϊ0
	AVLTreeNode(const pair<K, V>& kv = pair<K, V>()) 
		: _kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0)
	{}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree() : _root(nullptr) {}

	int height()
	{
		return _height(_root);
	}

	// ����
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else return false;
		}
		// ����һ����� ֻ��Ӱ���������ȵ�ƽ������
		cur = new Node(kv);
		cur->_parent = parent;
		if (parent->_kv.first > cur->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		// ����ƽ��
		// 1������ƽ������
		// 2�������쳣��ƽ������(2, -2)����ô��Ҫ����תƽ����"
		while (parent)
		{
			if (parent->_left == cur)
			{
				--parent->_bf;
			}
			else
			{
				++parent->_bf;
			}

			if (parent->_bf == 0)
			{
				break; // ƽ�����ӱ��0����� ֱ��ֹͣ����
			}
			else if (abs(parent->_bf) == 1)
			{
				// ƽ������û���ƻ�ƽ��
				// �������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				// ��ת����
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					// ������������ҵ���ת
					RotateR(parent);
				}
				// ��ѡ
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				// ����˫��
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				// ����˫��
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				break;
			}
			else
			{
				// ˵������ƽ������֮ǰ���λ�þͳ�������
				// assert�ϵ�
				assert(false);
			}
		}
		return true;
	}
	// �ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		parent->_left = subLR;
		if (subLR) subLR->_parent = parent;
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent) parentParent->_left = subL;
			else parentParent->_right = subL;
			subL->_parent = parentParent;
		}
		subL->_bf = parent->_bf = 0;
	}

	// ���� ƽ������Ϊparent == 2 cur == 1
	// ת��ƽ������Ϊ0,0
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentParent = parent->_parent;
		parent->_parent = subR;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL) subRL->_parent = parent;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else parentParent->_right = subR;
			subR->_parent = parentParent;
		}
		subR->_bf = parent->_bf = 0;
	}
	// ����˫��
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int checkbf = subLR->_bf;
		// ��ѡparent������ ��������
		RotateL(parent->_left);
		// �ٰ�parent��������
		RotateR(parent);
		// ƽ�����Ӹ��£�
		if (checkbf == -1)
		{
			// ͼ1
			parent->_bf = 1;
			subLR->_bf = subL->_bf = 0;
		}
		else if (checkbf == 1)
		{
			// ͼ2
			subL->_bf = -1;
			subLR->_bf = parent->_bf = 0;
		}
		else
		{
			// ͼ3
			subL->_bf = subLR->_bf = parent->_bf = 0;
		}
	}
	// ����˫��
	void RotateRL(Node* parent)
	{
		// �Ȱѽ������� ����������
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int checkbf = subRL->_bf;
		// ����parent���Һ��� ��������
		RotateR(parent->_right);
		// �ٰ�parent��������
		RotateL(parent);
		// ƽ�����Ӹ���
		if (checkbf == 1)
		{
			// ���1
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (checkbf == -1)
		{
			// ���2
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			// ���3
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
	}
	// ����
	void Inorder()
	{
		_Inorder(_root);
	}
	// ��֤ƽ��
	bool isBalance()
	{
		return _isBalance(_root);
	}
private:
	void _Inorder(Node* root)
	{
		if (root == nullptr) return;
		_Inorder(root->_left);
		cout << root->_kv.first << ':' << root->_kv.second << endl;
		_Inorder(root->_right);
	}
	bool _isBalance(Node* root)
	{
		if (root == nullptr) return true;
		int leftheight = _height(root->_left);
		int rightheight = _height(root->_right);

		// ���ƽ�������Ƿ��쳣
		if (rightheight - leftheight != root->_bf)
		{
			cout << root->_kv.first << "������" << root->_bf << endl;
			cout << root->_kv.first << "Ӧ����" << rightheight - leftheight << endl;
			return false;
		}

		return abs(leftheight - rightheight) < 2 && _isBalance(root->_left) && _isBalance(root->_right);
	}

	int _height(Node* root)
	{
		if (root == nullptr) return 0;
		int leftheight = _height(root->_left);
		int rightheight = _height(root->_right);
		return 1 + max(leftheight, rightheight);
	}
	Node* _root;
};
