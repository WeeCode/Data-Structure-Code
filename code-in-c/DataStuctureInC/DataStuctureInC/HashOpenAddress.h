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
typedef Index Position;

typedef int ElementType;
typedef struct HashTbl_OpenAddress *HashTbl;

extern HashTbl InitializeHashTbl(int tableSize);

extern void MakeEmptyHashTbl(HashTbl H);

extern void DestoryHashTbl(HashTbl H);

extern Position FindHashTbl(ElementType Key,HashTbl H);

extern void InsertHashTbl(ElementType Key,HashTbl H);

extern void DeleteHashTbl(ElementType Key,HashTbl H);

extern ElementType RetrieveHashTbl(Position P,HashTbl H);

static HashTbl ReHashTbl(HashTbl H);

#endif // !_HASHOPENADDRESS_H_
