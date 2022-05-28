#pragma once
#include <vector>
#include <iostream>
#include <fstream>
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
	template <size_t N>
	class TwoBitset
	{
	public:
		bit_set<N> _bt1;
		bit_set<N> _bt2;
	};
	void test()
	{
		TwoBitset<1000> t;
		std::ifstream ifs("test.txt");
		size_t x;
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
		for (size_t i = 0; i < 1000; ++i)
		{
			if (t._bt1.test(i) && !t._bt2.test(i))
			{
				cout << i << endl;
			}
		}
	}
	void go()
	{
		std::ofstream ofs("test.txt");
		srand((unsigned int)time(nullptr));
		for (size_t i = 0; i < 100; ++i)
		{
			int x = rand() % 1000;
			ofs << x << endl;
		}
	}
}