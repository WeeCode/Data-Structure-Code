/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：QueueADT.cpp
* 文件标识：队列-头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月4日
* 说    明：由数组实现队列
*/

#include "stdafx.h"
#include <stdlib.h>
#include "QueueADT.h"

#define MinQueueSize (5)

/*Array implementation of queue*/
struct QueueRecord
{
	int Capacity;	/*max size*/
	int Front;
	int Rear;
	int Size;		/*actual size*/
	ElementType *Array;
};

int IsQueueEmpty(Queue Q)
{
	return Q->Size == 0;
}

int IsQueueFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements)
{
	Queue Q;

	Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (Q == NULL)
	{
		perror("CreateQueue error: malloc() out of space!\n");
		return NULL;
	}

	Q->Capacity = MaxElements;
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
	Q->Array = (ElementType*)malloc(MaxElements*sizeof(ElementType));
	if (Q->Array == NULL)
	{
		perror("CreateQueue error: malloc() out of space!\n");
		return NULL;
	}

	return Q;
}

void DisposeQueue(Queue Q)
{
	free(Q->Array);
	free(Q);
}

void MakeQueueEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

void EnQueue(ElementType X, Queue Q)
{
	if (IsQueueFull(Q))
	{
		perror("EnQueue error: full queue!\n");
	}
	else
	{
		Q->Size++;
		Q->Rear = QueueSucc(Q->Rear,Q);
		Q->Array[Q->Rear] = X;
	}
}

int QueueSucc(int value, Queue Q)
{
	if (++value == Q->Capacity)
	{
		value = 0;
	}
	return value;
}

ElementType FrontQueue(Queue Q)
{
	return Q->Array[Q->Front];
}

void Dequeue(Queue Q)
{

}

ElementType FrontAndDequeue(Queue Q)
{
	return ElementType();
}
