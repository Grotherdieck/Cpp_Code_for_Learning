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

# 二、布隆过滤器

## 1 布隆过滤器的提出

&emsp;&emsp;尽管位图相对哈希容器和红黑树容器来说，节省了很多空间，并且是利用位运算操作的，速度严格O(1)，但是缺点是位图只能处理**整数**。

&emsp;&emsp;那么如果我不是整数呢？这就引出了布隆过滤器。

&emsp;&emsp;布隆过滤器是由布隆（Burton Howard Bloom）在1970年提出的 一种紧凑型的、比较巧妙的概率型数据结构，特点是高效地插入和查询，可以用来告诉你 “某样东西一定不存在或者可能存在”，它是用多个哈希函 数，将一个数据映射到位图结构中。此种方式不仅可以提升查询效率，也可以节省大量的内存空间。

&emsp;&emsp;一个简易的利用字符串哈希加位图来做到查询字符串：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531190228.png" style="zoom:80%;" />

&emsp;&emsp;这样一个字符串映射到一个比特位，不就大大节约了空间吗？

&emsp;&emsp;但是这样仍然有问题，因为字符串理论上来说是无限的，很可能会发生哈希冲突，这样字符串转整形如果冲突了，因为我们采用的不是哈希表的开散列那种挂拉链的方法，所以可能**我判断一个字符串在的时候会发生误判**。

&emsp;&emsp;这种数据结构，如果数据结构的判断结果是字符串在，那么可能是因为和我冲突的字符串来了，然后判断就出错了，而判断结果为字符串不在，那么结果一定是准确的。

&emsp;&emsp;那么布隆是怎么把这种东西改进的呢？布隆的想法是：**允许误判，但是尽量把误判的概率降低**。

&emsp;&emsp;正如数据存储时，常常把数据存给多个副本放到不同的环境中，每个环境都出问题了后数据才会丢失，这里的思想也是一样的，采用多个哈希算法把字符串映射到多个位置。

&emsp;&emsp;现在需要这多个哈希函数都在这俩字符串冲突的情况下，才会发生误判。

&emsp;&emsp;所以判断字符串在不在时，通过多个哈希函数找到对应位，如果有一个位置为0（不在），那么就表明这个字符串不在，如果都为1，那么很大概率这个字符串就是在的（除非多个哈希函数都冲突了）。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531191919.png" style="zoom:80%;" />

## 2 布隆过滤器实现

&emsp;&emsp;利用模板，去网站[各种字符串Hash函数 - clq - 博客园 (cnblogs.com)](https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html)偷几个字符串哈希函数，先看看这几个哈希值是多少？

```cpp
struct BKDRhash
{
	size_t operator()(const string& str)
	{
		size_t ret = 0;
		for (char ch : str) ret *= 31, ret += ch;
		return ret;
	}
};
struct APHash
{
    size_t operator()(const string& str)
    {
        register size_t hash = 0;
        size_t ch;
        long i = 0;
        for (char ch : str)
        {
            if ((i & 1) == 0)
            {
                hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
            }
            else
            {
                hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
            }
            ++i;
        }
        return hash;
    }
};
template <size_t N, class K = std::string, 
	class HashFunc1 = hash<string>, 
	class HashFunc2 = BKDRhash, 
	class HashFunc3 = APHash>
class BloomFilter
{
public:
    void Set(const K& key)
    {
        cout << HashFunc1()(key) << endl;
        cout << HashFunc2()(key) << endl;
        cout << HashFunc3()(key) << endl;
    }
private:
	std::bitset<N> _bs;
};

void test_bloomfilter()
{
    BloomFilter<100> bfter;
    bfter.Set("我劝你好自为之");
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531193712.png" style="zoom:80%;" />

&emsp;&emsp;实现一下布隆过滤器的Set函数，它就是把那几个位置都置为1：

```cpp
void Set(const K& key)
{
    size_t index1 = HashFunc1()(key);
    size_t index2 = HashFunc2()(key);
    size_t index3 = HashFunc3()(key);
    _bs.set(index1);
    _bs.set(index2);
    _bs.set(index3);
}
```

&emsp;&emsp;那么布隆过滤器具体要弄多少个比特位的位图呢？
$$
k = \frac{m}{n}ln2\\
k是哈希函数个数\\
m为布隆过滤器长度\\
n为插入元素的个数\\
$$
&emsp;&emsp;视``ln2 = 0.7``， 有``m = 4.2n``。

&emsp;&emsp;我们实现Test，并且测试一下插入的误判率：

```cpp
struct BKDRhash
{
	size_t operator()(const string& str)
	{
		size_t ret = 0;
		for (char ch : str) ret *= 31, ret += ch;
		return ret;
	}
};
struct APHash
{
    size_t operator()(const string& str)
    {
        register size_t hash = 0;
        size_t ch;
        long i = 0;
        for (char ch : str)
        {
            if ((i & 1) == 0)
            {
                hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
            }
            else
            {
                hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
            }
            ++i;
        }
        return hash;
    }
};
// 模板参数N表示可能要插入多少元素
template <size_t N, class K = std::string, 
	class HashFunc1 = hash<string>, 
	class HashFunc2 = BKDRhash, 
	class HashFunc3 = APHash>
class BloomFilter
{
public:
    void Set(const K& key)
    {
        size_t len = 4 * N;
        size_t index1 = HashFunc1()(key) % len;
        size_t index2 = HashFunc2()(key) % len;
        size_t index3 = HashFunc3()(key) % len;
        _bs.set(index1);
        _bs.set(index2);
        _bs.set(index3);
    }
    bool Test(const K& key)
    {
        size_t len = 4 * N;
        size_t index1 = HashFunc1()(key) % len;
        if (!_bs.test(index1)) return false;
        size_t index2 = HashFunc2()(key) % len;
        if (!_bs.test(index2)) return false;
        size_t index3 = HashFunc3()(key) % len;
        if (!_bs.test(index3)) return false;
        return true;// 三个都在 很大概率是在吧。
    }
private:
	std::bitset<4 * N> _bs;
};

void test_bloomfilter()
{
    BloomFilter<100> bfter;
    bfter.Set("我劝你好自为之");
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531200907.png" style="zoom:80%;" />

&emsp;&emsp;我们如果能把比特位开多，误判率可以显著下降，如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531201114.png" style="zoom:80%;" />

&emsp;&emsp;所以对于布隆过滤器，最重要要去合理调节的就是这个X，X大了会更加浪费空间，但是误判率会降低，X小了会节约空间，但是误判率会提高。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531201334.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531201400.png" style="zoom:80%;" />

## 3 布隆过滤器的删除问题

&emsp;&emsp;传统的布隆过滤器不支持删除，因为你可能把冲突的位置给删除了。

&emsp;&emsp;如果想拓展布隆过滤器使其支持删除，需要使用引用计数的思想，通过一些比特位模拟整数，替代单一的比特位，删除时就使引用计数减1即可。

&emsp;&emsp;但是这样又会引出新的问题，删除后可能因为多个哈希函数都冲突了，导致以为这个东西还在，而且还浪费了空间。

## 4 布隆过滤器的具体应用

&emsp;&emsp;当需求是数据量大、节省空间、允许误判，这种场景就可以使用布隆过滤器。

&emsp;&emsp;假如注册界面判断用户昵称是否有人用过，用过的话就不给过，需要重新输入昵称。

&emsp;&emsp;一种方法是直接去数据库查，但是这样效率太低了，这种场景就可以用布隆过滤器。

&emsp;&emsp;我们需要保证的是昵称没人用过是准确的，即不在布隆过滤器中是准确的，这显然是ok的，显示√。

&emsp;&emsp;显示昵称被人用过了，有可能是真的用过了，有可能是冲突了，但是这样也无所谓呀hhh。

&emsp;&emsp;如果为了更准确，可以在布隆过滤器显示这个昵称存在时再去数据库查询一下确认一下。

&emsp;&emsp;这里布隆过滤器的价值就是昵称不在数据库中的场景直接被准确的过滤出来了。

&emsp;&emsp;垃圾邮件也是类似的使用场景，如果邮箱不在我的垃圾邮箱名称构成的布隆过滤器，那么因为布隆过滤器的不在是准确的，它一定不是垃圾邮件，如果它在布隆过滤器中，再去数据库里查一下。

&emsp;&emsp;总之**布隆过滤器可以快速准确的的过滤掉不在布隆过滤器的情况**。

## 5 海量数据处理面试题

1. 给两个文件，分别有100亿个query，我们只有1G内存，如何找到两个文件交集？分别给出精确算法和 近似算法 

   近似算法可以用布隆过滤器把一个文件里的字符串先放到一个布隆过滤器里，然后会有一些不是交集的query会被放进来，如果允许这种情况，那么没问题。

   精确算法呢？正常方式``set``和``unordered_set``都放不下这么多数据，就得用**哈希切分**。

   大思路很简单，100亿我们处理不了，我给你切割成100份，两个文件都被切分成100份(总之是能够加载到内存的大小份数)，然后100*100，

   但是这样效率还是太低，这里我们可以再多进行哈希切割，读取query，做下面的操作：

   <img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531212501.png" style="zoom:80%;" />

   但是这样还有问题，因为这样不是均分的，可能很多query都去了同一个桶里，然后这个文件就会非常非常大，这时一种方法是让它切得份数更多，但是其实还可以对两个都没法加载到内存的文件A[i]和B[i]，换一个字符串哈希算法再切分一次。

2. 给一个超过100G大小的log file, log中存着IP地址, 设计算法找到出现次数最多的IP地址？ 与上题条件相同， 如何找到top K的IP？如何直接用Linux系统命令实现？

   同上，本题依然使用哈希切分，依次读取IP，利用一个字符串算法得到它的哈希值再取模，然后和上面一样把它放到不同的文件里，出现切分后的文件太大可以用上面的方法处理，然后每个文件都可以加载到内存后，统计一下出现次数，每个文件保留出现次数最大的IP，然后再每个文件的最大值取大。

   topK呢？其实也很简单，存一个大小为K的优先级队列(大的就是小堆，小的就是大堆)，然后遍历文件得到的结果``<次数, IP>``,遇到的次数比堆顶大(最多的K个)，就弹出堆顶，然后进堆。

# 三、一致性哈希

&emsp;&emsp;如果我们的用户数据存在多台服务器上，那么为了让我们可以通过用户ID得知我们要往那个服务器上发数据而不是遍历所有服务器，显然我们这里也需要一个哈希函数。

&emsp;&emsp;这个哈希函数最好不要取``strhash(id) % 服务器台数``，因为假如我们要增加一台服务器呢，那所有的数据都得重新根据新的服务器数量的哈希算法找到新的位置。

&emsp;&emsp;所以哈希函数可以取``strhash(id) % 2^32``，服务器的位置可以这样分配：``服务器IP % 2^32``，然后进来的请求从哈希后的位置往后找第一个存在服务器结点的位置，进行存储。

&emsp;&emsp;这样的好处是增减服务器时，只需要挪动一部分数据而非所有数据，

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220531220216.png" style="zoom:80%;" />

&emsp;&emsp;一致性哈希这个算法可能出现哈希环倾斜的情况，导致数据被过多的放到某一台服务器上，这时，可以考虑把哈希环上替代为均匀的虚拟结点，然后每个服务器去对应一些虚拟结点。

