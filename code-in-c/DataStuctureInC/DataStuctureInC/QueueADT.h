/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：QueueADT.h
* 文件标识：队列-头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月4日
* 说    明：由数组实现队列
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

