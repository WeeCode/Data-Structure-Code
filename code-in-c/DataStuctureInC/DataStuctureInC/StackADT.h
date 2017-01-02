/*
* Copyright (c) 2016, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：StackADT.h
* 文件标识：栈-头文件
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2016年12月29日
* 说    明：由带表头的链表实现栈
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


