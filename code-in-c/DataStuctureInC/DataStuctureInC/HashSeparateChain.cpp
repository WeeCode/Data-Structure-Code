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

struct HashTable_SepChain
{
	int TableSize;
	List *TheLists;
};

HashTable InitialHashTable(int tableSize)
{
	return HashTable();
}

void MakeEmptyHashTable(HashTable H)
{
}

void DestoryHashTable(HashTable H)
{
}

Position FindHashTable(ElementType Key, HashTable H)
{
	return Position();
}

void InsertHashTable(ElementType Key, HashTable H)
{
}

void DeleteHashTable(ElementType Key, HashTable H)
{
}

ElementType RetrieveHashTable(Position P)
{
	return ElementType();
}
