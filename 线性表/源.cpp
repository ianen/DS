#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//————顺序线性表————
//线性表的顺序存储结构代码
#define MAXSIZE 20
typedef int ElemType;
typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}sqList;

//函数结果状态代码
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
typedef int Status;

/**
  *@brief  顺序线性表初始化
  *@param  L,顺序线性表指针
  *@retval 无
  */
void List1Init(sqList** L)
{
	int i;
	*L = (sqList*)malloc(sizeof(sqList));
	for (i = 0; i < MAXSIZE; i++)
		(*L)->data[i] = 0;
	(*L)->length = 0;
}

/**
  *@brief  线性表顺序存储结构获取元素函数,并将指针e指向该元素位置
  *@param  L,顺序线性表
  *@param  i,要获取的元素位置，范围1<=i<=ListLength(L)
  *@param  e,获取元素存储位置的指针
  *@retval 函数获取元素状态结果，成功返回1，失败则返回0
  */
Status Get1Elem(sqList *L,int i,ElemType *e)
{
	if (L->length == 0 || i<1 || i>L->length)//线性表为空或者i不在范围内时
		return ERROR;
	*e = L->data[i - 1];
	return OK;
}

/**
  *@brief  将元素e插入到顺序线性表L中的i位置
  *@param  L,顺序线性表的指针
  *@param  i,插入元素的位置，范围1<=i<=ListLength(L)
  *@param  e,要插入的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status List1Insert(sqList* L, int i, ElemType e)
{
	int k;
	if (L->length == MAXSIZE)//线性表满时
		return ERROR;
	if (i<1 || i>L->length + 1)//i不在范围内
		return ERROR;
	if (i <= L->length)
	{
		for (k = L->length - 1; k >= i - 1; k--)
			L->data[k + 1] = L->data[k];
	}
	L->data[i - 1] = e;
	L->length++;
	return OK;
}

/**
  *@brief  将顺序线性表L中位置为i的元素获取到e指针后，删除该元素
  *@param  L,顺序线性表的指针
  *@param  i,插入元素的位置，范围1<=i<=ListLength(L)
  *@param  e,要插入的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status List1Delete(sqList* L, int i, ElemType* e)
{
	int k;
	if (L->length == 0)//线性表为空
		return ERROR;
	if (i<1 || i>L->length)//i不在范围内
		return ERROR;
	*e = L->data[i - 1];
	if (i < L->length)
	{
		for (k = i; k < L->length; k++)
			L->data[k - 1] = L->data[k];
	}
	L->length--;
	return OK;
}


//————单链线性表————
//单链表结构代码
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node* LinkList;

/**
  *@brief  将单链表L中位置为i的元素读取到e指针
  *@param  L,单链表的头指针
  *@param  i,读取元素的位置，范围1<=i<=ListLength(L)
  *@param  e,读取后元素存放位置
  *@retval 函数读取元素状态结果，成功返回1，失败则返回0
  */
Status Get2Elem(LinkList L, int i, ElemType* e)
{
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)//若i过大或者过小时
		return ERROR;
	*e = p->data;
	return OK;
}

/**
  *@brief  将元素e插入到单链表L中位置为i的地方
  *@param  L,单链表的头指针
  *@param  i,插入元素的位置，范围1<=i<=ListLength(L)
  *@param  e,插入的元素
  *@retval 函数插入元素状态结果，成功返回1，失败则返回0
  */
Status List2Insert(LinkList L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = L;
	j = 1;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)//若i过大或者过小时
		return ERROR;
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

/**
  *@brief  将单链表L中位置为i的元素删除
  *@param  L,单链表的头指针
  *@param  i,删除元素的位置，范围1<=i<=ListLength(L)
  *@param  e,删除元素存放的指针
  *@retval 函数删除元素状态结果，成功返回1，失败则返回0
  */
Status List2Delete(LinkList L, int i, ElemType* e)
{
	int j;
	LinkList p, q;//前一元素和插入位置元素
	p = L;
	j = 1;
	while (p->next && j < i)
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

/**
  *@brief  随机产生n个元素的值，采用头插法建立带表头节点的单链线性表L
  *@param  L,单链表的头指针
  *@param  n,随机产生元素的个数
  *@retval 无
  */
void CreateList2Head(LinkList *L, int n)
{
	LinkList p;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	for (i = 0; i < n; i++)
	{
		p= (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

/**
  *@brief  随机产生n个元素的值，采用尾插法建立带表头节点的单链线性表L
  *@param  L,单链表的头指针
  *@param  n,随机产生元素的个数
  *@retval 无
  */
void CreateList2Tail(LinkList *L, int n)
{
	LinkList p, r;//新的节点和尾部节点
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

/**
  *@brief  将单链表L整表删除
  *@param  L,单链表的头指针
  *@retval 函数整表删除状态结果，成功返回1
  */
Status ClearList2(LinkList L)
{
	LinkList p, q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}


//————静态链表————
//线性表的静态链表存储结构
#define MAXSIZE 1000
typedef struct
{
	ElemType data;
	int cur;
}Component,StaticLinkList[MAXSIZE];

/**
  *@brief  初始化一条静态链表
  *@param  space，静态链表
  *@retval 函数整表删除状态结果，成功返回1
  */
Status List3Init(StaticLinkList space)
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0;
	return OK;
}

/**
  *@brief  若备用空间链表非空，则放回分配的节点下表
  *@param  space，静态链表
  *@retval 分配的空闲节点下标
  */
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur;//返回第一个备用空闲节点的下标
	if (space[0].cur)
		space[0].cur = space[i].cur;
	return i;//放回分配的空闲节点下标
}

/**
  *@brief  将下标为k的空闲节点回收到备用链表中
  *@param  space，静态链表
  *@param  k，要回收的空闲节点的下标
  *@retval 无
  */
void Free_SSL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

/**
  *@brief  在L的第i个元素之前插入新的数据元素e
  *@param  L，静态链表
  *@param  i,插入的位置
  *@param  e，插入的数据元素
  *@retval 函数整表删除状态结果，成功返回1，失败返回0
  */
Status List3Insert(StaticLinkList L, int i, ElemType e)
{
	int j, k, l;
	k = MAXSIZE - 1;//k为最后一个元素的下标，其存放第一个有数值的元素下标
	if (i < 1 || i>L[0].cur+2)//i不在静态链表可插入范围内时
		return ERROR;
	j = Malloc_SSL(L);//j为第一个备用空闲节点的下标
	if (j)
	{
		L[j].data = e;
		for (l = 1; l <= i - 1; l++)//找到第i个元素之前的位置，赋值给k
			k = L[k].cur;
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	}
	return ERROR;
}

/**
  *@brief  将L的第i个元素删除
  *@param  L，静态链表
  *@param  i,要删除元素的位置
  *@retval 函数整表删除状态结果，成功返回1，失败返回0
  */
Status List3Delete(StaticLinkList L, int i)
{
	int j, k;
	if (i<1 || i>L[0].cur + 1)//i不在静态链表数据范围内时
		return ERROR;
	k = MAXSIZE - 1;//k为第一个数据的下标
	for (j = 1; j <= i - 1; j++)//循环到k的cur指向第i个元素
		k = L[k].cur;
	j = L[k].cur;//将第i个元素的下标赋值给j
	L[k].cur = L[j].cur;
	Free_SSL(L, j);
	return OK;
}

int main()
{
	//顺序线性表测试
	sqList* P;
	ElemType* e, * f;
	e = (ElemType*)malloc(sizeof(ElemType));
	f = (ElemType*)malloc(sizeof(ElemType));
	List1Init(&P);
	List1Insert(P, 1, 100);
	List1Insert(P, 2, 200);
	List1Delete(P, 1, e);
	Get1Elem(P, 1, f);
	printf("顺序线性表测试结果：%d %d\n", *e, *f);

	//单链线性表测试
	LinkList L1, L2;
	CreateList2Head(&L1, 10);
	CreateList2Tail(&L2, 10);
	List2Insert(L1, 3, 100);
	List2Delete(L1, 2, e);
	Get2Elem(L1, 2, f);
	printf("单链线性表测试结果：%d %d\n", *e, *f);
	ClearList2(L1);
	ClearList2(L2);

	//静态链表测试
	StaticLinkList L;
	List3Init(L);
	List3Insert(L, 1, 200);
	List3Insert(L, 2, 100);
	List3Delete(L, 1);
	printf("静态链表测试结果：%d\n", L[L[MAXSIZE - 1].cur].data);
	return 0;
}