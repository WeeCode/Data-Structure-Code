/*
* Copyright (c) 2017, 华中科技大学 国家数控系统工程中心
* All rights reserved.
*
* 文件名称：HashOpenAddress.h
* 文件标识：散列（哈希表）-开放定址法实现
* 摘    要：
* 运行平台：windows
*
* 版    本：1.00
* 作    者：潘成龙
* 日    期：2017年1月12日
* 说    明：开放定址法实现散列（哈希表）
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
