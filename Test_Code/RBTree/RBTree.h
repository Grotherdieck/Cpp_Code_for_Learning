#pragma once
#include <iostream>
#include <utility>

using namespace std;

enum Color
{
	RED = 0,
	BLACK = 1
};


template <class K, class V>
struct RBTreeNode
{
    // 默认染色为红色
	RBTreeNode(const pair<K, V>& kv) 
		: _kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED)
	{}
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Color _color;
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree() : _root(nullptr) {}
    void inorder()
    {
        _inorder(_root);
    }
    // 插入
    bool Insert(const pair<K, V>& kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_color = BLACK;
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
            else
                return false;
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
        while (parent && parent->_color == RED)
        {
            // 父亲存在且为红 则父节点一定不是根
            Node* grandfather = parent->_parent;
            // 如果父亲是祖父的左
            if (parent == grandfather->_left)
            {
                // 叔叔就是祖父的右
                Node* uncle = grandfather->_right;
                if (uncle && uncle->_color == RED)
                {
                    // 叔叔父亲弄成黑色 祖父染成红色 再往上处理
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // 叔叔不存在或叔叔存在且为黑
                else
                {
                    //    g
                    //  p   u
                    // cur
                    if (parent->_left == cur)
                    {
                        // 左单旋
                        RotateL(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                    }
                    //     g 
                    //  p    u
                    //    cur
                    // 左右双旋
                    else
                    {
                        RotateL(parent);
                        RotateR(grandfather);
                        // 染色
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                    }

                    break;
                }
            }
            else
            {
                // 父亲是祖父的右
                Node* uncle = grandfather->_left;
                if (uncle && uncle->_color == RED)
                {
                    // 叔叔父亲弄成黑色 祖父染成红色 再往上处理
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // 叔叔不存在或叔叔存在且为黑
                else
                {
                    //  g
                    //     p
                    //        cur
                    if (parent->_right == cur)
                    {
                        // 右单旋
                        RotateL(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                    }
                    //  g
                    //      p
                    //   cur
                    // 右左双旋
                    else
                    {
                        RotateR(parent);
                        RotateL(grandfather);
                        // 染色
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                    }

                    break;
                }
            }
        }
        // 单独把根染黑
        _root->_color = BLACK;
        return true;
    }
    // 检查是否为红黑树
    bool isbalance()
    {
        if (_root && _root->_color == RED)
        {
            cout << "违反根结点是黑色的规则" << endl;
            return false;
        }
        // 获得最左路径的黑结点数量
        int banchmark = 0;
        Node* left = _root;
        while (left)
        {
            if (left->_color == BLACK) ++banchmark;
            left = left->_left;
        }

        return _isbalance(_root, banchmark, 0);
    }
    int height()
    {
        return _height(_root);
    }
private:
	Node* _root;
    // 右单旋
    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        Node* parentParent = parent->_parent;
        subL->_right = parent;
        parent->_parent = subL;
        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;
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
    }
    // 左单旋
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
    }

    void _inorder(Node* root)
    {
        if (root == nullptr) return;
        _inorder(root->_left);
        cout << root->_kv.first << ":" << root->_kv.second << endl;
        _inorder(root->_right);
    }

    int _height(Node* root)
    {
        if (root == nullptr)
            return 0;
        int leftheight = _height(root->_left);
        int rightheight = _height(root->_right);
        return 1 + max(leftheight, rightheight);
    }

    bool _isbalance(Node* root, int banchmark, int blacknum)
    {
        if (root == nullptr)
        {
            if (banchmark != blacknum)
            {
                cout << "存在路径黑色结点的数量不相等" << endl;
                return false;
            }
            return true;
        }

        if (root->_color == RED && root->_parent && root->_parent->_color == RED)
        {
            cout << "出现连续的红结点" << endl;
            return false;
        }

        // 统计一个路径的黑色结点数量
        if (root->_color == BLACK) ++blacknum;

        return _isbalance(root->_left, banchmark, blacknum) 
            && _isbalance(root->_right, banchmark, blacknum);
    }
};

namespace Router
{
    enum Color
    {
        RED = 0,
        BLACK = 1
    };

    // 红黑树结点
    template <class T>
    struct RBTreeNode
    {
        // 默认染色为红色
        RBTreeNode(const T& data)
            : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED)
        {}
        RBTreeNode<T>* _left;
        RBTreeNode<T>* _right;
        RBTreeNode<T>* _parent;
        T _data;
        Color _color;
    };
    // 迭代器
    template <class T, class Ref, class Ptr>
    struct RBTreeIterator
    {
        typedef RBTreeNode<T> Node;
        typedef RBTreeIterator<T, Ref, Ptr> self;
        // 结点就是一个迭代器。
        Node* _node;
        RBTreeIterator(Node* node) : _node(node) {}
        // 解引用
        Ref operator*()
        {
            return _node->_data;
        }
        // ->
        Ptr operator->()
        {
            return &(_node->_data);
        }
        // ++迭代器 指向中序的下一个位置
        self& operator++()
        {
            Node* cur = this->_node;
            if (cur->_right)
            {
                Node* ans = cur->_right;
                while (ans && ans->_left) ans = ans->_left;
                _node = ans;
            }
            else
            {
                Node* parent = cur->_parent;
                while (parent && parent->_left != cur)
                {
                    cur = parent;
                    parent = cur->_parent;
                }
                _node = parent;
            }
            return *this;
        }
        self& operator--()
        {
            Node* cur = this->_node;
            if (cur->_left)
            {
                Node* ans = cur->_left;
                while (ans && ans->_right) ans = ans->_right;
                _node = ans;
            }
            else
            {
                Node* parent = cur->_parent;
                // 否则沿着三叉连找到是父亲的右的节点
                while (parent && parent->_right != cur)
                {
                    cur = parent;
                    parent = parent->_parent;
                }
                _node = parent;
            }
            return *this;
        }

        bool operator==(const self& it)
        {
            return _node == it._node;
        }
        bool operator!=(const self& it)
        {
            return !(*this == it);
        }
    };

    // 红黑树
    template <class K, class T, class KeyofT>
    class RBTree
    {
        typedef RBTreeNode<T> Node;
    public:
        typedef RBTreeIterator<T, T&, T*> iterator;
        RBTree() : _root(nullptr) {}
        ~RBTree()
        {
            destroy(_root);
            _root = nullptr;
        }
        RBTree(const RBTree<K, T, KeyofT>& t)
        {
            _root = copy(t._root);
        }

        // 赋值的现代写法
        RBTree<K, T, KeyofT>& operator=(RBTree<K, T, KeyofT> t)
        {
            std::swap(_root, t._root);
            return *this;
        }
        iterator begin()
        {
            Node* min = _root;
            while (min && min->_left)
            {
                min = min->_left;
            }
            return iterator(min);
        }
        iterator end()
        {
            return iterator(nullptr);
        }
        void inorder()
        {
            _inorder(_root);
        }
        // 插入
        pair<iterator, bool> Insert(const T& data)
        {
            if (_root == nullptr)
            {
                _root = new Node(data);
                _root->_color = BLACK;
                return make_pair(iterator(_root), true);
            }
            Node* parent = nullptr;
            Node* cur = _root;
            KeyofT kot;
            while (cur)
            {
                if (kot(cur->_data) > kot(data))
                {
                    parent = cur;
                    cur = cur->_left;
                }
                else if (kot(cur->_data) < kot(data))
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else
                    return make_pair(iterator(cur), false);
            }
            // 插入一个结点 只会影响它的祖先的平衡因子
            cur = new Node(data);
            Node* newnode = cur;
            cur->_parent = parent;
            if (kot(parent->_data) > kot(cur->_data))
            {
                parent->_left = cur;
            }
            else
            {
                parent->_right = cur;
            }
            while (parent && parent->_color == RED)
            {
                // 父亲存在且为红 则父节点一定不是根
                Node* grandfather = parent->_parent;
                // 如果父亲是祖父的左
                if (parent == grandfather->_left)
                {
                    // 叔叔就是祖父的右
                    Node* uncle = grandfather->_right;
                    if (uncle && uncle->_color == RED)
                    {
                        // 叔叔父亲弄成黑色 祖父染成红色 再往上处理
                        parent->_color = uncle->_color = BLACK;
                        grandfather->_color = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    // 叔叔不存在或叔叔存在且为黑
                    else
                    {
                        //    g
                        //  p   u
                        // cur
                        if (parent->_left == cur)
                        {
                            // 左单旋
                            RotateL(grandfather);
                            parent->_color = BLACK;
                            grandfather->_color = RED;
                        }
                        //     g 
                        //  p    u
                        //    cur
                        // 左右双旋
                        else
                        {
                            RotateL(parent);
                            RotateR(grandfather);
                            // 染色
                            cur->_color = BLACK;
                            grandfather->_color = RED;
                        }

                        break;
                    }
                }
                else
                {
                    // 父亲是祖父的右
                    Node* uncle = grandfather->_left;
                    if (uncle && uncle->_color == RED)
                    {
                        // 叔叔父亲弄成黑色 祖父染成红色 再往上处理
                        parent->_color = uncle->_color = BLACK;
                        grandfather->_color = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    // 叔叔不存在或叔叔存在且为黑
                    else
                    {
                        //  g
                        //     p
                        //        cur
                        if (parent->_right == cur)
                        {
                            // 右单旋
                            RotateL(grandfather);
                            parent->_color = BLACK;
                            grandfather->_color = RED;
                        }
                        //  g
                        //      p
                        //   cur
                        // 右左双旋
                        else
                        {
                            RotateR(parent);
                            RotateL(grandfather);
                            // 染色
                            cur->_color = BLACK;
                            grandfather->_color = RED;
                        }

                        break;
                    }
                }
            }
            // 单独把根染黑
            _root->_color = BLACK;
            return make_pair(iterator(newnode), true);
        }
        // find
        iterator find(const K& key)
        {
            Node* cur = _root;
            KeyofT kot;
            while (cur)
            {
                if (kot(cur->_data) < key)
                    cur = cur->_right;
                else if (kot(cur->_data) > key) cur = cur->_left;
                else return iterator(cur);
            }
            return end();
        }
        // 检查是否为红黑树
        bool isbalance()
        {
            if (_root && _root->_color == RED)
            {
                cout << "违反根结点是黑色的规则" << endl;
                return false;
            }
            // 获得最左路径的黑结点数量
            int banchmark = 0;
            Node* left = _root;
            while (left)
            {
                if (left->_color == BLACK) ++banchmark;
                left = left->_left;
            }

            return _isbalance(_root, banchmark, 0);
        }
        int height()
        {
            return _height(_root);
        }
    private:
        Node* _root;
        // 释放树资源
        void destroy(Node* root)
        {
            if (root == nullptr) return;

            destroy(root->_left);
            destroy(root->_right);
            delete root;
        }
        // 拷贝树
        Node* copy(Node* root)
        {
            if (root == nullptr) return nullptr;
            Node* newnode = new Node(root->_data);
            newnode->_color = root->_color;
            newnode->_left = copy(root->_left);
            newnode->_right = copy(root->_right);
            if (newnode->_left) newnode->_left->_parent = newnode;
            if (newnode->_right) newnode->_right->_parent = newnode;
            return newnode;
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
            if (subLR)
                subLR->_parent = parent;
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
        }
        // 左单旋
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
        }

        void _inorder(Node* root)
        {
            if (root == nullptr) return;
            _inorder(root->_left);
            cout << root->_kv.first << ":" << root->_kv.second << endl;
            _inorder(root->_right);
        }

        int _height(Node* root)
        {
            if (root == nullptr)
                return 0;
            int leftheight = _height(root->_left);
            int rightheight = _height(root->_right);
            return 1 + max(leftheight, rightheight);
        }

        bool _isbalance(Node* root, int banchmark, int blacknum)
        {
            if (root == nullptr)
            {
                if (banchmark != blacknum)
                {
                    cout << "存在路径黑色结点的数量不相等" << endl;
                    return false;
                }
                return true;
            }

            if (root->_color == RED && root->_parent && root->_parent->_color == RED)
            {
                cout << "出现连续的红结点" << endl;
                return false;
            }

            // 统计一个路径的黑色结点数量
            if (root->_color == BLACK) ++blacknum;

            return _isbalance(root->_left, banchmark, blacknum)
                && _isbalance(root->_right, banchmark, blacknum);
        }
    };
}



