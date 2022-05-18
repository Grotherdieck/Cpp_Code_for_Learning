#pragma once
template <class Iterator, class Ref, class Ptr>
//template <class Iterator>
class reverse_iterator
{
	typedef reverse_iterator<Iterator, Ref, Ptr> self;
	// typedef reverse_iterator<Iterator> self;
	// typedef typename Iterator::reference Ref;
	// typedef typename Iterator::pointer Ptr;
public:
	reverse_iterator(Iterator it):_it(it)
	{}
	// �����ã���λ
	Ref operator*()
	{
		Iterator tmp = _it;
		return *(--tmp);
	}
	// ->�����ý�����
	Ptr operator->()
	{
		return &(operator*());
	}
	// ǰ��++:���������--
	self& operator++()
	{
		--_it;
		return *this;
	}
	// ����++
	self operator++(int)
	{
		self tmp = *this;
		--_it;
		return tmp;
	}
	// ǰ��--
	self& operator--()
	{
		++_it;
		return *this;
	}
	// ����--
	self operator--(int)
	{
		self tmp = *this;
		++_it;
		return tmp;
	}
	// ==
	bool operator==(const self& rit)
	{
		return _it == rit._it;
	}
	// !=
	bool operator!=(const self& rit)
	{
		return !(*this == rit);
	}
private:
	Iterator _it;
};