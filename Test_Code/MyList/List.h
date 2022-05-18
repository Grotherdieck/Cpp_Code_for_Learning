//
// Created by lenovo on 2022/3/14.
//

#ifndef MYLIST_LIST_H
#define MYLIST_LIST_H

#include <iostream>
using namespace std;
#include "reverse_iterator.h"
#include <cstdio>

namespace scu
{
    template<class T>
    struct ListNode
    {
        ListNode(const T& val = T(), ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr)
        {
            _val = val;
            _prev = prev;
            _next = next;
        }
        T _val;
        ListNode<T>* _prev;
        ListNode<T>* _next;
    };

    template<class T, class Ref, class Ptr>
    struct __list_iterator
    {
        typedef ListNode<T> Node;
        typedef __list_iterator<T, Ref, Ptr> self;
        Node* _node;
        __list_iterator(Node* node) : _node(node)
        {}
        Ref operator*()
        {
            return _node->_val;
        }
        // ++it
        self& operator++()
        {
            _node = _node->_next;
            return *this;
        }
        Ptr operator->()
        {
            return &_node->_val;
        }
        // it++
        self operator++(int)
        {
            self tmp(_node);
            _node = _node->_next;
            return tmp;
        }

        // --it
        self& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        // it--
        self operator--(int)
        {
            self tmp(_node);
            _node = _node->_prev;
            return tmp;
        }
        bool operator==(const self & it)
        {
            return it._node == _node;
        }
        bool operator!=(const self& it)
        {
            return !(*this == it);
        }
    };

//    template<class T>
//    struct __list_const_iterator
//    {
//        typedef ListNode<T> Node;
//
//        Node* _node;
//        __list_const_iterator(Node* node) : _node(node)
//        {}
//        const T& operator*()
//        {
//            return _node->_val;
//        }
//        // ++it
//        __list_const_iterator<T>& operator++()
//        {
//            _node = _node->_next;
//            return *this;
//        }
//        // it++
//        __list_const_iterator<T> operator++(int)
//        {
//            __list_const_iterator tmp(_node);
//            _node = _node->_next;
//            return tmp;
//        }
//
//        // --it
//        __list_const_iterator<T>& operator--()
//        {
//            _node = _node->_prev;
//            return *this;
//        }
//
//        // it--
//        __list_const_iterator<T> operator--(int)
//        {
//            __list_const_iterator tmp(_node);
//            _node = _node->_prev;
//            return tmp;
//        }
//        bool operator==(const __list_const_iterator<T>& it)
//        {
//            return it._node == _node;
//        }
//        bool operator!=(const __list_const_iterator<T>& it)
//        {
//            return !(*this == it);
//        }
//    };

    template<class T>
    class list
    {
    public:
        typedef ListNode<T> Node;
        typedef __list_iterator<T, T&, T*> iterator;
        typedef __list_iterator<T, const T&, const T*> const_iterator;
        typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
        typedef reverse_iterator<iterator, T&, T*> reverse_iterator;
        // typedef __list_const_iterator<T> const_iterator;
        list()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }
        // 传统写法拷贝构造 利用尾插
//        list(const list<T>& lt)
//        {
//            _head = new Node;
//            _head->_next = _head->_prev = _head;
//            for (auto e : lt)
//            {
//                push_back(e);
//            }
//        }
        // 拷贝构造现代写法依赖的东西:利用InputIterator区间构造
        template<class InputIterator>
        list(InputIterator first, InputIterator last)
        {
            _head = new Node;
            _head->_prev = _head->_next = _head;
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }
        list(size_t n, const T& val = T())
        {
            _head = new Node;
            _head->_next = _head->_prev = _head;
            while (n--)
            {
                push_back(val);
            }
        }
        list(int n, const T& val = T())
        {
            _head = new Node;
            _head->_next = _head->_prev = _head;
            while (n--)
            {
                push_back(val);
            }
        }
        // lt2(lt1) 现代写法 复用迭代器区间构造
        list(const list<T>& lt)
        {
            _head = new Node;
            _head->_next = _head->_prev = _head;
            // 利用临时对象tmp来调用迭代器区间初始化
            list<T> tmp(lt.begin(), lt.end());
            // 交换指针即可
            std::swap(_head, tmp._head);
        }
        // 传统写法赋值运算符重载(深拷贝)
//        list<T>& operator=(const list<T>& lt)
//        {
//            if (this != &lt)
//            {
//                clear();
//                for (auto e : lt)
//                {
//                    push_back(e);
//                }
//            }
//            return *this;
//        }
        // 现代版本赋值运算符重载 利用传值复用拷贝构造函数
        list<T>& operator=(list<T> lt)
        {
            std::swap(_head, lt._head);
            return *this;
        }
        // 析构 把头结点也干掉
        ~list()
        {
            clear();
            delete _head;
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
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }
        iterator begin()
        {
            return iterator(_head->_next);
        }
        iterator end()
        {
            return iterator(_head);
        }
        const_iterator begin() const
        {
            return const_iterator(_head->_next);
        }
        const_iterator end() const
        {
            return const_iterator(_head);
        }
        void push_back(const T& x)
        {
            insert(end(), x);
        }
        void push_front(const T& x)
        {
            insert(begin(), x);
        }
        iterator insert(iterator pos, const T& x)
        {
            Node* prev = pos._node->_prev;
            Node* newnode = new Node(x);
            newnode->_next = pos._node;
            pos._node->_prev = newnode;
            newnode->_prev = prev;
            prev->_next = newnode;
            return iterator(newnode);
        }
        iterator erase(iterator pos)
        {
            // 不能删哨兵位的头
            assert(pos != end());
            Node* prev = pos._node->_prev;
            Node* next = pos._node->_next;
            prev->_next = next;
            next->_prev = prev;
            delete pos._node;
            return iterator(next);
        }
        void pop_back()
        {
            erase(--end());
        }
        void pop_front()
        {
            erase(begin());
        }
    private:
        Node* _head;
    };

    struct Date
    {
        Date(int year = 2022, int month = 3, int day = 14) :_year(year), _month(month), _day(day)
        {}
        int _year;
        int _month;
        int _day;
    };

    void list_test1()
    {
        list<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);
        l.push_back(6);
        cout << endl;
    }
    void listprint(const list<int>& l)
    {
        list<int>::const_iterator it = l.begin();
        while (it != l.end())
        {
            cout << *it << ' ';
            ++it;
        }
    }
    void list_test2()
    {
        list<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);
        l.push_back(6);
        listprint(l);
    }

    void listdateprint(const list<Date>& lt)
    {
        list<Date>::const_iterator it = lt.begin();
        while (it != lt.end())
        {
            cout << it->_year << '/' << it->_month << '/' << it->_day << endl;
            ++it;
        }
    }

    void list_test3()
    {
        list<Date> lt;
        lt.push_front(Date(2022, 3, 14));
        lt.push_front(Date(2022, 3, 13));
        lt.push_front(Date(2022, 3, 12));
        list<Date>::iterator it = lt.begin();
        while (it != lt.end())
        {
            // cout << (*it)._year << '/' << (*it)._month << '/' << (*it)._day << endl;
            it->_month *= 2;
            cout << it->_year << '/' << it->_month << '/' << it->_day << endl;

            ++it;
        }
         listdateprint(lt);
    }
    void list_test4()
    {
        list<int> l1;
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);

        list<int> l2(l1);
        l1.clear();
        for (auto e : l2)
        {
            cout << e << ' ';
        }
        cout << endl;
    }
    void list_test5()
    {
        list<int> l1(5 ,1);
    }
    void list_test6()
    {
        list<int> l1;
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(3);
        l1.push_back(4);
        l1.push_back(5);
        list<int>::reverse_iterator rit = l1.rbegin();
        while (rit != l1.rend())
        {
            cout << *rit << ' ';
            ++rit;
        }
    }
    void list_test7()
    {
        list<Date> lt;
        lt.push_back(Date(2022, 3, 14));
        lt.push_back(Date(2022, 3, 13));
        lt.push_back(Date(2022, 3, 12));
        list<Date>::reverse_iterator it = lt.rbegin();
        while (it != lt.rend())
        {
            // cout << (*it)._year << '/' << (*it)._month << '/' << (*it)._day << endl;
            it->_month *= 2;
            cout << it->_year << '/' << it->_month << '/' << it->_day << endl;

            ++it;
        }
        // listdateprint(lt);
    }
}


#endif //MYLIST_LIST_H
