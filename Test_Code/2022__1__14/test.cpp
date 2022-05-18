#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
//#include <typeinfo>
using namespace std;
#include "stack.h"
//void f(int*)
//{
//	cout << "f(int*)" << endl;
//}
//void f(int)
//{
//	cout << "f(int)" << endl;
//}
//void func(int(*arr)[5])
//{
//	for (auto& e : *arr)
//	{
//		e = 2;
//	}
//}
//int main()
//{
//	f(NULL);
//	f(0);
//	f((int*)NULL);
//	f(nullptr);
//	int arr[] = { 1, 2, 3, 4, 5 };
//	func(&arr);
//	for (auto e : arr)
//	{
//		cout << e << " ";
//	}
//}

//class student
//{
//public:
//    //成员变量
//    char _name[20];
//    int _age;
//    int _id;
//    //Goole成员变量经常在后面加_
//    //还有前面加m代表member
//    //成员方法
//    void Init(const char* name, int age, int id)
//    {
//        strcpy(_name, name);
//        _age = age;
//        _id = id;
//    }
//    void print()
//    {
//        cout << _name << endl;
//        cout << _age << endl;
//        cout << _id << endl;
//    }
//};
//
//int main()
//{
//    student s1;
//    s1.Init("路由器", 20, 2111410800);
//    s1.print();
//}

//int main()
//{
//	Stack s;
//	cout << sizeof(Stack) << endl;
//	cout << sizeof(s) << endl;
//	
//}

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
    {
        vector<vector<int>> ans(k);
        Heap hp(k);
        int sz1 = nums1.size();
        int sz2 = nums2.size();
        int count = 0;
        for (int i = 0; i < sz1; i++)
        {
            for (int j = 0; j < sz2; j++)
            {
                HeapNode tmp;
                tmp._index1 = i;
                tmp._index2 = j;
                tmp._val = nums1[i] + nums2[j];
                if (count < k)
                {
                    hp.HeapPush(tmp);
                }
                else
                {
                    if (hp.Top() > tmp._val)
                    {
                        hp.HeapPop();
                        hp.HeapPush(tmp);
                    }
                }
                count++;
            }
        }
        for (int i = 0; i < k; i++)
        {
            ans[i].push_back(hp._a[i]._index1);
            ans[i].push_back(hp._a[i]._index2);
        }
        return ans;
    }
    struct HeapNode
    {
        int _index1;
        int _index2;
        int _val;
    };
    class Heap
    {
    public:
        Heap(int k)
        {
            _size = 0;
            _capacity = k;
            _a = new HeapNode[k];
        }
        ~Heap()
        {
            _size = 0;
            _capacity = 0;
            delete[]_a;
        }
        void HeapPush(HeapNode x)
        {
            _a[_size++] = x;
            AdjustUp(_size - 1);
        }
        void HeapPop()
        {
            swap(_a[0], _a[_size - 1]);
            _size--;
            AdjustDown(0);
        }
        int Top()
        {
            return _a[0]._val;
        }
        void AdjustUp(int child);
        void AdjustDown(int parent);
        int _size;
        int _capacity;
        HeapNode* _a;
    };
    void swap(HeapNode& x, HeapNode& y)
    {
        HeapNode tmp = x;
        x = y;
        y = tmp;
    }
    void Solution::Heap::AdjustUp(int child)
    {
        int parent = (child - 1) / 2;
        while (child > 0)
        {
            if (_a[child]._val > _a[parent]._val)
            {
                swap(_a[child], _a[parent]);
                child = parent;
                parent = (child - 1) / 2;
            }
            else
            {
                break;
            }
        }
    }
    void Solution::Heap::AdjustDown(int parent)
    {
        int child = 2 * parent + 1;
        while (child < _size)
        {
            if (child + 1 < _size && _a[child + 1]._val > _a[child]._val)
            {
                child++;
            }
            if (_a[child]._val > _a[parent]._val)
            {
                swap(_a[child], _a[parent]);
                parent = child;
                child = parent * 2 + 1;
            }
            else
            {
                break;
            }
        }
    }
};