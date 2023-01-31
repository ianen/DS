#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//���Ա��˳��洢�ṹ����
#define MAXSIZE 20
typedef int ElemType;
typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}sqList;

//�������״̬����
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
typedef int Status;

/**
  *@brief  ˳�����Ա��ʼ��
  *@param  L,˳�����Ա�
  *@retval ��
  */
void ListInit(sqList* L)
{
	int i;
	for (i = 0; i < MAXSIZE; i++)
		L->data[i] = 0;
	L->length = 0;
}

/**
  *@brief  ���Ա�˳��洢�ṹ��ȡԪ�غ���,����ָ��eָ���Ԫ��λ��
  *@param  L,˳�����Ա�
  *@param  i,Ҫ��ȡ��Ԫ��λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,��ȡԪ�ش洢λ�õ�ָ��
  *@retval ������ȡԪ��״̬�������ȡ�ɹ�����OK��ʧ���򷵻�ERROR
  */
Status GetElem(sqList L,int i,ElemType *e)
{
	if (L.length == 0 || i<1 || i>L.length)//���Ա�Ϊ�ջ���i���ڷ�Χ��ʱ
		return ERROR;
	*e = L.data[i - 1];
	return OK;
}

/**
  *@brief  ��Ԫ��e���뵽˳�����Ա�L�е�iλ��
  *@param  L,˳�����Ա�ı�ͷ
  *@param  i,����Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,Ҫ�����Ԫ��
  *@retval ��������Ԫ��״̬�������ȡ�ɹ�����OK��ʧ���򷵻�ERROR
  */
Status ListInsert(sqList* L, int i, ElemType e)
{
	int k;
	if (L->length == MAXSIZE)//���Ա���ʱ
		return ERROR;
	if (i<1 || i>L->length + 1)//i���ڷ�Χ��
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
  *@brief  ��˳�����Ա�L��λ��Ϊi��Ԫ�ػ�ȡ��eָ���ɾ����Ԫ��
  *@param  L,˳�����Ա�ı�ͷ
  *@param  i,����Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,Ҫ�����Ԫ��
  *@retval ��������Ԫ��״̬�������ȡ�ɹ�����OK��ʧ���򷵻�ERROR
  */
Status ListDelete(sqList* L, int i, ElemType* e)
{
	int k;
	if (L->length == 0)//���Ա�Ϊ��
		return ERROR;
	if (i<1 || i>L->length)//i���ڷ�Χ��
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