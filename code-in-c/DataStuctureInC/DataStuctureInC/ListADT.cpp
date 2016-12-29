/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：ListADT.cpp
* 文件标识：线性表源文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2016年12月29日
* 说    明：
*/

#include "stdafx.h"
#include <stdlib.h>
//#include <errno.h>
#include "ListADT.h"

/*----------assume the linked list has a header-------------*/
struct Node
{
	ElementType Element;
	Position Next;
};

/*-----------function to operate the linked list ADT----------*/

/* Return ture/1 if L is empty */
int IsEmpty(List L)
{
	return L->Next == NULL;
}

/*Return an empty list L,with a header*/
List MakeEmpty(List L)
{
	Position P,Tmp;

	P = L->Next; 
	L->Next = NULL;

	if (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
	
	return L;
}

/* Return ture/1 if P is the last position of L  */
int IsLast(Position P, List L)
{
	return P->Next == NULL;
}

/*Return Position of X in L,NULL if not found*/
Position Find(ElementType X, List L)
{
	Position P;

	P = L->Next;
	//while (P != NULL)
	//{
	//	if (P->Element == X)
	//	{
	//		break;
	//	}
	//	P = P->Next;
	//}
	while (P != NULL && P->Element != X)
		P = P->Next;

	return P;
}

/*If X is not found, the next node of returned position is NULL */
Position FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;

	return P;
}

/*Delete first occurrence of X from L*/
void Delete(ElementType X, List L)
{
	Position P,Tmp;

	P = FindPrevious(X, L);
	Tmp = P->Next;
	if (Tmp != NULL )
	{
		P->Next = Tmp->Next;
		free(Tmp);
	}
	
}

/*Insert X after P,assume P is legal*/
void Insert(ElementType X, List L, Position P)
{
	Position Tmp;

	Tmp = (Position)malloc(sizeof( struct Node));
	if (Tmp == NULL)
		perror("malloc error: out of space!");
	Tmp->Element = X;
	Tmp->Next = P->Next;
	P->Next = Tmp;
}

void DeleteList(List L)
{
}

Position Header(List L)
{
	return Position();
}

Position First(List L)
{
	return Position();
}

Position Advance(Position P)
{
	return Position();
}

ElementType Retrieve(Position P)
{
	return ElementType();
}
