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
		while (_tables[index]._status != EMPTY)
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

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220523154412.png" style="zoom:80%;" />

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

    while (_tables[index]._status != EMPTY)
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
    --_n;
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

&emsp;&emsp;然后在需要计算取模时，进行一个哈希函数:

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220523155142.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220523155209.png" style="zoom:80%;" />

### V 闭散列总代吗

```cpp
namespace CloseHash
{
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

	// 字符串的特化
	template<>
	struct Hash<string>
	{
		size_t operator()(const string& str)
		{
			size_t ret = 0;
			for (char ch : str) ret *= 31, ret += ch;
			return ret;
		}
	};



	template <class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{
	public:
		bool Erase(const K& key)
		{
			HashData<K, V>* ret = find(key);
			if (ret == nullptr) return false;
			ret->_status = DELETE;
			--_n;
			return true;
		}
		HashData<K, V>* find(const K& key)
		{
			HashFunc hf;
			if (_tables.size() == 0) return nullptr;
			size_t start = hf(key) % _tables.size();// 如果vector为空进来会发生/0错误
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				if (_tables[index]._status == EXIST &&
					_tables[index]._kv.first == key) return &_tables[index];
				++i;
				// 线性探测 如果是存在就继续探测
				//index = start + i;
				// 二次探测
				index = start + i * i;
				index %= _tables.size();
			}
			return nullptr;
		}
		bool insert(const pair<K, V>& kv)
		{
			HashFunc hf;
			// 先看看是否存在
			HashData<K, V>* ret = find(kv.first);
			if (ret) return false;
			// 控制负载因子
			// 负载因子越小 冲突概率越低 效率越高 但是空间浪费越多
			// 负载因子月大 冲突概率越大 效率越低 空间浪费越少
			//if (10 * _n / _tables.size() > 7)
			if (_tables.size() == 0 || 10 * _n / 7 > _tables.size())
			{
				// 扩容
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				// 旧方式
				//vector<HashData<K, V>> newTables;
				//newTables.resize(newSize);
				//// 遍历原表 把原表中的数据按newSize重新映射到新表
				//for (int i = 0; i < _tables.size(); ++i)
				//{

				//}
				//_tables.swap(newTables);

				// 直接开一个新的大小的哈希表 然后往里头插入 然后交换他们的vector 用vector的swap
				HashTable<K, V, HashFunc> newHT;
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
			size_t start = hf(kv.first) % _tables.size();
			size_t i = 0;
			size_t index = start + i;

			while (_tables[index]._status != EMPTY)
			{
				++i;
				// 线性探测 如果是存在就继续探测
				//index = start + i;
				// 二次探测
				index = start + i * i;
				index %= _tables.size();
			}
			_tables[index]._kv = kv;
			_tables[index]._status = EXIST;
			++_n;// 有效数字+1
			return true;
		}
	private:
		vector<HashData<K, V>> _tables;
		size_t _n = 0;// 有效数据个数
	};

	void test_hash1()
	{
		HashTable<int, int, Hash<int>> ht;
		int a[] = { 2, 3, 12, -4, -5, 6, 9 , 7, 11, 29, 37, 47, 55 };
		for (auto e : a)
		{
			ht.insert(make_pair(e, e));
		}
		cout << ht.find(12) << endl;
		ht.Erase(12);
		cout << ht.find(12) << endl;
	}

	void test_hash2()
	{
		HashTable<string, string> htf;
		htf.insert(make_pair("sort", "排序"));
		htf.insert(make_pair("map", "地图"));
		htf.insert(make_pair("stl", "标准模板库"));
	}
}
```

## 3 开散列(拉链法)

&emsp;&emsp;开散列的缺点是冲突时，冲突的会去抢别的位置，冲突时会互相影响，就算使用了二次探测，还是会影响效率。

&emsp;&emsp;因此就有了一种新的思路：开散列，也叫拉链法，也叫哈希桶，冲突的值直接像链表一样挂起来就行。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220223123520.png" style="zoom:80%;" />

&emsp;&emsp;极端情况1：表长度是100，来了50个值，假设有40个值是冲突的，挂在同一个桶中，其他桶为空，一个桶太长，查找就会变慢。

&emsp;&emsp;极端情况2：表长度为100，存了10000个值，平均每个桶有100个数，极端场景下有些桶可能有上千个值，查找效率也会变低。

&emsp;&emsp;为应对这两种情况，第一种方法是去控制负载因子(负载因子到了就扩容)，这样从概率上说就很好的控制住了冲突的情况，与闭散列不同，负载因子可以控制的少大一点再扩容，如到了1再扩容。

&emsp;&emsp;这样极端情况2就被控制住了，不过极端情况1仍然是可能存在的，所以有一个处理方法：**当一个桶的长度一定值后，就把这个桶转化为红黑树**，这样高度就会变低了，这样就能 防止极端情况1的防止一个桶位置冲突太多，链表太长，如Java中的HashSet就是如此，不过C/C++中的哈希容器并没有增加这一点来预防这个情况，因为如果这样实现，哈希容器的迭代器会非常难实现，所以我们只实现基于负载因子扩容的开散列。

### I 插入、查找、删除实现

&emsp;&emsp;插入就是直接去哈希到对应位置去头插、如果要扩容，不要像上面闭散列一样去复用``insert``，因为那样会重新开一堆单链表的节点，我们应该把这些结点挂到新的vector里头去，然后调用vector的swap函数交换它们内部的指针。

```cpp
template <class K, class V>
struct HashNode
{
    pair<K, V> _val;
    HashNode<K, V> *_next;
    HashNode(const pair<K, V> &val) : _val(val), _next(nullptr) {}
};
template <class K, class V, class HashFunc = hash<K>>
class HashTable
{
    typedef HashNode<K, V> Node;

public:
    bool insert(const pair<K, V> &kv)
    {
        Node *it = find(kv.first);
        if (it != nullptr)
            return false;
        // 增容
        // 负载因子等于1时扩容
        HashFunc hf;
        if (_n == _tables.size())
        {
            _n = 0;
            int newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
            vector<Node *> newHashTable;
            newHashTable.resize(newSize);
            // 这里不建议使用复用Insert 建议自己遍历原表实现 原因：
            // 因为复用insert会再开新节点，需要重新申请内存
            for (int i = 0; i < _tables.size(); ++i)
            {
                Node *cur = _tables[i];
                while (cur != nullptr)
                {
                    // 全部头插进去
                    Node *next = cur->_next;
                    int index = hf(cur->_val.first) % newHashTable.size();
                    cur->_next = newHashTable[index];
                    newHashTable[index] = cur;
                    ++_n;
                    cur = next;
                }
                _tables[i] = nullptr;
            }
            _tables.swap(newHashTable);
        }
        size_t index = hf(kv.first) % _tables.size();
        // 头插
        ++_n; // 增加负载因子
        Node *newnode = new Node(kv);
        newnode->_next = _tables[index];
        _tables[index] = newnode;
        return true;
    }
    Node *find(const K &key)
    {
        if (_n == 0)
            return nullptr;
        HashFunc hf;
        int index = hf(key) % _tables.size();
        Node *cur = _tables[index];
        while (cur != nullptr && cur->_val.first != key)
            cur = cur->_next;
        return cur;
    }
    bool Erase(const K &key)
    {
        Node *del = find(key);
        if (del == nullptr)
            return false;
        --_n;
        HashFunc hf;
        int index = hf(key) % _tables.size();
        Node *cur = _tables[index];
        if (cur == del)
        {
            _tables[index] = cur->_next;
            delete del;
            return true;
        }
        else
        {
            while (cur->_next != del)
                cur = cur->_next;
            cur->_next = del->_next;
            delete del;
            return true;
        }
    }

private:
    vector<Node *> _tables;
    int _n = 0; // 用于计算负载因子
};
```

&emsp;&emsp;``HashTable``的大小为素数时，从数学上讲冲突的概率比较低，因此源码中扩容时都是直接找下一个素数去扩容的，和我们的10的2倍扩容是不同的，因此我们需要一个素数表：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528175058.png" style="zoom:80%;" />

&emsp;&emsp;因此修改我们的HashTable如下：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528175608.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528175504.png" style="zoom:80%;" />



# 三、封装实现unordered_set和unordered_map

&emsp;&emsp;map只要求key可以比较大小，所以它的模板参数里头只需要支持一个小于比较类型仿函数（大于就反过来即可），

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528110638.png" style="zoom:80%;" />

&emsp;&emsp;而unordered系列容器的模板参数要多一些：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528110018.png" style="zoom:80%;" />

&emsp;&emsp;第三个参数我们很熟悉了，是哈希函数，那第四个参数是啥呢？

&emsp;&emsp;Key要做unorder系列容器的关键字，应该要支持取模或支持能转化为支持取模的整形。

&emsp;&emsp;它要求一个东西，要求Key能比较是否相等，第四个参数就是支持Key比较相等的仿函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528111111.png" style="zoom:80%;" />

&emsp;&emsp;为啥要自己指定是否相等的仿函数呢？以Key是指针类型的情况，默认的是按地址是否相等比较，我们希望比较相等的东西是解引用指针的对象，所以这时需要自己定义是否相等的仿函数。

## 1 基础封装

&emsp;&emsp;这里基础封装和前面的set和map很像，为了只用一个哈希表实现``unordered_set``和``unordered_map``，我们提供一个模板参数``KeyOfT``，注意为了外层能够指定哈希函数，这里``unordered_set``和``unordered_map``的外层模板参数也要给一个hash用来指定哈希函数，我们现在先不考虑比较是否相等的仿函数。

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528114325.png" style="zoom:80%;" />

```cpp
// unordered_set
namespace Router
{
	template <class K, class hash = std::hash<K>>
	class unordered_set
	{
		struct SetKeyofT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		bool insert(const K& key)
		{
			return _ht.insert(key);
		}
	private:
		LinkHash::HashTable<K, K, SetKeyofT, hash> _ht;
	};
}
// unordered_map
namespace Router
{
	// 在外层指定哈希的模板参数
	template <class K, class V, class hash = std::hash<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		bool insert(const pair<K, V>& kv)
		{
			return _ht.insert(kv);
		}
	private:
		LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash> _ht;
	};
}
```

## 2 迭代器

&emsp;&emsp;和以前一样，我们定义一个结构体``__HTIterator``来表示我们的迭代器，首先思考，我们的迭代器重要的是要完成++操作，我们这里针对的是开散列的方法，所以首先要存一个结点的指针，但是仅仅存这个还不够的。

&emsp;&emsp;思考，如果我这个迭代器要++，如果当前结点所在的桶遍历完了（即下一个是空了），我怎么找到下一个位置呢？

&emsp;&emsp;仔细想想会发现这里的矛盾在于我们要找到下一个位置的话，**需要根据当前结点的值找到它对应在哈希表的vector中的位置，然后找后面第一个不为空的位置，作为下一个位置**。

&emsp;&emsp;因此这里的矛盾点在于我们需要获得当前结点的所在的哈希表的位置以及哈希表的大小(防止找出界)，因此**我们增加一个成员变量:指向迭代器所属于的哈希表的指针**，所以迭代器的模板参数不仅仅是迭代器中那个结点的值类型T，还要有哈希表的所有模板参数：

&emsp;&emsp;这样迭代器的结构大概如下：

```cpp
template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc = hash<K>>
struct __HTIterator
{
    typedef HashNode<T> Node;
    typedef __HTIterator<K, Ref, Ptr, T, KeyOfT, HashFunc> self;
    Node *_node;
    HashTable<K, T, KeyOfT, HashFunc> *_pht; // 存一个指向哈希表的指针

    __HTIterator(Node *node, HashTable<K, T, KeyOfT, HashFunc> *pht) : _node(node), _pht(pht)
    {
    }

    Ref operator*()
    {
        return _node->_data;
    }
    Ptr operator->()
    {
        return &(_node->_data);
    }

    // operator++ 前面存一个哈希表的指针就是为了这个
    // 这样如果在某个桶时下一个为空时 那么要往下找下一个不为空的桶
    // 所以需要用一个指向哈希表的指针 来算出当前位置是第几个桶 好往后走
    self &operator++()
    {
        if (_node->_next != nullptr)
        {
            // 桶没走完 走下一个位置
            _node = _node->_next;
        }
        else
        {
            KeyOfT kot;
            HashFunc hf;
            int index = hf(kot(_node->_data)) % (_pht->_tables.size());
            ++index;
            while (index < _pht->_tables.size() && _pht->_tables[index] == nullptr)
            {
                ++index;
            }
            if (index == _pht->_tables.size())
            {
                _node = nullptr;
            }
            else
            {
                _node = _pht->_tables[index];
            }
        }
        return *this;
    }
    self operator++(int)
	{
		self ans = *this;
        ++(*this);
		return ans;
	}
    bool operator==(const self &it)
    {
        return it._node == _node && it._pht == _pht;
    }
    bool operator!=(const self &it)
    {
        return !(*this == it);
    }
};
```

&emsp;&emsp;这里出现了迭代器和哈希表互相引用的问题，因此先声明一下哈希表这个模板类就可以解决这个问题：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528134732.png" style="zoom:80%;" />

&emsp;&emsp;然后在``LinkHash::HashTable``中增加``begin``和``end``函数，在``unordered``同样的begin和end函数去调用哈希表的begin和end函数去得到迭代器，注意和以前一样，要在模板类``LinkHash::HashTable``中提取它的``typedef``的``iterator``，需要增加``typename``关键字去告知编译器这是个类型，在实例化时再做处理。

&emsp;&emsp;当前``LinkHash::Table``和``unordered_set``和``unordered_map``的模板如下：

```cpp
// HashTable.hpp
namespace LinkHash
{
	/*template <class K, class V>
	struct HashData
	{
		forward_list<pair<K, V>> list;
	};*/
	template <class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data) : _data(data), _next(nullptr) {}
	};
	// 迭代器用哈希表 哈希表定义用了哈希表 出现了互相引用的问题
	// 加一个前置声明
	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable;
	template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc = hash<K>>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, Ref, Ptr, T, KeyOfT, HashFunc> self;
		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;// 存一个指向哈希表的指针

		__HTIterator(Node* node, HashTable<K, T, KeyOfT, HashFunc>* pht) : _node(node), _pht(pht) 
		{}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &(_node->_data);
		}

		// operator++ 前面存一个哈希表的指针就是为了这个
		// 这样如果在某个桶时下一个为空时 那么要往下找下一个不为空的桶
		// 所以需要用一个指向哈希表的指针 来算出当前位置是第几个桶 好往后走
		self& operator++()
		{
			if (_node->_next != nullptr)
			{
				// 桶没走完 走下一个位置
				_node = _node->_next;
			}
			else
			{
				KeyOfT kot;
				HashFunc hf;
				int index = hf(kot(_node->_data)) % (_pht->_tables.size());
				++index;
				while (index < _pht->_tables.size() && _pht->_tables[index] == nullptr)
				{
					++index;
				}
				if (index == _pht->_tables.size())
				{
					_node = nullptr;
				}
				else
				{
					_node = _pht->_tables[index];
				}
			}
			return *this;
		}
		self operator++(int)
		{
			self ans = *this;
			++(*this);
			return ans;
		}
		bool operator==(const self& it)
		{
			return it._node == _node && it._pht == _pht;
		}
		bool operator!=(const self& it)
		{
			return !(*this == it);
		}
	};
	template <class K, class T, class KeyOfT, class HashFunc = hash<K>>
	class HashTable
	{
		// 把迭代器弄成友元 这样就可以在迭代器里头访问_tables
		template <class K, class Ref, class Ptr, class T, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
		typedef HashNode<T> Node;
	public:
		typedef __HTIterator<K, T&, T*, T, KeyOfT, HashFunc> iterator;
		iterator begin()
		{
			int index = 0;
			for (index = 0; index < _tables.size(); ++index)
			{
				if (_tables[index])
				{
					return iterator(_tables[index], this);
				}
			}
			return end();
			
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
		bool insert(const T& kv)
		{
			KeyOfT kot;
			Node* it = find(kot(kv));
			if (it != nullptr) return false;
			// 增容
			// 负载因子等于1时扩容
			HashFunc hf;
			if (_n == _tables.size())
			{
				_n = 0;
				int newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
				vector<Node*> newHashTable;
				newHashTable.resize(newSize);
				// 这里不建议使用复用Insert 建议自己遍历原表实现 原因？
				for (int i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur != nullptr)
					{
						Node* next = cur->_next;
						int index = hf(kot(cur->_data)) % newHashTable.size();
						cur->_next = newHashTable[index];
						newHashTable[index] = cur;
						++_n;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newHashTable);
			}
			size_t index = hf(kot(kv)) % _tables.size();
			// 头插
			++_n;// 增加负载因子
			Node* newnode = new Node(kv);
			newnode->_next = _tables[index];
			_tables[index] = newnode;
			return true;
		}
		Node* find(const K& key)
		{
			if (_n == 0) return nullptr;
			HashFunc hf;
			KeyOfT kot;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur != nullptr && kot(cur->_data) != key) cur = cur->_next;
			return cur;
		}
		bool Erase(const K& key)
		{
			Node* del = find(key);
			if (del == nullptr) return false;
			--_n;
			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			if (cur == del)
			{
				_tables[index] = cur->_next;
				delete del;
				return true;
			}
			else
			{
				while (cur->_next != del) cur = cur->_next;
				cur->_next = del->_next;
				delete del;
				return true;
			}
		}
	private:
		vector<Node*> _tables;
		int _n = 0;// 用于计算负载因子
	};
}

// Unordered_set.hpp
#pragma once
#include "HashTable.hpp"
namespace Router
{
	template <class K, class hash = std::hash<K>>
	class unordered_set
	{
		struct SetKeyofT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		// 迭代器拿出来
		typedef typename LinkHash::HashTable<K, K, SetKeyofT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}
		
		iterator end()
		{
			return _ht.end();
		}

		bool insert(const K& key)
		{
			return _ht.insert(key);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

		iterator find(const K& key)
		{
			return iterator(_ht.find(key), &_ht);
		}
	private:
		LinkHash::HashTable<K, K, SetKeyofT, hash> _ht;
	};
}

// Unordered_map.hpp
#pragma once
#include "HashTable.hpp"
namespace Router
{
	// 在外层指定哈希的模板参数
	template <class K, class V, class hash = std::hash<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		bool insert(const pair<K, V>& kv)
		{
			return _ht.insert(kv);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

		iterator find(const K& key)
		{
			return iterator(_ht.find(key), &(_ht));
		}
	private:
		LinkHash::HashTable<K, pair<K, V>, MapKeyOfT, hash> _ht;
	};
}
```

&emsp;&emsp;test一下：

```cpp
void testunordered_set()
{
	Router::unordered_set<int> ust;
	ust.insert(1);
	ust.insert(2);
	ust.erase(2);
	int a[] = { 2, 3, 12, -4, -5, 6, 9 , 7, 11, 29, 37, 47, 55 };
	for (int p : a)
	{
		ust.insert(p);
	}
	Router::unordered_set<int>::iterator it = ust.begin();
	while (it != ust.end())
	{
		cout << *it << endl;
		++it;
	}
	Router::unordered_map<string, string> mymap;
	mymap.insert(make_pair("sort", "排序"));
	mymap.insert(make_pair("map", "地图"));
	auto mit = mymap.begin();
	while (mit != mymap.end())
	{
		cout << mit->first << ' ' << mit->second << endl;
		++mit;
	}
}
```

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528140239.png" style="zoom:80%;" />

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528140306.png" style="zoom:80%;" />

## 3 unordered_map的operator[]

&emsp;&emsp;和map的``operator[]``一样，把``insert``的返回值修改为``pair<iterator, bool>``，然后``operator[]``的操作就是先插入make_pair(key, V())，然后返回其返回值的first(得到这个迭代器)指向的second。

```cpp
V& operator[](const K& key)
{
    auto it = _ht.insert(make_pair(key, V()));
    return (it.first)->second;
}
```

## 4 拷贝构造、赋值、析构函数

&emsp;&emsp;拷贝构造函数就遍历待拷贝的哈希表，把桶的在new出来即可：

```cpp
// 拷贝构造函数
HashTable(const HashTable<K, T, KeyOfT, HashFunc>& ht)
{
    // 要完成深拷贝
    _tables.resize(ht._tables.size());
    for (int i = 0; i < _tables.size(); ++i)
    {
        Node* cur = ht._tables[i];
		while (cur != nullptr)
        {
			Node* newnode = new Node(cur->_data);
            newnode->_next = _tables[i];
			_tables[i] = newnode;
            cur = cur->_next;
		}
    }
}
```

&emsp;&emsp;因为我们写了拷贝构造，编译器就不会给我们生成默认构造了，所以我们自己写一下，有两种写法：

<img src="https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/20220528145851.png" style="zoom:80%;" />

&emsp;&emsp;赋值：使用现代写法

```cpp
// 赋值
self& operator=(self ht)
{
    // 现代写法
    _n = ht._n;
    _tables.swap(ht._tables);
    return *this;
}
```

&emsp;&emsp;析构函数就去释放每个桶就行了：

```cpp
// 析构函数
~HashTable()
{
    for (int i = 0; i < _table.size(); ++i)
    {
        Node* cur = _tables[i];
		while (cur != nullptr)
        {
			Node* ne = cur->_next;
            delete cur;
			cur = ne;
        }
		_tables[i] = nullptr;
    }
}
```

&emsp;&emsp;``unordered_set``和``unordered_map``就不必去再写构造、析构、赋值了，因为编译器默认生成的就够用了。

# 四、基数树的哈希映射

&emsp;&emsp;假设有一个32位整数给我们作为关键字来映射，有一种哈希方法就是把这个32位整数分成4部分，然后根据它的每8位二进制位进行插入，这样最多冲突四次，而且还节约了空间，页表就经常用这种映射方式，也称为多阶哈希。
