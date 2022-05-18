//
// Created by lenovo on 2022/3/10.
//

#ifndef CLIONTEST_MYVECTOR_H
#define CLIONTEST_MYVECTOR_H



#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <algorithm>
#include <forward_list>
#include "reverse_iterator.h"
using namespace std;

namespace scu
{
    template<class T>
    class vector
    {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
        typedef reverse_iterator<iterator, T&, T*> reverse_iterator;
        vector() : _start(nullptr), _finish(nullptr), _end_of_capacity(nullptr)
        {}
        // 传统写法
//        vector(const vector<T>& vec)
//        {
//            _start = new T[vec.size()];
//            for (size_t i = 0; i < vec.size(); ++i)
//            {
//                _start[i] = vec[i];
//            }
//            _finish = _end_of_capacity = _start + vec.size();
//        }
        // 一个类模板的成员函数 本身也可以是函数模板
        // 优势在于你可以传其他类型的迭代器过来拷贝构造
        template<class InputIterator>
        vector(InputIterator first, InputIterator last)
        : _start(nullptr), _finish(nullptr), _end_of_capacity(nullptr)
        {
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }
        vector(const vector<T>& v)
        :_start(nullptr), _finish(nullptr), _end_of_capacity(nullptr)
        {
            vector<T> tmp(v.begin(), v.end());
            swap(tmp);
        }
        ~vector()
        {
            if (_start != nullptr)
            {
                delete[] _start;
            }
            _start = _finish = _end_of_capacity = nullptr;
        }
        void swap(vector<T>& v)
        {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_end_of_capacity, v._end_of_capacity);
        }
        vector<T>& operator=(vector<T> v)
        {
            swap(v);
            return *this;
        }
        size_t size() const
        {
            return _finish - _start;
        }
        size_t capacity() const
        {
            return _end_of_capacity - _start;
        }
        T& operator[](size_t i)
        {
            assert(i < size());
            return _start[i];
        }
        const T& operator[](size_t i) const
        {
            assert(i < size());
            return _start[i];
        }
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
        iterator begin()
        {
            return _start;
        }
        iterator end()
        {
            return _finish;
        }
        const_iterator begin() const
        {
            return _start;
        }
        const_iterator end() const
        {
            return _finish;
        }
        void reserve(size_t n)
        {
            size_t sz = size();
            size_t cap = capacity();
            if (n > cap)
            {
                T* tmp = new T[n];
                if (_start != nullptr)
                {
                    for (size_t i = 0; i < sz; ++i)
                    {
                        tmp[i] = _start[i];
                    }
                    delete[] _start;
                }
                _start = tmp;
                _finish = tmp + sz;
                _end_of_capacity = tmp + n;
            }
        }
        void resize(size_t n, const T& x = T())
        {
            size_t sz = size(), ca = capacity();
            if (n < sz)
            {
                _finish = _start + n;
            }
            else if (n < ca)
            {
                while (_finish != _start + n)
                {
                    *_finish = x;
                    ++_finish;
                }
            }
            else if (n > capacity())
            {
                reserve(n);
                while (_finish != _start + n)
                {
                    *_finish = x;
                    ++_finish;
                }
            }
        }
        void push_back(const T& x)
        {
            if (_finish == _end_of_capacity)
            {
                reserve(capacity() == 0 ? 4 : 2 * capacity());
            }
            *_finish = x;
            ++_finish;
        }
        bool empty() const
        {
            return _start == _finish;
        }
        void pop_back()
        {
            assert(!empty());
            --_finish;
        }
        iterator insert(iterator pos, const T& x)
        {
            // 根据指针特性 检查迭代器是否有效
            assert(pos >= _start);
            assert(pos <= _finish);
            // 满了就扩容
            if (_finish == _end_of_capacity)
            {
                // 扩容后更新pos
                size_t len = pos - _start;
                reserve(capacity() == 0 ? 4 : 2 * capacity());
                pos = _start + len;
            }
            // 挪动数据
            iterator end = _finish - 1;
            while (end >= pos)
            {
                // 往后挪动
                *(end + 1) = *end;
                --end;
            }
            *pos = x;
            ++_finish;
            return pos;
        }
        iterator erase(iterator pos)
        {
            assert(pos < _finish);
            assert(pos >= _start);
            iterator mv = pos + 1;
            // 从pos + 1开始 往前挪动
            // 到_finish停止
            while (mv < _finish)
            {
                *(mv - 1) = *mv;
                ++mv;
            }
            // 容器大小减小
            --_finish;
            return pos;
        }
    private:
        iterator _start;
        iterator _finish;
        iterator _end_of_capacity;
    };
}


#endif //CLIONTEST_MYVECTOR_H


