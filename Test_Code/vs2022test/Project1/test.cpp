//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//typedef tuple<int, int, int, int> PIV;
//const int N = 2e5 + 10;
//int a[N][N];//ԭ����
//int b[N][N];//�������
//vector<PIV> quest;//��ʱ����(x1,y1) (x2, y2)'
//vector<int> Xarr;
//vector<int> Yarr;
///*����Ⱦ�ھ����ھ�����Ǹ����� + 1 �ж�ʱֻҪ��ԭ���鲻��0�ĵ㶼�Ǳ�Ⱦ�ڹ���*/
//
///*ӳ�� ��ֵӳ�䵽����ȥ�غ�������±� + 1*/
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
///*��ֵĲ������*/
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
//    /*��xӳ�䵽1~n ��yӳ�䵽1~m*/
//    /*��Ū����*/
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
//    /*ȥ��*/
//    Xarr.erase(unique(Xarr.begin(), Xarr.end()), Xarr.end());
//    Yarr.erase(unique(Yarr.begin(), Yarr.end()), Yarr.end());
//    /*���ò�ִ���Ⱦɫ����*/
//    for (auto& e : quest)
//    {
//        auto [x1, y1, x2, y2] = e;
//        x1 = find(Xarr, x1);
//        y1 = find(Yarr, y1);
//        x2 = find(Xarr, x2);
//        y2 = find(Yarr, y2);
//        Insert(x1, y1, x2, y2, 1);
//    }
//    /*�ɲ�����黹ԭԭ����a �������b��ǰ׺����a*/
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