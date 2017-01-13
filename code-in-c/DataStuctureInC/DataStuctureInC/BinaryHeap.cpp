/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�BinaryHeap.cpp
* �ļ���ʶ�����ȶ��У�����ѣ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��13��
* ˵    �������ȶ��У�����ѣ�- ����ʵ��
*/

#include "stdafx.h"
#include <stdlib.h>
#include "BinaryHeap.h"

#define MinElementSize   (3)
#define MinElement     (-9999)
/*implementate binary heap by an array*/
struct BinaryHeap
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

/*Init Priority Queue,implrmented by binary heap*/
PriorityQueue InitPriQueue(int maxElements)
{
	PriorityQueue PriQ;

	if (maxElements< MinElementSize)
	{
		perror("InitPriQueue error: maxElements size too small!\n");
		return NULL;
	}

	PriQ = (PriorityQueue)malloc(sizeof(struct BinaryHeap));
	if (PriQ == NULL)
	{
		perror("InitPriQueue error: malloc() out of space!\n");
		return NULL;
	}

	PriQ->Capacity = maxElements;
	PriQ->Size = 0;
	PriQ->Elements = (ElementType*)malloc((PriQ->Capacity + 1)*sizeof(ElementType));
	if (PriQ->Elements == NULL)
	{
		perror("InitPriQueue error: malloc() out of space!\n");
		return NULL;
	}
	PriQ->Elements[0] = MinElement; /*sentia*/

	return PriQ;

}

/*Destory Priority Queue , free memory*/
void DestoryPriQueue(PriorityQueue PriQ)
{
	if (PriQ != NULL)
	{
		free(PriQ->Elements);
		free(PriQ);
	}
}

/*Make Priority Empty*/
void MakeEmptyPriQueue(PriorityQueue PriQ)
{
	if (PriQ != NULL)
	{
		PriQ->Size = 0;
	}
	else
	{
		perror("MakeEmptyPriQueue error: empty PriQueue!\n");
	}
	
}

/*Insert Element X onto priority queue PriQ,using percolate up strategry*/
void InsertPriQueue(ElementType X, PriorityQueue PriQ)
{
	int tmpPos;

	if (IsFullPriQueue(PriQ))
	{
		perror("InsertPriQueue error: Insert in full PriQueue!\n");
		return;
	}
	else if (IsEmptyPriQueue(PriQ))
	{
		PriQ->Elements[1] = X;
		PriQ->Size++;
	}
	else
	{
		for ( tmpPos = ++PriQ->Size; X < PriQ->Elements[tmpPos/2]; tmpPos /= 2)
		{
			PriQ->Elements[tmpPos] = PriQ->Elements[tmpPos / 2];
		}

		PriQ->Elements[tmpPos] = X;
	}

	
}

/*Delete and return minim Element X in priority queue PriQ,using percolate down strategry*/
ElementType DeletMinPriQueue(PriorityQueue PriQ)
{
	ElementType min,last;
	int tmpPos,child;

	if (IsEmptyPriQueue(PriQ))
	{
		perror("DeletMinPriQueue error: empty PriQueue!\n");
		return MinElement;
	}

	min = PriQ->Elements[1];
	last = PriQ->Elements[PriQ->Size];
	PriQ->Size--;

	for (tmpPos = 1; 2*tmpPos <= PriQ->Size; tmpPos = child)
	{
		/*find smaller child*/
		child = 2 * tmpPos;
		if ((child != PriQ->Size) && (PriQ->Elements[child + 1] < PriQ->Elements[child]))
			child++;

		/*percolate one level*/
		if (last > PriQ->Elements[child])
		{
			PriQ->Elements[tmpPos] = PriQ->Elements[child];
		}
		else
		{
			break;
		}
	}

	PriQ->Elements[tmpPos] = last;
	
	return min;
}

/*Find minim Element X in priority queue PriQ*/
ElementType FindMinPriQueue(PriorityQueue PriQ)
{
	if (!IsEmptyPriQueue(PriQ))
	{
		return PriQ->Elements[1];
	}
	else
	{
		perror("FindMinPriQueue error: empty PriQueue!\n");
		return MinElement;
	}
}

/*Return true/1 if Priority Queue is empty*/
int IsEmptyPriQueue(PriorityQueue PriQ)
{
	return PriQ->Size == 0;
}

/*Return true/1 if Priority Queue is full*/
int IsFullPriQueue(PriorityQueue PriQ)
{
	return PriQ->Size == PriQ->Capacity;
}
