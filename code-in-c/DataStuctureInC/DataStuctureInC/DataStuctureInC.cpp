// DataStuctureInC.cpp :start of the console program.
//
//
//

#include "stdafx.h"

#include "ListADT.h"
#include "StackADT.h"

static int Test_List(void);
static int test_RadixSort(void);
static int test_Stack(void);
int main()
{
	test_Stack();

    return 0;
}

/*test function for ListADT operation*/
int Test_List(void)
{
	List L;
	Position header, first;
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
