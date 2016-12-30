// DataStuctureInC.cpp :start of the console program.
//
//
//

#include "stdafx.h"

#include "ListADT.h"

static int Test_List();
int main()
{
	Test_List();

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
