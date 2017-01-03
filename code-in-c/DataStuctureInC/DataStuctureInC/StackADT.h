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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern int IsStackEmpty(Stack S)
// 
//    功能：
//            判断栈(链表实现)是否为空栈
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  无
//
//    返回：
//			  true/1: 空链表
//            false/0:非空链表
////////////////////////////////////////////////////////////////////////////
extern int IsStackEmpty(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern Stack CreateStack(void)
// 
//    功能：
//            栈(链表实现)初始化
// 
//    参数：
//			  无
// 
//    描述：
//			  生成链表实现的空栈
//
//    返回：
//			  空栈
////////////////////////////////////////////////////////////////////////////
extern Stack CreateStack(void);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DisposeStack(Stack S)
// 
//    功能：
//            完全删除栈(链表实现)
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  完整删除栈，释放栈空间，置S = NULL(函数调用返回后S不是NULL)
//			  
//    返回：
//			  无
////////////////////////////////////////////////////////////////////////////
extern void DisposeStack(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeStackEmpty(Stack S)
// 
//    功能：
//            栈(链表实现)置空
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  栈置空，释放栈节点占用空间
//
//    返回：
//			  无
////////////////////////////////////////////////////////////////////////////
extern void MakeStackEmpty(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void PushStack(ElementType X,Stack S)
// 
//    功能：
//            新元素入栈(链表实现)
// 
//    参数：
//			  X: 新元素
//			  S：待处理栈S
// 
//    描述：
//			  新元素X入栈S
//
//    返回：
//			  无
////////////////////////////////////////////////////////////////////////////
extern void PushStack(ElementType X,Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType TopStack(Stack S)
// 
//    功能：
//            读栈顶元素(查找并返回)
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  查找栈顶节点，并返回栈顶元素值，若是空栈则报错并返回0
//
//    返回：
//			  栈顶元素值
////////////////////////////////////////////////////////////////////////////
extern ElementType TopStack(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType PopStack(Stack S)
// 
//    功能：
//            出栈(删除栈顶元素）
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  删除栈顶元素，释放节点空间，空栈则报错
//
//    返回：
//			  无
////////////////////////////////////////////////////////////////////////////
extern void PopStack(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType TopAndPopStack(Stack S)
// 
//    功能：
//            读栈顶然后出栈
// 
//    参数：
//			  S：待处理栈S
// 
//    描述：
//			  返回栈顶元素值，并删除栈顶节点,若是空栈则报错并返回0
//
//    返回：
//			  栈顶元素值
////////////////////////////////////////////////////////////////////////////
extern ElementType TopAndPopStack(Stack S);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InfixToPostfix(char *infix, char *postfix)
// 
//    功能：
//            中缀表达式(infix)转换为后缀表达式(postfix)，数值为整型
// 
//    参数：
//			  infix： 中缀表达式（输入）
//			  postfix:后缀表达式（输出）
//    描述：
//			  利用栈操作，将中缀表达式转化为对应的后缀表达式
//
//    返回：
//			  无
////////////////////////////////////////////////////////////////////////////
extern void InfixToPostfix(char *infix, char *postfix);
static int OperatorPrecedence(char first, char second);

#endif // !_StackADT_h


