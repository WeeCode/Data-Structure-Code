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

/////////////////////////////////////////////////////////////////////////////
// 
//    extern HashTable InitializeHashTable(int tableSize)
// 
//    功能：
//            哈希表初始化（分离链接法实现）
// 
//    参数：
//			  tableSize：哈希表大小
// 
//    描述：
//			  初始化哈希表与内部链表
//
//    返回：
//			  初始化完成的哈希表
//			  
////////////////////////////////////////////////////////////////////////////
extern HashTable InitializeHashTable(int tableSize);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void MakeEmptyHashTable(HashTable H)
// 
//    功能：
//            哈希表（分离链接法实现）置空
// 
//    参数：
//			  H：待处理哈希表
// 
//    描述：
//			  删除哈希表元素，释放内部链表节点内存，保留链表表头
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void MakeEmptyHashTable(HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//   extern void DestoryHashTable(HashTable H)
// 
//    功能：
//            删除哈希表（分离链接法实现）
// 
//    参数：
//			  H：待处理哈希表
// 
//    描述：
//			 删除内部链表，删除哈希表，释放内存
//
//    返回：
//			  无
//			  
////////////////////////////////////////////////////////////////////////////
extern void DestoryHashTable(HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern Position FindHashTable(ElementType Key, HashTable H)
// 
//    功能：
//            在哈希表H中查找键值Key,返回键值Key所在位置
// 
//    参数：
//			  Key: 待查找键值Key
//			  H：  待处理哈希表
//    描述：
//			  若未找到则返回NULL
//
//    返回：
//			  键值Key所在链表节点的位置指针
//			  
////////////////////////////////////////////////////////////////////////////
extern Position FindHashTable(ElementType Key, HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void InsertHashTable(ElementType Key, HashTable H)
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
extern void InsertHashTable(ElementType Key, HashTable H);
static Index Hash(ElementType Key,HashTable H);

/////////////////////////////////////////////////////////////////////////////
// 
//    extern void DeleteHashTable(ElementType Key, HashTable H)
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
extern void DeleteHashTable(ElementType Key, HashTable H);

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
//			  节点P的键值Key
////////////////////////////////////////////////////////////////////////////
extern ElementType RetrieveHashTable(Position P);

#endif // !_HASHSEPARATECHAIN_H_
