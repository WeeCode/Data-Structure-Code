/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�HashOpenAddress.cpp
* �ļ���ʶ��ɢ�У���ϣ��-���Ŷ�ַ��ʵ��
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��12��
* ˵    �������Ŷ�ַ��ʵ��ɢ�У���ϣ��
*/

#include "stdafx.h"
#include <stdlib.h>
#include "HashOpenAddress.h"

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
	return HashTbl();
}

void MakeEmptyHashTbl(HashTbl H)
{
}

void DestoryHashTbl(HashTbl H)
{
}

Position FindHashTbl(ElementType Key, HashTbl H)
{
	return Position();
}

void InsertHashTbl(ElementType Key, HashTbl H)
{
}

void DeleteHashTbl(ElementType Key, HashTbl H)
{
}

ElementType RetrieveHashTbl(Position P, HashTbl H)
{
	return ElementType();
}

HashTbl ReHashTbl(HashTbl H)
{
	return HashTbl();
}
