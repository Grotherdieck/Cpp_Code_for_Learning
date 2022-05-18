//
// Created by lenovo on 2022/3/15.
//

#ifndef MYLIST_REVERSE_ITERATOR_H
#define MYLIST_REVERSE_ITERATOR_H

namespace scu
{
    template<class Iterator, class Ref, class Ptr>
    class reverse_iterator
    {
        typedef reverse_iterator<Iterator, Ref, Ptr> self;
    public:
        reverse_iterator(Iterator it) : _it(it)
        {}
        // 反向迭代器 ++复用正向迭代器的--
        self& operator++()
        {
            --_it;
            return *this;
        }
        self& operator--()
        {
            ++_it;
            return *this;
        }
        // 后置++
        self operator++(int)
        {
            self tmp = *this;
            --_it;
            return tmp;
        }
        // 后置--
        self operator--(int)
        {
            self tmp = *this;
            ++_it;
            return tmp;
        }
        // 复用正向迭代器的!=
        bool operator!=(const self& rit)
        {
            return _it != rit._it;
        }

        bool operator==(const self& rit)
        {
            return !(*this != rit);
        }
        // 因为对称问题 访问的是_it前面一个元素
        Ref operator*()
        {
            Iterator tmp = _it;
            return *(--tmp);
        }
        // 复用反向迭代器的引用 然后取地址得到指针变量
        Ptr operator->()
        {
            return &operator*();
        }
    private:
        Iterator _it;
    };
}


#endif //MYLIST_REVERSE_ITERATOR_H
