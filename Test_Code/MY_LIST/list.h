#pragma once
#include <iostream>
#include <cassert>
#include "reverse_iterator.h"
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::initializer_list;

template <class T>
struct ListNode
{
	ListNode(const T& val = T(), ListNode<T>* next = nullptr, ListNode<T>* prev = nullptr)
		: _val(val), _next(next), _prev(prev)
	{}
	T _val;
	ListNode<T>* _next;
	ListNode<T>* _prev;
};

template<class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef __list_iterator<T, Ref, Ptr> self;
	typedef ListNode<T> Node;
	typedef Ref reference;
	typedef Ptr pointer;
	Node* _node;
	__list_iterator(Node* node) : _node(node)
	{}
	// 解引用
	Ref operator*()
	{
		return _node->_val;
	}
	Ptr operator->()
	{
		return &(_node->_val);
	}
	// 前置++
	self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// 后置++
	self operator++(int)
	{
		self tmp(_node);
		_node = _node->_next;
		return tmp;
	}
	// 前置--
	self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// 后置--
	self operator--(int)
	{
		self tmp(_node);
		_node = _node->_prev;
		return tmp;
	}
	// ==
	bool operator==(const self& it)
	{
		return _node == it._node;
	}
	// !=
	bool operator!=(const self& it)
	{
		return !(*this == it);
	}
};


template<class T>
class list
{
	typedef ListNode<T> Node;
public:
	// 无参构造
	list()
	{
		_head = new Node;
		_head->_next = _head->_prev = _head;
	}
	// 迭代器区间初始化
	template <class InputIterator>
	list(InputIterator first, InputIterator last)
	{
		_head = new Node;
		_head->_next = _head->_prev = _head;
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}
	// 拷贝构造现代写法
	list(const list<T>& lt)
	{
		_head = new Node;
		_head->_next = _head->_prev = _head;
		list<T> tmp(lt.begin(), lt.end());
		std::swap(_head, tmp._head);
	}

	// 赋值运算符重载现代写法
	list<T>& operator=(list<T> lt)
	{
		std::swap(_head, lt._head);
		return *this;
	}
	// 花括号初始化
	list(initializer_list<T> it)
	{
		_head = new Node;
		_head->_next = _head->_prev = _head;
		/*for (auto e : it)
		{
			push_back(e);
		}*/
		// 复用迭代器区间构造
		list<T> tmp(it.begin(), it.end());
		std::swap(_head, tmp._head);
	}
	// initializer_list的operator=
	list<T>& operator=(initializer_list<T> it)
	{
		list<T> tmp(it.begin(), it.end());
		std::swap(_head, tmp._head);
		return *this;
	}

	list(int n, const T& x = T())
	{
		_head = new Node;
		_head->_next = _head->_prev = _head;
		while (n--)
		{
			push_back(x);
		}
	}

	// 析构函数
	~list()
	{
		clear();
		delete _head;
	}
	// 迭代器
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	// 反向迭代器:增加模板参数法
	typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
	typedef reverse_iterator<iterator, T&, T*> reverse_iterator;
	// typedef reverse_iterator<const_iterator> const_reverse_iterator;
	// typedef reverse_iterator<iterator> reverse_iterator;
	bool empty()
	{
		return _head->_next == _head;
	}
	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			iterator del = it++;
			delete del._node;
		}
		_head->_next = _head->_prev = _head;
	}

	// 反向迭代器
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// 正向迭代器
	iterator begin()
	{
		return iterator(_head->_next);
	}
	const_iterator begin() const
	{
		return const_iterator(_head->_next);
	}
	iterator end()
	{
		return iterator(_head);
	}
	const_iterator end() const
	{
		return const_iterator(_head);
	}

	// 任意位置插入
	iterator insert(iterator pos, const T& x)
	{
		Node* newnode = new Node(x);
		Node* prev = pos._node->_prev;
		prev->_next = newnode;
		newnode->_prev = prev;
		pos._node->_prev = newnode;
		newnode->_next = pos._node;
		// 返回一个指向新插入结点的迭代器
		return iterator(newnode);
	}

	void push_back(const T& x)
	{
		insert(end(), x);
	}
	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	iterator erase(iterator pos)
	{
		assert(!empty());
		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;
		prev->_next = next;
		next->_prev = prev;
		delete pos._node;
		// 返回删除位置后一位置的迭代器
		return iterator(next);
	}
	
	void pop_back()
	{
		// end()前一个位置就是最后一个元素
		erase(--end());
	}
	void pop_front()
	{
		erase(begin());
	}
private:
	Node* _head;
};
