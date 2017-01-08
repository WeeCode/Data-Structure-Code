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

extern	AvlTree MakeAvlTreeEmpty(AvlTree T);
extern	AvlPos FindAvlTree(ElementType X, AvlTree T);
extern	AvlPos FindMinAvlTree(AvlTree T);
extern	AvlPos FindMaxAvlTree(AvlTree T);
extern	AvlTree InsertAvlTree(ElementType X, AvlTree T);
extern	AvlTree DeleteAvlTree(ElementType X, AvlTree T);
extern	ElementType RetrieveAvlTree(AvlPos P);

#endif // !_AVLTREE_H_
