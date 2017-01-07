// DataStuctureInC.cpp :start of the console program.
//
//
//

#include "stdafx.h"

#include "ListADT.h"
#include "StackADT.h"
#include "QueueADT.h"
#include "BinarySearchTree.h"

static int Test_List(void);
static int test_RadixSort(void);
static int test_Stack(void);
static int test_Postfix(void);
static int test_Queue(void);
static int test_BinarySearchTree(void);

int main()
{
	test_BinarySearchTree();

    return 0;
}

/*test function for ListADT operation*/
int Test_List(void)
{
	List L;
	Position header;
	ElementType tmp;
	int i;

	L = CreateList();
	PrintList(L);

	header = Header(L);
	for ( i = 0; i < 10; i++)
	{
		tmp = i;
		//first = First(L);
		Insert(tmp, L, header);
	}
	PrintList(L);

	printf("the first element: %d\n",Retrieve(First(L)));
	printf("find 5 in List?  %d\n",(Find(5,L)==NULL));
	Delete(5, L);
	printf("find 5 in List?  %d\n", (Find(5, L)==NULL));
	Delete(9, L);
	printf("the first element: %d\n", Retrieve(First(L)));
	PrintList(L);

	printf("is empty?  %d\n", IsListEmpty(L));
	MakeListEmpty(L);
	printf("is empty?  %d\n",IsListEmpty(L));
	PrintList(L);
	DeleteList(L);
	printf("delete list?%d\n", (L == NULL) ? 1 : 0);

	
	return 0;
}

int test_RadixSort(void)
{
	int i = 0;
	ElementType data[10] = {12, 23, 4, 34, 123, 112, 2423, 111, 96, 667};
	RadixSort(data,10);

	for ( i = 0; i < 10; i++)
	{
		printf("the %dth num is: %d \n",i+1,data[i] );
	}

	return 0;
}

int test_Stack(void)
{
	Stack S;
	int i;

	S = CreateStack();
	printf("Is stack empty? %d\n",IsStackEmpty(S));
	
	for ( i = 0; i < 10; i++)
	{
		PushStack(i, S);
		printf("Top of stack is: %d \n",TopStack(S));
	}

	for ( i = 0; i < 5; i++)
	{
		PopStack(S);
		printf("Top of stack is: %d \n", TopStack(S));
	}

	MakeStackEmpty(S);
	printf("Is stack empty? %d\n", IsStackEmpty(S));
	DisposeStack(S);
	
	printf("delete stack?%d\n",(S == NULL)?1:0 );


	return 0;
}

int test_Postfix(void)
{
	ElementType answer;
	char infix[128] = "1-4/2+(4*5-6)*7";
	char postfix[128] = "\0";
	printf("infix is : %s \n", infix);
	InfixToPostfix(infix, postfix);
	printf("postfix is : %s \n",postfix);
	answer = EvaluatePostfix(postfix);
	printf("the answer is : %d \n", answer);

	return 0;
}

int test_Queue(void)
{
	Queue Q;
	int i;

	Q = CreateQueue(3);
	if (Q == NULL)
	{
		Q = CreateQueue(10);
		if (Q == NULL)
		{
			perror("create queue error!\n");
		}
	}

	printf("Is queue empty? %d\n", IsQueueEmpty(Q));
	printf("Is queue full? %d\n", IsQueueFull(Q));
	for ( i = 0; i < 11; i++)
	{
		EnQueue((ElementType)i, Q);
		printf("the front on queue is: %d\n", FrontQueue(Q));
	}
	printf("Is queue empty? %d\n", IsQueueEmpty(Q));
	printf("Is queue full? %d\n", IsQueueFull(Q));
	for (i = 0; i < 5; i++)
	{
		DeQueue(Q);
		printf("the front on queue is: %d\n", FrontQueue(Q));
	}
	printf("the front on queue is: %d\n", FrontAndDeQueue(Q));
	printf("the front on queue is: %d\n", FrontQueue(Q));

	printf("Is queue empty? %d\n", IsQueueEmpty(Q));
	printf("Is queue full? %d\n", IsQueueFull(Q));
	MakeQueueEmpty(Q);
	printf("Is queue empty? %d\n", IsQueueEmpty(Q));
	DisposeQueue(Q);
	

	return 0;
}

int test_BinarySearchTree(void)
{
	BinarySearchTree T = NULL;
	BStreePos P;

	T = MakeBSTreeEmpty(T);
		
	T = InsertBSTree(1,T);
	printf("the bigest element in T is :%d \n",FindMaxBSTree(T)->Element);
	printf("the smallest element in T is :%d \n", FindMinBSTree(T)->Element);

	T = InsertBSTree(3, T);
	T = InsertBSTree(2, T);
	T = InsertBSTree(5, T);
	T = InsertBSTree(4, T);

	P = FindBSTree(5, T);
	printf("find element %d in T \n", RetrieveBSTree(P));

	T = DeleteBSTree(5,T);
	P = FindBSTree(5, T);
	printf("find element %d in T \n", RetrieveBSTree(P));
	T = DeleteBSTree(1, T);
	printf("the bigest element in T is :%d \n", FindMaxBSTree(T)->Element);
	printf("the smallest element in T is :%d \n", FindMinBSTree(T)->Element);

	T = MakeBSTreeEmpty(T);


	return 0;
}
