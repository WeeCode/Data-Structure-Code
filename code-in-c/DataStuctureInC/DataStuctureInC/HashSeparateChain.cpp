/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：HashSeparateChain.cpp
* 文件标识：散列（哈希表）-分离链接法实现
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月11日
* 说    明：分离链接法实现散列
*/

#include "stdafx.h"
#include <stdlib.h>
#include "HashSeparateChain.h"

#define MinTableSize   (3)
struct HashTable_SepChain
{
	int TableSize;
	List *TheLists;
};
 
/*Initilize HashTable with settled table size,return NULL if failed*/
HashTable InitializeHashTable(int tableSize)
{
	HashTable H;
	int i;

	if (tableSize < MinTableSize)
	{
		perror("InitializeHashTable error: table size too small!\n");
		return NULL;
	}

	H = (HashTable)malloc(sizeof(struct HashTable_SepChain));
	if (H == NULL)
	{
		perror("InitializeHashTable error: malloc() out of space!\n");
		return NULL;
	}
	/*init hashTable*/
	H->TableSize = tableSize;  //H->TableSize = NextPrime(tableSize);
	H->TheLists = (List*)malloc(H->TableSize*sizeof(List));
	if (H->TheLists == NULL)
	{
		perror("InitializeHashTable error: malloc() out of space!\n");
		return NULL;
	}
	/*init list*/
	for ( i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = CreateList(i);
	}

	return H;
}

/*Make HashTable empty, reserved list heads,release node's memory*/
void MakeEmptyHashTable(HashTable H)
{
	int i;

	if (H != NULL)
	{
		for ( i = 0; i < H->TableSize; i++)
		{
			if (H->TheLists[i] != NULL)
			{
				H->TheLists[i] = MakeListEmpty(H->TheLists[i]);
			}
		}

		H->TableSize = 0;
	}
}

/*Destory HashTable entire,release whole memory*/
void DestoryHashTable(HashTable H)
{
	int i;

	if (H != NULL)
	{
		for (i = 0; i < H->TableSize; i++)
		{
			/*destory The Lists*/
			if (H->TheLists[i] != NULL)
			{
				DeleteList(H->TheLists[i]);
			}
		}
		/*destory HashTable*/
		free(H);
	}
}

/*Find Key in HashTable,return it's Position in corresponding List,return NULL if Key do not exist in table*/
Position FindHashTable(ElementType Key, HashTable H)
{
	List L;
	Position P;

	if (H != NULL)
	{
		L = H->TheLists[Hash(Key, H)];
		P = Find(Key, L);
	}
	else
	{
		perror("FindHashTable error: empty HashTable!\n");
		return NULL;
	}
}

/*Insert Key to Hashtable,do nothing if Key is already exist in table*/
void InsertHashTable(ElementType Key, HashTable H)
{
	Position Pos;
	if (H != NULL)
	{
		Pos = FindHashTable(Key,H);
		if (Pos == NULL)
		{
			InsertInEnd(Key, H->TheLists[Hash(Key, H)]);
		}
		/*else key exist, do nothing*/
	}
	else
	{
		perror("InsertHashTable error: empty HashTable!\n");
	}
}

/*Hash function*/
Index Hash(ElementType Key, HashTable H)
{
	if (H != NULL)
	{
		return Key % H->TableSize;
	}
	else
	{
		perror("Hash error: empty HashTable!\n");
		return 0;
	}
	
}

/*Delete Key in Hashtable,do nothing if Key is not exist in table*/
void DeleteHashTable(ElementType Key, HashTable H)
{
	Position Pos;
	if (H != NULL)
	{
		Pos = FindHashTable(Key, H);
		if (Pos != NULL)
		{
			Delete(Key, H->TheLists[Hash(Key, H)]);
		}
		/*else key  not exist, do nothing*/
	}
	else
	{
		perror("DeleteHashTable error: empty HashTable!\n");
	}
}

/*Get Key value in Position,assume Position P is legal*/
ElementType RetrieveHashTable(Position P)
{
	if (P == NULL)
	{
		perror("RetrieveHashTable error: NULL Position!\n");
		return 0;
	}
	else
	{
		return Retrieve(P);
	}
	
}
