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