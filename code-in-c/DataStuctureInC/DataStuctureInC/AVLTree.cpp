/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�AVLTree.cpp
* �ļ���ʶ����ƽ�������Ķ��������-Դ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��8��
* ˵    ������ƽ�������Ķ��������
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
