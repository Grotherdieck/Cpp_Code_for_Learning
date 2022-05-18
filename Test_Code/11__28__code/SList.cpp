#define  _CRT_SECURE_NO_WARNINGS 1
#include "SList.h"

void SLprint(SLNode* phead)
{
	if (phead == NULL)
	{
		printf("链表为空\n");
		return;
	}
	SLNode* p = phead;
	while (p != NULL)
	{
		printf("%d->", p->data);
		p = p->next;
	}
	printf("NULL\n");
}

void SLpushback(SLNode** pphead, Datatype x)
{
	SLNode* newnode = createListNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

void SLpushfront(SLNode** pphead, Datatype x)
{
	SLNode* newnode = createListNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

SLNode* createListNode(Datatype x)
{
	SLNode* newnode = (SLNode*)malloc(sizeof(SLNode));
	if (newnode == NULL)
	{
		printf("malloc fault\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void SLpopback(SLNode** pphead)
{
	if (*pphead == NULL)
	{
		printf("链表已空\n");
		return;
	}
	//assert(*pphead!=NULL);
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		//SLNode* tail = *pphead;
		//while (tail->next->next)
		//{
		//	tail = tail->next;
		//}
		//free(tail->next);
		//tail->next = NULL;
		SLNode* tail = *pphead;
		SLNode* pre = NULL;
		while (tail->next != NULL)
		{
			pre = tail;
			tail = tail->next;
		}
		free(tail);
		pre->next = NULL;
		tail = NULL;
	}
}

void SLpopfront(SLNode** pphead)
{
	if (*pphead == NULL)
		return;
	else
	{
		SLNode* p = (*pphead)->next;
		free(*pphead);
		*pphead = p;
	}
}

SLNode* SListfind(SLNode* phead, Datatype x)
{
	SLNode* p = phead;
	while (p)
	{
		if (p->data == x)
		{
			return p;
		}
		p = p->next;
	}
	//如果最后都没有找到 返回NULL
	return NULL;
}

void SListInsert(SLNode** pphead, SLNode* pos, Datatype x)
{
	if (*pphead == NULL)
	{
		*pphead = createListNode(x);
	}
	else if (pos == *pphead)
	{
		SLNode* newnode = createListNode(x);
		newnode->next = *pphead;
		*pphead = newnode;
	}
	else if (pos == NULL)
	{
		SLpushback(pphead, x);
	}
	else
	{
		SLNode* pre = *pphead;
		while (pre->next != pos)
		{
			pre = pre->next;
		}
		SLNode* newnode = createListNode(x);
		newnode->next = pos;
		pre->next = newnode;
	}
}

void SListInsert2(SLNode** pphead, int pos, Datatype x)
{
	if (*pphead == NULL)
	{
		*pphead = createListNode(x);
	}
	else if (pos == 0)
	{
		SLNode* newnode = createListNode(x);
		newnode->next = *pphead;
		*pphead = newnode;
	}
	else
	{
		SLNode* p = *pphead;
		for (int i = 0; i < pos - 1; i++)
		{
			p = p->next;
		}
		SLNode* newnode = createListNode(x);
		newnode->next = p->next;
		p->next = newnode;
	}
}

void SListInsert_after(SLNode* pos, Datatype x)
{
	SLNode* newnode = createListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

void SListEase(SLNode** pphead, SLNode* pos)
{
	assert(*pphead != NULL);
	if (pos == NULL)
	{
		printf("No such element\n");
		return;
	}
	else if ((*pphead) == pos)
	{
		*pphead = (*pphead)->next;
		free(pos);
	}
	else
	{
		SLNode* p = *pphead;
		while (p->next != pos)
		{
			p = p->next;
		}
		p->next = pos->next;
		free(pos);
	}
}

void SListEase2(SLNode** pphead, int pos)
{
	assert(*pphead != NULL);
	if ((*pphead)->next == NULL && pos == 1)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else if (pos == 1)
	{
		SLNode* tmp = *pphead;
		*pphead = (*pphead)->next;
		free(tmp);
	}
	else
	{
		SLNode* p = *pphead;
		for (int i = 0; i < pos - 2 ; i++)
		{
			p = p->next;
		}
		SLNode* tmp = p->next;
		p->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

void SListEaseAfter(SLNode* pos)
{
	assert(pos->next != NULL);
	SLNode* tmp = pos->next;
	pos->next = pos->next->next;
	free(tmp);
}

void SLdestroy(SLNode** pphead)
{
	SLNode* p = *pphead;
	SLNode* q = NULL;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	*pphead = NULL;
}