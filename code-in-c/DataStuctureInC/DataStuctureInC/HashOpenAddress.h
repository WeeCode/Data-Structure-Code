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
typedef Index HashTblPosition;

typedef int ElementType;
typedef struct HashTbl_OpenAddress *HashTbl;

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTbl InitializeHashTbl(int tableSize)
// 
//    功能：
//            哈希表初始化（开放定址法实现）
// 
//    参数：
//			  tableSize：哈希表大小
// 
//    描述：
//			  初始化哈希表与内部数组
//
//    返回：
//			  初始化完成的哈希表
//			  
////////////////////////////////////////////////////////////////////////////
extern HashTbl InitializeHashTbl(int tableSize);
extern int NextPrime(unsigned int limit);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeEmptyHashTbl(HashTbl H)
// 
//    功能：
//            哈希表（开放定址法实现）置空
// 
//    参数：
//			  H：待处理哈希表
// 
//    描述：
//			  所有cell标记为empty
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeEmptyHashTbl(HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DestoryHashTbl(HashTbl H)
// 
//    功能：
//            删除哈希表（开放定址法实现）
// 
//    参数：
//			  H：待处理哈希表
// 
//    描述：
//			 删除哈希表，释放内存
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void DestoryHashTbl(HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTblPosition FindHashTbl(ElementType Key,HashTbl H)
// 
//    功能：
//            在哈希表H中查找键值Key,返回键值Key所在位置
// 
//    参数：
//			  Key: 待查找键值Key
//			  H：  待处理哈希表
//    描述：
//			  平方探测法继续向下查找，直到Key或者empty
//
//    返回：
//			  键值Key所在位置，或者empty位置
//			  
////////////////////////////////////////////////////////////////////////////
extern HashTblPosition FindHashTbl(ElementType Key,HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InsertHashTbl(ElementType Key,HashTbl H)
// 
//    功能：
//            在哈希表H中插入新键值Key
// 
//    参数：
//			  Key: 待插入键值Key
//			  H：  待处理哈希表
//    描述：
//			  若Key已经存在于H中，则什么也不做
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void InsertHashTbl(ElementType Key,HashTbl H);
static Index Hash(ElementType Key, HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DeleteHashTbl(ElementType Key,HashTbl H)
// 
//    功能：
//            在哈希表H中删除键值Key
// 
//    参数：
//			  Key: 待删除键值Key
//			  H：  待处理哈希表
//    描述：
//			  若Key不存在于H中，则什么也不做
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void DeleteHashTbl(ElementType Key,HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern ElementType Retrieve(Position P)
// 
//    功能：
//            获取哈希表中指定内部链表节点位置的节点键值Key
// 
//    参数：
//			  P: 指定节点P
// 
//    描述：
//			  无
//
//    返回：
//			  若节点标记为Legitimate，则节点P的键值Key；
//			  否则报警并返回0
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveHashTbl(HashTblPosition P,HashTbl H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTbl ReHashTbl(HashTbl H)
// 
//    功能：
//            再散列(针对开放定址法散列)
// 
//    参数：
//			  H：  待处理哈希表
// 
//    描述：
//			  将原散列表扩充两倍
//
//    返回：
//			  再散列后的散列表
////////////////////////////////////////////////////////////////////////////
extern HashTbl ReHashTbl(HashTbl H);

#endif // !_HASHOPENADDRESS_H_
