/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：LeftistHeap.h
* 文件标识：左式堆（优先队列）
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月15日
* 说    明：左式堆（优先队列）--二叉树实现
*/
#pragma once
#include "Tree.h"

#ifndef _LEFTISTHEAP_H_
#define _LEFTISTHEAP_H_

extern LeftHeap InitLeftHeap(void);

extern ElementType FindMinLeftHeap(LeftHeap LH);

extern int IsEmptyLeftHeap(LeftHeap LH);

extern LeftHeap MergeLeftHeap(LeftHeap LH1, LeftHeap LH2);

#define InsertLeftHeap(X,LH) ( LH = Insert1LeftHeap((X) ,LH) )
extern LeftHeap Insert1LeftHeap(ElementType X,LeftHeap LH);

extern LeftHeap DeleteMinLeftHeap(LeftHeap LH);


#endif // !_LEFTISTHEAP_H_

