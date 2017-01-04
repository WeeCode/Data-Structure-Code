/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�QueueADT.h
* �ļ���ʶ������-ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��4��
* ˵    ����������ʵ�ֶ���
*/
#pragma once

#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

typedef int ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;

extern int IsQueueEmpty(Queue Q);
extern int IsQueueFull(Queue Q);
extern Queue CreateQueue(int MaxElements);
extern void DisposeQueue(Queue Q);
extern void MakeQueueEmpty(Queue Q);
extern void EnQueue(ElementType X,Queue Q);
extern ElementType FrontQueue(Queue Q);
extern void Dequeue(Queue Q);
extern ElementType FrontAndDequeue(Queue Q);


#endif // !_QUEUEADT_H_

