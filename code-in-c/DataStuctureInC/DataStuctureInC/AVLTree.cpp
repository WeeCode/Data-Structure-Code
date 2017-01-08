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

#define Max(a,b)  a>b?a:b

/*Make AVL binary search tree Empty,mainly used for initialization*/
AvlTree MakeAvlTreeEmpty(AvlTree T)
{
	if (T != NULL)
	{
		MakeAvlTreeEmpty(T->Left);
		MakeAvlTreeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

/*Find element in AVL binary search tree,return NULL if not found*/
AvlPos FindAvlTree(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		return NULL;
	}
	else if (X < T->Element)
	{
		return FindAvlTree(X,T->Left);
	}
	else if (X > T->Element)
	{
		return FindAvlTree(X, T->Right);
	}
	else
	{
		return T;
	}
}

/*return the position of the smallest element in the AVL binary search tree,return NULL if empty*/
/*Recursive implementation:*/
AvlPos FindMinAvlTree(AvlTree T)
{
	if (T == NULL)
	{
		return NULL;
	}

	if (T->Left != NULL)
	{
		return FindMinAvlTree(T->Left);
	}
	else
	{
		return T;
	}
}

/*return the position of the largest element in the AVL binary search tree,return NULL if empty*/
/*Nonrecursive implementation:*/
AvlPos FindMaxAvlTree(AvlTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
		{
			T = T->Right;
		}
	}

	return T;
}

/*Insert element X to T, if X was existed, do nothing*/
AvlTree InsertAvlTree(ElementType X, AvlTree T)
{
	if ( T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if (T == NULL)
		{
			perror("InsertAvlTree error: malloc() out of space!\n");
		}
		else
		{
			T->Element = X;
			T->Height = 0;
			T->Left = NULL;
			T->Right = NULL;
		}
	}
	else if (X < T->Element)
	{
		T->Left = InsertAvlTree(X,T->Left);
		if ((HeightAvlTree(T->Left) - HeightAvlTree(T->Right)) == 2)
		{
			if (X < T->Left->Element)
			{
				T = SingleRotateWithLeft(T); /*case 1: left-left*/
			}
			else
			{
				T = DoubleRotateWithLeft(T); /*case 2: left-right*/
			}
		}
	}
	else if (X > T->Element)
	{
		T->Right = InsertAvlTree(X,T->Right);
		if ((HeightAvlTree(T->Right) - HeightAvlTree(T->Left)) == 2)
		{
			if (X > T->Right->Element)
			{
				T = SingleRotateWithRight(T); /*case 3: right-right*/
			}
			else
			{
				T = DoubleRotateWithRight(T); /*case 4: right-left*/
			}
		}
	}
	/*else if (X == T->Element),we will do nothing*/

	T->Height = Max(HeightAvlTree(T->Left),HeightAvlTree(T->Right)) + 1;
	return T;
}

/*case 1: left-left ：SingleRotateWithLeft routine

				K2						K1
			   /  \					  /	   \
			  K1  _Z_     ==>		_X_	   K2
			/   \						 /    \
		  _X_   _Y_					   _Y_   _Z_
*/
AvlPos SingleRotateWithLeft(AvlPos P)
{
	AvlPos newRoot;

	newRoot = P->Left;
	P->Left = newRoot->Right;
	newRoot->Right = P;

	P->Height = Max(HeightAvlTree(P->Left), HeightAvlTree(P->Right)) + 1;
	newRoot->Height = Max(HeightAvlTree(newRoot->Left), P->Height) + 1;

	return newRoot;
}

/*  case 2: left-right:DoubleRotateWithLeft routine

				K3					K2
			  /    \			  /    \
			 K1			 ==>	 K1	   K3
		   /   \
			   K2
*/
AvlPos DoubleRotateWithLeft(AvlPos P)
{
	/*Rotate between K1 and K2*/
	P->Left = SingleRotateWithRight(P->Left);

	/*Rotate between K3 and K1*/
	return SingleRotateWithLeft(P);
}

/*case 3: right-right: SingleRotateWithRight*/
AvlPos SingleRotateWithRight(AvlPos P)
{
	AvlPos newRoot;

	newRoot = P->Right;
	P->Right = newRoot->Left;
	newRoot->Left = P;

	P->Height = Max(HeightAvlTree(P->Left), HeightAvlTree(P->Right)) + 1;
	newRoot->Height = Max(P->Height,HeightAvlTree(newRoot->Right)) + 1;

	return newRoot;
}

/*case 4: right-left; DoubleRotateWithRight*/
AvlPos DoubleRotateWithRight(AvlPos P)
{
	P->Right = SingleRotateWithLeft(P->Right);

	return SingleRotateWithRight(P);
}

/*Delete element X in T,
	if node of X has two childern,replace it with smallest data of the right subtree,
		then delete the smallest data of the right subtree*/
AvlTree DeleteAvlTree(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		perror("DeleteAvlTree error: delete in empty AVL tree!\n");
		return NULL;
	}
	else if (X < T->Element)
	{
		T->Left = DeleteAvlTree(X,T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = DeleteAvlTree(X,T->Right);
	}
	else
	{
		if (T->Left || T->Right)
		{
			if (HeightAvlTree(T->Right) > HeightAvlTree(T->Left))
			{
				T->Element = T->Right->Element;
				T->Right = DeleteAvlTree(T->Element, T->Right);
			}
			else
			{
				T->Element = T->Left->Element;
				T->Left = DeleteAvlTree(T->Element, T->Left);
			}
		}
		else
		{
			free(T);
			T = NULL;
		}
	}

	T->Height = Max(HeightAvlTree(T->Left), HeightAvlTree(T->Right)) + 1;
	return T;
}

/*Return the Element of P,if P is illegal,release an error and return 0*/
ElementType RetrieveAvlTree(AvlPos P)
{
	if (P != NULL)
	{
		return P->Element;
		
	}
	else
	{
		perror("RetrieveBSTree error: illegal BStreePos!\n");
		return 0;
	}
}

/*Return the Height of P,if P is illegal,release an error and return -1*/
int HeightAvlTree(AvlPos P)
{
	if (P != NULL)
	{
		return P->Height;
	}
	else
	{
		return -1;
	}
}
