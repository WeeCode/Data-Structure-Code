/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�ListADT.cpp
* �ļ���ʶ�����Ա�Դ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2016��12��29��
* ˵    ����
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
