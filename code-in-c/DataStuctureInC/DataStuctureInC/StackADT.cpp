/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：ListADT.cpp
* 文件标识：栈-源文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月2日
* 说    明：由带表头的链表实现栈
*/
#include "stdafx.h"
#include "StackADT.h"


struct Node
{
	ElementType Element;
	PtrToNode Next;
};

int IsEmpty(Stack S)
{
	return 0;
}

Stack CreateStack(void)
{
	return Stack();
}

void DisposeStack(Stack S)
{
}

void MakeEmpty(Stack S)
{
}

void Push(ElementType X, Stack S)
{
}

ElementType Top(Stack S)
{
	return ElementType();
}

void Pop(Stack S)
{
}
