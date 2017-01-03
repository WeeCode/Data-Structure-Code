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
#include <stdlib.h>
#include "StackADT.h"

/*stack of linked list implementation*/
struct Node
{
	ElementType Element;
	PtrToNode Next;
};

/*Return ture/1 if stack S is empty*/
int IsStackEmpty(Stack S)
{
	return S->Next == NULL;
}

/*Create an empty stack*/
Stack CreateStack(void)
{
	Stack S;

	S = (Stack)malloc(sizeof(struct Node));
	if (S == NULL)
	{
		perror("malloc error: out of space! \n");
	}
	S->Element = 0;
	S->Next = NULL;
	
	return S;
}

/*Delete stack S completely,include it's header,free memory*/
void DisposeStack(Stack S)
{
	PtrToNode node, tmp;

	node = S;
	S = NULL;

	while (node != NULL)
	{
		tmp = node->Next;
		free(node);
		node = tmp;
	}
}

/*Make stack S empty,free memory of it's node */
void MakeStackEmpty(Stack S)
{
	PtrToNode node,tmp;

	node = S->Next;
	S->Next = NULL;

	while (node != NULL)
	{
		tmp = node->Next;
		free(node);
		node = tmp;
	}
}

/*Push element X onto stack S*/
void PushStack(ElementType X, Stack S)
{
	PtrToNode node;

	node = (Stack)malloc(sizeof(struct Node));
	if (node == NULL)
	{
		perror("malloc error: out of space! \n");
	}
	else
	{
		node->Element = X;
		node->Next = S->Next;
		S->Next = node;
	}
}

/*Get top element on stack S, release error and return 0 if an empty stack*/
ElementType TopStack(Stack S)
{
	if(!IsStackEmpty(S))
	{
		return S->Next->Element;
	}

	perror("Top error: top an empty stack! \n");
	return 0;
}

/* Pop/delete the first element on stack S */
void PopStack(Stack S)
{
	PtrToNode node;

	if (!IsStackEmpty(S))
	{
		node = S->Next;
		S->Next = node->Next;
		free(node);
	}
	else
	{
		perror("Pop error: Pop an empty stack! \n");
	}
}

/* Get the first element on stack S, then delete it, free it's memory */
ElementType TopAndPopStack(Stack S)
{
	PtrToNode node;
	ElementType first;

	if (!IsStackEmpty(S))
	{
		node = S->Next;
		S->Next = node->Next;
		first = node->Element;
		free(node);
		return first;
	}
	else
	{
		perror("Pop error: Pop an empty stack! \n");
		return 0;
	}
}

void InfixToPostfix(char * infix, char * postfix)
{
	Stack operatorStack;
	char top;

	if (infix == NULL || postfix == NULL)
	{
		perror("Use NULL pointer in InfixToPostfix()! \n");
	}

	operatorStack = CreateStack();
	if (operatorStack == NULL)
	{
		perror("InfixToPostfix: Create Stack Failed! \n");
	}

	/* loop until end of string infix*/
	while (*infix != '\0')
	{


		if (*infix >= '0' && *infix <= '9') 
		{/*rule 1:when oprerand is read, immediately output*/
			*(postfix++) = *(infix++);
			continue;
		}
		else if (*infix == ')')
		{/*rule 2:when ')' is read, TopAndPop operator stack until encounter '('*/
			for (; ; )
			{
				if (IsStackEmpty(operatorStack))
				{
					perror("InfixToPostfix: can't find '(' when read ')'! \n");
					return;
				}
				top = (char)TopAndPopStack(operatorStack);
				if (top == '(')
					break;
				*(postfix++) = top;
			}
			infix++;
			continue;
		}
		else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/' || *infix == '(')
		{/*rule 3: when other symbol is read, TopAndPop operator stack until encounter entry with low priority,
					then Pust that symbol onto operator stack*/
			if (!IsStackEmpty(operatorStack))
			{
				for (; ; )
				{
					top = (char)TopAndPopStack(operatorStack);
					if (OperatorPrecedence(top, *infix) < 0)/*encounter entry with low priority*/
						break;
					*(postfix++) = top;
				}
				PushStack((ElementType)top, operatorStack);
			}
			PushStack((ElementType)*(infix++),operatorStack);
			continue;
		}
		else
		{/*illlegal symbol*/
			perror("illegal input infix! \n");
			return;
		}

	}

	/*rule 4: when end of Input is read, TopAndPop operator stack until empty*/
	while (!IsStackEmpty(operatorStack))
	{
		*(postfix++) = (char)TopAndPopStack(operatorStack);
	}

	return;

}

/*compare priority of two operator,
	return -1 when first has a low priority then second operator;
	return 0 when equal;
	return 1 when first has a high priority then second operator;*/
int OperatorPrecedence(char first, char second)
{
	if (first != '(' && first != ')' && first != '*' && first != '/' && first != '+' && first != '-')
	{
		perror("OperatorPrecedence: first operator illlegal! \n");
		return -2;
	}

	if (second != '(' && second != ')' && second != '*' && second != '/' && second != '+' && second != '-')
	{
		perror("OperatorPrecedence: second operator illlegal! \n");
		return -2;
	}

	if (first == '(' || first == ')')
	{
		if (second == '(' || second == ')')
			return 0;
		else
			return 1;
	}
	else if (first == '*' || first == '/')
	{
		if (second == '(' || second == ')')
			return -1;
		else if (second == '*' || second == '/')
			return 0;
		else
			return 1;
	}
	else
	{
		if (second == '+' || second == '-')
			return 0;
		else
			return -1;
	}
}
