/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�AVLTree.h
* �ļ���ʶ����ƽ�������Ķ��������-ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��8��
* ˵    ������ƽ�������Ķ��������
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
