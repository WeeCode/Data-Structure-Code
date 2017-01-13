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
