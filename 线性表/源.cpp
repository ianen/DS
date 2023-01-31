#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
  *@param  L,顺序线性表
  *@retval 无
  */
void ListInit(sqList* L)
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
		L->data[i] = 0;
	L->length = 0;
}

/**
  *@brief  线性表顺序存储结构获取元素函数,并将指针e指向该元素位置
  *@param  L,顺序线性表
  *@param  i,要获取的元素位置，范围1<=i<=ListLength(L)
  *@param  e,获取元素存储位置的指针
  *@retval 函数获取元素状态结果，获取成功返回OK，失败则返回ERROR
  */
Status GetElem(sqList L,int i,ElemType *e)
{
	if (L.length == 0 || i<1 || i>L.length)//线性表为空或者i不在范围内时
		return ERROR;
	*e = L.data[i - 1];
	return OK;
}

/**
  *@brief  将元素e插入到顺序线性表L中的i位置
  *@param  L,顺序线性表的表头
  *@param  i,插入元素的位置，范围1<=i<=ListLength(L)
  *@param  e,要插入的元素
  *@retval 函数插入元素状态结果，获取成功返回OK，失败则返回ERROR
  */
Status ListInsert(sqList* L, int i, ElemType e)
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
  *@param  L,顺序线性表的表头
  *@param  i,插入元素的位置，范围1<=i<=ListLength(L)
  *@param  e,要插入的元素
  *@retval 函数插入元素状态结果，获取成功返回OK，失败则返回ERROR
  */
Status ListDelete(sqList* L, int i, ElemType* e)
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


int main()
{
	sqList *P;
	ElemType* e, * f;
	e = (ElemType *)malloc(sizeof(ElemType));
	f = (ElemType *)malloc(sizeof(ElemType));
	P = (sqList *)malloc(sizeof(sqList));
	ListInit(P);
	ListInsert(P, 1, 3);
	ListInsert(P, 2, 5);
	ListDelete(P, 1, e);
	GetElem(*P, 1, f);
	printf("%d %d", *e, *f);
}