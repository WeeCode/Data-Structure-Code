/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�ListADT.h
* �ļ���ʶ�����Ա�ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2016��12��29��
* ˵    ����
*/
#pragma once

//The Linked List
#ifndef _ListADT_H
typedef  int ElementType;
struct Node;
typedef	struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

/*operations on the list ADT */
extern List MakeEmpty(List L);
extern int IsEmpty(List L);
extern int IsLast(Position P,List L);
extern Position Find(ElementType X,List L);
extern void Delete(ElementType X,List L);
extern Position FindPrevious(ElementType X,List L);
extern void Insert(ElementType X,List L,Position P);
extern void DeleteList(List L);
extern Position Header(List L);
extern Position First(List L);
extern Position Advance(Position P);
extern ElementType Retrieve(Position P);

#endif




