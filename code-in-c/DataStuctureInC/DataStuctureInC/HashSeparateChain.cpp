/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�HashSeparateChain.cpp
* �ļ���ʶ��ɢ�У���ϣ��-�������ӷ�ʵ��
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��11��
* ˵    �����������ӷ�ʵ��ɢ��
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
  
HashTable InitialHashTable(int tableSize)
{
	HashTable H;
	int i;

	if (tableSize < MinTableSize)
	{
		perror("InitialHashTable error: table size too small!\n");
	}

	H = (HashTable)malloc(sizeof(struct HashTable_SepChain));
	if (H == NULL)
	{
		perror("InitialHashTable error: malloc() out of space!\n");
		return NULL;
	}
	/*init hashTable*/
	H->TableSize = tableSize;  //H->TableSize = NextPrime(tableSize);
	H->TheLists = (List*)malloc(H->TableSize*sizeof(List));
	if (H->TheLists == NULL)
	{
		perror("InitialHashTable error: malloc() out of space!\n");
		return NULL;
	}
	/*init list*/
	for ( i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = CreateList(i);
	}

	return H;
}

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

ElementType RetrieveHashTable(Position P)
{
	return Retrieve(P);
}
