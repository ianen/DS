#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��������˳�����Ա�������
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
  *@param  L,˳�����Ա�ָ��
  *@retval ��
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
  *@brief  ���Ա�˳��洢�ṹ��ȡԪ�غ���,����ָ��eָ���Ԫ��λ��
  *@param  L,˳�����Ա�
  *@param  i,Ҫ��ȡ��Ԫ��λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,��ȡԪ�ش洢λ�õ�ָ��
  *@retval ������ȡԪ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status Get1Elem(sqList *L,int i,ElemType *e)
{
	if (L->length == 0 || i<1 || i>L->length)//���Ա�Ϊ�ջ���i���ڷ�Χ��ʱ
		return ERROR;
	*e = L->data[i - 1];
	return OK;
}

/**
  *@brief  ��Ԫ��e���뵽˳�����Ա�L�е�iλ��
  *@param  L,˳�����Ա��ָ��
  *@param  i,����Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,Ҫ�����Ԫ��
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status List1Insert(sqList* L, int i, ElemType e)
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
  *@param  L,˳�����Ա��ָ��
  *@param  i,����Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,Ҫ�����Ԫ��
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status List1Delete(sqList* L, int i, ElemType* e)
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


//���������������Ա�������
//������ṹ����
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node* LinkList;

/**
  *@brief  ��������L��λ��Ϊi��Ԫ�ض�ȡ��eָ��
  *@param  L,�������ͷָ��
  *@param  i,��ȡԪ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,��ȡ��Ԫ�ش��λ��
  *@retval ������ȡԪ��״̬������ɹ�����1��ʧ���򷵻�0
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
	if (!p || j > i)//��i������߹�Сʱ
		return ERROR;
	*e = p->data;
	return OK;
}

/**
  *@brief  ��Ԫ��e���뵽������L��λ��Ϊi�ĵط�
  *@param  L,�������ͷָ��
  *@param  i,����Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,�����Ԫ��
  *@retval ��������Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
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
	if (!p || j > i)//��i������߹�Сʱ
		return ERROR;
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

/**
  *@brief  ��������L��λ��Ϊi��Ԫ��ɾ��
  *@param  L,�������ͷָ��
  *@param  i,ɾ��Ԫ�ص�λ�ã���Χ1<=i<=ListLength(L)
  *@param  e,ɾ��Ԫ�ش�ŵ�ָ��
  *@retval ����ɾ��Ԫ��״̬������ɹ�����1��ʧ���򷵻�0
  */
Status List2Delete(LinkList L, int i, ElemType* e)
{
	int j;
	LinkList p, q;//ǰһԪ�غͲ���λ��Ԫ��
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
  *@brief  �������n��Ԫ�ص�ֵ������ͷ�巨��������ͷ�ڵ�ĵ������Ա�L
  *@param  L,�������ͷָ��
  *@param  n,�������Ԫ�صĸ���
  *@retval ��
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
  *@brief  �������n��Ԫ�ص�ֵ������β�巨��������ͷ�ڵ�ĵ������Ա�L
  *@param  L,�������ͷָ��
  *@param  n,�������Ԫ�صĸ���
  *@retval ��
  */
void CreateList2Tail(LinkList *L, int n)
{
	LinkList p, r;//�µĽڵ��β���ڵ�
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
  *@brief  ��������L����ɾ��
  *@param  L,�������ͷָ��
  *@retval ��������ɾ��״̬������ɹ�����1
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


//����������̬����������
//���Ա�ľ�̬����洢�ṹ
#define MAXSIZE 1000
typedef struct
{
	ElemType data;
	int cur;
}Component,StaticLinkList[MAXSIZE];

/**
  *@brief  ��ʼ��һ����̬����
  *@param  space����̬����
  *@retval ��������ɾ��״̬������ɹ�����1
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
  *@brief  �����ÿռ�����ǿգ���Żط���Ľڵ��±�
  *@param  space����̬����
  *@retval ����Ŀ��нڵ��±�
  */
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur;//���ص�һ�����ÿ��нڵ���±�
	if (space[0].cur)
		space[0].cur = space[i].cur;
	return i;//�Żط���Ŀ��нڵ��±�
}

/**
  *@brief  ���±�Ϊk�Ŀ��нڵ���յ�����������
  *@param  space����̬����
  *@param  k��Ҫ���յĿ��нڵ���±�
  *@retval ��
  */
void Free_SSL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

/**
  *@brief  ��L�ĵ�i��Ԫ��֮ǰ�����µ�����Ԫ��e
  *@param  L����̬����
  *@param  i,�����λ��
  *@param  e�����������Ԫ��
  *@retval ��������ɾ��״̬������ɹ�����1��ʧ�ܷ���0
  */
Status List3Insert(StaticLinkList L, int i, ElemType e)
{
	int j, k, l;
	k = MAXSIZE - 1;//kΪ���һ��Ԫ�ص��±꣬���ŵ�һ������ֵ��Ԫ���±�
	if (i < 1 || i>L[0].cur+2)//i���ھ�̬����ɲ��뷶Χ��ʱ
		return ERROR;
	j = Malloc_SSL(L);//jΪ��һ�����ÿ��нڵ���±�
	if (j)
	{
		L[j].data = e;
		for (l = 1; l <= i - 1; l++)//�ҵ���i��Ԫ��֮ǰ��λ�ã���ֵ��k
			k = L[k].cur;
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	}
	return ERROR;
}

/**
  *@brief  ��L�ĵ�i��Ԫ��ɾ��
  *@param  L����̬����
  *@param  i,Ҫɾ��Ԫ�ص�λ��
  *@retval ��������ɾ��״̬������ɹ�����1��ʧ�ܷ���0
  */
Status List3Delete(StaticLinkList L, int i)
{
	int j, k;
	if (i<1 || i>L[0].cur + 1)//i���ھ�̬�������ݷ�Χ��ʱ
		return ERROR;
	k = MAXSIZE - 1;//kΪ��һ�����ݵ��±�
	for (j = 1; j <= i - 1; j++)//ѭ����k��curָ���i��Ԫ��
		k = L[k].cur;
	j = L[k].cur;//����i��Ԫ�ص��±긳ֵ��j
	L[k].cur = L[j].cur;
	Free_SSL(L, j);
	return OK;
}

int main()
{
	//˳�����Ա����
	sqList* P;
	ElemType* e, * f;
	e = (ElemType*)malloc(sizeof(ElemType));
	f = (ElemType*)malloc(sizeof(ElemType));
	List1Init(&P);
	List1Insert(P, 1, 100);
	List1Insert(P, 2, 200);
	List1Delete(P, 1, e);
	Get1Elem(P, 1, f);
	printf("˳�����Ա���Խ����%d %d\n", *e, *f);

	//�������Ա����
	LinkList L1, L2;
	CreateList2Head(&L1, 10);
	CreateList2Tail(&L2, 10);
	List2Insert(L1, 3, 100);
	List2Delete(L1, 2, e);
	Get2Elem(L1, 2, f);
	printf("�������Ա���Խ����%d %d\n", *e, *f);
	ClearList2(L1);
	ClearList2(L2);

	//��̬�������
	StaticLinkList L;
	List3Init(L);
	List3Insert(L, 1, 200);
	List3Insert(L, 2, 100);
	List3Delete(L, 1);
	printf("��̬������Խ����%d\n", L[L[MAXSIZE - 1].cur].data);
	return 0;
}