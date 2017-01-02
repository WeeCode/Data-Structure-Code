/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�ListADT.cpp
* �ļ���ʶ��ջ-Դ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��2��
* ˵    �����ɴ���ͷ������ʵ��ջ
*/

#include <stdlib.h>
#include "stdafx.h"
#include "StackADT.h"

/*stack of linked list implementation*/
struct Node
{
	ElementType Element;
	PtrToNode Next;
};

/*Return ture/1 if stack S is empty*/
int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

/*Create an empty stack*/
Stack CreateStack(void)
{
	Stack S;

	S = (Stack)malloc(sizeof(struct Node));
	if (S == NULL)
	{
		perror("malloc error: out of space!");
	}
	S->Element = 0;
	S->Next = NULL;
	
	return S;
}

void DisposeStack(Stack S)
{
}

/*Make stack S empty,free memory of it's node */
void MakeEmpty(Stack S)
{
	PtrToNode node,tmp;

	node = S->Next;
	S->Next = NULL;

	while (node != NULL)
	{
		tmp = node->Next;
		free(node);
		node = tmp;
	}
}

/*Push element X onto stack S*/
void Push(ElementType X, Stack S)
{
	PtrToNode node;

	node = (Stack)malloc(sizeof(struct Node));
	if (node == NULL)
	{
		perror("malloc error: out of space!");
	}
	else
	{
		node->Element = X;
		node->Next = S->Next;
		S->Next = node;
	}
}

/*Get top element on stack S, release error and return 0 if an empty stack*/
ElementType Top(Stack S)
{
	if(!IsEmpty(S))
	{
		return S->Next->Element;
	}

	perror("Top error: top an empty stack!");
	return 0;
}

/* Pop/delete the first element on stack S */
void Pop(Stack S)
{
	PtrToNode node;

	if (!IsEmpty(S))
	{
		node = S->Next;
		S->Next = node->Next;
		free(node);
	}
	else
	{
		perror("Pop error: Pop an empty stack!");
	}
}
