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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern int IsQueueEmpty(Queue Q)
// 
//    功能：
//            判断队列(数组实现)是否为空
// 
//    参数：
//			  Q：待处理队列Q
// 
//    描述：
//			  无
//
//    返回：
//			  true/1: 空队列
//            false/0:非空队列
////////////////////////////////////////////////////////////////////////////
extern int IsQueueEmpty(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern int IsQueueFull(Queue Q)
// 
//    功能：
//            判断队列(数组实现)是否已满
// 
//    参数：
//			  Q：待处理队列Q
// 
//    描述：
//			  无
//
//    返回：
//			  true/1: 满队列
//            false/0:未满队列
////////////////////////////////////////////////////////////////////////////
extern int IsQueueFull(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern Queue CreateQueue(int MaxElements)
// 
//    功能：
//            创建新的空队列(数组实现)
// 
//    参数：
//			  MaxElements：队列最大容量
// 
//    描述：
//			  若创建失败，报错并返回NULL
//
//    返回：
//			  空队列
//			  
////////////////////////////////////////////////////////////////////////////
extern Queue CreateQueue(int MaxElements);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DisposeQueue(Queue Q)
// 
//    功能：
//            删除队列(数组实现)
// 
//    参数：
//			   Q：待处理队列Q
// 
//    描述：
//			  删除队列，释放队列占用内存
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void DisposeQueue(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeQueueEmpty(Queue Q)
// 
//    功能：
//            队列(数组实现)置空
// 
//    参数：
//			   Q：待处理队列Q
// 
//    描述：
//			  假定输入队列Q合法
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeQueueEmpty(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void EnQueue(ElementType X,Queue Q)
// 
//    功能：
//            元素入队
// 
//    参数：
//			   X: 待入队元素
//			   Q：待处理队列Q
//    描述：
//			  队列Q尾部增加元素X,队列已满时报错
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void EnQueue(ElementType X,Queue Q);
static int QueueSucc(int value,Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType FrontQueue(Queue Q)
// 
//    功能：
//            读队列首元素
// 
//    参数：
//			   Q：待处理队列Q
//
//    描述：
//			  返回队列首元素值,队列为空时报错
//
//    返回：
//			  队列首元素值
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType FrontQueue(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType FrontQueue(Queue Q)
// 
//    功能：
//            首元素离队
// 
//    参数：
//			   Q：待处理队列Q
//
//    描述：
//			  将队列Q的首元素移出队列,队列为空时报错
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void Dequeue(Queue Q);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType FrontQueue(Queue Q)
// 
//    功能：
//            读队列首元素并离队
// 
//    参数：
//			   Q：待处理队列Q
//
//    描述：
//			  返回队列首元素值,并将队列Q的首元素移出队列，队列为空时报错
//
//    返回：
//			  队列首元素值
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType FrontAndDequeue(Queue Q);


#endif // !_QUEUEADT_H_

