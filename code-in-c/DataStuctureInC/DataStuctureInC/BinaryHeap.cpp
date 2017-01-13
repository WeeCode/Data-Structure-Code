/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：BinaryHeap.cpp
* 文件标识：优先队列（二叉堆）
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月13日
* 说    明：优先队列（二叉堆）- 数组实现
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
