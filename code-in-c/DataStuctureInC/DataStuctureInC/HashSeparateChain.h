/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�HashSeparateChain.h
* �ļ���ʶ��ɢ�У���ϣ��-�������ӷ�ʵ��
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��11��
* ˵    �����������ӷ�ʵ��ɢ��
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
