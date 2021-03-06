/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：AVLTree.h
* 文件标识：带平衡条件的二叉查找树-头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月8日
* 说    明：带平衡条件的二叉查找树
*/
#pragma once

#include "Tree.h"
#ifndef _AVLTREE_H_
#define _AVLTREE_H_
typedef PtrToAvlNode AvlPos;

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlTree MakeAvlTreeEmpty(AvlTree T)
// 
//    功能：
//            AVL二叉查找树置空，一般用于AVL二叉查找树的初始化
// 
//    参数：
//			  T：待处理AVL二叉查找树T
// 
//    描述：
//			  释放内存，置空指针
//
//    返回：
//			  NULL指针
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlTree MakeAvlTreeEmpty(AvlTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlPos FindAvlTree(ElementType X, AvlTree T)
// 
//    功能：
//            在AVL二叉查找树T中查找元素X
// 
//    参数：
//			  X: 待查找元素X 
//			  T：待处理AVL二叉查找树T
//    描述：
//			  若未找到则返回NULL
//
//    返回：
//			  元素X所在节点的指针
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlPos FindAvlTree(ElementType X, AvlTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlPos FindMinAvlTree(AvlTree T)
// 
//    功能：
//            查找AVL二叉查找树T中最小元素
// 
//    参数：
//			  T：待处理AVL二叉查找树T
//
//    描述：
//			  递归实现
//
//    返回：
//			  最小元素所在节点的指针，若未找到则返回NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlPos FindMinAvlTree(AvlTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlPos FindMaxAvlTree(AvlTree T)
// 
//    功能：
//            查找AVL二叉查找树T中最大元素
// 
//    参数：
//			  T：待处理AVL二叉查找树T
//
//    描述：
//			  非递归实现
//
//    返回：
//			  最大元素所在节点的指针，若未找到则返回NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlPos FindMaxAvlTree(AvlTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlTree InsertAvlTree(ElementType X, AvlTree T)
// 
//    功能：
//            AVL二叉查找树T中插入新元素X
// 
//    参数：
//			  X: 待插入元素X 
//			  T：待处理二叉查找树T
//    描述：
//			  若X已经存在于T中，则什么也不做
//
//    返回：
//			  插入元素X后的新AVL二叉查找树
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlTree InsertAvlTree(ElementType X, AvlTree T);
static  AvlPos SingleRotateWithLeft(AvlPos P);
static  AvlPos DoubleRotateWithLeft(AvlPos P);
static  AvlPos SingleRotateWithRight(AvlPos P);
static  AvlPos DoubleRotateWithRight(AvlPos P);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	AvlTree DeleteAvlTree(ElementType X, AvlTree T)
// 
//    功能：
//            AVL二叉查找树T中删除元素X
// 
//    参数：
//			  X: 待删除元素X 
//			  T：待处理二叉查找树T
//    描述：
//			  无
//
//    返回：
//			  删除元素X后的新AVL二叉查找树
//			  
////////////////////////////////////////////////////////////////////////////
extern	AvlTree DeleteAvlTree(ElementType X, AvlTree T);
static  AvlTree DeleteRotateFix(AvlTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern	ElementType RetrieveAvlTree(AvlPos P)
// 
//    功能：
//            获取AVL二叉查找树中节点P的元素值
// 
//    参数：
//			  P: AVL二叉查找树中节点P 
//			  
//    描述：
//			  调用时应保证P合法
//
//    返回：
//			  节点P的元素值
//			  
////////////////////////////////////////////////////////////////////////////
extern	ElementType RetrieveAvlTree(AvlPos P);

/////////////////////////////////////////////////////////////////////////////
// 
//    static int HeightAvlTree(AvlPos P)
// 
//    功能：
//            获取AVL二叉查找树中节点P的高度
// 
//    参数：
//			  P: AVL二叉查找树中节点P 
//			  
//    描述：
//			  调用时应保证P合法
//
//    返回：
//			  节点P的高度
//			  
////////////////////////////////////////////////////////////////////////////
static int HeightAvlTree(AvlPos P);

#endif // !_AVLTREE_H_
