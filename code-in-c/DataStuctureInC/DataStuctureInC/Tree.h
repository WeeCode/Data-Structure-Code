/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：Tree.h
* 文件标识：各类树结构体通用部分声明头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月5日
* 说    明：对各类树结构体的通用部分集中声明
*/
#pragma once

#ifndef _TREE_H_
#define _TREE_H_
typedef int ElementType;

/*normal tree node, Applicable to all tree*/
typedef struct NormalTreeNode *PtrToNorNode;
typedef PtrToNorNode NormalTree;
struct NormalTreeNode
{
	ElementType Element;
	NormalTree FisrtChild;
	NormalTree NextSibling;
};

/*binary tree node, Applicable to binary tree*/
typedef struct BinaryTreeNode *PtrToBinNode;
typedef PtrToBinNode BinaryTree;
struct BinaryTreeNode
{
	ElementType Element;
	BinaryTree Left;
	BinaryTree Right;
};

#endif

