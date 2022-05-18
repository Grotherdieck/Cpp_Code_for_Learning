# 一、关联式容器

&emsp;&emsp;``STL``容器中，底层为线性序列的数据结构的容器``vector list deque forward_list``，这些容器被称为序列式容器；

&emsp;&emsp;关联式容器也是来存储数据的，插入元素时，数据是必须往固定的位置插入的，数据之间有着强烈的关联关系，因此数据的检索效率会更高。

# 二、key模型有序序列set

&emsp;&emsp;原型：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508091311.png" style="zoom:80%;" />

&emsp;&emsp;第二个参数是仿函数，用来给内部进行比较。

## 1 简单使用

&emsp;&emsp;所有的容器都可以用范围for或迭代器来遍历，其中范围for的底层的原理就是迭代器。

```cpp
int main()
{
	set<int> myset;
	myset.insert(1);
	myset.insert(3);
	myset.insert(-5);
	myset.insert(9);
	myset.insert(-10);
	auto it = myset.begin();
	while (it != myset.end())
	{
		cout << *it << ' ';
		++it;
	}
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508091826.png" style="zoom:80%;" />

## 2 迭代器

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092140.png" style="zoom:80%;" />

&emsp;&emsp;显然支持正向和反向迭代器的``set``的迭代器是一个双向迭代器。

## 3 修改容器

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092305.png" style="zoom:80%;" />

&emsp;&emsp;它的删除支持给一个迭代器位置删除、给一个值删除、或者给一个迭代器区间删除：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092324.png" style="zoom:80%;" />

&emsp;&emsp;删除一个迭代器位置和删除一个值的区别：如果按迭代器位置删除，给的是一个无效迭代器，很可能会报错。

```cpp
int main()
{
	set<int> myset;
	myset.insert(1);
	myset.insert(3);
	myset.insert(-5);
	myset.insert(9);
	myset.insert(-10);
	auto it = myset.begin();
	while (it != myset.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	it = myset.find(10);
	myset.erase(it);
	for (auto e : myset)
	{
		cout << e << ' ';
	}
	return 0;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092558.png" style="zoom:80%;" />

&emsp;&emsp;而用值删除，如果目标元素不存在，我们直接删，它不会给我报错，会通过返回值告诉我被删除的数据的个数：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092742.png" style="zoom:80%;" />

&emsp;&emsp;对于``set``来说，返回1表示这个元素存在且被删除，返回0表示这个元素不存在。

&emsp;&emsp;交换：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508092940.png" style="zoom:80%;" />

## 4 lower_bound和upper_bound

&emsp;&emsp;set维护的是一个有序集合，其``lower_bound(val)``返回的是第一个不在``val``之前的元素的迭代器。（即如果``set``中有``val``，它可以是指向``val``的迭代器）。

&emsp;&emsp;``upper_bound(val)``返回的是第一个在``val``之后的元素的迭代器，如果``set``中有``val``，它会指向它之后的一个元素。

# 二、multiset

&emsp;&emsp;为了解决排序而不去重的需求，``multiset``容器应运而生。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508093248.png" style="zoom:80%;" />

&emsp;&emsp;它的接口和``set``的接口都类似，区别在哪呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508093440.png" style="zoom:80%;" />

&emsp;&emsp;它可以直接排序，并且元素重复时依然允许我们插入。

## 1 multiset的find

&emsp;&emsp;既然``multiset``中可能有重复元素，那么我们``find(重复元素)``返回的迭代器到底是指向谁的?

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508093909.png" style="zoom:80%;" />

&emsp;&emsp;可见它找的是中序的第一个结点，返回的是中序的第一个值所在的结点的迭代器。

## 2 multiset的erase

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508094200.png" style="zoom:80%;" />

&emsp;&emsp;按迭代器删除只删除迭代器指向的节点，按值删除可以在``multiset``中删除所有值为``val``的结点。

&emsp;&emsp;这里如果一个一个删除，那么也可能出现迭代器失效的问题，而``C++98``中没有用返回值来防止迭代器失效，``C++11``给了我们用返回值来防止这种迭代器失效的场景：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508094625.png" style="zoom:80%;" />

&emsp;&emsp;如果不能用C++11，你可以提前储存下一个位置的迭代器来规避迭代器失效。

&emsp;&emsp;不过一次性删除``multiset``中所有值为``val``的元素，我们可以按值删除。

&emsp;&emsp;``set``没有像其他容器一样给我们提供专门的修改接口，就算通过迭代器也不能修改，``*it``在``set``中是常引用，无法修改。

&emsp;&emsp;因为擅自修改一个值，很可能直接破坏了搜索树的结构，有的结构破坏了以后，没法通过旋转等操作弄回来。

# 三、key-value模型有序序列map

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508095407.png" style="zoom:80%;" />

&emsp;&emsp;每个结点除了存一个``Key``，还存了一个``T``,它是使用``pair<const Key, T>``键值对实现的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508095539.png" style="zoom:80%;" />

## 1 map的简单使用

&emsp;&emsp;``map``的大部分操作和``set``都相同，除了这个``operator[]``：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508095704.png" style="zoom:80%;" />

&emsp;&emsp;它的``insert``：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508095916.png" style="zoom:80%;" />

&emsp;&emsp;它的``value_type``是``pair``去``typedef``出来的。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508100648.png" style="zoom:80%;" />

&emsp;&emsp;它的遍历不能直接把``pair``输出出来，因为``pair``没有去重载``operator<<``，

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508101211.png" style="zoom:80%;" />

```cpp
void test_map1()
{
	map<string, string> dict;
	// 第一种插入方式
	pair<string, string> p1("sort", "排序");
	dict.insert(p1);
	// 第二种插入方式 匿名对象
	dict.insert(pair<string, string>("unique", "不同的"));
	// 还可使用make_pair 优势在于自动推导类型
	dict.insert(make_pair("value", "值"));
	// 还可以用{}
	dict.insert({ "type", "类型" });
	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << '(' << (*it).first << ' ' << (*it).second << ')';
        // 还是operator->看起来正常
		cout << '(' << it->first << ' ' << it->second << ')';
		++it;
	}
	cout << endl;
    // 范围for
	for (auto& p : dict)
	{
		cout << '(' << p.first << ',' << p.second << ')' << endl;
	}
}
```

&emsp;&emsp;这里排序是按``key``进行排序的。

&emsp;&emsp;erase和find和set的类似，但是是只针对``key``做查找和删除。

## 2 map的operator[]

&emsp;&emsp;map的key不支持修改，但是其value支持修改。

&emsp;&emsp;如果我们朴素的去统计一个字典中单词出现的次数：

```cpp
void test_map2()
{
	string arr[] = { "苹果", "香蕉", "菠萝", "香蕉", "苹果", "梨", "苹果" };
	map<string, int> cnt;
	for (auto& s : arr)
	{
		auto it = cnt.find(s);
		if (it == cnt.end()) cnt.insert(make_pair(s, 1));
		else
		{
			++(*it).second;
		}
	}
}
```

&emsp;&emsp;这里还可以优化一下，``cnt.find``查找一次，``cnt.insert``再查找一次。

&emsp;&emsp;我们先看这个insert的返回值：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508103954.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508103941.png" style="zoom:80%;" />

&emsp;&emsp;如果key已经存在了，返回值的第二个成员为true，第一个成员就是新位置的迭代器，如果已经存在了，那么第二个成员为false，第一个成员为就是已经存在的位置的迭代器。

&emsp;&emsp;所以不用``find``了，直接用``insert``的返回值来搞就行了

```cpp
void test_map2()
{
	string arr[] = { "苹果", "香蕉", "菠萝", "香蕉", "苹果", "梨", "苹果" };
	map<string, int> cnt;
	for (auto& s : arr)
	{
		// 如果是key第一次出现 直接就插入进去了 pb.second == true
		auto pb = cnt.insert(make_pair(s, 1));
		// 如果插入失败 说明key不是第一次出现 这时
		// 返回了一个迭代器指向已经出现的节点
		// 然后利用这个迭代器++其second(次数)
		if (pb.second == false)
		{
			pb.first->second++;
		}
	}
    for (auto& kv : cnt)
	{
		cout << kv.first << ':' << kv.second << endl;
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508110928.png" style="zoom:80%;" />

&emsp;&emsp;但是其实更常用的做法是使用``operator[]``

```cpp
void test_map2()
{
	string arr[] = { "苹果", "香蕉", "菠萝", "香蕉", "苹果", "梨", "苹果" };
	map<string, int> cnt;
	for (auto& s : arr)
	{
		++cnt[s];
	}
	for (auto& kv : cnt)
	{
		cout << kv.first << ':' << kv.second << endl;
	}
}
```

&emsp;&emsp;以前的``operator[]``是数组行为，但这里``operator[]``是以关键字来返回value的引用，如果不存在则插入：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508111231.png" style="zoom:80%;" />

```cpp
// 这是operator[]的简略等价版本
(*((this->insert(make_pair(k,mapped_type()))).first)).second
```

&emsp;&emsp;含义就是``this``调用``insert``函数，插入``make_pair(k,mapped_type())``，然后得到其返回值``pair<iteraot, bool>``的``first``，即那个key位置的迭代器，然后解引用这个迭代器去访问其``second``，访问到``value``.

&emsp;&emsp;所以这个``operator[]``同时做到了插入、查找、修改value的功能，如果``[key]``第一次出现，那么它会做到插入并且返回刚初始化的value的引用，如果``[key]``不是第一次出现，通过查找返回``value``的引用，然后可以通过其他运算修改这个值。

&emsp;&emsp;``operator``的三种作用：

```cpp
dict["string"];// 单纯插入
dict["sort"] = "排序"; // 插入加排序
dict["sort"] = "不想玩了"; // 修改
```

# 四、multimap

&emsp;&emsp;它的用法和map的用法几乎一致，和``multiset``一样，如果``key``存在它仍然会继续插入。

&emsp;&emsp;因此它就没有``operator[]``，因为``key``相同的可能有很多节点，我到底要返回哪一个呢？

```cpp
void test_map3()
{
	multimap<string, string> mdict;
	mdict.insert(make_pair("排序", "sort"));
	mdict.insert(make_pair("排序", "mysort"));
	for (auto& e : mdict)
	{
		cout << e.first << ' ' << e.second << endl;
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508115220.png" style="zoom:80%;" />

&emsp;&emsp;它支持``count``，会返回关键字等于``key``的节点的个数。

&emsp;&emsp;``erase``和``multiset``也是一样，传迭代器就删除一个结点，传键值就删除所有键值为key的结点。

&emsp;&emsp;对于topk问题，数据量不大时，我们可以用``map<string, int>``计数，然后``vector<map<string, int>::iterator>``加函数对象排序；

&emsp;&emsp;也可以用``multimap<int, string>``把``<次数, 关键字>``存进来并排序，降序的话搞个``greater<int>``进去就行。

# 五、平衡二叉树—AVL树

&emsp;&emsp;前面对``map/multimap/set/multiset``进行了简单的介绍，在其文档介绍中发现，这几个容器有个共同点是： 其底层都是按照二叉搜索树来实现的，但是二叉搜索树有其自身的缺陷，假如往树中插入的元素有序或者接 近有序，二叉搜索树就会退化成单支树，时间复杂度会退化成O(N)，因此map、set等关联式容器的底层结构 是对二叉树进行了平衡处理，即采用平衡树来实现。

&emsp;&emsp;AVL树又称高度平衡二叉搜索树，以高度来控制二叉搜索树的平衡。

&emsp;&emsp;二叉搜索树虽可以缩短查找的效率，但如果数据有序或接近有序二叉搜索树将退化为单支树，查找元素相当 于在顺序表中搜索元素，效率低下。因此，两位俄罗斯的数学家G.M.Adelson-Velskii和E.M.Landis在1962年 发明了一种解决上述问题的方法：当向二叉搜索树中插入新结点后，如果能保证每个结点的左右子树高度之 差的绝对值不超过1(需要对树中的结点进行调整)，即可降低树的高度，从而减少平均搜索长度。

&emsp;&emsp;AVL树有很多实现方法，其中一种比较经典的实现方式就是去使用平衡因子（右子树高度减左子树高度），这种情况下，AVL树要求：

- 它的左右子树都是AVL树 
- 左右子树高度之差(简称平衡因子)的绝对值不超过1(-1/0/1)

&emsp;&emsp;如果一棵二叉搜索树是高度平衡的，它就是AVL树。如果它有n个结点，其高度可保持在 ，搜索时间复杂度``O(logN)``，效率就非常高，如果往AVL树中插入10亿个结点，它最多查找30次。

## 1 基础结构

```cpp
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
private:
	Node* _root;
};
```

## 2 插入

&emsp;&emsp;插入时，要更新祖先的平衡因子（更新到根也会结束），更新逻辑：

1. ``cur == parent->left``，``parent->bf--``。
2. ``cur == parent->right``，``parent->bf++``。
3. 如果更新后``parent->bf == 0``，说明更新前``parent``的bf是1或-1，现在变成0，说明填上了矮的那边，``parent``所在的子树高度不变，自然更新结束。
4. 更新以后，``parent->bf == 1 / -1``，当前``parent``所在子树是平衡的，但是要继续往上更新新插入结点的影响，说明更新前``parent``的``bf``是0，新插入的节点使得高度变高了，需要继续往上更新。
5. 更新以后，``parent->bf == 2 / -2``，则说明``parent``所在的子树已经不平衡了，需要旋转处理

&emsp;&emsp;我们提供一下插入的总框架：

```cpp
// 插入
bool Insert(const pair<K, V> &kv)
{
    if (_root == nullptr)
    {
        _root = new Node(kv);
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
```



## 3 旋转的情况

### I 右单旋(左边高)

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508164700.png)

&emsp;&emsp;注意这个过程要控制三叉链，结合下面的图，我们写出代码：

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508173611.png)

```cpp
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
    if (parent == —_root)
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
```

### II 左单旋(右边高)

&emsp;&emsp;同理，这里就是反过来了，parent的平衡因子是2，cur的平衡因子是1，只要画出图来，注意维护三叉链，很快就能写出来：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508174829.png" style="zoom:80%;" />

```cpp
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
```

### III 左右双旋和右左双旋

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220508181936.png)

```cpp
// 左右双旋
void RotateLR(Node *parent)
{
    // 先选parent的左孩子 进行左旋
    RotateL(parent->_left);
    // 再把parent进行右旋
    RotateR(parent);
    // 平衡因子更新：
}
// 右左双旋
void RotateRL(Node *parent)
{
    // 先旋parent的右孩子 进行右旋
    RotateR(parent->_right);
    // 再把parent进行左旋
    RotateL(parent);
    // 平衡因子更新
}
```

&emsp;&emsp;如何在左右双旋的情况下更新平衡因子我们稍后讨论。

## 4 验证平衡

&emsp;&emsp;手动验证未免过于麻烦，我们遍历每个点，如果每个点的左右子树的高度差小于一即说明平衡，否则说明不平衡。

```cpp
bool _isBalance(Node *root)
{
    if (root == nullptr)
        return true;
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

int _height(Node *root)
{
    if (root == nullptr)
        return 0;
    int leftheight = _height(root->_left);
    int rightheight = _height(root->_right);
    return 1 + max(leftheight, rightheight);
}
```

&emsp;&emsp;发现这组测试用例:``{4, 2, 6, 1, 3, 5, 15, 7, 16, 14}``通过不了验证：

```cpp
void TestAVLTree1()
{
	AVLTree<int, int> t;
	//int a[] = { 5, 4, 3, 2, 1 };
	// int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// int a[] = { 1, 2, 3, 4, 5 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto& e : a)
	{
		t.Insert(make_pair(e, e));
		if (!t.isBalance())
		{
			cout << "插入" << e << "出问题了" << endl;
		} 
	}
	t.Inorder();
	if (!t.isBalance()) cout << "该树异常" << endl;
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514095556.png" style="zoom:80%;" />

&emsp;&emsp;它的问题在于我们右左双旋时，平衡因子都是按照单旋时的平衡因子更新，没有做对应的平衡因子更新

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516001854.png" style="zoom:80%;" />

## 5 右左双旋平衡因子更新

&emsp;&emsp;触发右左双旋的三个场景如下，并且它们引发的不同平衡因子更新变化结果如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514104633.png" style="zoom:80%;" />

&emsp;&emsp;方法是去识别60的平衡因子，插入结点后，旋转前，第一种情况“60”的平衡因子是1，第二种情况“60”的平衡因子是-1，第三种情况60的平衡因子是0.

```cpp

// 左右双旋
void RotateLR(Node *parent)
{
    Node *subL = parent->_left;
    Node *subLR = subL->_right;
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
```



## 6 左右双旋平衡因子更新

&emsp;&emsp;仿照右左双旋平衡因子更新的方法，画出图来：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220514105655.png" style="zoom:80%;" />

```cpp
// 左右双旋
void RotateLR(Node *parent)
{
    Node *subL = parent->_left;
    Node *subLR = subL->_right;
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
```

## 7 通过验证

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516002558.png" style="zoom:80%;" />

## 8 AVL树的删除

&emsp;&emsp;因为AVL树也是二叉搜索树，可按照二叉搜索树的方式将节点删除，然后再更新平衡因子，只不错与删除不 同的时，删除节点后的平衡因子更新，最差情况下一直要调整到根节点的位置。

&emsp;&emsp;因为比较复杂，这里不做讲解，详细可以参考《算法导论》或者《数据结构-用面向对象方法与C++描述》殷人昆版。

## 9 AVL树的性能

&emsp;&emsp;AVL树是一棵绝对平衡的二叉搜索树，其要求每个节点的左右子树高度差的绝对值都不超过1，这样可以保证查询时高效的时间复杂度，即``logN`` 。**但是如果要对AVL树做一些结构修改的操作，性能非常低下**，比如： 插入时要维护其绝对平衡，旋转的次数比较多，更差的是在删除时，有可能一直要让旋转持续到根的位置。 因此：如果需要一种查询高效且有序的数据结构，而且数据的个数为静态的(即不会改变)，可以考虑AVL树， 但一个结构经常修改，就不太适合。

&emsp;&emsp;我们来测试一下AVL树插入1e9个结点的速度和它的高度。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220516003418.png" style="zoom:80%;" />

&emsp;&emsp;可以看到AVL树的效率还是很不错的。



