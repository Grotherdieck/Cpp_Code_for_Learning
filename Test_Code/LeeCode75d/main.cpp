#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

//typedef long long LL;
//long long numberOfWays(string s)
//{
//    int n = s.size();
//    int l = 0, r = n - 1;
//    LL res = 0;
//    while (l < r)
//    {
//        int stepl = 0;
//        while (l < r && s[l] != '0')
//        {
//            ++l;
//            ++stepl;
//        }
//        int stepr = 0;
//        while (r > l && s[r] != '0')
//        {
//            --r;
//            ++stepr;
//        }
//        if (stepl == 0 && stepr == 0) break;
//        int cnt = 0;
//        for (int i = l; i <= r; ++i)
//        {
//            if (s[i] == '1') ++cnt;
//        }
//        res += cnt;
//        ++l;
//    }
//    l = 0, r = n - 1;
//    while (l < r)
//    {
//        int stepl = 0;
//        while (l < r && s[l] != '0')
//        {
//            ++l;
//            ++stepl;
//        }
//        int stepr = 0;
//        while (r > l && s[r] != '0')
//        {
//            --r;
//            ++stepr;
//        }
//        if (stepl == 0 && stepr == 0) break;
//        int cnt = 0;
//        for (int i = l; i <= r; ++i)
//        {
//            if (s[i] == '1') ++cnt;
//        }
//        res += cnt;
//        --r;
//    }
//    l = 0, r = n - 1;
//    while (l < r)
//    {
//        int stepl = 0;
//        while (l < r && s[l] != '1')
//        {
//            ++l;
//            ++stepl;
//        }
//        int stepr = 0;
//        while (r > l && s[r] != '1')
//        {
//            --r;
//            ++stepr;
//        }
//        if (stepl == 0 && stepr == 0) break;
//        int cnt = 0;
//        for (int i = l; i <= r; ++i)
//        {
//            if (s[i] == '0') ++cnt;
//        }
//        res += cnt;
//        ++l;
//    }
//    l = 0, r = n - 1;
//    while (l < r)
//    {
//        int stepl = 0;
//        while (l < r && s[l] != '1')
//        {
//            ++l;
//            ++stepl;
//        }
//        int stepr = 0;
//        while (r > l && s[r] != '1')
//        {
//            --r;
//            ++stepr;
//        }
//        if (stepl == 0 && stepr == 0) break;
//        int cnt = 0;
//        for (int i = l; i <= r; ++i)
//        {
//            if (s[i] == '0') ++cnt;
//        }
//        res += cnt;
//        --r;
//    }
//    return res;
//}
//
//int main()
//{
//    cout << numberOfWays("001101") << endl;
//	return 0;
//}

//vector<vector<int>> findWinners(vector<vector<int>>& matches)
//{
//    vector<set<int>> ans(2);
//    unordered_map<int, int> mytable;// 记录loser
//    for (auto& mat : matches)
//    {
//        mytable[mat[1]]++;
//    }
//    for (auto& mat : matches)
//    {
//        int win = mat[0];
//        if (mytable.count(win) == 0)
//        {
//            ans[0].insert(win);
//        }
//        else if (mytable[win] == 1)
//        {
//            ans[1].insert(win);
//        }
//        int lose = mat[0];
//        if (mytable[lose] == 1)
//        {
//            ans[1].insert(lose);
//        }
//    }
//    vector<vector<int>> res(2);
//    for (int i = 0; i < 2; ++i)
//    {
//        for (auto p : ans[i])
//        {
//            res[i].push_back(p);
//        }
//    }
//    return res;
//}
//
//int main()
//{
//    vector<vector<int>> vec = { {1, 3},{2, 3},{3, 6},{5, 6},{5, 7},{4, 5},{4, 8},{4, 9},{10, 4},{10, 9} };
//    findWinners(vec);
//}

//typedef long long LL;
//int maximumCandies(vector<int>& candies, long long k)
//{
//    LL sum = accumulate(candies.begin(), candies.end(), LL(0));
//    if (k > sum) return 0;
//    if (k == sum) return 1;
//    int sz = candies.size();
//    int l = 0, r = *max_element(candies.begin(), candies.end());
//    while (l < r)
//    {
//        int mid = (l + r + 1) >> 1;
//        LL cnt = 0;
//        for (auto c : candies)
//        {
//            cnt += c / mid;
//        }
//        if (cnt >= k)
//        {
//            l = mid;
//        }
//        else
//        {
//            r = mid + 1;
//        }
//    }
//    return r;
//}
//
//int main()
//{
//    vector<int> vec = { 5,6,4,10,10,1,1,2,2,2 };
//    cout << maximumCandies(vec, 9);
//}

//class NumArray {
//public:
//    NumArray(vector<int>& nums)
//        : tr(nums.size() + 1), num(nums)
//    {
//        for (int i = 0; i < nums.size(); ++i)
//        {
//            add(i + 1, nums[i]);
//        }
//    }
//
//    int lowbit(int x)
//    {
//        return x & (-x);
//    }
//
//    void add(int k, int val)
//    {
//        for (int i = k; i < tr.size(); i += lowbit(i)) tr[i] += val;
//    }
//
//    void update(int index, int val)
//    {
//        int prval = num[index];
//        add(index, val - prval);
//    }
//
//    int sum(int index)
//    {
//        int res = 0;
//        if (index == 0) return res;
//        for (int i = index; i > 0; i -= lowbit(i)) res += tr[i];
//        return res;
//    }
//    int sumRange(int left, int right)
//    {
//        return sum(right + 1) - sum(left);
//    }
//private:
//    vector<int> tr;
//    vector<int>& num;
//};
//
//int main()
//{
//    vector<int> a = { -1 };
//    NumArray n(a);
//    cout << n.sumRange(0, 0) << endl;
//    n.update(0, 1);
//    cout << n.sumRange(0, 0) << endl;
//}

//typedef long long LL;
//// 树状数组
//class BIndexT
//{
//public:
//    BIndexT(int sz)
//        : tr(sz + 1)
//    {}
//    int lowbit(int x)
//    {
//        return x & (-x);
//    }
//    void add(int k, int val)
//    {
//        for (int i = k; i < tr.size(); i += lowbit(i)) tr[i] += val;
//    }
//    int sum(int x)
//    {
//        int res = 0;
//        for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
//        return res;
//    }
//private:
//    vector<int> tr;
//};
//class Solution {
//public:
//    int countRangeSum(vector<int>& nums, int lower, int upper)
//    {
//        vector<LL> preSum(nums.size() + 1);
//        // 求解前缀和
//        for (int i = 0; i < nums.size(); ++i)
//        {
//            preSum[i + 1] = preSum[i] + nums[i];
//        }
//        vector<LL> alls;
//        for (LL p : preSum)
//        {
//            alls.push_back(p);
//            alls.push_back(p - upper);
//            alls.push_back(p - lower);
//        }
//        // 离散化
//        sort(alls.begin(), alls.end());
//        alls.erase(unique(alls.begin(), alls.end()), alls.end());
//        unordered_map<LL, int> fix;
//        int idx = 0;
//        for (LL num : alls)
//        {
//            fix[num] = idx++;
//        }
//        // 创建树状数组 其sum表示小于x的元素出现的次数
//        BIndexT B(preSum.size());
//        int res = 0;
//        // 遍历前缀和数组
//        // 查询前缀和下标(0, i)中值处于区间[preSum[i] - upper, preSum[i] - lower]的个数
//        for (int i = 0; i < preSum.size(); ++i)
//        {
//            LL p = preSum[i];
//            int l = fix[p - upper];
//            int r = fix[p - lower];
//            int L = B.sum(l);
//            int R = B.sum(r + 1);
//            res += R - L;
//            B.add(fix[p] + 1, 1);
//        }
//        return res;
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<int> vec = { -2, 5, -1 };
//    s.countRangeSum(vec, -2, 2);
//}

//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//string mypop(string& s)
//{
//    if (s.front() == '"')
//    {
//        return s.substr(1, s.size() - 2);
//    }
//    return s;
//}
//
//int main()
//{
//    string s;
//    getline(cin, s);
//    int i = 0;
//    int n = s.size();
//    vector<string> ans;
//    while (i < n)
//    {
//        // if (ans.size() == 4) break;
//        if (s[i] != '"')
//        {
//            int j = s.find(' ', i);
//            if (j != -1)
//            {
//                string tmp = s.substr(i, j - i);
//                ans.push_back(tmp);
//                i = j + 1;
//            }
//            else
//            {
//                string tmp = s.substr(i);
//                ans.push_back(tmp);
//                i = n;
//            }
//        }
//        else
//        {
//            int j = i + 1;
//            while (j < n && s[j] != '"') ++j;
//            string tmp = s.substr(i + 1, j - i - 1);
//            ans.push_back(tmp);
//            i = j + 1;
//        }
//    }
//    cout << ans.size() << endl;
//    for (const auto& s : ans)
//    {
//        cout << s << endl;
//    }
//    return 0;
//}

//class A
//{
//	~A()
//	{
//		delete this;
//		this = NULL;
//	}
//};

//int main()
//{
//	auto p = new vector<int>(10);
//	vector<int>& w = *p;
//	delete (&w);
//	return 0;
//}

//string reverseWords(string s)
//{
//    string res;
//    int i = 0;
//    int n = s.size();
//    while (i < n && s[i] == ' ') ++i;
//    int j = n - 1;
//    while (j >= 0 && s[j] == ' ') --j;
//    while (j > i)
//    {
//        while (j > i && s[j] == ' ') --j;
//        int sz = s.rfind(j, ' ');
//        res += s.substr(sz + 1, j - sz);
//        j = sz - 1;
//    }
//    return res;
//}
//
//int main()
//{
//    cout << reverseWords("the sky is blue") << endl;
//}

//bool isStraight(vector<int>& nums)
//{
//    int cnt0 = 0;
//    sort(nums.begin(), nums.end());
//    for (int p : nums)
//    {
//        if (p == 0) ++cnt0;
//    }
//    int i = nums[0], n = nums.size();
//    while (i < n && nums[i] == 0) ++i;
//    int prev = nums[i];
//    for (int j = i + 1; j < n; ++j)
//    {
//        if (nums[j] = prev + 1)
//        {
//            prev = nums[j];
//        }
//        else if (nums[j] - prev - 1 <= cnt0)
//        {
//            cnt0 -= (nums[j] - prev - 1);
//            prev = nums[j];
//        }
//        else
//        {
//            return false;
//        }
//    }
//    return true;
//}
//
//int main()
//{
//    vector<int> vec = { 0, 0, 1, 2, 5, 7 };
//    isStraight(vec);
//}

//class Solution {
//public:
//    typedef long long LL;
//    bool check(LL sx, LL sy, LL tx, LL ty)
//    {
//        if (sx == tx && sy == ty) return true;
//        return sx == ty && sy == tx;
//    }
//    bool reachingPoints(int sx, int sy, int tx, int ty)
//    {
//        return _reachingPoints(sx, sy, tx, ty);
//    }
//    bool _reachingPoints(LL sx, LL sy, LL tx, LL ty)
//    {
//        if (check(sx, sy, tx, ty)) return true;
//        if (max(sx, sy) > max(tx, ty)) return false;
//        return _reachingPoints(sx, sx + sy, tx, ty) || _reachingPoints(sx + sy, sy, tx, ty);
//    }
//};
//
//int main()
//{
//    Solution s;
//    s.reachingPoints(1, 1, 3, 5);
//}

class Date
{
public:
	Date(int year = 2000, int month = 1, int day = 1)
		: _year(year), _month(month), _day(day)
	{}
	//friend ofstream& operator<<(ofstream& out, Date& d);
	// friend ostringstream& operator<<(ostringstream& out, Date& d);
	friend ostream& operator<<(ostream& out, const Date& d);
	//friend istringstream& operator>>(istringstream& sin, Date& d);
	friend istream& operator>>(istream& in, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day;
	return out;
}

/*ofstream& operator<<(ofstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}

ostringstream& operator<<(ostringstream& out, Date& d)
{
	out << d._year << ' ' << d._month << ' ' << d._day << endl;
	return out;
}*/

//istream& operator>>(istream& in, Date& d)
//{
//	in >> d._year >> d._month >> d._day;
//	return in;
//}
//
//struct Personinfo
//{
//	string _name;
//	int _age;
//	Date _d;
//};
//
//int main()
//{
//	Personinfo p = { "路由器", 20 };
//	ostringstream oss;
//	oss << p._name << " " << p._age << " " << p._d;// 不用换行咯
//	cout << oss.str() << endl;
//	string tmp = oss.str();
//	istringstream iss(tmp);
//	Personinfo p1;
//	iss >> p1._name >> p1._age >> p1._d;
//	cout << p1._name << '*' << p1._age << '+' << p1._d << endl;
//}


//int largestInteger(int num)
//{
//    string s = to_string(num);
//    vector<char> num1;
//    vector<char> num0;
//    for (auto ch : s)
//    {
//        int number = ch - '0';
//        if (number % 2)
//        {
//            num1.push_back(ch);
//        }
//        else num0.push_back(ch);
//    }
//    sort(num1.begin(), num1.end());
//    sort(num0.begin(), num0.end());
//    int i = num1.size() - 1, j = num0.size() - 1;
//    string res;
//    for (auto ch : s)
//    {
//        int number = ch - '0';
//        if (number % 2)
//        {
//            res += num1[i];
//            --i;
//        }
//        else
//        {
//            res += num0[j];
//            --j;
//        }
//    }
//    return stoi(res);
//}
//
//int main()
//{
//    largestInteger(1234);
//}

//string minimizeResult(string expression)
//{
//    int addpos = expression.find('+', 0);
//    int n = expression.size();
//    string res;
//    int minnum = 0x3f3f3f3f;
//    for (int i = 0; i < addpos; ++i)
//    {
//        for (int j = addpos + 1; j < n; ++j)
//        {
//            // (插入在i位置前面 )插入在j位置后面
//            if (i == 0 && j == n - 1)
//            {
//                int num1 = stoi(expression.substr(0, addpos));
//                int num2 = stoi(expression.substr(addpos + 1));
//                int sum = num1 + num2;
//                if (sum < minnum)
//                {
//                    minnum = sum;
//                    res = "(" + expression + ")";
//                }
//            }
//            else
//            {
//                if (i == 0)
//                {
//                    int num1 = stoi(expression.substr(0, addpos));
//                    int num2 = stoi(expression.substr(addpos + 1, j - addpos));
//                    int num3 = stoi(expression.substr(j + 1));
//                    int val = (num1 + num2) * num3;
//                    if (val < minnum)
//                    {
//                        minnum = val;
//                        res = expression;
//                        res.insert(0, "(");
//                        res.insert(j + 2, ")");
//                    }
//                }
//                else if (j == n - 1)
//                {
//                    int num3 = stoi(expression.substr(addpos + 1));
//                    int num1 = stoi(expression.substr(0, i));
//                    int num2 = stoi(expression.substr(i, addpos - i));
//                    int val = num1 * (num2 + num3);
//                    if (val < minnum)
//                    {
//                        minnum = val;
//                        res = expression;
//                        res.push_back(')');
//                        res.insert(i, "(");
//                    }
//                }
//                else
//                {
//                    int num1 = stoi(expression.substr(0, i));
//                    int num2 = stoi(expression.substr(i, addpos - i));
//                    int num3 = stoi(expression.substr(addpos + 1, j - addpos));
//                    int num4 = stoi(expression.substr(j + 1));
//                    int val = num1 * (num2 + num3) * num4;
//                    if (val < minnum)
//                    {
//                        minnum = val;
//                        res = expression;
//                        res.insert(i, "(");
//                        res.insert(j + 2, ")");
//                    }
//                }
//            }
//        }
//    }
//    return res;
//}
//
//int main()
//{
//    cout << minimizeResult("12+34") << endl;
//}


//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
//    
//};
//
//const int N = 1e6 + 10;
//#define ll long long 
//int n, m;
//int w[N];
//struct Node
//{
//    int l, r;
//    int add, sum, malt;//建立线段树节点，sum表示区间和，l, r废话少说，add和malt是懒标记
//}tr[N * 4];//懒标记和这个维护的sum要有可叠加性，所以选择了先乘再加
//void pushup(int u)
//{
//    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
//    tr[u].sum = tr[u].sum;//更新这个sum，没啥好说的
//}
//void pushdown(int u)
//{
//    tr[u << 1].sum = ((ll)tr[u << 1].sum * tr[u].malt + (ll)tr[u].add * (tr[u << 1].r - tr[u << 1].l + 1));
//    tr[u << 1 | 1].sum = ((ll)tr[u << 1 | 1].sum * tr[u].malt + (ll)tr[u].add * (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1));
//    tr[u << 1].add = ((ll)tr[u << 1].add * tr[u].malt + tr[u].add);
//    tr[u << 1 | 1].add = ((ll)tr[u << 1 | 1].add * tr[u].malt + tr[u].add);
//    tr[u << 1].malt = (ll)tr[u << 1].malt * tr[u].malt;
//    tr[u << 1 | 1].malt = (ll)tr[u << 1 | 1].malt * tr[u].malt;//先乘再加，然后取模，注意longlong，不然就像我第一次搞的时候一样建祖宗了
//    tr[u].add = 0;//最后记得清空懒标记
//    tr[u].malt = 1;//乘法的懒标记一定是1，不然就全都0了
//}
//void build(int u, int l, int r)//开始建树
//{
//    if (l == r) tr[u] = { l, r, 0, w[r], 1 };//只要是叶节点的话就直接建立，sum自然是w[r]，当然写w[l]也行
//    else
//    {
//        tr[u] = { l, r, 0, 0, 1 };//乘法懒标记搞成1
//        int mid = (l + r) >> 1;
//        build(u << 1, l, mid);//build左右两边
//        build(u << 1 | 1, mid + 1, r);
//        pushup(u);//最后记得上传，build是一层层往下的，不用分裂处理，也就是不用pushdown
//    }
//}
//void change(int u, int l, int r, int malt, int add)//改变函数，我习惯change
//{
//    if (tr[u].l >= l && tr[u].r <= r)//如果包含在区间内部
//    {
//        //改变懒标记和sum，先乘后加！！！注意开long long
//        tr[u].sum = ((ll)tr[u].sum * malt + (ll)add * (tr[u].r - tr[u].l + 1));
//        tr[u].add = ((ll)tr[u].add * malt + add);
//        tr[u].malt = (ll)tr[u].malt * malt;
//    }
//    else//分裂处理，先pushdown
//    {
//        pushdown(u);//处理懒标记
//        int mid = (tr[u].l + tr[u].r) >> 1;//算一下终点
//        if (l <= mid) change(u << 1, l, r, malt, add);//算左右两边
//        if (r > mid) change(u << 1 | 1, l, r, malt, add);
//        pushup(u);//合并一下，然后处理sum
//    }
//}
//int query(int u, int l, int r)//查询操作
//{
//    if (tr[u].l >= l && tr[u].r <= r)
//    {
//        return tr[u].sum;//如果在区间之内直接返回
//    }
//    pushdown(u);//这个跟修改很像，也先分裂一下，处理懒标记
//    int mid = (tr[u].l + tr[u].r) >> 1;//处理左右两边
//    ll res = 0;//开个res记录
//    if (l <= mid)
//    {
//        res += query(u << 1, l, r);
//        res = res;//取模不要忘啊
//    }
//    if (r > mid)
//    {
//        res += query(u << 1 | 1, l, r);
//        res = res;
//    }
//    return res;
//}
//
//class Solution {
//public:
//    int getNumber(TreeNode* root, vector<vector<int>>& ops)
//    {
//        vector<int> mytree;
//        Inorder(root, mytree);
//        n = mytree.size();
//        for (int i = 1; i <= n; ++i) w[i] = 0;
//        build(1, 1, n);
//        unordered_map<int, int> myhash;
//        // 离散化
//        for (int i = 0; i < n; ++i)
//        {
//            myhash[mytree[i]] = i + 1;
//        }
//        for (auto& op : ops)
//        {
//            // 染红 设置为+1
//            if (op[0] == 1)
//            {
//                int l = myhash[op[1]], r = myhash[op[2]];
//                change(1, l, r, 1, 1);
//            }
//            else
//            {
//                int l = myhash[op[1]], r = myhash[op[2]];
//                change(1, l, r, 0, 0);
//            }
//        }
//        int res = query(1, 1, n);
//        return res;
//    }
//    void Inorder(TreeNode* root, vector<int>& mytree)
//    {
//        if (root == nullptr) return;
//        Inorder(root->left, mytree);
//        mytree.push_back(root->val);
//        Inorder(root->right, mytree);
//    }
//};
//
//int main()
//{
//    TreeNode* root = new TreeNode(1);
//    TreeNode* node2 = new TreeNode(2);
//    TreeNode* node3 = new TreeNode(3);
//    TreeNode* node4 = new TreeNode(4);
//    TreeNode* node5 = new TreeNode(5);
//    root->right = node2;
//    node2->right = node3;
//    node3->right = node4;
//    node4->right = node5;
//    Solution s;
//    vector<vector<int>> ops = { {1, 2, 4},{1, 1, 3},{0, 3, 5} };
//    s.getNumber(root, ops);
//}
//
//int findClosestNumber(vector<int>& nums)
//{
//	int res = 0x3f3f3f3f;
//	for (int p : nums)
//	{
//		int val = abs(p);
//		if (val < abs(res))
//		{
//			res = p;
//		}
//		else if (val == abs(res))
//		{
//			res = max(res, p);
//		}
//	}
//	return res;
//}
//
//int main()
//{
//	vector<int> a = { -100000, -100000 };
//	findClosestNumber(a);
//}

//class Solution {
//public:
//    int minimumRounds(vector<int>& tasks)
//    {
//        sort(tasks.begin(), tasks.end());
//        int res = -1;
//        unordered_map<int, int> cnt;
//        for (int p : tasks)
//        {
//            ++cnt[p];
//        }
//        for (auto p : cnt)
//        {
//            int curcnt = p.second;
//            if (curcnt == 1) return -1;
//            if (curcnt % 3 == 0) res = res == -1 ? curcnt / 3 : res + curcnt / 3;
//            else if (curcnt % 2 == 0 && curcnt == 4) res = res == -1 ? curcnt / 2 : res + curcnt / 2;
//            else
//            {
//                int num3 = curcnt / 3;
//                if ((curcnt - num3 * 3) % 2 == 0)
//                    res = (res == -1 ? curcnt / 3 + (curcnt - num3 * 3) / 2 : res + curcnt / 3 + (curcnt - num3 * 3) / 2);
//                else
//                {
//                    num3--;
//                    res = (res == -1 ? num3 + (curcnt - num3 * 3) / 2 : res + num3 + (curcnt - num3 * 3) / 2);
//                }
//            }
//        }
//        return res;
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<int> v = { 69, 65, 62, 64, 70, 68, 69, 67, 60, 65, 69, 62, 65, 65, 61, 66, 68, 61, 65, 63, 60, 66, 68, 66, 67, 65, 63, 65, 70, 69, 70, 62, 68, 70, 60, 68, 65, 61, 64, 65, 63, 62, 62, 62, 67, 62, 62, 61, 66, 69 };
//    cout << s.minimumRounds(v) << endl;
//}

//class Solution {
//public:
//    void dfs(int idx, char prev, string& s, const vector<vector<int>>& adj, int len, vector<bool>& used)
//    {
//        if (used[idx] == true)
//        {
//            res = max(res, len - 1);
//            return;
//        }
//        if (prev != '\0' && prev == s[idx])
//        {
//            res = max(res, len);
//            return;
//        }
//        used[idx] = true;
//        for (auto p : adj[idx])
//        {
//            dfs(p, s[idx], s, adj, len + 1, used);
//        }
//        used[idx] = false;
//    }
//    int res = 1;
//    int longestPath(vector<int>& parent, string s)
//    {
//        int n = s.size();
//        vector<vector<int>> adj(n);
//        for (int i = 1; i < n; ++i)
//        {
//            adj[i].push_back(parent[i]);
//            adj[parent[i]].push_back(i);
//        }
//        for (int i = 0; i < n; ++i)
//        {
//            vector<bool> used(n);
//            dfs(i, '\0', s, adj, 1, used);
//        }
//        return res;
//    }
//};
//
//
//int main()
//{
//    Solution s;
//    vector<int> v = { -1,0,0,1,1,2 };
//    string str = "abacbe";
//    s.longestPath(v, str);
//}
//
//class Solution {
//public:
//    string mostCommonWord(string paragraph, vector<string>& banned)
//    {
//        istringstream iss(paragraph);
//        vector<string> dic;
//        unordered_set<string> ban;
//        for (string& wd : banned)
//        {
//            transform(wd.begin(), wd.end(), wd.begin(), ::tolower);
//            ban.insert(wd);
//        }
//        string tmp;
//        unordered_map<string, int> cnt;
//        while (iss >> tmp)
//        {
//            if (tmp.back() == '!' || tmp.back() == '?'
//                || tmp.back() == ',' || tmp.back() == ';' || tmp.back() == '\''
//                || tmp.back() == '.')
//            {
//                tmp.pop_back();
//            }
//            transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
//            if (ban.count(tmp) != 0) continue;
//            cnt[tmp]++;
//        }
//        string res;
//        int cur = 0;
//        for (auto& p : cnt)
//        {
//            if (p.second > cur) {
//                res = p.first;
//                cur = p.second;
//            }
//        }
//        return res;
//    }
//};
//
//int main()
//{
//    Solution s;
//    string str = "a, a, a, a, b,b,b,c, c";
//    vector<string> mydic = { "a" };
//    s.mostCommonWord(str, mydic);
//}

//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
//};
//
//class Codec {
//public:
//
//    // Encodes a tree to a single string.
//    string serialize(TreeNode* root)
//    {
//        if (root == nullptr) return "[]";
//        // string ans = "[";
//        vector<string> ans;
//        queue<TreeNode*> q;
//        q.push(root);
//        while (!q.empty())
//        {
//            auto p = q.front();
//            q.pop();
//            if (p != nullptr) {
//                ans.push_back(to_string(p->val));;
//                q.push(p->left);
//                q.push(p->right);
//            }
//            else {
//                ans.push_back("null");
//            }
//        }
//        string res = "[";
//        int n = ans.size();
//        for (int i = 0; i < n - 4; ++i)
//        {
//            res += ans[i];
//            res.push_back(',');
//        }
//        res.pop_back();
//        res.push_back(']');
//        // cout << res << endl;
//        return res;
//    }
//
//    // Decodes your encoded data to tree.
//    TreeNode* deserialize(string data)
//    {
//        if (data == "[]") return nullptr;
//        string tmp1 = data.substr(1);
//        tmp1.pop_back();
//        transform(tmp1.cbegin(), tmp1.cend(), tmp1.begin(),
//            [](auto& ch) { return ch == ',' ? ' ' : ch; });
//        istringstream iss(tmp1);
//        string tmp;
//        vector<string> seq;
//        while (iss >> tmp)
//        {
//            seq.push_back(tmp);
//        }
//        if (seq.size() == 1 && seq.front() == "null") return nullptr;
//        if (seq.size() == 1) return new TreeNode(stoi(seq[0]));
//        unordered_map<int, TreeNode*> myhash;
//        int n = seq.size();
//        for (int i = 0; i < n; ++i)
//        {
//            if (seq[i] == "null") {
//                myhash[i] = nullptr;
//            }
//            else {
//                int val = stoi(seq[i]);
//                myhash[i] = new TreeNode(val);
//            }
//        }
//        int m = 0;
//        for (int i = 0; i < n; ++i)
//        {
//            if (myhash[i] == nullptr) {
//                ++m;
//                continue;
//            }
//            // 它的孩子为2 * (i - m) + 1 和2 * (i - m) + 2
//            else
//            {
//                if (2 * (i - m) + 1 < n) myhash[i]->left = myhash[2 * (i - m) + 1];
//                if (2 * (i - m) + 2 < n) myhash[i]->right = myhash[2 * (i - m) + 2];
//            }
//        }
//
//        return myhash[0];
//    }
//};
//
//int main()
//{
//    string s = "[1]";
//    Codec c;
//    c.deserialize(s);
//}

//class BIT
//{
//public:
//    BIT(int n)
//        : tr(n + 1)
//    {}
//    int lowbit(int x)
//    {
//        return x & (-x);
//    }
//    void add(int x, int val)
//    {
//        for (int i = x; i < tr.size(); i += lowbit(i)) tr[i] += val;
//    }
//    int sum(int x)
//    {
//        int ret = 0;
//        for (int i = x; i > 0; i -= lowbit(i)) ret += tr[i];
//        return ret;
//    }
//private:
//    vector<int> tr;
//};
//
//class Solution {
//public:
//    int reversePairs(vector<int>& nums)
//    {
//        vector<int> tmp(nums);
//        sort(tmp.begin(), tmp.end());
//        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
//        unordered_map<int, int> myhash;
//        int idx = 1;
//        for (int p : tmp)
//        {
//            myhash[p] = idx++;
//        }
//        int n = tmp.size();
//        BIT bt(n);
//        int ret = 0;
//        for (int p : nums)
//        {
//            ret += bt.sum(n) - bt.sum(p);
//            bt.add(myhash[p], 1);
//        }
//        return ret;
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<int> vec = { 7,5,6,4 };
//    s.reversePairs(vec);
//}

//class Solution {
//public:
//    void insert(vector<vector<int>>& b, int x1, int y1, int x2, int y2)
//    {
//        b[x1][y1] += 1;
//        b[x1][y2 + 1] -= 1;
//        b[x2 + 1][y1] -= 1;
//        b[x2 + 1][y2 + 1] += 1;
//    }
//    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points)
//    {
//        vector<int> alls;
//        for (auto& p : rectangles)
//        {
//            alls.push_back(p[0]);
//        }
//        for (auto& p : points)
//        {
//            alls.push_back(p[0]);
//        }
//        sort(alls.begin(), alls.end());
//        alls.erase(unique(alls.begin(), alls.end()), alls.end());
//        unordered_map<int, int> myhash;
//        int n = alls.size();
//        for (int i = 0; i < n; ++i) myhash[alls[i]] = i + 1;
//        vector<vector<int>> b(n + 10, vector<int>(6));
//        for (auto& p : rectangles)
//        {
//            int x = myhash[p[0]], y = p[1];
//            insert(b, 0, 0, x, y);
//        }
//        vector<vector<int>> a(n + 10, vector<int>(6));
//        for (int i = 1; i <= n; ++i)
//        {
//            for (int j = 1; j < 5; ++j)
//            {
//                a[i][j] = b[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
//            }
//        }
//        vector<int> ans;
//        for (auto& p : points)
//        {
//            int x = myhash[p[0]], y = p[1];
//            ans.push_back(a[x][y]);
//        }
//        return ans;
//    }
//};
//
//int main()
//{
//    vector<vector<int>> a = {{1, 2}, { 2, 3 }, { 2, 5 }};
//    vector<vector<int>> b = { {2, 1},{1, 4} };
//    Solution s;
//    s.countRectangles(a, b);
//        
//}


//#include <iostream>
//using namespace std;
//
//const int N = 1e6 + 10;
//
//int q[N];
//
//int n;
//
//void quicksort(int l, int r)
//{
//	if (l >= r) return;
//	int mid = (l + r) >> 1;
//	int i = l - 1, j = r + 1;
//	while (i < j)
//	{
//		do i++; while (q[i] < q[mid]);
//		do j--; while (q[j] > q[mid]);
//		if (i < j) swap(q[i], q[j]);
//	}
//	quicksort(l, j);
//	quicksort(j + 1, r);
//}
//
//int main()
//{
//	cin >> n;
//	for (int i = 0; i < n; ++i) cin >> q[i];
//	quicksort(0, n - 1);
//	for (int i = 0; i < n; ++i) cout << q[i] << ' ';
//	cout << endl;
//	return 0;
//}


//class Solution {
//public:
//    int minimumAverageDifference(vector<int>& nums)
//    {
//        int n = nums.size();
//        vector<int> s(n + 1);
//        for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + nums[i - 1];
//        int curval = 0x3f3f3f3f;
//        int ans = -1;
//        for (int i = n; i >= 1; --i)
//        {
//            int leftval = 0;
//            int rightval = 0;
//            if (i == n)
//            {
//                leftval = s[n] / n;
//            }
//            else if (i == 1)
//            {
//                rightval = (s[n] - s[1]) / (n - 1);
//                leftval = s[1];
//            }
//            else
//            {
//                leftval = s[i] / i;
//                rightval = (s[n] - s[i]) / (n - i);
//            }
//            int cur = abs(leftval - rightval);
//            if (cur <= curval)
//            {
//                ans = i - 1;
//                curval = cur;
//            }
//        }
//        return ans;
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<int> a = { 4,2,0 };
//    cout << s.minimumAverageDifference(a) << endl;
//}

//class Solution {
//public:
//    vector<vector<int>> ispro;
//    int dx[4] = { 1, -1, 0, 0 };
//    int dy[4] = { 0, 0, -1, 1 };
//    int _m;
//    int _n;
//    void dfs(int x, int y)
//    {
//        if (ispro[x][y] == 0) ispro[x][y] = 3;
//        for (int i = 0; i < 4; ++i)
//        {
//            int nx = x + dx[i], ny = y + dy[i];
//            if (nx < 0 || nx >= _m || ny < 0 || ny >= _n || ispro[nx][ny] != 0) continue;
//            dfs(nx, ny);
//        }
//    }
//
//    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls)
//    {
//        _m = m;
//        _n = n;
//        ispro = vector<vector<int>>(m, vector<int>(n));
//        // 1表示这个格子有警察 2表示这个格子有墙 3表示这个格子可以被警察看到 0表示这个格子没有被保护
//        for (auto& gd : guards)
//        {
//            int x = gd[0], y = gd[1];
//            ispro[x][y] = 1;
//        }
//        for (auto& wa : walls)
//        {
//            int x = wa[0], y = wa[1];
//            ispro[x][y] = 2;
//        }
//        for (int i = 0; i < m; ++i)
//            for (int j = 0; j < n; ++i)
//                if (ispro[i][j] == 1) dfs(i, j);
//        int ans = 0;
//        for (int i = 0; i < m; ++i)
//            for (int j = 0; j < n; ++j)
//                if (ispro[i][j] == 0) ++ans;
//        return ans;
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<vector<int>> a = { {0,0} ,{1,1},{2,3} };
//    vector<vector<int>> b = { {0, 1},{2, 2},{1, 4} };
//    s.countUnguarded(4, 6, a, b);
//}


//class Solution {
//    typedef pair<int, int> pii;
//    int n, m;
//    vector<vector<int>> MAP;
//    vector<vector<long long>> fire;
//
//    short dir[4][2] = { 0, 1, 1, 0, -1, 0, 0, -1 };
//
//    void bfs() {
//        queue<pii> q;
//        fire.resize(n, vector<long long>(m));
//        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) fire[i][j] = 1e18;
//        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (MAP[i][j] == 1)
//            q.push(pii(i, j)), fire[i][j] = 0;
//        while (!q.empty()) {
//            pii p = q.front(); q.pop();
//            int i = p.first, j = p.second;
//            for (int k = 0; k < 4; k++) {
//                int ii = i + dir[k][0], jj = j + dir[k][1];
//                if (ii < 0 || jj < 0 || ii >= n || jj >= m || fire[ii][jj] < 1e18 || MAP[ii][jj]) continue;
//                fire[ii][jj] = fire[i][j] + 1;
//                q.push(pii(ii, jj));
//            }
//        }
//    }
//
//    bool check(int LIM) {
//        queue<pii> q;
//        vector<vector<long long>> dis;
//        dis.resize(n, vector<long long>(m));
//        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) dis[i][j] = 1e18;
//        q.push(pii(0, 0)); dis[0][0] = LIM;
//        while (!q.empty()) {
//            pii p = q.front(); q.pop();
//            int i = p.first, j = p.second;
//            for (int k = 0; k < 4; k++) {
//                int ii = i + dir[k][0], jj = j + dir[k][1];
//                if (ii < 0 || jj < 0 || ii >= n || jj >= m || dis[ii][jj] < 1e18 || MAP[ii][jj]) continue;
//                dis[ii][jj] = dis[i][j] + 1;
//                if (ii == n - 1 && jj == m - 1) return dis[ii][jj] <= fire[ii][jj];
//                else if (dis[ii][jj] < fire[ii][jj]) q.push(pii(ii, jj));
//            }
//        }
//        return false;
//    }
//
//public:
//    int maximumMinutes(vector<vector<int>>& grid) {
//        n = grid.size(); m = grid[0].size();
//        MAP = grid;
//        bfs();
//        if (!check(0)) return -1;
//
//        int head = 0, tail = 1e9;
//        while (head < tail) {
//            int mid = (head + tail + 1) >> 1;
//            if (check(mid)) head = mid;
//            else tail = mid - 1;
//        }
//        return head;
//    }
//};


//class Solution {
//public:
//
//    bool check(vector<int>& nums, int l, int r, int k, int p)
//    {
//        int cnt = 0;
//        for (int i = l; i <= r; ++i)
//        {
//            if (nums[i] % p == 0) ++cnt;
//            if (cnt > k) return false;
//        }
//        return true;
//    }
//
//    int countDistinct(vector<int>& nums, int k, int p)
//    {
//        int n = nums.size();
//        set<vector<int>> myset;
//        for (int i = 0; i < n; ++i)
//        {
//            for (int j = 0; j <= i; ++j)
//            {
//                // [j, i]
//                if (check(nums, j, i, k, p))
//                {
//                    vector<int> tmp(nums.begin() + j, nums.begin() + i);
//                    myset.insert(tmp);
//                }
//            }
//        }
//        return myset.size();
//    }
//};
//
//int main()
//{
//    Solution s;
//    vector<int> a = { 2, 3, 3, 2, 2 };
//    s.countDistinct(a, 2, 2);
//}

//class Solution {
//public:
//    unordered_map <char, int> ori, cnt;
//
//    bool check() {
//        for (const auto& p : ori) {
//            if (cnt[p.first] < p.second) {
//                return false;
//            }
//        }
//        return true;
//    }
//
//    string minWindow(string s, string t) {
//        for (const auto& c : t) {
//            ++ori[c];
//        }
//
//        int l = 0, r = -1;
//        int len = INT_MAX, ansL = -1, ansR = -1;
//
//        while (r < int(s.size())) {
//            if (ori.find(s[++r]) != ori.end()) {
//                ++cnt[s[r]];
//            }
//            while (check() && l <= r) {
//                if (r - l + 1 < len) {
//                    len = r - l + 1;
//                    ansL = l;
//                }
//                if (ori.find(s[l]) != ori.end()) {
//                    --cnt[s[l]];
//                }
//                ++l;
//            }
//        }
//
//        return ansL == -1 ? string() : s.substr(ansL, len);
//    }
//};


//// Definition for a Node.
//class Node {
//public:
//    Node(int _val, Node* p1, Node* p2, Node* p3)
//        : val(_val), prev(p1), next(p2), child(p3)
//    {}
//    int val;
//    Node* prev;
//    Node* next;
//    Node* child;
//};
//
//
//class Solution {
//public:
//    void getstartandtail(Node* cur, Node*& start, Node*& tail)
//    {
//        start = cur;
//        while (cur != nullptr)
//        {
//            if (cur->child != nullptr)
//            {
//                Node* mystart = nullptr, * mytail = nullptr;
//                getstartandtail(cur->child, mystart, mytail);
//                Node* ne = cur->next;
//                if (ne != nullptr)
//                {
//                    cur->next = mystart;
//                    mystart->prev = cur;
//                    ne->prev = mytail;
//                    mytail->next = ne;
//                    cur->child = nullptr;
//                    cur = ne;
//                }
//                else
//                {
//                    cur->next = mystart;
//                    mystart->prev = cur;
//                    mytail->next = nullptr;
//                    tail = mytail;
//                    cur = nullptr;
//                }
//            }
//            else
//            {
//                if (cur->next == nullptr) tail = cur;
//                cur = cur->next;
//            }
//        }
//    }
//    Node* flatten(Node* head)
//    {
//        if (head == nullptr) return nullptr;
//        Node* dummyhead = new Node(0, nullptr, head, nullptr);
//        Node* cur = dummyhead;
//        while (cur != nullptr)
//        {
//            if (cur->child != nullptr)
//            {
//                Node* start = nullptr;
//                Node* tail = nullptr;
//                getstartandtail(cur->child, start, tail);
//                auto ne = cur->next;
//                if (ne != nullptr)
//                {
//                    cur->next = start;
//                    start->prev = cur;
//                    ne->prev = tail;
//                    tail->next = ne;
//                    cur->child = nullptr;
//                    cur = ne;
//                }
//                else
//                {
//                    cur->next = start;
//                    start->prev = cur;
//                    tail->next = nullptr;
//                    cur = nullptr;
//                }
//            }
//            else cur = cur->next;
//        }
//        Node* ret = dummyhead->next;
//        delete dummyhead;
//        return ret;
//    }
//};
//
//
//int main()
//{
//    Solution s;
//    Node* n1 = new Node(1, nullptr, nullptr, nullptr);
//    Node* n2 = new Node(2, nullptr, nullptr, nullptr);
//    Node* n3 = new Node(3, nullptr, nullptr, nullptr);
//    n1->child = n2;
//    n2->child = n3;
//    s.flatten(n1);
//}


class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen)
    {
        sort(tiles.begin(), tiles.end());
        int n = tiles.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int curmaxright = tiles[i][0] + carpetLen;
            if (curmaxright < tiles[i][1]) return carpetLen;
            int l = i, r = n - 1;
            // 二分找第一个tiles[x][1] > carpetLen的区间的左边界
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (tiles[mid][1] <= curmaxright) l = mid + 1;
                else r = mid;
            }
            int curval = 0;
            for (int k = i; k < r; ++k) curval += tiles[k][1] - tiles[k][0] + 1;
            if (tiles[r][0] < curmaxright) curval += min(curmaxright, tiles[r][1]) - tiles[r][0];
            if (tiles[r][1] >= curmaxright) curval++;
            // curval += carpetLen - tiles[r][0];
            ans = max(ans, curval);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> a = { {1, 5},{10, 11},{12, 18},{20, 25},{30, 32} };
    s.maximumWhiteTiles(a, 35);
}
