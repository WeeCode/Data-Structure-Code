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

/*implementate binary heap by an array*/
struct BinaryHeap
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

PriorityQueue InitPriQueue(int maxElements)
{
	return PriorityQueue();
}

void DestoryPriQueue(PriorityQueue PriQ)
{
}

void MakeEmptyPriQueue(PriorityQueue PriQ)
{
}

void InsertPriQueue(ElementType X, PriorityQueue PriQ)
{
}

ElementType DeletMinPriQueue(PriorityQueue PriQ)
{
	return ElementType();
}

ElementType FindMinPriQueue(PriorityQueue PriQ)
{
	return ElementType();
}

int IsEmptyPriQueue(PriorityQueue PriQ)
{
	return 0;
}

int IsFullPriQueue(PriorityQueue PriQ)
{
	return 0;
}
