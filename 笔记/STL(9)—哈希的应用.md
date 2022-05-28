# 一、位图

&emsp;&emsp;给定40亿个无符号整数，如何快速判断一个数是否在这40亿个数中。

&emsp;&emsp;如果数据有序的话，直接用二分查找在``Log(N)``的速度就能找到，40亿最多找32次：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528153406.png" style="zoom:80%;" />

&emsp;&emsp;但是如果用其他容器，40亿个整形大概占的空间为``16G``空间，完全存不下来。

&emsp;&emsp;本题可以通过哈希的一种思想位图去解决：它的思想就是开16亿个二进制位，哪个值出现了就让对应的位标记为1，没出现过的数对应的位标记为0，最后只要看这个数对应的二进制位是否为1即可，每个数映射到对应的二进制位就直接用直接定址法就行。

&emsp;&emsp;开42亿多(这是个二进制位，其需要的空间大概为``16 / 32 = 0.5G``，内存就足够了，所以本题通过位图就可以解决。

## 1 位图的简单实现

&emsp;&emsp;使用一个数组``vector``里头来存``char``，然后利用一个char是8个字节，所以``size_t x``应该放在vector中的下标``i = x / 8``，然后想要操纵它的第``j = x % 8``位就通过位运算即可：

```cpp
//Bitset.hpp
#pragma once
#include <vector>
#include <iostream>
namespace Router
{
	// 非类型模板参数N表示要开多少个比特位
	template<size_t N>
	class bit_set
	{
	public:
		bit_set()
		{
			_bits.resize(N / 8 + 1);
		}
		// x的标记为搞成1
		void set(size_t x)
		{
			size_t i = x / 8;// _bits[i]
			size_t j = x % 8;// j位
			_bits[i] |= 1 << j;
		}
		// x的标记为改成0
		void reset(size_t x)
		{
			size_t i = x / 8, j = x % 8;
			_bits[i] &= (~(1 << j));
		}
		// 1->true 0->false
		bool test(size_t x)
		{
			size_t i = x / 8, j = x % 8;
			return _bits[i] & (1 << j);
		}
	private:
		std::vector<char> _bits;
	};
	void test_bitset()
	{
		bit_set<10> bst;
		bst.set(3);
		bst.set(7);
		std::cout << bst.test(3) << std::endl;
		bst.reset(3);
		std::cout << bst.test(3) << std::endl;
	}
}
```

&emsp;&emsp;所以那个题就可以开成``bit_set<0xffffffff> bst;``或利用补码``bit_set<-1> bst``。

## 2 STL位图简单介绍

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528164503.png" style="zoom:80%;" />

&emsp;&emsp;一些常用的接口：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528164538.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528164641.png" style="zoom:80%;" />

## 3 位图应用

- 1 给定100亿个整数，怎样找出只出现了一次的数字？

&emsp;&emsp;我们可以把状态表示为三种：没有出现过、出现过1次、出现过2次及其以上，可以考虑改造位图改成2个比特位表示一个值的状态，或者是用两个位图，第一个位图表示该数字是否出现过、第二个位图表示该数字是否出现了2次及其以上，最后要找的就是第一个位图的位是1且第二个图的位是0个数字。

00(未出现)->10(只出现了1次)->11(出现两次及其以上)

```cpp
template <size_t N>
class TwoBitset
{
public:
    bit_set<N> _bt1;
    bit_set<N> _bt2;
};
void test()
{
    TwoBitset<-1> t;
    std::ifstream ifs("text.txt");
    int x;
    while (ifs >> x)
    {
        if (!t._bt1.test(x) && !t._bt2.test(x))
        {
            t._bt1.set(x);
        }
        else if (t._bt1.test(x) && !t._bt2.test(x))
        {
            t._bt2.set(x);
        }
    }
    for (size_t i = 0; i < 0xffffffff; ++i)
    {
        if (t._bt1.test(i) && !t._bt2.test(i))
        {
            cout << i << endl;
        }
    }
}
```

- 2 两个文件各有100亿整数，求两个文件的交集

&emsp;&emsp;无符号整形``size_t``最多有42亿，所以一个位图最多0.5G，问题不大。

&emsp;&emsp;思路一：先把文件1的内容全部放进位图里，然后遍历第二个文件的每个元素，看其是否在位图里。

&emsp;&emsp;缺点，这样会出现重复的元素。

&emsp;&emsp;所以最好把文件1的值弄到一个位图bs1，文件2的数据弄到一个位图bs2，然后有两种思路：

- 遍历bs1，看其是否在bs2中；
- 把两个位图的每一位按位与，最后为1的就是交集。

- 3 一个文件中有100亿个整形，找出现次数小于等于2次的数字。

&emsp;&emsp;两个位图00（0次）、01（1次）、10（2次）、11（3次及其以上)