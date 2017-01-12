/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：HashSeparateChain.h
* 文件标识：散列（哈希表）-分离链接法实现
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月11日
* 说    明：分离链接法实现散列
*/
#pragma once
#include "ListADT.h"

#ifndef _HASHSEPARATECHAIN_H_
#define _HASHSEPARATECHAIN_H_

struct HashTable_SepChain;
typedef struct HashTable_SepChain *HashTable;
typedef unsigned int Index;

extern HashTable InitialHashTable(int tableSize);
extern void MakeEmptyHashTable(HashTable H);
extern void DestoryHashTable(HashTable H);
extern Position FindHashTable(ElementType Key, HashTable H);
extern void InsertHashTable(ElementType Key, HashTable H);
static Index Hash(ElementType Key,HashTable H);
extern void DeleteHashTable(ElementType Key, HashTable H);
extern ElementType RetrieveHashTable(Position P);

#endif // !_HASHSEPARATECHAIN_H_
