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
