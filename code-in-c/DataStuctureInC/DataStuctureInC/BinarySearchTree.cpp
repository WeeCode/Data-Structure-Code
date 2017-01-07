/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�BinarySearchTree.cpp
* �ļ���ʶ�����������-Դ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��6��
* ˵    �������������
*/

#include "stdafx.h"
#include <stdlib.h>
#include "Tree.h"
#include "BinarySearchTree.h"

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

/*Make binary search tree Empty,mainly used for initialization*/
BinarySearchTree MakeBSTreeEmpty(BinarySearchTree T)
{
	if (T!=NULL)
	{
		MakeBSTreeEmpty(T->Left);
		MakeBSTreeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

/*Find element in binary search tree,return NULL if not found*/
BStreePos FindBSTree(ElementType X, BinarySearchTree T)
{
	if (T == NULL)
		return NULL;
	
	if (X < T->Element)
		return FindBSTree(X, T->Left);
	else if (X > T->Element)
		return FindBSTree(X, T->Right);
	else
		return T;
}

/*return the position of the smallest element in the binary search tree,return NULL if empty*/
/*Recursive implementation:*/
BStreePos FindMinBSTree(BinarySearchTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMinBSTree(T->Left);
}

/*return the position of the largest element in the binary search tree,return NULL if empty*/
/*Nonrecursive implementation:*/
BStreePos FindMaxBSTree(BinarySearchTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
			T = T->Right;
	}
	
	return T;
}

/*Insert element X to T, if X was existed, do nothing*/
BinarySearchTree InsertBSTree(ElementType X, BinarySearchTree T)
{
	if ( T == NULL)
	{
		T = (BinarySearchTree)malloc(sizeof(struct BinaryTreeNode));
		if (T == NULL)
		{
			perror("InsertBSTree error: malloc() out of space!\n");
			return NULL;
		}
		else
		{
			T->Element = X;
			T->Left = NULL;
			T->Right = NULL;
		}
	}
	else if (X < T->Element)
	{
		T->Left = InsertBSTree(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = InsertBSTree(X, T->Right);
	}
	/*else if (X == T->Element),we will do nothing*/

	return T; /*this line is important!*/
}

/*Delete element X in T,
	if node of X has two childern,replace it with smallest data of the right subtree,
		then delete the smallest data of the right subtree*/
BinarySearchTree DeleteBSTree(ElementType X, BinarySearchTree T)
{
	BStreePos P;

	if (T == NULL)
	{
		perror("DeleteBSTree warning: element not found !\n");
	}
	else if (X < T->Element)
	{
		DeleteBSTree(X,T->Left); /*Go Left*/
	}
	else if (X > T->Element)
	{
		DeleteBSTree(X,T->Right); /*Go Right*/
	}
	else                          /*found element X*/
	{
		if (T->Left && T->Right)
		{/*double children*/
			P = FindMinBSTree(T->Right);
			T->Element = P->Element;
			DeleteBSTree(P->Element,T->Right);

		}
		else
		{/*one or zero children*/
			P = T;
			if (T->Left == NULL) /*zero or a Right children*/
				T = T->Right;
			else                /*a Left children*/
				T = T->Left;
			free(P);
		}
	}

	return T;
}

/*Return the Element of P,if P is illegal,release an error and return 0*/
ElementType RetrieveBSTree(BStreePos P)
{
	if (P != NULL)
		return P->Element;
	else
	{
		perror("RetrieveBSTree error: illegal BStreePos!\n");
		return 0;
	}
}