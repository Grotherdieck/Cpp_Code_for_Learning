#pragma once
#include <iostream>
#include <string>
#include <bitset>
using namespace std;
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
template <size_t N, 
    size_t X = 5,
    class K = std::string, 
	class HashFunc1 = hash<string>, 
	class HashFunc2 = BKDRhash, 
	class HashFunc3 = APHash>
class BloomFilter
{
public:
    void Set(const K& key)
    {
        size_t len = X * N;
        size_t index1 = HashFunc1()(key) % len;
        size_t index2 = HashFunc2()(key) % len;
        size_t index3 = HashFunc3()(key) % len;
        _bs.set(index1);
        _bs.set(index2);
        _bs.set(index3);
    }
    bool Test(const K& key)
    {
        size_t len = X * N;
        size_t index1 = HashFunc1()(key) % len;
        if (!_bs.test(index1)) return false;
        size_t index2 = HashFunc2()(key) % len;
        if (!_bs.test(index2)) return false;
        size_t index3 = HashFunc3()(key) % len;
        if (!_bs.test(index3)) return false;
        return true;// 三个都在 很大概率是在吧。
    }
private:
	std::bitset<X * N> _bs;
};

void test_bloomfilter()
{
    BloomFilter<100> bfter;
    bfter.Set("我劝你好自为之");
}

void test_Bloomfilter()
{
    const int N = 10000;
    BloomFilter<N> bfter;
    string url = "https://www.routeryt.com";
    
    for (int i = 0; i < N; ++i)
    {
        string tmp = url + to_string(i + 12345);
        bfter.Set(tmp);
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        string tmp = url + to_string(i + 56789);
        if (bfter.Test(tmp)) ++cnt;
    }
    double p = 1.0 * cnt / N;
    cout << "误判率为" << p << endl;
}