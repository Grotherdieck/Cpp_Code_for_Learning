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
	AVLTreeNode<K, V>* _parent;// 三叉链
	pair<K, V> _kv;

	int _bf;// 平衡因子
	// 不加平衡因子需要用递归实现 不好理解
	// 新增结点平衡因子为0
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

	// 插入
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
		// 插入一个结点 只会影响它的祖先的平衡因子
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
		// 控制平衡
		// 1、更新平衡因子
		// 2、出现异常的平衡因子(2, -2)，那么需要“旋转平衡树"
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
				break; // 平衡因子变成0的情况 直接停止更新
			}
			else if (abs(parent->_bf) == 1)
			{
				// 平衡因子没有破坏平衡
				// 继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				// 旋转处理
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					// 这种情况就是右单旋转
					RotateR(parent);
				}
				// 左单选
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				// 左右双旋
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				// 右左双旋
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				break;
			}
			else
			{
				// 说明插入平衡因子之前这个位置就出问题了
				// assert断掉
				assert(false);
			}
		}
		return true;
	}
	// 右单旋
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

	// 左单旋 平衡因子为parent == 2 cur == 1
	// 转后平衡因子为0,0
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
	// 左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int checkbf = subLR->_bf;
		// 先选parent的左孩子 进行左旋
		RotateL(parent->_left);
		// 再把parent进行右旋
		RotateR(parent);
		// 平衡因子更新：
		if (checkbf == -1)
		{
			// 图1
			parent->_bf = 1;
			subLR->_bf = subL->_bf = 0;
		}
		else if (checkbf == 1)
		{
			// 图2
			subL->_bf = -1;
			subLR->_bf = parent->_bf = 0;
		}
		else
		{
			// 图3
			subL->_bf = subLR->_bf = parent->_bf = 0;
		}
	}
	// 右左双旋
	void RotateRL(Node* parent)
	{
		// 先把结点存起来 方便后面更新
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int checkbf = subRL->_bf;
		// 先旋parent的右孩子 进行右旋
		RotateR(parent->_right);
		// 再把parent进行左旋
		RotateL(parent);
		// 平衡因子更新
		if (checkbf == 1)
		{
			// 情况1
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (checkbf == -1)
		{
			// 情况2
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			// 情况3
			parent->_bf = subR->_bf = subRL->_bf = 0;
		}
	}
	// 中序
	void Inorder()
	{
		_Inorder(_root);
	}
	// 验证平衡
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

		// 检查平衡因子是否异常
		if (rightheight - leftheight != root->_bf)
		{
			cout << root->_kv.first << "现在是" << root->_bf << endl;
			cout << root->_kv.first << "应该是" << rightheight - leftheight << endl;
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
