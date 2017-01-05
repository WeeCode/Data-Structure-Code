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
/*
-----------------------------------------------------------------
	array index:	[0]  [1]  [2]  ...  [n] ...  [maxsize]		|
						  |				 |						|
		DeQueue	<---	front			rear    <---Enqueue		|
-----------------------------------------------------------------
*/
struct QueueRecord
{
	int Capacity;	/*max size*/
	int Front;
	int Rear;
	int Size;		/*actual size*/
	ElementType *Array;
};
/*Return ture/1 if Queue Q is empty*/
int IsQueueEmpty(Queue Q)
{
	return Q->Size == 0;
}
/*Return ture/1 if Queue Q is full*/
int IsQueueFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}
/*Create an empty queue,return NULL if encounter an error*/
Queue CreateQueue(int MaxElements)
{
	Queue Q;

	Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (Q == NULL)
	{
		perror("CreateQueue error: malloc() out of space!\n");
		return NULL;
	}

	if (MaxElements<MinQueueSize)
	{
		perror("CreateQueue error: queue size under min size! \n");
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
/*Delete queue Q completely,free memory*/
void DisposeQueue(Queue Q)
{
	free(Q->Array);
	free(Q);
}
/*make queue Q empty,assume queue Q legal*/
void MakeQueueEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
/*Enqueue element X after rear of Queue Q*/
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
/*circular array: whenever Fornt or Rear gets end of array,wrap around to beginning*/
int QueueSucc(int value, Queue Q)
{
	if (++value == Q->Capacity)
	{
		value = 0;
	}
	return value;
}
/*Get front element on Queue Q,do not dequeue it*/
ElementType FrontQueue(Queue Q)
{
	if (!IsQueueEmpty(Q))
	{
		return Q->Array[Q->Front];
	}
	else
	{
		perror("FrontQueue error: Empty queue!\n");
		return 0;
	}
	
}
/*DeQueue fornt element*/
void DeQueue(Queue Q)
{
	if (!IsQueueEmpty(Q))
	{
		Q->Size--;
		Q->Front = QueueSucc(Q->Front, Q);
	}
	else
	{
		perror("DeQueue error: Empty queue!\n");
	}
}
/*Get front element,then dequeue*/
ElementType FrontAndDeQueue(Queue Q)
{
	ElementType tmp;

	if (!IsQueueEmpty(Q))
	{
		tmp =  Q->Array[Q->Front];
		Q->Size--;
		Q->Front = QueueSucc(Q->Front, Q);
		return tmp;
	}
	else
	{
		perror("FrontQueue error: Empty queue!\n");
		return 0;
	}
}
