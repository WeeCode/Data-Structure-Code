/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�BinaryHeap.h
* �ļ���ʶ�����ȶ��У�����ѣ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��13��
* ˵    �������ȶ��У�����ѣ�- ����ʵ��
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

