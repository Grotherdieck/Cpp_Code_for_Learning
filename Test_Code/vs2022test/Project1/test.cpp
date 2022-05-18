//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//typedef tuple<int, int, int, int> PIV;
//const int N = 2e5 + 10;
//int a[N][N];//原数组
//int b[N][N];//差分数组
//vector<PIV> quest;//暂时储存(x1,y1) (x2, y2)'
//vector<int> Xarr;
//vector<int> Yarr;
///*定义染黑就是在矩阵的那个区域 + 1 判断时只要看原数组不是0的点都是被染黑过了*/
//
///*映射 把值映射到排序去重后的数组下标 + 1*/
//int find(vector<int>& arr, int x)
//{
//    int l = 0, r = arr.size() - 1;
//    while (l < r)
//    {
//        int mid = (l + r) >> 1;
//        if (arr[mid] >= x) r = mid;
//        else l = mid + 1;
//    }
//    return r + 1;
//}
///*差分的插入操作*/
//void Insert(int x1, int y1, int x2, int y2, int c)
//{
//    b[x1][y1] += c;
//    b[x1][y2 + 1] -= c;
//    b[x2 + 1][y1] -= c;
//    b[x2 + 1][y2 + 1] += c;
//}
//
//int main()
//{
//    int n;
//    cin >> n;
//    int x1, y1, x2, y2;
//    for (int i = 0; i < n; ++i)
//    {
//        cin >> x1 >> y1 >> x2 >> y2;
//        quest.push_back({ x1, y1, x2, y2 });
//    }
//    /*把x映射到1~n 把y映射到1~m*/
//    /*先弄进来*/
//    for (auto& e : quest)
//    {
//        auto [x1, y1, x2, y2] = e;
//        Xarr.push_back(x1);
//        Xarr.push_back(x2);
//        Yarr.push_back(y1);
//        Yarr.push_back(y2);
//    }
//    sort(Xarr.begin(), Xarr.end());
//    sort(Yarr.begin(), Yarr.end());
//    /*去重*/
//    Xarr.erase(unique(Xarr.begin(), Xarr.end()), Xarr.end());
//    Yarr.erase(unique(Yarr.begin(), Yarr.end()), Yarr.end());
//    /*利用差分处理染色请求*/
//    for (auto& e : quest)
//    {
//        auto [x1, y1, x2, y2] = e;
//        x1 = find(Xarr, x1);
//        y1 = find(Yarr, y1);
//        x2 = find(Xarr, x2);
//        y2 = find(Yarr, y2);
//        Insert(x1, y1, x2, y2, 1);
//    }
//    /*由差分数组还原原数组a 差分数组b的前缀和是a*/
//    int cnt = 0;
//    for (int i = 1; i <= (int)Xarr.size(); ++i)
//    {
//        for (int j = 1; j <= (int)Yarr.size(); ++j)
//        {
//            a[i][j] = b[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
//            if (a[i][j] != 0) ++cnt;
//        }
//    }
//    cout << cnt;
//    return 0;
//}
#include <iostream>
using namespace std;
template <class T, double x>
class Stack
{
	void add()
	{
		cout << "sss" << endl;
	}
};

int main()
{
	Stack<int, 1.1> st;
}