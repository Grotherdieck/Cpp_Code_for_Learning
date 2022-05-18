#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int StackDataType;
typedef struct {
	int top;
	StackDataType* arr;
	int capacity;
}Stack;

//#ifdef __cplusplus
//extern "C"
//{
//#endif
//	void StackInit(Stack* ps);
//	void StackPush(Stack* ps, StackDataType e);
//	void StackPop(Stack* ps);
//	StackDataType StackTop(Stack* ps);
//	int StackSize(Stack* ps);
//	bool StackEmpty(Stack* ps);
//	void Stackdestroy(Stack* ps);
//#ifdef __cplusplus
//}
//#endif

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
EXTERN_C void StackInit(Stack* ps);
EXTERN_C void StackPush(Stack* ps, StackDataType e);
EXTERN_C void StackPop(Stack* ps);
EXTERN_C StackDataType StackTop(Stack* ps);
EXTERN_C int StackSize(Stack* ps);
EXTERN_C bool StackEmpty(Stack* ps);
EXTERN_C void Stackdestroy(Stack* ps);
