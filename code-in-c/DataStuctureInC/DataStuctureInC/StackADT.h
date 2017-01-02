/*
* Copyright (c) 2016, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�StackADT.h
* �ļ���ʶ��ջ-ͷ�ļ�
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2016��12��29��
* ˵    �����ɴ���ͷ������ʵ��ջ
*/
#pragma once

#ifndef _StackADT_h

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

extern int IsStackEmpty(Stack S);
extern Stack CreateStack(void);
extern void DisposeStack(Stack S);
extern void MakeStackEmpty(Stack S);
extern void PushStack(ElementType X,Stack S);
extern ElementType TopStack(Stack S);
extern void PopStack(Stack S);

#endif // !_StackADT_h


