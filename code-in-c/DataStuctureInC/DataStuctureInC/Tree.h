/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�Tree.h
* �ļ���ʶ���������ṹ��ͨ�ò�������ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��5��
* ˵    �����Ը������ṹ���ͨ�ò��ּ�������
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

