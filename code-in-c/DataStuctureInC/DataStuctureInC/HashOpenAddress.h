/*
* Copyright (c) 2017, ���пƼ���ѧ ��������ϵͳ��������
* All rights reserved.
*
* �ļ����ƣ�HashOpenAddress.h
* �ļ���ʶ��ɢ�У���ϣ��-���Ŷ�ַ��ʵ��
* ժ    Ҫ��
* ����ƽ̨��windows
*
* ��    ����1.00
* ��    �ߣ��˳���
* ��    �ڣ�2017��1��12��
* ˵    �������Ŷ�ַ��ʵ��ɢ�У���ϣ��
*/
#pragma once

#ifndef _HASHOPENADDRESS_H_
#define _HASHOPENADDRESS_H_

typedef unsigned int Index;
typedef Index HashTblPosition;

typedef int ElementType;
typedef struct HashTbl_OpenAddress *HashTbl;

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTbl InitializeHashTbl(int tableSize)
// 
//    ���ܣ�
//            ��ϣ���ʼ�������Ŷ�ַ��ʵ�֣�
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
extern HashTbl InitializeHashTbl(int tableSize);
extern int NextPrime(unsigned int limit);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeEmptyHashTbl(HashTbl H)
// 
//    ���ܣ�
//            ��ϣ�����Ŷ�ַ��ʵ�֣��ÿ�
// 
//    ������
//			  H���������ϣ��
// 
//    ������
//			  ����cell���Ϊempty
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeEmptyHashTbl(HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DestoryHashTbl(HashTbl H)
// 
//    ���ܣ�
//            ɾ����ϣ�����Ŷ�ַ��ʵ�֣�
// 
//    ������
//			  H���������ϣ��
// 
//    ������
//			 ɾ����ϣ���ͷ��ڴ�
//
//    ���أ�
//			  ��
//			  
////////////////////////////////////////////////////////////////////////////
extern void DestoryHashTbl(HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTblPosition FindHashTbl(ElementType Key,HashTbl H)
// 
//    ���ܣ�
//            �ڹ�ϣ��H�в��Ҽ�ֵKey,���ؼ�ֵKey����λ��
// 
//    ������
//			  Key: �����Ҽ�ֵKey
//			  H��  �������ϣ��
//    ������
//			  ƽ��̽�ⷨ�������²��ң�ֱ��Key����empty
//
//    ���أ�
//			  ��ֵKey����λ�ã�����emptyλ��
//			  
////////////////////////////////////////////////////////////////////////////
extern HashTblPosition FindHashTbl(ElementType Key,HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InsertHashTbl(ElementType Key,HashTbl H)
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
extern void InsertHashTbl(ElementType Key,HashTbl H);
static Index Hash(ElementType Key, HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DeleteHashTbl(ElementType Key,HashTbl H)
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
extern void DeleteHashTbl(ElementType Key,HashTbl H);

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
//			  ���ڵ���ΪLegitimate����ڵ�P�ļ�ֵKey��
//			  ���򱨾�������0
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveHashTbl(HashTblPosition P,HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTbl ReHashTbl(HashTbl H)
// 
//    ���ܣ�
//            ��ɢ��(��Կ��Ŷ�ַ��ɢ��)
// 
//    ������
//			  H��  �������ϣ��
// 
//    ������
//			  ��ԭɢ�б���������
//
//    ���أ�
//			  ��ɢ�к��ɢ�б�
////////////////////////////////////////////////////////////////////////////
extern HashTbl ReHashTbl(HashTbl H);

#endif // !_HASHOPENADDRESS_H_
