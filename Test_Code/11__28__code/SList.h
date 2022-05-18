#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int Datatype;

typedef struct SLNODE {
	Datatype data;
	struct SLNODE* next;
}SLNode,*SList;

void SLprint(SLNode* phead);

void SLpushback(SLNode** pphead, Datatype x);

void SLpushfront(SLNode** pphead, Datatype x);

SLNode* createListNode(Datatype x);

void SLpopback(SLNode** pphead);

void SLpopfront(SLNode** pphead);

SLNode* SListfind(SLNode* phead, Datatype x);
//查找返回指向结点的指针是为了方便修改值
//并且可以设计循环查找后面的相同元素。

//在pos位置之前插入一个节点
void SListInsert(SLNode** pphead, SLNode* pos, Datatype x);
//这种实现主要是用find返回位置然后插入

void SListInsert_after(SLNode* pos, Datatype x);//在pos位置之后插入

//在下标为pos的元素之前插入x
void SListInsert2(SLNode** pphead, int pos, Datatype x);

void SListEase(SLNode** pphead, SLNode* pos);

void SListEase2(SLNode** pphead, int pos);

void SListEaseAfter(SLNode* pos);

void SLdestroy(SLNode** pphead);