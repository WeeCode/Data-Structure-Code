/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：HashOpenAddress.cpp
* 文件标识：散列（哈希表）-开放定址法实现
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月12日
* 说    明：开放定址法实现散列（哈希表）
*/

#include "stdafx.h"
#include <stdlib.h>
#include "HashOpenAddress.h"

#define MinTableSize   (3)

/*state of hash table entry*/
enum KindOfEntry
{
	Legitimate,
	Empty,
	Deleted
};

/*hash table entry,include an element and it's state information*/
struct HashTblEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashTblEntry Cell;

/*Cell *TheCells will be an array of HashTblEntry cells,allocated later*/
struct HashTbl_OpenAddress
{
	int TableSize;
	Cell *TheCells;
};

HashTbl InitializeHashTbl(int tableSize)
{
	HashTbl H;
	int i;

	if (tableSize < MinTableSize)
	{
		perror("InitializeHashTbl error: table size too small!\n");
		return NULL;
	}
	/*malloc table*/
	H = (HashTbl)malloc(sizeof(struct HashTbl_OpenAddress));
	if (H == NULL)
	{
		perror("InitializeHashTbl error: malloc() out of space!\n");
		return NULL;
	}

	/*malloc array of cells*/
	H->TableSize = NextPrime(tableSize);
	H->TheCells = (Cell*)malloc(H->TableSize*sizeof(struct HashTblEntry));
	if (H->TheCells == NULL)
	{
		perror("InitializeHashTbl error: malloc() out of space!\n");
		return NULL;
	}

	/*init cells*/
	for ( i = 0; i < H->TableSize; i++)
	{
		H->TheCells[i].Info = Empty;
	}

	return H;
}

int NextPrime(unsigned int limit)
{
	bool IsPrime;
	int i;

	if (limit < 3)
	{/*Input 0/1/2,then NextPrime is 2*/
		return 2;
	}
	else if (limit == 3)
	{/*Input 3,then  next prime is 3*/
		return 3;
	}
	else
	{/*input > 3*/
		/*if Input is an even,it can't be an prime,Input++*/
		if (limit % 2 == 0)
			limit++;

		/*Loop until find next prime*/
		while (true)
		{
			IsPrime = true;
			for (i = 3; (unsigned int)i*i <= limit; i = i + 2)
			{
				if (limit%i == 0)
				{
					IsPrime = false;
					break;
				}
			}
			/*determine whether go on */
			if (IsPrime)
			{
				break;     /*find next prime*/
			}
			else
			{
				limit += 2;/*for even can't be a prime, ++2*/
			}
		}
		return limit;
	}
}

void MakeEmptyHashTbl(HashTbl H)
{
	int i;
	if (H != NULL)
	{
		for ( i = 0; i < H->TableSize; i++)
		{
			H->TheCells[i].Info = Empty;
		}
	}
}

void DestoryHashTbl(HashTbl H)
{
	int i;
	if (H != NULL)
	{
		for (i = 0; i < H->TableSize; i++)
		{
			free(H->TheCells);
		}
		free(H);
	}
	
}

HashTblPosition FindHashTbl(ElementType Key, HashTbl H)
{
	HashTblPosition CurrentPos;
	int CollisionNum = 0;

	CurrentPos = Hash(Key,H);
	while (H->TheCells[CurrentPos].Info != Empty || H->TheCells[CurrentPos].Element != Key)
	{
		CurrentPos += 2*(++CollisionNum) - 1; // i^2 =(i-1)^2 + 2i -1 

		/*put back if location is past the array*/
		if (CurrentPos >= (unsigned int)H->TableSize)
		{
			CurrentPos -= H->TableSize;
		}
	}

	return CurrentPos;

}

void InsertHashTbl(ElementType Key, HashTbl H)
{
	HashTblPosition P;

	P = FindHashTbl(Key,H);

	if (H->TheCells[P].Info != Legitimate)
	{
		H->TheCells[P].Element = Key;
		H->TheCells[P].Info = Legitimate;
	}
	/*else Key is already existed,do noting*/
}

Index Hash(ElementType Key, HashTbl H)
{
	return Key % H->TableSize;
}

void DeleteHashTbl(ElementType Key, HashTbl H)
{
	HashTblPosition P;

	P = FindHashTbl(Key, H);

	if (H->TheCells[P].Info == Legitimate)
	{
		H->TheCells[P].Info = Deleted;
	}
}

ElementType RetrieveHashTbl(HashTblPosition P, HashTbl H)
{
	return H->TheCells[P].Element;
}

HashTbl ReHashTbl(HashTbl H)
{
	return HashTbl();
}
