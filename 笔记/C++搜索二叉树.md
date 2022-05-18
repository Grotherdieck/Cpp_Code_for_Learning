# 一、二叉搜索树的定义

&emsp;&emsp;对二叉搜索树的任何一个结点来说，其左子树的节点的值一定比当前结点的值小，右子树的节点的值一定比当前结点的值大。

&emsp;&emsp;二叉搜索树正如其名字，是用来查找的。

&emsp;&emsp;显然它的最多查找次数是其高度次。

&emsp;&emsp;但是理想情况是搜索二叉树是完全二叉树形态，但是如果二叉树是那种单边的斜着的那种样子呢？

&emsp;&emsp;这是时间复杂度就会变成``O(n)``，时间复杂度大幅提高。

&emsp;&emsp;因此搜索二叉树是不成熟的，为了优化它这种情况，计算机科学家提出了平衡二叉树的概念，它的两个经典实现就是``AVL``树和红黑树。

&emsp;&emsp;搜索二叉树的另一性质是其中序遍历的结果就是有序序列，因此它也被叫做排序二叉树。

# 二、二叉搜索树的代码实现

## 1 基础框架

&emsp;&emsp;二叉树的结构我们很熟悉了，这里增加上模板，定义为模板类即可。

```cpp
// 结点
template <class K>
struct BSTNode
{
	BSTNode(const K& key = K())
		: _val(key), _left(nullptr), _right(nullptr)
	{}
	K _val;
	BSTNode<K>* _left;
	BSTNode<K>* _right;
};

// 树

template <class K>
class BSTree
{
public:
	typedef BSTNode<K> Node;
	BSTree()
		: _root(nullptr)
	{}
private:
	Node* _root;
};
```



## 2 插入结点

&emsp;&emsp;我们发现，如果树为空，那么新的结点直接成为根节点即可；

&emsp;&emsp;否则，我们就先遍历这课树，利用二叉搜索树的特点，其左子树的值全部小于根结点，其右子树的值全部大于根结点，如果我们要插入的值比根节点大，那么它应该插入在右子树，如果要插入的值比根节点小，那么它应该插入在左子树，如果要插入的值和根节点相等，那么它是重复结点，不要插入。

&emsp;&emsp;这样我们会遍历到一个空结点位置，这个位置就是我们的节点应该插入的位置，但是我们要插入结点还需要之前那个位置啊，不然怎么插入到树上，所以还要维护一个``parent``指针。

```cpp
bool insert(const K &key)
{
    if (_root == nullptr)
    {
        _root = new Node(key);
        return true;
    }
    Node *cur = _root, *parent = nullptr;
    while (cur)
    {
        parent = cur;
        if (cur->_val < key)
        {
            cur = cur->_right;
        }
        else if (cur->_val > key)
        {
            cur = cur->_left;
        }
        else
            return false;
    }
    if (parent->_val > key)
        parent->_left = new Node(key);
    else
        parent->_right = new Node(key);
    return true;
}
```



## 3 中序遍历

&emsp;&emsp;中序遍历我们需要在函数的参数中不断变换根节点的值（至少递归写法是这样的），所以我们可以单独搞一个子函数以进行中序遍历。

```cpp
void Inorder()
{
    _Inorder(_root);
    return;
}
void _Inorder(Node *root)
{
    if (root == nullptr)
        return;
    _Inorder(root->_left);
    cout << root->_val << ' ';
    _Inorder(root->_right);
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220412155316.png" style="zoom:80%;" />



## 4 查找

&emsp;&emsp;查找也是一个比较简单的操作，和插入类似。

```cpp
Node* find(const K &key) const
{
    Node *cur = _root;
    while (cur)
    {
        if (cur->_val == key)
            return cur;
        else if (cur->_val > key)
            cur = cur->_left;
        else
            cur = cur->_right;
    }
    return n;
}
```



## 5 删除

&emsp;&emsp;如果是叶子结点，直接干掉就行，并且把其父节点的对应指针置空，如下图的0、2。

&emsp;&emsp;那么如果我们要删除单子树的节点呢？把自己的子树给接到父节点就行如下图的8。

&emsp;&emsp;上面这两种情况，可以合并为一种情况，直接删除，如果左为空，把右孩子给自己的父节点，否则把左孩子给父亲。

&emsp;&emsp;假如要删除有两个孩子的结点呢？如下图中的5和7：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220415213444.png" style="zoom:80%;" />

&emsp;&emsp;我们使用**替换法删除**，我这个点不太好删除，找一个其他的结点，如果来替换的值能比左子树大，右子树小，那么就过来替换就行了，根据搜索二叉树的性质，需要有这种能来替换这个结点的，就是**其左子树的最右结点（左子树的最大结点）或右子树的最左节点（右子树的最小结点）**，并且这两种结点必然是个叶子结点，所以删除起来应该比较容易把，实际细节多的要死。

&emsp;&emsp;情况一：托孤时父亲是空，那么说明自己是根节点，要修改根节点为孤；

&emsp;&emsp;情况二：找右子树的最左结点，替换后，正常来讲应该让最左节点的父亲的左去接最左结点的右，但是如果最左结点他就没动过呢，也就是说此时``rightmaxleft == cur->right``，此时显然要让``cur->right = rightmaxleft;``。

```cpp
bool erase(const K &key)
{
    Node *cur = _root;
    Node *parent = nullptr;
    while (cur)
    {
        if (cur->_val > key)
        {
            parent = cur;
            cur = cur->_left;
        }
        else if (cur->_val < key)
        {
            parent = cur;
            cur = cur->_right;
        }
        else
        {
            // 找到了 准备删除
            if (cur->_left == nullptr)
            {
                // 特判父亲为空的情况 这时需要修改根
                if (parent == nullptr)
                {
                    _root = cur->_right;
                }
                else
                {
                    // 若父亲不为空 则根据我是父亲的位置来判断我要交给父亲的还是是啥
                    if (parent->_left == cur)
                    {
                        parent->_left = cur->_right;
                    }
                    else
                    {
                        parent->_right = cur->_right;
                    }
                }
                delete cur;
                cur = nullptr;
                return true;
            }
            else if (cur->_right == nullptr)
            {
                if (parent == nullptr)
                {
                    _root = cur->_left;
                }
                else
                {
                    if (parent->_left == cur)
                    {
                        parent->_left = cur->_left;
                    }
                    else
                    {
                        parent->_right = cur->_left;
                    }
                }
                delete cur;
                cur = nullptr;
                return true;
            }
            else
            {
                // 左右都不为空 替换法删除
                // 假设找右子树的最左结点
                Node *p = cur; // 为了删除这个结点保留的它的父亲
                Node *rightmaxleft = cur->_right;
                while (rightmaxleft->_left != nullptr)
                {
                    p = rightmaxleft;
                    rightmaxleft = rightmaxleft->_left;
                }
                // swap(rightmaxleft->_val, cur->_val);
                // cur的数据被覆盖成_val
                cur->_val = rightmaxleft->_val;
                // 如果p->_right就等于rightmaxleft
                // 那么说明p就没动 这时候要把p->_right连到rightmaxleft->_right
                if (p->_right == rightmaxleft)
                {
                    p->_right = rightmaxleft->_right;
                }
                // 否则 要把p->_left连到rightmaxleft的_right
                else
                {
                    p->_left = rightmaxleft->_right;
                }
                delete rightmaxleft;
                rightmaxleft = nullptr;
                return true;
            }
        }
    }
    return false;
}
```

&emsp;&emsp;非常麻烦！

## 6 递归查找、插入、删除

&emsp;&emsp;查找还算简单，直接走递归就行：

```cpp
Node* _findR(Node* root, const K& key)
{
    if (root == nullptr) return nullptr;
	if (root->_val == key) return root;
    else if (root->_val > key) return _findR(root->_left, key);
	else return _findR(root->_right, key);
}
```

&emsp;&emsp;递归插入就有点意思了，考虑到插入时其实我们要修改``Node*``的值，也就是要修改结点指针的值，所以我们递归插入的参数是``Node*&``，这样就可以在到达空结点时，直接让``root = new Node(key);``使得让前一个结点的孩子指针的值被引用后修改。

```cpp
bool _insertR(Node *&root, const K &key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        return true;
    }
    if (root->_val > key)
    {
        return _insertR(root->_left, key);
    }
    else if (root->_val < key)
    {
        return _insertR(root->_right, key);
    }
    else
        return false;
}
```

&emsp;&emsp;递归删除也是同理，找到结点后，如果左子树或右子树为空，就直接托孤；若都不为空，则使用替换法，首先交换待删除结点和右子树的最左结点的值，然后在右子树中删除``key``，它一定是一个左子树为空的节点，可以通过上面的逻辑干掉。

```cpp
bool _eraseR(Node *&root, const K &key)
{
    if (root == nullptr)
        return false;
    if (root->_val > key)
        return _eraseR(root->_left, key);
    else if (root->_val < key)
        return _eraseR(root->_right, key);
    // 找到了这个结点
    else
    {
        Node *del = root;
        // 如果左子树为空
        if (root->_left == nullptr)
            root = root->_right;
        // 右子树为空
        else if (root->_right == nullptr)
            root = root->_left;
        else
        {
            // 都不为空 找右子树的最左结点
            Node *rightmin = root->_right;
            while (rightmin->_left)
            {
                rightmin = rightmin->_left;
            }
            // 替换法 root的值替换为rightmin的值
            swap(root->_val, rightmin->_val);
            // 然后在右子树中删除这个结点
            return _eraseR(root->_right, key);
            // 删除这个结点
        }
        delete del;
        return true;
    }
}
```

# 三、搜索树的价值

- 搜索，key模型或``<key, value>``键值对模型。
- 排序加去重

&emsp;&emsp;``<key, value>``可以通过模板增加一个参数来实现：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220423151052.png" style="zoom:80%;" />

&emsp;&emsp;一个简易应用：单词翻译

```cpp
void test1()
{
    BSTree<string, vector<string>> dic;
	dic.insert("sort", { "排序" });
    dic.insert("left", { "左边" });
	dic.insert("right", { "右边" });
    dic.insert("map", { "地图", "映射" });
	string str;
    while (1)
	{
        cout << "请输入单词 :";
		cin >> str;
		BSTNode<string, vector<string>>* pnode = dic.find(str);
        if (pnode == nullptr) cout << "查无此单词" << endl;
		else
		{
            cout << "翻译为:";
			for (const string& wd : pnode->_val)
			{
				cout << wd << ' ';				}
				cout << endl;
			}
		}
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220423152519.png" style="zoom:80%;" />

# 四、普通搜索二叉树的问题

&emsp;&emsp;搜索二叉树在有序插入时，会退化成一个单只的二叉树，其深度为``O(N)``，此时搜索效率就很低，所以单独使用搜索二叉树的场景很少，因为你的效率是O(N)的话我为啥不直接遍历一遍数组呢？

&emsp;&emsp;所以我们后续在使用搜索二叉树时，一般使用的是**平衡二叉搜索树**，左右比较均匀，树的高度可以控制在``O(logN)``，此时插入搜索查找的效率一般就比较高了。

# 五、二叉树的OJ



<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220423170349.png" style="zoom:80%;" />

1 三叉链——转化为链表相交问题

2 搜索二叉树：如果两个值一个比自己小，一个比自己大，我就是最近公共结点；否则都比我小则递归搜索左树，都比我大则递归搜索右树

3 普通树：观察到规律：对一个根节点拉说，如果p q在我左右两边，则我就是最近公共祖先，否则如果都在我左边，则去左边搜索；否则如果都在我右边，就去右边搜索。

树的遍历非递归：

&emsp;&emsp;思考递归的过程，一个树的访问分为两个部分：

- 左路结点，并且左路结点入栈;
- 依次出栈访问左路结点的右子树，右子树又可以当成一棵树（原问题）访问。

```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) 
    {
        // 栈中存右子树尚未访问的节点
        stack<TreeNode*> st;
        vector<int> ans;
        auto cur = root;
        // 每一次一个循环都是遍历一棵树
        // cur非空且栈不为空(栈中元素表示其右树还没访问)则要访问
        while (cur != nullptr || !st.empty())
        {
            // 1.把元素加入ans中 并且遍历其左路节点
            while (cur)
            {
                ans.push_back(cur->val);
                st.push(cur);
                cur = cur->left;
            }
            // 获得栈顶节点的右子树
            TreeNode* top = st.top();
            st.pop();
            // 访问栈顶节点的右子树 利用循环解决
            cur = top->right;
        }
        return ans;
    }
};
```

&emsp;&emsp;中序遍历非递归：

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) 
    {
        // 栈中存右子树尚未访问的节点
        stack<TreeNode*> st;
        vector<int> ans;
        auto cur = root;
        // 每一次一个循环都是遍历一棵树
        // cur非空且栈不为空(栈中元素表示其右树还没访问)则要访问
        while (cur != nullptr || !st.empty())
        {
            // 1.把元素加入ans中 并且遍历其左路节点
            while (cur)
            {
                // ans.push_back(cur->val);
                st.push(cur);
                cur = cur->left;
            }
            // 获得栈顶节点的右子树
            TreeNode* top = st.top();
            st.pop();
            ans.push_back(top->val);
            // 访问栈顶节点的右子树 利用循环解决
            cur = top->right;
        }
        return ans;
    }
};
```

&emsp;&emsp;后序遍历非递归：

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) 
    {
        // 对于一个根节点 如果其右树没被访问过 则访问其右树
        // 如果其右树已经被访问过了 则这个结点可以入答案
        // 怎么判断右树已经被访问过了呢？ 
        // 要么其右树为空 要么根据后序遍历的特点 
        // 其前一个访问的节点一定是右树的根节点
        vector<int> ans;
        stack<TreeNode*> st;
        if (root == nullptr) return ans;
        auto cur = root;
        TreeNode* prev = nullptr;
        while (cur || !st.empty())
        {
            // 左路入栈
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            // 判断栈顶节点
            auto top = st.top();
            // 如果已经访问过右树或右树为
            if (top->right == nullptr || top->right == prev)
            {
                prev = top;
                ans.push_back(top->val);
                st.pop();
            }
            // 否则 访问其右树
            else 
            {
                cur = top->right;
            }
        }
        return ans;
    }
};
```



