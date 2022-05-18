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
//    // ���������ջ�Ŀռ� Ȼ�����ջ�Ĺ��캯��(��int* _a������ϵ��ڴ�)
//    delete pst;
//    Stack* pst1 = (Stack*)operator new(10);
//    // �ȵ���ջ��������������ջ����Դ(�黹int* _a���ڴ�) 
//    // Ȼ���pstָ���ջ��������ڴ�黹�����ڴ�ռ�
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
        // ����STL�еĿռ����������䵱�ڴ��
        // ����List������ �黹���ʱ����ֱ����ϵͳ �ٶȻ���Կ�һ��
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
// ���ص��Ǹ�operator new(sizeof(ListNode)) + ListNode(1)

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

//template <class T>//����Ҳ����д template <typename T> ģ������б�
//void Swap(T& a, T& b)// ���������б�
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
//    char s[] = "�������";
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
//    // һ����������[R....L]��[L.....L]��[R.....R]��[L....R]
//    for (int i = 0; i < n; ++i)
//    {
//        // �����ǰ�����ұߵ�����'L'
//        if (dominoes[i] == 'L')
//        {
//            // ���������˵���'N' ǰ�̻�û���� ��ô�Ͱ�����ȫ��Ⱦɫ��'L'
//            // ��ʾ������
//            if (prevch == 'N')
//            {
//                trans(ret, previdx + 1, i - 1, 'L');
//            }
//            // [L...L] ȫ��������
//            else if (prevch == 'L')
//            {
//                trans(ret, previdx + 1, i - 1, 'L');
//            }
//            // [R....L] ���һ������ �ұ�һ������
//            else
//            {
//                int cnt = (i - previdx - 1) / 2;// ����Ӧ��Ⱦɫ�ĸ���
//                trans(ret, previdx + 1, previdx + cnt, 'R');
//                trans(ret, i - cnt, i - 1, 'L');
//            }
//            previdx = i;
//            prevch = 'L';
//        }
//        else if (dominoes[i] == 'R')
//        {
//            // [R......R] ȫ��Ⱦɫ������
//            if (prevch == 'R')
//            {
//                trans(ret, previdx + 1, i - 1, 'R');
//            }
//            // �����������������
//            previdx = i;
//            previdx = 'R';
//        }
//        
//    }
//    if (prevch == 'R')
//    {
//        // ���ǰһ����'R' �ߵ���β���'R'��û���� ��������һ��
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
// �ܹ���N���� ÿ������31λ
// �����31 * N�����
const int M = 31 * N;

int son[M][2];
int idx = 0;
int a[N];

void insert(int x)
{
    // �ӵ�30λ(��0��ʼ��)��ʼ����
    int p = 0;
    for (int i = 30; i >= 0; --i)
    {
        // �õ�x�ĵ�iλ
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
        // �ȿ����ܷ��ߺ͵�iλ����ȵ�λ��
        if (son[p][!u] != 0)
        {
            // ���ߵĻ� �Ȱ�ֵ��¼��Ȼ���ٽ�ȥ
            // ��ô��¼�� ������ret���������ƶ�һλȻ����ϵ�ǰλ
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
        // �Ȱѵ�ǰ���ֲ���Trie��
        insert(a[i]);
        ret = max(ret, query(a[i]));
    }
    print(ret);
    return 0;
}