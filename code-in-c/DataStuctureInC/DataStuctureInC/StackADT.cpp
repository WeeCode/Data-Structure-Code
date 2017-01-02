/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：ListADT.cpp
* 文件标识：栈-源文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月2日
* 说    明：由带表头的链表实现栈
*/


#include "stdafx.h"
#include <stdlib.h>
#include "StackADT.h"

/*stack of linked list implementation*/
struct Node
{
	ElementType Element;
	PtrToNode Next;
};

/*Return ture/1 if stack S is empty*/
int IsStackEmpty(Stack S)
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

/*Delete stack S completely,include it's header,free memory*/
void DisposeStack(Stack S)
{
	PtrToNode node, tmp;

	node = S;
	S = NULL;

	while (node != NULL)
	{
		tmp = node->Next;
		free(node);
		node = tmp;
	}
}

/*Make stack S empty,free memory of it's node */
void MakeStackEmpty(Stack S)
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
void PushStack(ElementType X, Stack S)
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
ElementType TopStack(Stack S)
{
	if(!IsStackEmpty(S))
	{
		return S->Next->Element;
	}

	perror("Top error: top an empty stack!");
	return 0;
}

/* Pop/delete the first element on stack S */
void PopStack(Stack S)
{
	PtrToNode node;

	if (!IsStackEmpty(S))
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
