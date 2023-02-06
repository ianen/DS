#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
typedef int Status;

//��������ջ��˳��洢�ṹ��������
//ջ��˳��洢�ṹ����
#define MAXSIZE 40
typedef int SElemType;
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;

/**
  *@brief  ��ʼ��ջS
  *@param  S��˳��ջ��ָ��
  *@retval ��
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
  *@brief  ����Ԫ��eΪ�µ�ջ��Ԫ��
  *@param  S��˳��ջ��ָ��
  *@param  e,Ҫ����ջ��Ԫ��
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status Push1(SqStack* S, SElemType e)
{
	if (S->top == MAXSIZE - 1)//ջ��ʱ
		return ERROR;
	S->top++;
	S->data[S->top] = e;
	return OK;
}

/**
  *@brief  ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
  *@param  S��˳��ջ��ָ��
  *@param  e,��ȡջ��Ԫ�ص�ָ��
  *@retval ����ɾ��Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status Pop1(SqStack* S, SElemType* e)
{
	if (S->top == -1)//ջΪ��ʱ
		return ERROR;
	*e = S->data[S->top];
	S->top--;
	return OK;
}

//����������ջ����ռ䡪������
//��ջ����ռ�ṹ
typedef struct
{
	SElemType data[MAXSIZE];
	int top1;//ջ1ջ��ָ��
	int top2;//ջ2ջ��ָ��
}SqDoubleStack;

/**
  *@brief  ��ʼ������ջS
  *@param  S��˳��ջ��ָ��
  *@retval ��
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
  *@brief  ���ݽ�ջѡ���������Ԫ��eΪ�µ�ջ��Ԫ��
  *@param  S��˳��ջ��ָ��
  *@param  e,Ҫ����ջ��Ԫ��
  *@param  StackNumber,ѡ���ջ�Ĳ��� 
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status Push2(SqDoubleStack* S, SElemType e, int stackNumber)
{
	if (S->top1 + 1 == S->top2)//ջ��ʱ
		return ERROR;
	if (stackNumber == 1)//��ջ1ʱ
		S->data[++S->top1] = e;
	else if (stackNumber == 2)//��ջ2ʱ
		S->data[--S->top2] = e;
	return OK;
}

/**
  *@brief  ���ݽ�ջѡ���������ջ��Ϊ��ʱɾ��ջ��Ԫ�أ���e������ֵ
  *@param  S��˳��ջ��ָ��
  *@param  e,��ȡջ��Ԫ�ص�ָ��
  *@retval ����ɾ��Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
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

//��������ջ����ʽ�洢�ṹ��������
//ջ����ʽ�洢�ṹ����
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
  *@brief  ����ʽջS�в���eԪ����Ϊ�µ�ջ��Ԫ��
  *@param  S����ʽջ��ָ��
  *@param  e,Ҫ����ջ��Ԫ��
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
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
  *@brief  ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
  *@param  S����ʽջ��ָ��
  *@param  e,��ȡջ��Ԫ�ص�ָ��
  *@retval ����ɾ��Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
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
	//ջ��˳��洢�ṹ����
	SqStack* S;
	SElemType* e;
	e = (SElemType*)malloc(sizeof(SElemType));
	Stack1Init(&S);
	Push1(S, 100);
	Push1(S, 200);
	Push1(S, 300);
	Pop1(S, e);
	printf("ջ��˳��洢�ṹ���Խ����%d ",*e);
	Pop1(S, e);
	printf("%d ", *e);
	Pop1(S, e);
	printf("%d \n", *e);

	//��ջ����ռ����
	SqDoubleStack* L;
	Stack2Init(&L);
	Push2(L, 100, 1);
	Push2(L, 200, 2);
	Push2(L, 300, 1);
	Push2(L, 400, 2);
	Pop2(L, e, 2);
	printf("��ջ����ռ���Խ����%d ", *e);
	Pop2(L, e, 1);
	printf("%d ", *e);
	Pop2(L, e, 2);
	printf("%d ", *e);
	Pop2(L, e, 1);
	printf("%d \n", *e);

	//ջ����ʽ�洢�ṹ����
	LinkStack *P;
	Stack3Init(&P);
	Push3(P, 100);
	Push3(P, 200);
	Push3(P, 300);
	Pop3(P, e);
	printf("ջ����ʽ�洢�ṹ���Խ����%d ", *e);
	Pop3(P, e);
	printf("%d ", *e);
	Pop3(P, e);
	printf("%d \n", *e);
}