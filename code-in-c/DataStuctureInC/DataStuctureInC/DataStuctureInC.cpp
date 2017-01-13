// DataStuctureInC.cpp :start of the console program.
//
//
//

#include "stdafx.h"

#include "ListADT.h"
#include "StackADT.h"
#include "QueueADT.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashSeparateChain.h"
#include "HashOpenAddress.h"

static int Test_List(void);
static int test_RadixSort(void);
static int test_Stack(void);
static int test_Postfix(void);
static int test_Queue(void);
static int test_BinarySearchTree(void);
static int test_AVLTree(void);
static int test_HashSeparateChain(void);
static int test_NextPrime(void);
static int test_HashOpenAddress(void);

int main()
{
	test_HashOpenAddress();

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

int test_AVLTree(void)
{
	AvlTree T = NULL;
	AvlPos P;

	T = MakeAvlTreeEmpty(T);

	T = InsertAvlTree(3, T);
	T = InsertAvlTree(2, T);
	T = InsertAvlTree(1, T);/*case 1: left-left*/

	T = InsertAvlTree(4, T);
	T = InsertAvlTree(5, T);/*case 3: right-right*/
	T = InsertAvlTree(6, T);/*case 3: right-right, in root*/
	T = InsertAvlTree(7, T);/*case 3: right-right*/

	T = InsertAvlTree(16, T);
	T = InsertAvlTree(15, T);/*case 4: right-left*/
	T = InsertAvlTree(14, T);/*case 4: right-left*/
	T = InsertAvlTree(13, T);/*case 3: right-right*/
	T = InsertAvlTree(12, T);/*case 1: left-left*/
	T = InsertAvlTree(11, T);/*case 1: left-left*/
	T = InsertAvlTree(10, T);/*case 1: left-left*/

	T = InsertAvlTree(8, T);
	T = InsertAvlTree(9, T);/*case 2: left-right*/

	printf("the bigest element in T is :%d \n", FindMaxAvlTree(T)->Element);
	printf("the smallest element in T is :%d \n", FindMinAvlTree(T)->Element);

	P = FindAvlTree(7, T);
	printf("find element %d in T \n", RetrieveAvlTree(P));

	T = DeleteAvlTree(7, T);
	P = FindAvlTree(7, T);
	printf("find element %d in T \n", RetrieveAvlTree(P));

	T = DeleteAvlTree(13, T);

	T = DeleteAvlTree(15, T);
	T = DeleteAvlTree(16, T);
	T = DeleteAvlTree(14, T);

	T = DeleteAvlTree(6, T);
	T = DeleteAvlTree(5, T);

	T = MakeAvlTreeEmpty(T);

	return 0;
}

int	test_HashSeparateChain(void)
{
	HashTable H;
	Position P;
	int i;

	H = InitializeHashTable(10);

	for ( i = 0; i < 20; i++)
	{
		InsertHashTable((ElementType)i,H);
	}

	P = FindHashTable(5,H);
	printf("find element %d in T \n", RetrieveHashTable(P));
	DeleteHashTable(5,H);
	P = FindHashTable(5, H);
	printf("find element %d in T \n", RetrieveHashTable(P));

	MakeEmptyHashTable(H);
	DestoryHashTable(H);

	return 0;
}

int test_NextPrime(void)
{
	printf("next prime after 0 is: %d  \n", NextPrime(0));

	printf("next prime after 1 is: %d  \n", NextPrime(1));

	printf("next prime after 2 is: %d  \n", NextPrime(2));

	printf("next prime after 3 is: %d  \n", NextPrime(3));

	printf("next prime after 4 is: %d  \n", NextPrime(4));

	printf("next prime after 5 is: %d  \n", NextPrime(5));

	printf("next prime after 10 is: %d  \n", NextPrime(10));

	printf("next prime after 15 is: %d  \n", NextPrime(15));

	printf("next prime after 25 is: %d  \n", NextPrime(25));

	return 0;

}

int test_HashOpenAddress(void)
{
	HashTbl H;
	HashTblPosition P;

	H = InitializeHashTbl(20);
	
	InsertHashTbl((ElementType)1, H);
	InsertHashTbl((ElementType)(23+1), H);
	InsertHashTbl((ElementType)(2*23+1), H);

	InsertHashTbl((ElementType)2, H);

	P = FindHashTbl((23 + 1),H);
	printf("find element %d in T \n", RetrieveHashTbl(P,H));
	DeleteHashTbl((23 + 1),H);
	P = FindHashTbl((23 + 1), H);
	printf("find element %d in T \n", RetrieveHashTbl(P, H));

	MakeEmptyHashTbl(H);
	DestoryHashTbl(H);

	return 0;
}
