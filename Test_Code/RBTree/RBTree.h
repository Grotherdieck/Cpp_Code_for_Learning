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
    // Ĭ��ȾɫΪ��ɫ
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
    // ����
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
        while (parent && parent->_color == RED)
        {
            // ���״�����Ϊ�� �򸸽ڵ�һ�����Ǹ�
            Node* grandfather = parent->_parent;
            // ����������游����
            if (parent == grandfather->_left)
            {
                // ��������游����
                Node* uncle = grandfather->_right;
                if (uncle && uncle->_color == RED)
                {
                    // ���常��Ū�ɺ�ɫ �游Ⱦ�ɺ�ɫ �����ϴ���
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // ���岻���ڻ����������Ϊ��
                else
                {
                    //    g
                    //  p   u
                    // cur
                    if (parent->_left == cur)
                    {
                        // ����
                        RotateL(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                    }
                    //     g 
                    //  p    u
                    //    cur
                    // ����˫��
                    else
                    {
                        RotateL(parent);
                        RotateR(grandfather);
                        // Ⱦɫ
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                    }

                    break;
                }
            }
            else
            {
                // �������游����
                Node* uncle = grandfather->_left;
                if (uncle && uncle->_color == RED)
                {
                    // ���常��Ū�ɺ�ɫ �游Ⱦ�ɺ�ɫ �����ϴ���
                    parent->_color = uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // ���岻���ڻ����������Ϊ��
                else
                {
                    //  g
                    //     p
                    //        cur
                    if (parent->_right == cur)
                    {
                        // �ҵ���
                        RotateL(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                    }
                    //  g
                    //      p
                    //   cur
                    // ����˫��
                    else
                    {
                        RotateR(parent);
                        RotateL(grandfather);
                        // Ⱦɫ
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                    }

                    break;
                }
            }
        }
        // �����Ѹ�Ⱦ��
        _root->_color = BLACK;
        return true;
    }
    // ����Ƿ�Ϊ�����
    bool isbalance()
    {
        if (_root && _root->_color == RED)
        {
            cout << "Υ��������Ǻ�ɫ�Ĺ���" << endl;
            return false;
        }
        // �������·���ĺڽ������
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
    // �ҵ���
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
    // ����
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
                cout << "����·����ɫ�������������" << endl;
                return false;
            }
            return true;
        }

        if (root->_color == RED && root->_parent && root->_parent->_color == RED)
        {
            cout << "���������ĺ���" << endl;
            return false;
        }

        // ͳ��һ��·���ĺ�ɫ�������
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

    // ��������
    template <class T>
    struct RBTreeNode
    {
        // Ĭ��ȾɫΪ��ɫ
        RBTreeNode(const T& data)
            : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED)
        {}
        RBTreeNode<T>* _left;
        RBTreeNode<T>* _right;
        RBTreeNode<T>* _parent;
        T _data;
        Color _color;
    };
    // ������
    template <class T, class Ref, class Ptr>
    struct RBTreeIterator
    {
        typedef RBTreeNode<T> Node;
        typedef RBTreeIterator<T, Ref, Ptr> self;
        // ������һ����������
        Node* _node;
        RBTreeIterator(Node* node) : _node(node) {}
        // ������
        Ref operator*()
        {
            return _node->_data;
        }
        // ->
        Ptr operator->()
        {
            return &(_node->_data);
        }
        // ++������ ָ���������һ��λ��
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
                // ���������������ҵ��Ǹ��׵��ҵĽڵ�
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

    // �����
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

        // ��ֵ���ִ�д��
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
        // ����
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
            // ����һ����� ֻ��Ӱ���������ȵ�ƽ������
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
                // ���״�����Ϊ�� �򸸽ڵ�һ�����Ǹ�
                Node* grandfather = parent->_parent;
                // ����������游����
                if (parent == grandfather->_left)
                {
                    // ��������游����
                    Node* uncle = grandfather->_right;
                    if (uncle && uncle->_color == RED)
                    {
                        // ���常��Ū�ɺ�ɫ �游Ⱦ�ɺ�ɫ �����ϴ���
                        parent->_color = uncle->_color = BLACK;
                        grandfather->_color = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    // ���岻���ڻ����������Ϊ��
                    else
                    {
                        //    g
                        //  p   u
                        // cur
                        if (parent->_left == cur)
                        {
                            // ����
                            RotateL(grandfather);
                            parent->_color = BLACK;
                            grandfather->_color = RED;
                        }
                        //     g 
                        //  p    u
                        //    cur
                        // ����˫��
                        else
                        {
                            RotateL(parent);
                            RotateR(grandfather);
                            // Ⱦɫ
                            cur->_color = BLACK;
                            grandfather->_color = RED;
                        }

                        break;
                    }
                }
                else
                {
                    // �������游����
                    Node* uncle = grandfather->_left;
                    if (uncle && uncle->_color == RED)
                    {
                        // ���常��Ū�ɺ�ɫ �游Ⱦ�ɺ�ɫ �����ϴ���
                        parent->_color = uncle->_color = BLACK;
                        grandfather->_color = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    }
                    // ���岻���ڻ����������Ϊ��
                    else
                    {
                        //  g
                        //     p
                        //        cur
                        if (parent->_right == cur)
                        {
                            // �ҵ���
                            RotateL(grandfather);
                            parent->_color = BLACK;
                            grandfather->_color = RED;
                        }
                        //  g
                        //      p
                        //   cur
                        // ����˫��
                        else
                        {
                            RotateR(parent);
                            RotateL(grandfather);
                            // Ⱦɫ
                            cur->_color = BLACK;
                            grandfather->_color = RED;
                        }

                        break;
                    }
                }
            }
            // �����Ѹ�Ⱦ��
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
        // ����Ƿ�Ϊ�����
        bool isbalance()
        {
            if (_root && _root->_color == RED)
            {
                cout << "Υ��������Ǻ�ɫ�Ĺ���" << endl;
                return false;
            }
            // �������·���ĺڽ������
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
        // �ͷ�����Դ
        void destroy(Node* root)
        {
            if (root == nullptr) return;

            destroy(root->_left);
            destroy(root->_right);
            delete root;
        }
        // ������
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
        // �ҵ���
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
        // ����
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
                    cout << "����·����ɫ�������������" << endl;
                    return false;
                }
                return true;
            }

            if (root->_color == RED && root->_parent && root->_parent->_color == RED)
            {
                cout << "���������ĺ���" << endl;
                return false;
            }

            // ͳ��һ��·���ĺ�ɫ�������
            if (root->_color == BLACK) ++blacknum;

            return _isbalance(root->_left, banchmark, blacknum)
                && _isbalance(root->_right, banchmark, blacknum);
        }
    };
}



