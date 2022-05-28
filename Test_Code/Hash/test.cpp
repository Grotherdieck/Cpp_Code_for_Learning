#define  _CRT_SECURE_NO_WARNINGS 1
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include "HashTable.hpp"
#include "Unordered_map.hpp"
#include "Unordered_set.hpp"
#include "Bitset.hpp"
using namespace std;

void test_unordered_set()
{
	unordered_set<int> myust;
	myust.insert(1);
	myust.insert(3);
	myust.insert(5);
	myust.insert(-6);
	myust.insert(-5);
	auto it = myust.begin();
	while (it != myust.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	/*for (auto p : myust)
	{
		cout << p << ' ';
	}
	cout << endl;*/
	unordered_multiset<int> myums;
	myums.insert(1);
	myums.insert(3);
	myums.insert(5);
	myums.insert(5);
	myums.insert(-6);
	myums.insert(-5);
	for (auto p : myums)
	{
		cout << p << ' ';
	}
	cout << endl;
}

void test_op()
{
	srand((unsigned int)time(nullptr));
	int n = 100000000;
	unordered_set<int> ust;
	set<int> myset;
	vector<int> tmp;
	for (int i = 0; i < n; ++i)
	{
		//int in = rand();
		tmp.push_back(i);
	}
	int begin1 = clock();
	for (int p : tmp) ust.insert(p);
	int end1 = clock();
	int begin2 = clock();
	for (int p : tmp) myset.insert(p);
	int end2 = clock();
	cout << "unordered_set insert : " << end1 - begin1 << "ms" << endl;
	cout << "set insert : " << end2 - begin2 << "ms" << endl;
	int begin3 = clock();
	for (int p : tmp) ust.find(p);
	int end3 = clock();
	int begin4 = clock();
	for (int p : tmp) myset.find(p);
	int end4 = clock();
	cout << "unordered_set find : " << end3 - begin3 << "ms" << endl;
	cout << "set find : " << end4 - begin4 << "ms" << endl;
	int begin5 = clock();
	for (int p : tmp) ust.erase(p);
	int end5 = clock();
	int begin6 = clock();
	for (int p : tmp) myset.erase(p);
	int end6 = clock();
	cout << "unordered_set erase : " << end3 - begin3 << "ms" << endl;
	cout << "set erase : " << end4 - begin4 << "ms" << endl;
}

void testunordered_set()
{
	Router::unordered_set<int> ust;
	ust.insert(1);
	ust.insert(2);
	ust.erase(2);
	int a[] = { 2, 3, 12, -4, -5, 6, 9 , 7, 11, 29, 37, 47, 55 , 55};
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
	mymap.insert(make_pair("sort", "ÅÅĞò"));
	mymap.insert(make_pair("map", "µØÍ¼"));
	auto mit = mymap.begin();
	while (mit != mymap.end())
	{
		cout << mit->first << ' ' << mit->second << endl;
		++mit;
	}
	Router::unordered_map<int, int> cnt;
	for (int p : a) ++cnt[p];
	for (auto& p : cnt)
	{
		cout << p.first << ' ' << p.second << endl;
	}
	Router::unordered_map<int, int> cnt2 = cnt;
	cnt = cnt2;
}

int main()
{
	// test_unordered_set();
	//test_op();
	//LinkHash::test_hash1();
	//LinkHash::test_hash2();
	testunordered_set();
	//Router::test_bitset();
	//Router::go();
	//Router::test();
}