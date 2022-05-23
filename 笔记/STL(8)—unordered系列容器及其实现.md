# 一、unordered_set的使用

## 1 常见接口与简单使用

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521111737.png" style="zoom:80%;" />

&emsp;&emsp;除了下面与底层有有关的接口，其他接口与map/set的接口类似，区别为：

- unordered系列容器的迭代器为单向迭代器；
- unordered容器内的元素不按Key排序。
- set可以做到排序和去重，unordered_set仅仅是去重

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521112427.png" style="zoom:80%;" />

&emsp;&emsp;那如果想把重复的也保留下来呢？用``unordered_multiset``:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521112655.png" style="zoom:80%;" />

## 2 与set的效率对比

&emsp;&emsp;那么如果接口和set都一样，那么为啥要搞出来``unordered_set``呢？由于底层实现不同，unordered_set有一定的效率优势。

```cpp
void test_op()
{
	srand((unsigned int)time(nullptr));
	int n = 10000000;
	unordered_set<int> ust;
	set<int> myset;
	vector<int> tmp;
	for (int i = 0; i < n; ++i)
	{
		int in = rand();
		tmp.push_back(in);
	}
	int begin1 = clock();
	for (int p : tmp) ust.insert(p);
	int end1 = clock();
	int begin2 = clock();
	for (int p : tmp) myset.insert(p);
	int end2 = clock();
	cout << "unordered_set insert : " << end1 - begin1 << "ms" << endl;
	cout << "set insert : " << end2 - begin2 << "ms" << endl;
}
```

100w个数的插入速度：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521113404.png" style="zoom:80%;" />

10000000个数的插入速度：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521113449.png" style="zoom:80%;" />

1亿个数据的插入：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521113910.png" style="zoom:80%;" />

我们知道rand的随机数是只有3w多个的，我们这些插入其中有大量的重复，如果不重复呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521114133.png" style="zoom:80%;" />

&emsp;&emsp;发现set的效率又行了。

&emsp;&emsp;从效率上来说，当数据不重复且有序插入时，红黑树为底层的set的效率会更高，因为此时红黑树左右两边都比较均匀，为红黑树的最好情况；有重复且数据随机插入时，unordered系列容器效率更好。

&emsp;&emsp;后续学习了底层结构后会知道，对哈希容器来说，大量重复数据对哈希来说效率是最好的情况。

&emsp;&emsp;再简单对比一下查找的效率

&emsp;&emsp;有序100w个数据：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521114740.png" style="zoom:80%;" />

&emsp;&emsp;随机且重复100w个数据：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521114853.png" style="zoom:80%;" />

&emsp;&emsp;发现unordered的查找的效率很高。

## 3 集合交集、差集、并集

&emsp;&emsp;并集很简单，放到同一个set里即可。

&emsp;&emsp;交集和差集可以这样获得，先分别放到set中排序加去重。

&emsp;&emsp;然后用两个迭代器遍历这两个set，分别为it1和it2，

- ``*it1 < *it2``，则``*it1``是出现在set1中但不可能出现在set2中的(因为现在it2及其往后的都是``>= *it2``元素)，所以它就是``s1-s2``的差集；
- ``*it1 > *it2``，则``*it2``是出现在set2中但不可能出现在set1中的(因为it1及其往后都是``>= *it1``的元素)，所以它就是``s2-s1``的差集；
- ``*it1 == *it2``，则两个相同，同时出现在set1和set2中，是s1和s2的交集。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521121422.png" style="zoom:80%;" />

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
    {
        set<int> s1, s2;
        for (int p : nums1) s1.insert(p);
        for (int p : nums2) s2.insert(p);
        auto it1 = s1.begin(), it2 = s2.begin();
        vector<int> ans;
        while (it1 != s1.end() && it2 != s2.end())
        {
            if (*it1 < *it2) ++it1;
            else if (*it1 > *it2) ++it2;
            else 
            {
                ans.push_back(*it1);
                ++it1, ++it2;
            }
        }
        return ans;
    }
};
```

# 二、底层结构

## 1 哈希概念

&emsp;&emsp;哈希又叫散列，我们之前学习计数排序时，就接触过哈希的思想，我们把元素x映射到``++count[x - min(arr)]``。

&emsp;&emsp;哈希的本质就是建立某种映射，把元素根据其值映射到某一位置，下一次通过再次找到这个位置去查找和删除它。

&emsp;&emsp;但是仅仅是普通的映射并不行，首先不同的值映射可能映射到同一位置（不可能对所有值都能找到双射的哈希映射）；其次哈希方式也是很不容易找的，哪有那么多的哈希函数给你用。。。

&emsp;&emsp;一种常见的哈希函数就是对一个数字，采用**除留余数法**:
$$
f(key) = key \% capacity
$$
&emsp;&emsp;但是取模很有可能导致不同的值映射到相同的位置，这时我们称为**冲突**或**碰撞**。

&emsp;&emsp;所以矛盾就转移了，怎么解决这种哈希冲突呢？有很多方法：**拉链法(开散列)**和**开放定址法(闭散列)**。

## 2 闭散列(开放寻址法)

### I 线性探测

&emsp;&emsp;线性探测的思想就是一种强盗逻辑，我的位置如果被冲突给占了，我就去占后面第一个空的位置(其实这是别人的位置)。

&emsp;&emsp;但是线性探测会有很多问题，一个是怎么表示空位置呢？另一个是如果进行erase后，那么这个位置究竟应该怎么表示，否则我在后面的东西就找不到了啊，比如下图中，假设是取模10，怎么找44呢？

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521162052.png" style="zoom:80%;" />

&emsp;&emsp;解决方式是增加一个枚举变量，标记每个位置是**存在**、**空**、**删除**，查找时遇到空才停止，遇到删除继续找。

&emsp;&emsp;大体逻辑（暂不考虑扩容）：

```cpp
// 标识每个位置的状态
enum Status
{
	EXIST,
	EMPTY,
	DELETE
};

template <class K, class V>
struct HashData
{
	pair<K, V> _kv;
	Status _status = EMPTY;
};

template <class K, class V>
class HashTable
{
public:
	bool insert(const pair<K, V>& kv)
	{
		// 这里不能模cap 因为这样会越size访问vector的空间 影响size的同时还会被拿下
		size_t start = kv.first % _tables.size();
		size_t i = 0;
		size_t index = start + i;
		// 线性探测 如果是存在就继续探测
		while (_tables[index]._status == EXIST)
		{
			++i;
			index = start + i;
			index %= _tables.size();
		}
		_tables[index]._kv = kv;
		_tables[index]._status = EXIST;
		++_n;// 有效数字+1

	}
private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0;// 有效数据个数
};
```

&emsp;&emsp;线性探测法的缺点是，如果插入的连续的值冲突的比较多，会引发“踩踏”的问题，互相挤位置，效率就会很低。

&emsp;&emsp;为了解决这个踩踏的问题，有人提出了二次探测的方法。

### II 二次探测

&emsp;&emsp;线性探测每次探测的位置是：``index = start + i(i = 0, 1, 2, 3,...)``，二次探测法的改进就是把``i``换成``i ^ 2``,``index = start + i ^ i(i = 0, 1, 2, 3,...)`` ，这样探测的时候整体会分散很多，就不会特别拥挤了。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521152930.png" style="zoom:80%;" />

### III 开散列的哈希表的插入、查找、删除实现

&emsp;&emsp;但是二次探测和线性探测都很有风险，如果快满了，每次找一个空位置都要找好久塞。

&emsp;&emsp;因此这种开散列来解决冲突的方法会引入一个载荷因子的概念， 也叫负载因子：

## 待替换图片

![image-20220521153109111](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220521153109111.png)

&emsp;&emsp;扩容的方法有两种，首先，扩容时我们要保证原来表中的元素的新位置满足新的空间大小的映射，所以要么新开一个新大小的vector然后把旧表中的元素按新的空间大小进行映射，或者直接复用insert时写的代码：

```cpp
bool insert(const pair<K, V> &kv)
{
    // 控制负载因子
    // 负载因子越小 冲突概率越低 效率越高 但是空间浪费越多
    // 负载因子月大 冲突概率越大 效率越低 空间浪费越少
    // if (10 * _n / _tables.size() > 7)
    if (_tables.size() == 0 || 10 * _n / 7 > _tables.size())
    {
        // 扩容
        size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
        // 旧方式
        // vector<HashData<K, V>> newTables;
        // newTables.resize(newSize);
        //// 遍历原表 把原表中的数据按newSize重新映射到新表
        // for (int i = 0; i < _tables.size(); ++i)
        //{

        //}
        //_tables.swap(newTables);

        // 直接开一个新的大小的哈希表 然后往里头插入 然后交换他们的vector 用vector的swap
        HashTable<K, V> newHT;
        newHT._tables.resize(newSize);
        for (int i = 0; i < _tables.size(); ++i)
        {
            if (_tables[i]._status == EXIST)
            {
                newHT.insert(_tables[i]._kv);
            }
        }
        _tables.swap(newHT._tables);
        // newHT自己去走析构函数释放资源就好
    }

    // 这里不能模cap 因为这样会越size访问vector的空间 影响size的同时还会被拿下
    size_t start = kv.first % _tables.size();
    size_t i = 0;
    size_t index = start + i;

    while (_tables[index]._status == EXIST)
    {
        ++i;
        // 线性探测 如果是存在就继续探测
        // index = start + i;
        // 二次探测
        index = start + i * i;
        index %= _tables.size();
    }
    _tables[index]._kv = kv;
    _tables[index]._status = EXIST;
    ++_n; // 有效数字+1
    return true;
}
```

&emsp;&emsp;简单测试一下：

```cpp
void test_hash1()
{
	HashTable<int, int> ht;
	int a[] = { 2, 3, 12, 4, 5, 6, 9 , 7, 11, 29, 37, 47, 55};
	for (auto e : a)
	{
		ht.insert(make_pair(e, e));
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521161135.png" style="zoom:80%;" />

&emsp;&emsp;但是我们当前的insert还缺少对重复值的判断，如果重复，就不必插入了。

&emsp;&emsp;所以增加一个find函数，主要逻辑就是根据开散列的方法去找这个点，为配合Erase，注意要保证查到的点既是key相等，这个点的状态又是``EXIST``，找得到就返回这个点的指针，找不到就返回空指针：

``find``:

```cpp
HashData<K, V> *find(const K &key)
{
    if (_tables.size() == 0)
        return nullptr;
    size_t start = key % _tables.size(); // 如果vector为空进来会发生/0错误
    size_t i = 0;
    size_t index = start + i;

    while (_tables[index]._status != EMPTY)
    {
        if (_tables[index]._status == EXIST &&
            _tables[index]._kv.first == key)
            return &_tables[index];
        ++i;
        // 线性探测 如果是存在就继续探测
        // index = start + i;
        // 二次探测
        index = start + i * i;
        index %= _tables.size();
    }
    return nullptr;
}
```

``Erase``:

```cpp
bool Erase(const K& key)
{
    HashData<K, V>* ret = find(key);
	if (ret == nullptr) return false;
    ret->_status = DELETE;
    --_
	return true;
}
```

### IV 自定义哈希函数—仿函数

&emsp;&emsp;我们上面的哈希容器没法处理字符串情况，所以我们可以增加一个模板参数，给一个哈希函数。

&emsp;&emsp;我们这里搞一个简单一点的字符串哈希方式，每个字符的ascii码加起来：

```cpp
template <class K, class V>
struct StrHash
{
	size_t operator()(const string& str)
	{
		size_t ret = 0;
		for (char ch : str) ret += ch;
		return ret;
	}
};
```

&emsp;&emsp;但是这样的哈希方式可能导致两个字符串映射到同一个哈希值，如abc和cba，但是冲突就冲突嘛，让哈希表用开散列的方法帮我们解决冲突即可，但是我们尽量还是做到，所以有大佬Brian Kernighan与Dennis Ritchie的字符串哈希算法，它被《The C programing Language》收录，是一种简易字符串哈希的方法，就是当前哈希值先乘一个数p再加下一个数的ASCII码，思路与我们在算法专栏介绍的字符串哈希方法相似：

```cpp
struct StrHash
{
	size_t operator()(const string& str)
	{
		size_t ret = 0;
		for (char ch : str) ret *= 31, ret += ch;
		return ret;
	}
};
```

&emsp;&emsp;然后为了让普通的整数也可以正常使用哈希而不用特别指定哈希函数，我们为模板增加一个缺省参数：

```cpp
// 缺省的哈希
template <class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		// 顺便把负数转成整数了 因为C++取模负数取模出来负数
		return key;
	}
};
```

&emsp;&emsp;STL中不需要指定哈希函数就可以使用string的哈希方式，说明它对``hash<string>``进行了特化，我们仿照一下，把我们的字符串哈希也特化一下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521171606.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521171712.png" style="zoom:80%;" />

&emsp;&emsp;所以如果我们使用STL时，使用unordered系列容器，对自定义类型（如日期类）需要自定义哈希函数，就可以给一个仿函数，或者给一个``hash<自定义类型>``的特化:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220521171852.png" style="zoom:80%;" />

```cpp
template<>
struct hash<Date>
{
    size_t operator()(const Date& date)
    {
        //...
    }
}
```

## 3 开散列(拉链法)

&emsp;&emsp;开散列的缺点是冲突时，冲突的会去抢别的位置，冲突时会互相影响，就算使用了二次探测，还是会影响效率。

&emsp;&emsp;因此就有了一种新的思路：开散列，也叫拉链法，也叫哈希桶。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220223123520.png" style="zoom:80%;" />





