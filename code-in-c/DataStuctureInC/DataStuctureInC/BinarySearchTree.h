/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：BinarySearchTree.h
* 文件标识：二叉查找树-头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月6日
* 说    明：二叉查找树
*/
#pragma once

/*
	The property that makes a binary tree into a binary search tree is that 
	for every node, X, in the tree, the values of all the keys in it's left subtree are smaller than the key value in X,
	and the values of all the keys in it's right subtree are larger than the key value in X.

	           X
			 /   \
		  left   right
		   |       |
		  < X     > X
*/

/*BSTree stand for BinarySearchTree,BStreePos stand for BinarySearchTreePostion*/
#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_

typedef PtrToBinNode BStreePos;
typedef BinaryTree BinarySearchTree;

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T)
// 
//    功能：
//            二叉查找树置空，一般用于二叉查找树的初始化
// 
//    参数：
//			  T：待处理二叉查找树T
// 
//    描述：
//			  释放内存，置空指针
//
//    返回：
//			  NULL指针
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindBSTree(ElementType X, BinarySearchTree T)
// 
//    功能：
//            在二叉查找树T中查找元素X
// 
//    参数：
//			  X: 待查找元素X 
//			  T：待处理二叉查找树T
//    描述：
//			  若未找到则返回NULL
//
//    返回：
//			  元素X所在节点的指针
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindMinBSTree(BinarySearchTree T)
// 
//    功能：
//            查找二叉查找树T中最小元素
// 
//    参数：
//			  T：待处理二叉查找树T
//
//    描述：
//			  递归实现
//
//    返回：
//			  最小元素所在节点的指针，若未找到则返回NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindMinBSTree(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindMaxBSTree(BinarySearchTree T)
// 
//    功能：
//            查找二叉查找树T中最大元素
// 
//    参数：
//			  T：待处理二叉查找树T
//
//    描述：
//			  非递归实现
//
//    返回：
//			  最大元素所在节点的指针，若未找到则返回NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindMaxBSTree(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T)
// 
//    功能：
//            二叉查找树T中插入新元素X
// 
//    参数：
//			  X: 待插入元素X 
//			  T：待处理二叉查找树T
//    描述：
//			  若X已经存在于T中，则什么也不做
//
//    返回：
//			  插入元素X后的新二叉查找树
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T)
// 
//    功能：
//            二叉查找树T中删除元素X
// 
//    参数：
//			  X: 待删除元素X 
//			  T：待处理二叉查找树T
//    描述：
//			  无
//
//    返回：
//			  删除元素X后的新二叉查找树
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//   extern ElementType RetrieveBSTree(BStreePos P)
// 
//    功能：
//            获取二叉查找树中节点P的元素值
// 
//    参数：
//			  P: 二叉查找树中节点P 
//			  
//    描述：
//			  调用时应保证P合法
//
//    返回：
//			  节点P的元素值
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveBSTree(BStreePos P);

#endif // !_BINARYSEARCHTREE_H_