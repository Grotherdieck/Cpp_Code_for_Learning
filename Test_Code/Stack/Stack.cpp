#define  _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"
void StackInit(Stack* ps)
{
	assert(ps);
	ps->capacity = 0;
	ps->arr = NULL;
	ps->top = 0;
	//top指0意味着指向栈顶数据的下一个位置
	//ps->top = -1;
	//top指-1意味着它指向栈顶数据
}
bool StackEmpty(Stack* ps)
{
	assert(ps);
	return ps->top == 0;
	//return ps->top == -1;
}
int StackSize(Stack* ps)
{
	assert(ps);
	return ps->top;
}
void checkcapacity(Stack* ps)
{
	if (ps->capacity == ps->top)
	{
		int newcapacity = (ps->arr == NULL ? 4 : 2 * ps->capacity);
		StackDataType* tmp = (StackDataType*)realloc(ps->arr, newcapacity*sizeof(StackDataType));
		if (tmp == NULL)
		{
			printf("realloc fault\n");
			exit(-1);
		}
		ps->arr = tmp;
		ps->capacity = newcapacity;
	}
}
void StackPush(Stack* ps, StackDataType e)
{
	assert(ps);
	checkcapacity(ps);
	ps->arr[ps->top] = e;
	ps->top++;
}
void StackPop(Stack* ps)
{
	assert(ps && StackEmpty(ps) != true);
	ps->top--;
}
StackDataType StackTop(Stack* ps)
{
	assert(ps && StackEmpty(ps) != true);
	return ps->arr[ps->top - 1];
}
void Stackdestroy(Stack* ps)
{
	assert(ps);
	ps->top = 0;
	ps->capacity = 0;
	free(ps->arr);
	ps->arr = NULL;
}