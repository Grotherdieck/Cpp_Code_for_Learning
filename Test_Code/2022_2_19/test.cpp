#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//class Stack {
//public:
//    Stack(int capacity = 4) : _top(0), _capacity(capacity)
//    {
//        _a = new int[_capacity];
//        cout << "Stack(int)" << endl;
//    }
//    ~Stack()
//    {
//        delete[] _a;
//        _a = nullptr;
//        _top = 0;
//        _capacity = 0;
//        cout << "~Stack()" << endl;
//    }
//private:
//    int* _a;
//    int _top;
//    int _capacity;
//};
//
//int main()
//{
//    Stack* pst = new Stack(10);
//    // 先向堆申请栈的空间 然后调用栈的构造函数(给int* _a申请堆上的内存)
//    delete pst;
//    Stack* pst1 = (Stack*)operator new(10);
//    // 先调用栈的析构函数清理栈的资源(归还int* _a的内存) 
//    // 然后把pst指向的栈对象本身的内存归还给堆内存空间
//}

struct ListNode
{
    ListNode* _next;
    ListNode* _prev;
    int _data;
    ListNode(int val = 0) : _data(val), _next(nullptr), _prev(nullptr)
    {}
    void* operator new(size_t n)
    {
        // 借助STL中的空间配置器来充当内存池
        // 这样List申请结点 归还结点时不用直接找系统 速度会相对快一点
        void* p = nullptr;
        cout << "My size = " << n << endl;
        p = allocator<ListNode>().allocate(1);
        cout << "memory pool allocate" << endl;
        return p;
    }
    void operator delete(void* p)
    {
        allocator<ListNode>().deallocate((ListNode*)p, 1);
        cout << "memory pool deallocate" << endl;
    }
};

// ListNode* newnode = new ListNode(1);
// 重载的那个operator new(sizeof(ListNode)) + ListNode(1)

/*void* operator new[](size_t sz)
{
    cout << "sz = " << sz << endl;
    return malloc(sz);
}*/

//class List
//{
//public:
//    List()
//    {
//        _head = new ListNode;
//        _head->_next = _head;
//        _head->_prev = _head;
//    }
//    ~List()
//    {
//        ListNode* cur = _head->_next;
//        while (cur != _head)
//        {
//            ListNode* next = cur->_next;
//            delete cur;
//            cur = next;
//        }
//        delete _head;
//        _head = nullptr;
//    }
//    void push_back(int val)
//    {
//        ListNode* newnode = new ListNode(val);
//        ListNode* tail = _head->_prev;
//        tail->_next = newnode;
//        newnode->_prev = tail;
//        newnode->_next = _head;
//        _head->_prev = newnode;
//    }
//private:
//    ListNode* _head;
//};
//int main()
//{
//    /*List l;
//    l.push_back(1);
//    l.push_back(2);
//    l.push_back(3);
//    l.push_back(4);
//    l.push_back(5);
//    l.push_back(6);
//    l.push_back(7);*/
//    //ListNode* l = new ListNode[10];
//    char* str = new char[1024u * 1024u * 1024u * 2 - 1];
//    return 0;
//}

//void swap(int& a, int& b)
//{
//    if (a != b)
//    {
//        a ^= b;
//        b ^= a;
//        a ^= b;
//    }
//}
//
//void swap(double& a, double& b)
//{
//    double tmp = a;
//    a = b;
//    b = tmp;
//}

//template <class T>//这里也可以写 template <typename T> 模板参数列表
//void Swap(T& a, T& b)// 函数参数列表
//{
//    T tmp = a;
//    a = b;
//    b = tmp;
//}
//
//int main()
//{
//    int a = 2, b = 1;
//    double c = 1.1, d = 1.2;
//    char e = '1', f = '2';
//    Swap(a, b);
//    Swap(c, d);
//    Swap(e, f);
//}

//int main()
//{
//    char s[] = "我是你爹";
//    cout << sizeof(s) << endl;
//}

//int cnt[26] = { 0 };
//string repeatLimitedString(string s, int repeatLimit)
//{
//    int n = s.size();
//    for (auto ch : s)
//    {
//        ++cnt[ch - 'a'];
//    }
//    string ret;
//    int i = 25;
//    while (i >= 0)
//    {
//        if (cnt[i] != 0)
//        {
//            int num = min(cnt[i], repeatLimit);
//            int tmp = num;
//            while (num--)
//            {
//                ret += i + 'a';
//            }
//            cnt[i] -= tmp;
//            if (cnt[i] == 0)
//            {
//                --i;
//            }
//            else
//            {
//                int j = i - 1;
//                while (j >= 0)
//                {
//                    if (cnt[j] > 0) break;
//                    --j;
//                }
//                if (j >= 0)
//                {
//                    ret += j + 'a';
//                }
//                else
//                {
//                    break;
//                }
//            }
//        }
//        else
//        {
//            --i;
//        }
//    }
//    return ret;
//}
//
//int main()
//{
//    string s = repeatLimitedString("cczazcc", 3);
//}

//void trans(string& s, int a, int b, char ch)
//{
//    if (a <= b)
//    {
//        for (int i = a; i <= b; ++i)
//        {
//            s[i] = ch;
//        }
//    }
//}
//string pushDominoes(string dominoes)
//{
//    int n = dominoes.size();
//    string ret = dominoes;
//    int previdx = -1;
//    char prevch = 'N';
//    // 一个区间形如[R....L]或[L.....L]或[R.....R]或[L....R]
//    for (int i = 0; i < n; ++i)
//    {
//        // 如果当前区间右边的力是'L'
//        if (dominoes[i] == 'L')
//        {
//            // 如果区间左端点是'N' 前继还没进串 那么就把区间全部染色成'L'
//            // 表示向左推
//            if (prevch == 'N')
//            {
//                trans(ret, previdx + 1, i - 1, 'L');
//            }
//            // [L...L] 全部向左推
//            else if (prevch == 'L')
//            {
//                trans(ret, previdx + 1, i - 1, 'L');
//            }
//            // [R....L] 左边一半向右 右边一半向左
//            else
//            {
//                int cnt = (i - previdx - 1) / 2;// 左右应当染色的个数
//                trans(ret, previdx + 1, previdx + cnt, 'R');
//                trans(ret, i - cnt, i - 1, 'L');
//            }
//            previdx = i;
//            prevch = 'L';
//        }
//        else if (dominoes[i] == 'R')
//        {
//            // [R......R] 全部染色成向右
//            if (prevch == 'R')
//            {
//                trans(ret, previdx + 1, i - 1, 'R');
//            }
//            // 其他情况不用做处理
//            previdx = i;
//            previdx = 'R';
//        }
//        
//    }
//    if (prevch == 'R')
//    {
//        // 如果前一个是'R' 走到结尾这个'R'还没处理 单独处理一下
//        trans(ret, previdx + 1, n - 1, 'R');
//    }
//    return ret;
//}
//
//int main()
//{
//    string s = pushDominoes(".L.R...LR..L..");
//}

#include <string>
#include <iostream>
#define read(x) scanf("%d", &(x))
#define print(x) printf("%d\n", (x))
using namespace std;

const int N = 1e5 + 10;
// 总共有N个数 每个数是31位
// 最多有31 * N个结点
const int M = 31 * N;

int son[M][2];
int idx = 0;
int a[N];

void insert(int x)
{
    // 从第30位(从0开始记)开始插入
    int p = 0;
    for (int i = 30; i >= 0; --i)
    {
        // 得到x的第i位
        int u = x >> i & 1;
        if (son[p][u] == 0) son[p][u] = ++idx;
        p = son[p][u];
    }
}

int query(int x)
{
    int p = 0;
    int ret = 0;
    for (int i = 30; i >= 0; --i)
    {
        int u = x >> i & 1;
        // 先看看能否走和第i位不相等的位置
        if (son[p][!u] != 0)
        {
            // 能走的话 先把值记录上然后再进去
            // 怎么记录呢 就是让ret整体往右移动一位然后加上当前位
            ret = (ret * 2) + !u;
            p = son[p][!u];
        }
        else
        {
            ret = (ret * 2) + u;
            p = son[p][u];
        }
    }
    return ret;
}


int main()
{
    int n;
    read(n);
    for (int i = 0; i < n; ++i) read(a[i]);
    int ret = 0;
    for (int i = 0; i < n; ++i)
    {
        // 先把当前数字插入Trie树
        insert(a[i]);
        ret = max(ret, query(a[i]));
    }
    print(ret);
    return 0;
}