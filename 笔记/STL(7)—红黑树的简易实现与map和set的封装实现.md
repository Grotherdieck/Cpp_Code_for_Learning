# 一、红黑树的介绍

&emsp;&emsp;红黑树是通过着色限制最长路径长度不超过最短路径的2倍，从而控制了红黑树的近似平衡，不同于``AVL``树，它并不是严格平衡的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514113911.png" style="zoom:80%;" />

## 1 红黑树的规则

1. 每个结点不是红色就是黑色 
2. 根节点是黑色的  
3. 如果一个节点是红色的，则它的两个孩子结点是黑色的 ，**即红黑树的路径中不存在连续红结点**。
4. 对于每个结点，从该结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点 ，**即每条路径的黑色结点数量相等**，这里的路径是要一直到根节点的。
5. 每个叶子结点都是黑色的(此处的叶子结点指的是空结点)

&emsp;&emsp;分析，如果存在最短路径，极端的最短路径就是全黑的结点，最长路径的极端情况是一黑一红(根据规则3，结点不能连续存在)，而每条路径的黑色结点数量都相等，最长的路径长度不超过最短路径的2倍。

&emsp;&emsp;假设任意一条路径的黑结点个数为N，则N<=任意路径长度<=2N。

&emsp;&emsp;第二个节点插入时，第二个节点必然是红结点，路径长度就不满足了，性质4可能就对不上了：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514114215.png" style="zoom:80%;" />

## 2 理解红黑树的相对平衡

&emsp;&emsp;``AVL``树左右两边更加均衡，高度控制在``logN``；

&emsp;&emsp;红黑树的左右两边没有那么均衡，当最长路径长度超过最短路径的2倍，它就一定要旋转。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516192245.png" style="zoom:80%;" />

&emsp;&emsp;假设红黑树中一条路径黑色结点的数量是``X``，红黑树的高度``h``就一定满足``X <= h <= 2X``。

&emsp;&emsp;那么结点数量``N``最少是高度为``X``的满二叉树对应个数（全黑的满二叉树），最多是高度为``2X``的满二叉树结点个数（一黑一红的满二叉树），即
$$
2^X - 1<=N<=2^{2X} - 1\\
\frac{1}{2}log_2(N+1)<=X<=log_2(N+ 1)\\
$$
&emsp;&emsp;所以红黑树的高度还是对数级别，最坏情况下是``2logN``的高度，这就是红黑树近似平衡的含义。

&emsp;&emsp;对比AVL树的严格平衡，它的增删查的效率是严格``logN``，而红黑树是近似平衡，它增删查的效率是``logN``，因为是对数级别，所以就算14亿也就30层，2logN也就60层，对CPU来说查找其实没有啥区别。

&emsp;&emsp;但是AVL树的更加平衡是付出了更多的旋转(删除时可能一直旋转到根)达到的，同样的一个树的模样，红黑树可能不旋转，AVL树可能要旋转。

## 3 红黑树的结构

&emsp;&emsp;首先我们仍然保持三叉链结构，因为需要给结点染色，所以我们再增加一个枚举类型，代表红色和黑色，其结点结构体如下：

```cpp
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
```

&emsp;&emsp;然后我们的红黑树的模板类就是封装一个根节点，无参构造函数把红黑树的根节点置成``nullptr``：

```cpp
template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree() : _root(nullptr) {}
private:
	Node* _root;
};
```

## 4 红黑树的插入

&emsp;&emsp;因为插入黑色结点可能会影响所有路径，所以我们默认新插入的结点``cur``为红色结点比较好。

&emsp;&emsp;插入过程的整体框架与AVL树类似，首先根据二叉搜索树的方法，找到对应位置并插入，新插入位置为cur，其父亲为``parent``，因为cur我们一直控制成红色的，如果其父亲不为空且父亲为红色结点，则需要调整红黑树。

&emsp;&emsp;如果约定``cur``为新增结点，p为新增结点的父节点，g为新增结点的祖父结点，u为新增结点的叔叔结点；

&emsp;&emsp;可以发现，只要父亲不是红色结点，我们就不会违反规则，但是当父亲也是红色结点时，我们需要调整红黑树以满足它的规则：

- 情况1：``cur``是红色，p是红色，g是黑色，**u是红色**

&emsp;&emsp;解决方法：p染成黑色，u染成黑色，**g染成红色**，**把g当做cur继续向上调整**；

&emsp;&emsp;父亲是祖父的左孩子的情况：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515213533.png" style="zoom:80%;" />

&emsp;&emsp;父亲是祖父的右孩子的情况：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515214003.png" style="zoom:80%;" />

&emsp;&emsp;因为为了解决新增结点导致的连续红结点问题，所以要把p染黑，然后因为把p染黑了，这个子树内黑结点多了一个，所以需要把u也染黑保证子树范围内黑结点个数相等，把p和u染黑色以后，就保证了这个子树范围内路径长度相等，但是相对其他的子树，这个子树的路径长度增加了1，所以要把g染成红色减少一个黑色结点，并继续往上调整。

- 情况2：``cur``是红、p为红、g为黑、u不存在或u存在且为黑

&emsp;&emsp;根据cur和parent和grandfather的位置关系，可以分成以下四种情况：

&emsp;&emsp;右单旋情况：父亲是祖父左孩子且cur是父亲左孩子：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514151041.png" style="zoom:80%;" />

&emsp;&emsp;左右双旋情况:父亲是祖父左孩子且cur是父亲右孩子

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514154314.png" style="zoom:80%;" />

&emsp;&emsp;右左双旋情况:父亲是祖父右孩子且cur是父亲左孩子

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514161100.png" style="zoom:80%;" />

&emsp;&emsp;左单旋情况：父亲是祖父右孩子且cur是父亲右孩子

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515212040.png" style="zoom:80%;" />

&emsp;&emsp;并且这四种旋转有一种好处，它把当前子树的根弄成了黑色，不用再往上调整了。

&emsp;&emsp;综上，综合代码如下：

```cpp
// 插入
bool Insert(const pair<K, V> &kv)
{
    if (_root == nullptr)
    {
        _root = new Node(kv);
        _root->_color = BLACK;
        return true;
    }
    Node *parent = nullptr;
    Node *cur = _root;
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
        Node *grandfather = parent->_parent;
        // 如果父亲是祖父的左
        if (parent == grandfather->_left)
        {
            // 叔叔就是祖父的右
            Node *uncle = grandfather->_right;
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
            Node *uncle = grandfather->_left;
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
```

## 5 红黑树的验证

&emsp;&emsp;首先，直接能通过遍历并不能说明我们的数是红黑树，只能说明我们的树是一颗二叉搜索树，实际上，想验证树是红黑树应该通过验证规则是否成立验证，也就是像``AVL``树一样，我们单独去写一个检查来验证。

&emsp;&emsp;根为黑，很好检查；没有连续的红结点也很好检查，遍历每个结点，如果结点为红且父亲为红，则往回返回false，对每个结点去检查其父亲的颜色比检查其孩子要轻松很多。

&emsp;&emsp;先把我们上面讨论的规则的验证实现一下：

```cpp
// 检查是否为红黑树
bool isbalance()
{
    if (_root && _root->_color == RED)
    {
        cout << "违反根结点是黑色的规则" << endl;
        return false;
    }
    return _isbalance(_root);
}
bool _isbalance(Node *root)
{
    if (root == nullptr)
        return true;

    if (root->_color == RED && root->_parent && root->_parent->_color == RED)
    {
        cout << "出现连续的红结点" << endl;
        return false;
    }

    return _isbalance(root->_left) && _isbalance(root->_right);
}
```

&emsp;&emsp;接下来要检查每条路径的黑色结点数量都相等，显然使用一个``dfs``就可以，参数里头带一个当前黑色结点数量，走到空时说明一条路径结束了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515220316.png" style="zoom:80%;" />

&emsp;&emsp;我们可以首先以最左边的路径的黑色结点个数为每条路径上的黑色结点数量的参考值，然后通过``dfs``得到每条路径的黑色结点数量，每遍历到一个根节点，就得到了一条路径，每次得到一条路径后比较一下该路径的黑色结点数量和黑色结点基准值是否相等即可。

```cpp
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
    Node *left = _root;
    while (left)
    {
        if (left->_color == BLACK)
            ++banchmark;
        left = left->_left;
    }

    return _isbalance(_root, banchmark, 0);
}

bool _isbalance(Node *root, int banchmark, int blacknum)
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
    if (root->_color == BLACK)
        ++blacknum;

    return _isbalance(root->_left, banchmark, blacknum) && _isbalance(root->_right, banchmark, blacknum);
}
```

&emsp;&emsp;每次插入后都检查一下，验证一下我们的红黑树插入没有问题：

```cpp
void RBTreetest1()
{
	RBTree<int, int> rbt1;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	const int N = 100000000;
	for (auto e : a)
	{
		rbt1.Insert(make_pair(e, e));
		cout << e << ':' << rbt1.isbalance() << endl;
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515222229.png" style="zoom:80%;" />

&emsp;&emsp;然后我们来看看红黑树的层数，开release版本往红黑树中插入``1e9``个结点：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515222503.png" style="zoom:80%;" />

&emsp;&emsp;可以看出红黑树的效率还是非常不错的。

## 6 红黑树的删除

&emsp;&emsp;因为其较为复杂，因此我们这里不做讲解，详情可参考这篇博客：[红黑树 - _Never_ - 博客园 (cnblogs.com)](https://www.cnblogs.com/fornever/archive/2011/12/02/2270692.html)

## 7 红黑树的应用

1. C++ STL库 -- map/set、mutil_map/mutil_set 
2. Java 库 
3. linux内核 
4. 其他一些库

&emsp;&emsp;基本红黑树就是数据加载到内存的二叉搜索树中综合性能最好的了。

&emsp;&emsp;数据库中，为快速检索数据，一般会将数据在磁盘中以B树系列结构来存储，B树是一颗多叉树，层数更低。

# 二、仅插入功能的红黑树封装出一个简单的map和set

## 1 STL中的架构

&emsp;&emsp;STL中，仅用一颗V的红黑树就实现出了map和set，我们来具体看看它是怎么做到的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515223320.png" style="zoom:80%;" />

&emsp;	可见``STL``中是把红黑树的结点模板参数仅限制为一个，即树的节点存的值中的值的类型是什么，红黑树的类模板参数的第一个参数为关键字，第二个模板参数为节点值类型，如果是map就是一个pair，如果是set就是一个普通的``T``。

&emsp;&emsp;为了控制set和map比较方式的不同，增加一个模板参数``Compare``，它来保证我们的``T``是从什么东西来比。

&emsp;&emsp;即让map和set传给红黑树一个模板参数，它是一个函数对象，然后通过这个告知红黑树从T的什么东西是关键字，然后用这个函数对象提取出这个关键字进行比较，``set``就直接通过值比较，map通过``.first``比较

## 2 set和map的第一层封装

```cpp
// map
namespace Router
{
	template <class K, class V>
	class map
	{
	public:
		// 指定T内哪个是关键字
		struct MapKeyofT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		bool insert(const pair<K, V>& kv)
		{
			_t.Insert(kv);
		}
	private:
		// 关键字 树中结点值
		RBTree<K, pair<K, V>, MapKeyofT> _t;
	};
}
// set
namespace Router
{
	template <class T>
	class set
	{
	public:
		struct SetKeyofT
		{
			const T& operator()(const T& k)
			{
				return k;
			}
		};
		bool insert(const T& key)
		{
			return _t.Insert(key);
		}
	private:
		RBTree<T, T, SetKeyofT> _t;
	};
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515225616.png" style="zoom:80%;" />

&emsp;&emsp;根据STL的架构，我们修改一下那颗红黑树：

```cpp
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

    // 红黑树 关键字,结点中的值,怎么从结点的值类型中得到关键字
    template <class K, class T, class KeyofT>
    class RBTree
    {
        typedef RBTreeNode<T> Node;
    public:
        RBTree() : _root(nullptr) {}
        void inorder()
        {
            _inorder(_root);
        }
        // 插入
        bool Insert(const T& data)
        {
            if (_root == nullptr)
            {
                _root = new Node(data);
                _root->_color = BLACK;
                return true;
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
                    return false;
            }
            // 插入一个结点 只会影响它的祖先的平衡因子
            cur = new Node(data);
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
}
```

## 3 set和map的迭代器

&emsp;&emsp;为实现访问map和set中的元素，我们提供迭代器，首先，仿照``list``的模拟实现中我们实现的迭代器：

```cpp
// 迭代器
template <class T, class Ref, class Ptr>
struct RBTreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef RBTreeIterator<T, Ref, Ptr> self;
    // 结点就是一个迭代器。
    Node *_node;
    RBTreeIterator(Node *node) : _node(node) {}
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
    self &operator++()
    {
        //...

        // 最后返回解引用this
        return *this;
    }
    bool operator==(self& it)
    {
        return _node == it._node;
    }
    bool operator!=(self& it)
    {
        return !(*this == it);
    }
};

```

&emsp;&emsp;然后在红黑树中增加迭代器，首先提供begin和end迭代器：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515231933.png" style="zoom:80%;" />

&emsp;&emsp;根据走中序的规律，``begin``就是最左结点的的迭代器，end就是最右节点的后一个结点，即``nullptr``。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515232126.png" style="zoom:80%;" />

&emsp;&emsp;接下来聚焦于``operator++``的逻辑，即中序的下一个：

&emsp;&emsp;因为中序的顺序是左中右，++it，访问到it时，我们认为it的左树已经结束了，

- 在中序顺序中，如果当前结点的右子树不为空，则“下一个结点“一定是右子树的最左结点。
- 如果右子树是空，详情见下图：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220515234443.png" style="zoom:80%;" />

&emsp;&emsp;这就是三叉连的好处，方便的直接从孩子找到父亲，实现如下：

```cpp
// ++迭代器 指向中序的下一个位置
self &operator++()
{
    Node *cur = this->_node;
    if (cur->_right)
    {
        Node *ans = cur->_right;
        while (ans && ans->_left)
            ans = ans->_left;
        _node = ans;
    }
    else
    {
        Node *parent = cur->_parent;
        while (parent && parent->_left != cur)
        {
            cur = parent;
            parent = cur->_parent;
        }
        _node = parent;
    }
    return *this;
}

```

&emsp;&emsp;再给set和map提供迭代器的层，注意这里要指明这里是一个类型，因为这个类模板还没实例化，所以要用``typename``关键字。

&emsp;&emsp;**map**

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516000905.png" style="zoom:80%;" />

&emsp;&emsp;**set**

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516001024.png" style="zoom:80%;" />

&emsp;&emsp;测试一下：(范围for是基于迭代器的，set用迭代器，map用范围for)

```cpp
void test_set()
{
    set<int> myset;
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for (auto c : a)
        myset.insert(c);
    auto it = myset.begin();
    while (it != myset.end())
    {
        cout << *it << endl;
        ++it;
    }
}

void test_map()
{
    map<int, int> mymap;
    mymap.insert(make_pair(1, 1));
    mymap.insert(make_pair(3, 3));
    mymap.insert(make_pair(-5, -5));
    mymap.insert(make_pair(-8, -8));
    mymap.insert(make_pair(9, 9));
    for (auto &p : mymap)
    {
        cout << p.first << ':' << p.second << endl;
    }
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516001246.png" style="zoom:80%;" />

&emsp;&emsp;operator--：与operator++顺序相反，它的顺序是右根左，如果当前结点的左子树不为空，则去访问左子树的最右节点。

&emsp;&emsp;否则，沿着三叉连找第一个是父亲的右的节点，然后要访问的就是父亲节点。

```cpp
self &operator--()
{
    Node *cur = this->_node;
    if (cur->_left)
    {
        Node *ans = cur->_left;
        while (ans && ans->_right)
            ans = ans->_right;
        _node = ans;
    }
    else
    {
        Node *parent = cur->_parent;
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
```

&emsp;&emsp;再提供一个``find``函数，首先在红黑树中提供find函数，然后map/set中提供一个接口即可。

```cpp
iterator find(const K &key)
{
    Node *cur = _root;
    KeyofT kot;
    while (cur)
    {
        if (kot(cur->_data) < key)
            cur = cur->_right;
        else if (kot(cur->_data) > key)
            cur = cur->_left;
        else
            return iterator(cur);
    }
    return end();
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521093652.png" style="zoom:80%;" />

&emsp;&emsp;因为模板参数不支持修改map/set的底层数据结构，所以map/set并不是适配器。

## 4 map的operator[]

&emsp;&emsp;首先修改插入的返回值：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521094628.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521095253.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521095310.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521095328.png" style="zoom:80%;" />

&emsp;&emsp;然后为map增加``operator[]``，其原理与我们之前在map中学习的``operator[]``一样：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521095209.png" style="zoom:80%;" />

## 5 析构函数、拷贝构造函数与赋值

&emsp;&emsp;应对拷贝和赋值的场景：

```cpp
set<int> s(p);
p = s;
```

&emsp;&emsp;当前我们实现的是一个浅拷贝，如果增加一个析构函数，则会因为浅拷贝析构同一块资源两次寄了。

&emsp;&emsp;所以先在红黑树中增加一个析构函数，其原理与销毁二叉搜索树一样，我们无需在set和map中增加析构函数和拷贝构造，因为对于自定义类型，编译器默认生成的这些函数会去掉对应类型的函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521100635.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521100708.png" style="zoom:80%;" />

&emsp;&emsp;然后以下代码就会崩溃：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521100746.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521100819.png" style="zoom:80%;" />

&emsp;&emsp;控制一个拷贝构造函数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521102132.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521101952.png" style="zoom:80%;" />

&emsp;&emsp;然后测试代码就可以通过：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521102458.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521102524.png" style="zoom:80%;" />

&emsp;&emsp;赋值的现代写法：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521103619.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521103720.png" style="zoom:80%;" />













&emsp;&emsp;