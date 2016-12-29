/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：ListADT.cpp
* 文件标识：线性表源文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2016年12月29日
* 说    明：
*/

#include "stdafx.h"

#include "ListADT.h"

struct Node
{
	ElementType Element;
	Position Next;
};

/*function to operate the linked list ADT */
List MakeEmpty(List L)
{
	return List();
}

int IsEmpty(List L)
{
	return 0;
}

int IsLast(Position P, List L)
{
	return 0;
}

Position Find(ElementType X, List L)
{
	return Position();
}

void Delete(ElementType X, List L)
{
}

Position FindPrevious(ElementType X, List L)
{
	return Position();
}

void Insert(ElementType X, List L, Position P)
{
}

void DeleteList(List L)
{
}

Position Header(List L)
{
	return Position();
}

Position First(List L)
{
	return Position();
}

Position Advance(Position P)
{
	return Position();
}

ElementType Retrieve(Position P)
{
	return ElementType();
}
