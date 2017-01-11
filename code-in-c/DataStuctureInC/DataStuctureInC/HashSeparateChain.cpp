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
