/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：AVLTree.cpp
* 文件标识：带平衡条件的二叉查找树-源文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月8日
* 说    明：带平衡条件的二叉查找树
*/

#include "stdafx.h"
#include <stdlib.h>
#include "AVLTree.h"

/*Make AVL binary search tree Empty,mainly used for initialization*/
AvlTree MakeAvlTreeEmpty(AvlTree T)
{
	return AvlTree();
}

/*Find element in AVL binary search tree,return NULL if not found*/
AvlPos FindAvlTree(ElementType X, AvlTree T)
{
	return AvlPos();
}

/*return the position of the smallest element in the AVL binary search tree,return NULL if empty*/
/*Recursive implementation:*/
AvlPos FindMinAvlTree(AvlTree T)
{
	return AvlPos();
}

/*return the position of the largest element in the AVL binary search tree,return NULL if empty*/
/*Nonrecursive implementation:*/
AvlPos FindMaxAvlTree(AvlTree T)
{
	return AvlPos();
}

/*Insert element X to T, if X was existed, do nothing*/
AvlTree InsertAvlTree(ElementType X, AvlTree T)
{
	return AvlTree();
}

/*Delete element X in T,
	if node of X has two childern,replace it with smallest data of the right subtree,
		then delete the smallest data of the right subtree*/
AvlTree DeleteAvlTree(ElementType X, AvlTree T)
{
	return AvlTree();
}

/*Return the Element of P,if P is illegal,release an error and return 0*/
ElementType RetrieveAvlTree(AvlPos P)
{
	return ElementType();
}
