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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTable InitializeHashTable(int tableSize)
// 
//    ���ܣ�
//            ��ϣ���ʼ�����������ӷ�ʵ�֣�
// 
//    ������
//			  tableSize����ϣ���С
// 
//    ������
//			  ��ʼ����ϣ�����ڲ�����
//
//    ���أ�
//			  ��ʼ����ɵĹ�ϣ��
//			  
////////////////////////////////////////////////////////////////////////////
extern HashTable InitializeHashTable(int tableSize);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeEmptyHashTable(HashTable H)
// 
//    ���ܣ�
//            ��ϣ���������ӷ�ʵ�֣��ÿ�
// 
//    ������
//			  H���������ϣ��
// 
//    ������
//			  ɾ����ϣ��Ԫ�أ��ͷ��ڲ�����ڵ��ڴ棬���������ͷ
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeEmptyHashTable(HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//   extern void DestoryHashTable(HashTable H)
// 
//    ���ܣ�
//            ɾ����ϣ���������ӷ�ʵ�֣�
// 
//    ������
//			  H���������ϣ��
// 
//    ������
//			 ɾ���ڲ�����ɾ����ϣ���ͷ��ڴ�
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void DestoryHashTable(HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern Position FindHashTable(ElementType Key, HashTable H)
// 
//    ���ܣ�
//            �ڹ�ϣ��H�в��Ҽ�ֵKey,���ؼ�ֵKey����λ��
// 
//    ������
//			  Key: �����Ҽ�ֵKey
//			  H��  �������ϣ��
//    ������
//			  ��δ�ҵ��򷵻�NULL
//
//    ���أ�
//			  ��ֵKey��������ڵ��λ��ָ��
//			  
////////////////////////////////////////////////////////////////////////////
extern Position FindHashTable(ElementType Key, HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InsertHashTable(ElementType Key, HashTable H)
// 
//    ���ܣ�
//            �ڹ�ϣ��H�в����¼�ֵKey
// 
//    ������
//			  Key: �������ֵKey
//			  H��  �������ϣ��
//    ������
//			  ��Key�Ѿ�������H�У���ʲôҲ����
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void InsertHashTable(ElementType Key, HashTable H);
static Index Hash(ElementType Key,HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DeleteHashTable(ElementType Key, HashTable H)
// 
//    ���ܣ�
//            �ڹ�ϣ��H��ɾ����ֵKey
// 
//    ������
//			  Key: ��ɾ����ֵKey
//			  H��  �������ϣ��
//    ������
//			  ��Key��������H�У���ʲôҲ����
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void DeleteHashTable(ElementType Key, HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType Retrieve(Position P)
// 
//    ���ܣ�
//            ��ȡ��ϣ����ָ���ڲ�����ڵ�λ�õĽڵ��ֵKey
// 
//    ������
//			  P: ָ���ڵ�P
// 
//    ������
//			  ��
//
//    ���أ�
//			  �ڵ�P�ļ�ֵKey
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveHashTable(Position P);

#endif // !_HASHSEPARATECHAIN_H_
