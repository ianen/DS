#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//————循环队列————
//循环队列的顺序结构代码
typedef int QElemType;
typedef struct
{
	QElemType data[MAXSIZE];
	int front;//头指针，指向队列的第一个元素
	int rear;//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;

/**
  *@brief  初始化一个空队列Q
  *@param  Q，要初始化的队列指针
  *@retval 函数初始化队列状态结果，成功返回1
  */
Status Queue1Init(SqQueue** Q)
{
	*Q = (SqQueue*)malloc(sizeof(SqQueue));
	(*Q)->front = 0;
	(*Q)->rear = 0;
	return OK;
}

/**
  *@brief  求队列Q的长度
  *@param  Q，队列
  *@retval 队列的长度
  */
int Queue1Length(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/**
  *@brief  将元素e插入队列Q的尾部
  *@param  Q，要插入队列的指针
  *@param e，要插入的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status EnQueue1(SqQueue* Q, QElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)//队列满时
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

/**
  *@brief  若队列不空，则删除队列的头元素，用e返回其值
  *@param  Q，要删除元素队列的指针
  *@param e，返回删除元素的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status DeQueue1(SqQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear)//队列为空时
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

//————队列的链式存储结构————
//链队列结构代码
typedef struct QNode
{
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front, rear;
}LinkQueue;

/**
  *@brief  初始化一个空链队列Q
  *@param  Q，要初始化的队列指针
  *@retval 函数初始化队列状态结果，成功返回1
  */
Status Queue2Init(LinkQueue** Q)
{
	*Q = (LinkQueue*)malloc(sizeof(LinkQueue));
	(*Q)->front = (QueuePtr)malloc(sizeof(QNode));
	(*Q)->rear = (*Q)->front;
	return OK;
}

/**
  *@brief  将元素e插入链队列Q的尾部
  *@param  Q，要插入链队列的指针
  *@param e，要插入的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status EnQueue2(LinkQueue* Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)//存储分配失败
		exit(OVERFLOW);
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}

/**
  *@brief  若队列不空，则删除队列的头元素，用e返回其值
  *@param  Q，要删除元素队列的指针
  *@param e，返回删除元素的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status DeQueue2(LinkQueue* Q, QElemType* e)
{
	QueuePtr p;
	if (Q->front == Q->rear)//队列为空时
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)//当删除后队列为空时
		Q->rear = Q->front;
	free(p);
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

	//循环队列的顺序结构测试
	SqQueue* Q;
	Queue1Init(&Q);
	EnQueue1(Q, 100);
	EnQueue1(Q, 200);
	EnQueue1(Q, 300);
	printf("循环队列的顺序结构测试结果：长度%d ", Queue1Length(*Q));
	DeQueue1(Q, e);
	printf("%d ", *e);
	DeQueue1(Q, e);
	printf("%d ", *e);
	DeQueue1(Q, e);
	printf("%d \n", *e);

	//队列的链式存储结构测试
	LinkQueue *LQ;
	Queue2Init(&LQ);
	EnQueue2(LQ, 100);
	EnQueue2(LQ, 200);
	EnQueue2(LQ, 300);
	DeQueue2(LQ, e);
	printf("队列的链式存储结构测试结果：%d ", *e);
	DeQueue2(LQ, e);
	printf("%d ", *e);
	DeQueue2(LQ, e);
	printf("%d \n", *e);
}