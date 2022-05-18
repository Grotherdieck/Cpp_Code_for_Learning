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
//���ҷ���ָ�����ָ����Ϊ�˷����޸�ֵ
//���ҿ������ѭ�����Һ������ͬԪ�ء�

//��posλ��֮ǰ����һ���ڵ�
void SListInsert(SLNode** pphead, SLNode* pos, Datatype x);
//����ʵ����Ҫ����find����λ��Ȼ�����

void SListInsert_after(SLNode* pos, Datatype x);//��posλ��֮�����

//���±�Ϊpos��Ԫ��֮ǰ����x
void SListInsert2(SLNode** pphead, int pos, Datatype x);

void SListEase(SLNode** pphead, SLNode* pos);

void SListEase2(SLNode** pphead, int pos);

void SListEaseAfter(SLNode* pos);

void SLdestroy(SLNode** pphead);