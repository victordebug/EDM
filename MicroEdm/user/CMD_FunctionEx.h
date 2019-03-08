// AMSKY File $Revision: /MAT800V120/ $
// Checkin $Date: JANU 6, 2013$
//###########################################################################
//###########################################################################
//
// FILE:   CMD_FunctionEx.h
//
// TITLE:  Module function parameters needed data structures.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################


#ifndef __CMD_FUNCTION_EX_H__
#define __CMD_FUNCTION_EX_H__

#include "Types.h"
#define CMD_FUNCTION_EX						0xC0D8
#define CMD_FUNCTION_EX_WORD				wordof(CMD_FunctionEx_t)

#define CMD_FUNCTION_EX_MINBYTE				byteof(CMD_FunctionEx_t)

typedef struct
{
	U16 m_ushMID;	//内核模块编号
	U16 m_ushFID;	//模块功能编号
	//模块功能函数所需的参数数据结构，4字节对齐
} CMD_FunctionEx_t;
typedef CMD_FunctionEx_t* CMD_FunctionEx_p;

/*
 * 各模块MID定义在[DDD]_List.h文件中，按照下面格式定义:
 * #define [DDD]_MID_[MMM]		0x[XX]00	//模块名称
 * 各模块FID定义在模块对应头文件中，按照下面格式定义:
 * #define [DDD]_[MMM]_FID_[FFF]		0x[ZZZZ]		//模块功能函数名称
 * #define [DDD]_[MMM]_FID_[FFF]_WORD	wordof([TTT])	//模块功能函数参数数据结构字节长度
 * 各个模块函数原型定义如下
 * U16 [MMM]_FunctionEx(U16 ushFID,U16* pBuffer,U16 ushWords);
 */
extern U16 ParseFunction_Ex(void);

#endif	//__CMD_FUNCTION_EX_H__
