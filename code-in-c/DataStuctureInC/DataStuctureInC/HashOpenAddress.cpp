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
