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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T)
// 
//    ���ܣ�
//            ����������ÿգ�һ�����ڶ���������ĳ�ʼ��
// 
//    ������
//			  T����������������T
// 
//    ������
//			  �ͷ��ڴ棬�ÿ�ָ��
//
//    ���أ�
//			  NULLָ��
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindBSTree(ElementType X, BinarySearchTree T)
// 
//    ���ܣ�
//            �ڶ��������T�в���Ԫ��X
// 
//    ������
//			  X: ������Ԫ��X 
//			  T����������������T
//    ������
//			  ��δ�ҵ��򷵻�NULL
//
//    ���أ�
//			  Ԫ��X���ڽڵ��ָ��
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindMinBSTree(BinarySearchTree T)
// 
//    ���ܣ�
//            ���Ҷ��������T����СԪ��
// 
//    ������
//			  T����������������T
//
//    ������
//			  �ݹ�ʵ��
//
//    ���أ�
//			  ��СԪ�����ڽڵ��ָ�룬��δ�ҵ��򷵻�NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindMinBSTree(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BStreePos FindMaxBSTree(BinarySearchTree T)
// 
//    ���ܣ�
//            ���Ҷ��������T�����Ԫ��
// 
//    ������
//			  T����������������T
//
//    ������
//			  �ǵݹ�ʵ��
//
//    ���أ�
//			  ���Ԫ�����ڽڵ��ָ�룬��δ�ҵ��򷵻�NULL
//			  
////////////////////////////////////////////////////////////////////////////
extern BStreePos FindMaxBSTree(BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T)
// 
//    ���ܣ�
//            ���������T�в�����Ԫ��X
// 
//    ������
//			  X: ������Ԫ��X 
//			  T����������������T
//    ������
//			  ��X�Ѿ�������T�У���ʲôҲ����
//
//    ���أ�
//			  ����Ԫ��X����¶��������
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T)
// 
//    ���ܣ�
//            ���������T��ɾ��Ԫ��X
// 
//    ������
//			  X: ��ɾ��Ԫ��X 
//			  T����������������T
//    ������
//			  ��
//
//    ���أ�
//			  ɾ��Ԫ��X����¶��������
//			  
////////////////////////////////////////////////////////////////////////////
extern BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T);

/////////////////////////////////////////////////////////////////////////////
// 
//   extern ElementType RetrieveBSTree(BStreePos P)
// 
//    ���ܣ�
//            ��ȡ����������нڵ�P��Ԫ��ֵ
// 
//    ������
//			  P: ����������нڵ�P 
//			  
//    ������
//			  ����ʱӦ��֤P�Ϸ�
//
//    ���أ�
//			  �ڵ�P��Ԫ��ֵ
//			  
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveBSTree(BStreePos P);

#endif // !_BINARYSEARCHTREE_H_