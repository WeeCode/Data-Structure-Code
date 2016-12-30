/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：ListADT.h
* 文件标识：线性表头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2016年12月29日
* 说    明：
*/
#pragma once

//The Linked List with a header/dummy node
#ifndef _ListADT_H
typedef  int ElementType;
struct Node;
typedef	struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

/*operations on the list ADT */

/////////////////////////////////////////////////////////////////////////////
// 
//    extern List MakeEmpty(List L)
// 
//    功能：
//            链表(含表头)置空
// 
//    参数：
//			  待处理链表L
// 
//    描述：
//			  释放链表占用空间，保留表头
//
//    返回：
//			  带表头的空链表
////////////////////////////////////////////////////////////////////////////
extern List MakeEmpty(List L);
extern void PrintList(List L);
extern int IsEmpty(List L);
extern int IsLast(Position P,List L);
extern Position Find(ElementType X,List L);
extern void Delete(ElementType X,List L);
extern void Insert(ElementType X,List L,Position P);
extern void DeleteList(List L);
extern Position Header(List L);
extern Position First(List L);
extern Position Advance(Position P);
extern ElementType Retrieve(Position P);

static Position FindPrevious(ElementType X, List L);

#endif




