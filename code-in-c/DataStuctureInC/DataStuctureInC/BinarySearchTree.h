/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�BinarySearchTree.h
* �ļ���ʶ�����������-ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��6��
* ˵    �������������
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

BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T);
BStreePos FindBSTree(ElementType X, BinarySearchTree T);
BStreePos FindMinBSTree(BinarySearchTree T);
BStreePos FindMaxBSTree(BinarySearchTree T);
BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T);
BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T);
ElementType RetrieveBSTree(BStreePos P);

#endif // !_BINARYSEARCHTREE_H_