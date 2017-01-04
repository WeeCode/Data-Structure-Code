/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�QueueADT.cpp
* �ļ���ʶ������-ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��4��
* ˵    ����������ʵ�ֶ���
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
