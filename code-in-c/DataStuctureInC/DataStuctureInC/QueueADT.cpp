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
	return 0;
}

int IsQueueFull(Queue Q)
{
	return 0;
}

Queue CreateQueue(int MaxElements)
{
	return Queue();
}

void DisposeQueue(Queue Q)
{
}

void MakeQueueEmpty(Queue Q)
{
}

void EnQueue(ElementType X, Queue Q)
{
}

ElementType FrontQueue(Queue Q)
{
	return ElementType();
}

void Dequeue(Queue Q)
{
}

ElementType FrontAndDequeue(Queue Q)
{
	return ElementType();
}
