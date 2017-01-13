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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern PriorityQueue InitPriQueue(int maxElements)
// 
//    功能：
//            优先队列初始化（二叉堆实现）
// 
//    参数：
//			  maxElements：队列最大容量
// 
//    描述：
//			  初始化优先队列与内部数组
//
//    返回：
//			  初始化完成的优先队列
//			  
////////////////////////////////////////////////////////////////////////////
extern PriorityQueue InitPriQueue(int maxElements);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DestoryPriQueue(PriorityQueue PriQ)
// 
//    功能：
//            删除优先队列（二叉堆实现）
// 
//    参数：
//			  PriQ：待处理优先队列
// 
//    描述：
//			  删除优先队列，释放内存
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void DestoryPriQueue(PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeEmptyPriQueue(PriorityQueue PriQ)
// 
//    功能：
//            置空优先队列（二叉堆实现）
// 
//    参数：
//			  PriQ：待处理优先队列
// 
//    描述：
//			  无
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeEmptyPriQueue(PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InsertPriQueue(ElementType X,PriorityQueue PriQ)
// 
//    功能：
//            插入新元素X到优先队列（二叉堆实现）
// 
//    参数：
//			  X:	待插入元素X 
//			  PriQ：待处理优先队列
//    描述：
//			  上滤法实现
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void InsertPriQueue(ElementType X,PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType DeletMinPriQueue(PriorityQueue PriQ);
// 
//    功能：
//            返回并删除优先队列（二叉堆实现）最小元素
// 
//    参数：
//			  PriQ：待处理优先队列
//
//    描述：
//			  下滤法实现
//
//    返回：
//			  优先队列最小元素
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType DeletMinPriQueue(PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType FindMinPriQueue(PriorityQueue PriQ)
// 
//    功能：
//            查找并返回优先队列（二叉堆实现）最小元素
// 
//    参数：
//			  PriQ：待处理优先队列
//
//    描述：
//			  无
//
//    返回：
//			  优先队列最小元素
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType FindMinPriQueue(PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern int IsEmptyPriQueue(PriorityQueue PriQ)
// 
//    功能：
//            判断优先队列（二叉堆实现）是否为空
// 
//    参数：
//			  PriQ：待处理优先队列
//
//    描述：
//			  要求输入合法优先队列
//
//    返回：
//			  true/1: 优先队列为空
//			  false/0:优先队列不为空
////////////////////////////////////////////////////////////////////////////
extern int IsEmptyPriQueue(PriorityQueue PriQ);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern int IsEmptyPriQueue(PriorityQueue PriQ)
// 
//    功能：
//            判断优先队列（二叉堆实现）是否已满
// 
//    参数：
//			  PriQ：待处理优先队列
//
//    描述：
//			  要求输入合法优先队列
//
//    返回：
//			  true/1: 优先队列已满
//			  false/0:优先队列未满
////////////////////////////////////////////////////////////////////////////
extern int IsFullPriQueue(PriorityQueue PriQ);

#endif // !_BINARYHEAP_H_

