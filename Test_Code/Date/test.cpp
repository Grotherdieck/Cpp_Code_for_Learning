#define  _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"
void TestDate1()
{
	Date d1(2022, 1, 16);
	Date d2;
	d2 = d1 + 100;
	d2.Print();
	d1 += 100;
	d1.Print();
	cout << (d1 >= d2) << endl;
	cout << (d1 < d2) << endl;
	Date d3(2022, 1, 16);
	d2 = d3 - 100;
	d2.Print();
	d3 -= 100;
	d3.Print();
}

void TestDate2()
{
	Date d1(2022, 1, 16);
	//正常测试
	Date m = d1 - 10;
	//跨年
	Date n = d1 - 16;
	m.Print();
	n.Print();
	//稍微大点数
	Date d2 = d1 + (-100);
	Date d3 = d1 - (-100);
	d2.Print();
	d3.Print();
	cout << d3 - d1 << endl;
	cout << d2 - d1 << endl;
	//跨闰年
	Date d4 = d1 - (-1500);
	Date d5 = d1 + (-1500);
	d4.Print();
	d5.Print();
	cout << d4 - d5 << endl;
}

void TestDate3()
{
	Date d1(2022, 1, 17);
	Date d2 = d1 - 10;
	d2.Print();
	Date d3 = d1 - 17;
	d3.Print();
	Date d4 = d3 - 100;
	d4.Print();
}

void TestDate4()
{
	Date d1(2022, 1, 17);
	Date d2(2022, 12, 31);
	Date d3(1900, 1, 1);
	cout << d2 - d1 << endl;
	cout << d3 - d1 << endl;
	d3.PrintWeekday();
}

int main()
{
	//TestDate1();
	//TestDate2();
	/*Date d1(2022, 1, 17);
	Date d2(2022, 7, 1);
	cout << 2 * (d2 - d1) << endl;*/
	//TestDate3();
	//TestDate4();
	Date(2022, 1, 17).PrintWeekday();
}