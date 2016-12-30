// DataStuctureInC.cpp :start of the console program.
//
//
//

#include "stdafx.h"

#include "ListADT.h"

static int Test_List();
static int test_RadixSort();
int main()
{
	test_RadixSort();

    return 0;
}

/*test function for ListADT operation*/
int Test_List()
{
	List L;
	Position header, first;
	ElementType tmp;
	int i;

	L = InitList();
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

	printf("is empty?  %d\n", IsEmpty(L));
	MakeEmpty(L);
	printf("is empty?  %d\n",IsEmpty(L));
	PrintList(L);
	
	return 0;
}

int test_RadixSort()
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
