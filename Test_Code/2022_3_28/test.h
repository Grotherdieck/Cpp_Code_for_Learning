#pragma once
#include <iostream>
using namespace std;

//template<class T1, class T2>
//class Data
//{
//public:
//	Data() { cout << "Data<T1, T2>" << endl; }
//private:
//	
//};
//// ƫ�ػ�ָ�����ֲ���
//template<class T>
//class Data<T, char>
//{
//public:
//	Data() { cout << "Data<T, char>" << endl; }
//private:
//	T _d1;
//	char _d2;
//};
//
//// ����Ϊָ��
//template<class T1, class T2>
//class Data<T1*, T2*>
//{
//public:
//	Data() { cout << "Data<T1*, T2*>" << endl; }
//private:
//	T1* _d1;
//	T2* _d2;
//};
//// �޶�Ϊ����
//template<class T1, class T2>
//class Data<T1&, T2&>
//{
//public:
//	Data() { cout << "Data<T1&, T2&>" << endl; }
//private:
//	
//};
//
//// һ������ һ��ָ��
//template<class T1, class T2>
//class Data<T1&, T2*>
//{
//public:
//	Data() { cout << "Data<T1&, T2*>" << endl; }
//private:
//
//};
//
//// ������ģ��������ػ�
//template<size_t N>
//class A
//{
//public:
//	A() { cout << "A<N>" << endl; }
//
//};
//
//template<>
//class A<10>
//{
//public:
//	A() { cout << "A<10>" << endl; }
//
//};

template <class T>
T add(const T& a, const T& b);

template <class T>
class A
{
public:
	A();
	T myval();
private:
	T _a;
};