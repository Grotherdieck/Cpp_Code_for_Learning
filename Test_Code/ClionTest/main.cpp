#include "myvector.h"


//class A
//{
//public:
//    ~A()
//    {
//        cout << "~A()" << endl;
//    }
//};

int main()
{
    scu::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    scu::vector<int>::reverse_iterator  it = a.rbegin();
    while (it != a.rend())
    {
        cout << *it << ' ';
        ++it;
    }
    // a.insert(pos, 5);
//    const scu::vector<int> b(a);
//    a = b;
//    for (auto num : a)
//    {
//        cout << num << ' ';
//    }
}

