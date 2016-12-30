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

/*return an empty List L with a header*/
List InitList(ElementType headerElement)
{
	List L;

	L = (List)malloc(sizeof(struct Node));
	if (L == NULL)
		perror("malloc error: out of space!");
	L->Next = NULL;
	L->Element = headerElement;

	return L;
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

/*Print element of L from head to bottom*/
void PrintList(List L)
{
	Position P;

	P = L->Next;
	printf("print list:\n");
	while (P!=NULL)
	{
		printf("%d\n",P->Element);
		P = P->Next;
	}
	printf("list end\n");
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

/*RadixSort with linked list operation,Input an array*/
void RadixSort(ElementType *Data, int Num)
{
	List list[10],list_mirror[10]; //基数为0-9的链表
	Position header[10],header_mirror[10];
	Position node;
	ElementType tmp;
	bool isEmpty = false;
	bool isMirror = true;
	int i,divisor = 1;

	/*linked list array init*/
	for ( i = 0; i < 10; i++)
	{
		list[i] = InitList(i);
		list_mirror[i] = InitList(i);
	}
	/*pull array data  to corresponding linked list*/
	for ( i = 0; i < Num; i++)
	{
		tmp = (*(Data + i))%10;
		InsertInEnd(*(Data + i), list[tmp]);
	}
	/*loop until sorted*/
	while (!isEmpty)
	{
		divisor *= 10;
		isEmpty = true;
		isMirror = !isMirror;
		if (isMirror)
		{
			SortMove(list_mirror, list,divisor);
			for (i = 1; i < 10; i++)
			{
				isEmpty = isEmpty && IsEmpty(list[i]);
			}
		}
		else
		{
			SortMove(list, list_mirror, divisor);
			for (i = 1; i < 10; i++)
			{
				isEmpty = isEmpty && IsEmpty(list_mirror[i]);
			}
		}
	}
	/*output the sorted array from linked list*/
	if (isMirror)
	{
		node = list[0]->Next;
		for ( i = 0; i < Num; i++)
		{
			if (node!=NULL)
			{
				*(Data + i) = Retrieve(node);
				node = node->Next;
			}
		}
	}
	else
	{
		node = list_mirror[0]->Next;
		for (i = 0; i < Num; i++)
		{
			if (node != NULL)
			{
				*(Data + i) = Retrieve(node);
				node = node->Next;
			}
		}
	}
	/*free the memory*/
	for ( i = 0; i < 10; i++)
	{
		DeleteList(list[i]);
		DeleteList(list_mirror[i]);
	}

}
/*design for RadixSort funtion*/
void SortMove(List orig[], List obj[], int divisor)
{
	int i,tmp;
	Position P, header[10];

	for ( i = 0; i < 10; i++)
	{
		P = orig[i]->Next;
		while (P!=NULL)
		{
			tmp = (Retrieve(P) / divisor) % 10;
			InsertInEnd(Retrieve(P), obj[tmp]);
			P = P->Next;
		}
		MakeEmpty(orig[i]);
	}
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

/*Insert element by it's size,make linked list increment*/
void InsertBySize(ElementType X, List L)
{
	Position P;

	P = L;
	while (P->Next!=NULL && P->Next->Element < X )
	{
		P = P->Next;
	}
	Insert(X,L,P);
}

void InsertInEnd(ElementType X, List L)
{
	Position P;

	P = L;
	while (P->Next!=NULL)
	{
		P = P->Next;
	}
	Insert(X, L, P);
}

/*Delete L completely,include it's header,free space*/
void DeleteList(List L)
{
	Position P, Tmp;

	P = L;
	L = NULL;

	if (P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}

/*return the header of L*/
Position Header(List L)
{
	return L;
}

/*return the first node of L*/
Position First(List L)
{
	return L->Next;
}

/*Return the node after P*/
Position Advance(Position P)
{
	return P->Next;
}

/*Return the Element of P*/
ElementType Retrieve(Position P)
{
	return P->Element;
}
