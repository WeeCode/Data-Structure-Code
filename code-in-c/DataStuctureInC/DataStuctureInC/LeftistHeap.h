/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�LeftistHeap.h
* �ļ���ʶ����ʽ�ѣ����ȶ��У�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��15��
* ˵    ������ʽ�ѣ����ȶ��У�--������ʵ��
*/
#pragma once
#include "Tree.h"

#ifndef _LEFTISTHEAP_H_
#define _LEFTISTHEAP_H_

extern LeftHeap InitLeftHeap(void);

extern ElementType FindMinLeftHeap(LeftHeap LH);

extern int IsEmptyLeftHeap(LeftHeap LH);

extern LeftHeap MergeLeftHeap(LeftHeap LH1, LeftHeap LH2);

#define InsertLeftHeap(X,LH) ( LH = Insert1LeftHeap((X) ,LH) )
extern LeftHeap Insert1LeftHeap(ElementType X,LeftHeap LH);

extern LeftHeap DeleteMinLeftHeap(LeftHeap LH);


#endif // !_LEFTISTHEAP_H_

