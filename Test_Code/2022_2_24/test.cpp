#define  _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//int main()
//{
//    string s = "http://www.cplusplus.com/reference/string/string/rfind/";
//    size_t p1 = s.find(':');
//    string protocol = s.substr(0, p1);
//    cout << protocol << endl;
//    size_t p2 = s.find('/', p1 + 3);// 从w开始找
//    string domain = s.substr(p1 + 3, p2 - p1 - 3);// 左闭右开 长度为p2 - p1 - 3 不用减-1
//    cout << domain << endl;
//    string uri = s.substr(p2 + 1);// 直接到最后
//    cout << uri << endl;
//}

string complexNumberMultiply(string num1, string num2)
{
    if ((num1[0] == '0' && num1[2] == '0') || (num2[0] == '0' && num2[2] == '0'))
        return "0+0i";
    size_t pos1 = num1.find('+');
    string Real1 = num1.substr(0, pos1);
    int real1 = stoi(Real1);
    string Image1 = num1.substr(pos1 + 1, num1.size() - 2 - pos1);
    int image1 = stoi(Image1);
    size_t pos2 = num2.find('+');
    string Real2 = num2.substr(0, pos2);
    int real2 = stoi(Real2);
    string Image2 = num2.substr(pos2 + 1, num2.size() - 2 - pos2);
    int image2 = stoi(Image2);
    /*(a + bi) * (c + di) = (ac - bd) + (ad + bc)i*/
    int retreal = real1 * real2 - image1 * image2;
    int retimage = real1 * image2 + image1 * real1;
    string ret;
    ret += (to_string(retreal) + '+' + to_string(retimage) + 'i');
    return ret;
}

int main()
{
    complexNumberMultiply("78 + -76i", "-86+72i");
}