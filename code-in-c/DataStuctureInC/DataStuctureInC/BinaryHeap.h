/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：BinaryHeap.h
* 文件标识：优先队列（二叉堆）
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月13日
* 说    明：优先队列（二叉堆）- 数组实现
*/
#pragma once

#ifndef _BINARYHEAP_H_
#define _BINARYHEAP_H_

typedef int ElementType;
typedef struct BinaryHeap *PriorityQueue;

extern PriorityQueue InitPriQueue(int maxElements);

extern void DestoryPriQueue(PriorityQueue PriQ);

extern void MakeEmptyPriQueue(PriorityQueue PriQ);

extern void InsertPriQueue(ElementType X,PriorityQueue PriQ);

extern ElementType DeletMinPriQueue(PriorityQueue PriQ);

extern ElementType FindMinPriQueue(PriorityQueue PriQ);

extern int IsEmptyPriQueue(PriorityQueue PriQ);

extern int IsFullPriQueue(PriorityQueue PriQ);

#endif // !_BINARYHEAP_H_

