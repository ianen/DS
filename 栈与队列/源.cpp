#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
typedef int Status;

//————栈的顺序存储结构————
//栈的顺序存储结构代码
#define MAXSIZE 40
typedef int SElemType;
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;

/**
  *@brief  初始化栈S
  *@param  S，顺序栈的指针
  *@retval 无
  */
void Stack1Init(SqStack** S)
{
	*S = (SqStack*)malloc(sizeof(SqStack));
	int i;
	for (i = 0; i < MAXSIZE; i++)
		(* S)->data[i] = 0;
	(*S)->top = -1;
}

/**
  *@brief  插入元素e为新的栈顶元素
  *@param  S，顺序栈的指针
  *@param  e,要插入栈的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status Push1(SqStack* S, SElemType e)
{
	if (S->top == MAXSIZE - 1)//栈满时
		return ERROR;
	S->top++;
	S->data[S->top] = e;
	return OK;
}

/**
  *@brief  若栈不空，则删除S的栈顶元素，用e返回其值
  *@param  S，顺序栈的指针
  *@param  e,获取栈顶元素的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status Pop1(SqStack* S, SElemType* e)
{
	if (S->top == -1)//栈为空时
		return ERROR;
	*e = S->data[S->top];
	S->top--;
	return OK;
}

//————两栈共享空间————
//两栈共享空间结构
typedef struct
{
	SElemType data[MAXSIZE];
	int top1;//栈1栈顶指针
	int top2;//栈2栈顶指针
}SqDoubleStack;

/**
  *@brief  初始化共享栈S
  *@param  S，顺序栈的指针
  *@retval 无
  */
void Stack2Init(SqDoubleStack** S)
{
	*S = (SqDoubleStack*)malloc(sizeof(SqDoubleStack));
	int i;
	for (i = 0; i < MAXSIZE; i++)
		(*S)->data[i] = 0;
	(*S)->top1 = -1;
	(*S)->top2 = MAXSIZE;
}

/**
  *@brief  根据进栈选择参数插入元素e为新的栈顶元素
  *@param  S，顺序栈的指针
  *@param  e,要插入栈的元素
  *@param  StackNumber,选择进栈的参数 
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status Push2(SqDoubleStack* S, SElemType e, int stackNumber)
{
	if (S->top1 + 1 == S->top2)//栈满时
		return ERROR;
	if (stackNumber == 1)//进栈1时
		S->data[++S->top1] = e;
	else if (stackNumber == 2)//进栈2时
		S->data[--S->top2] = e;
	return OK;
}

/**
  *@brief  根据进栈选择参数，若栈不为空时删除栈顶元素，用e返回其值
  *@param  S，顺序栈的指针
  *@param  e,获取栈顶元素的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status Pop2(SqDoubleStack* S, SElemType* e, int stackNumber)
{
	if (stackNumber == 1)
	{
		if (S->top1 == -1)
			return ERROR;
		*e = S->data[S->top1 --];
	}
	else if (stackNumber == 2)
	{
		if (S->top2 == MAXSIZE)
			return ERROR;
		*e = S->data[S->top2++];
	}
	return OK;
}

//————栈的链式存储结构————
//栈的链式存储结构代码
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;


void Stack3Init(LinkStack** S)
{
	*S = (LinkStack*)malloc(sizeof(LinkStack));
	(*S)->count = 0;
}

/**
  *@brief  在链式栈S中插入e元素作为新的栈顶元素
  *@param  S，链式栈的指针
  *@param  e,要插入栈的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status Push3(LinkStack* S, SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;
	S->top = s;
	S->count++;
	return OK;
}

/**
  *@brief  若栈不空，则删除S的栈顶元素，用e返回其值
  *@param  S，链式栈的指针
  *@param  e,获取栈顶元素的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status Pop3(LinkStack* S, SElemType* e)
{
	LinkStackPtr p;
	if (S->count = 0)
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	free(p);
	S->count--;
	return OK;
}

int main()
{
	//栈的顺序存储结构测试
	SqStack* S;
	SElemType* e;
	e = (SElemType*)malloc(sizeof(SElemType));
	Stack1Init(&S);
	Push1(S, 100);
	Push1(S, 200);
	Push1(S, 300);
	Pop1(S, e);
	printf("栈的顺序存储结构测试结果：%d ",*e);
	Pop1(S, e);
	printf("%d ", *e);
	Pop1(S, e);
	printf("%d \n", *e);

	//两栈共享空间测试
	SqDoubleStack* L;
	Stack2Init(&L);
	Push2(L, 100, 1);
	Push2(L, 200, 2);
	Push2(L, 300, 1);
	Push2(L, 400, 2);
	Pop2(L, e, 2);
	printf("两栈共享空间测试结果：%d ", *e);
	Pop2(L, e, 1);
	printf("%d ", *e);
	Pop2(L, e, 2);
	printf("%d ", *e);
	Pop2(L, e, 1);
	printf("%d \n", *e);

	//栈的链式存储结构测试
	LinkStack *P;
	Stack3Init(&P);
	Push3(P, 100);
	Push3(P, 200);
	Push3(P, 300);
	Pop3(P, e);
	printf("栈的链式存储结构测试结果：%d ", *e);
	Pop3(P, e);
	printf("%d ", *e);
	Pop3(P, e);
	printf("%d \n", *e);
}