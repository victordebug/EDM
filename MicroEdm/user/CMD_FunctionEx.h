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
	U16 m_ushMID;	//�ں�ģ����
	U16 m_ushFID;	//ģ�鹦�ܱ��
	//ģ�鹦�ܺ�������Ĳ������ݽṹ��4�ֽڶ���
} CMD_FunctionEx_t;
typedef CMD_FunctionEx_t* CMD_FunctionEx_p;

/*
 * ��ģ��MID������[DDD]_List.h�ļ��У����������ʽ����:
 * #define [DDD]_MID_[MMM]		0x[XX]00	//ģ������
 * ��ģ��FID������ģ���Ӧͷ�ļ��У����������ʽ����:
 * #define [DDD]_[MMM]_FID_[FFF]		0x[ZZZZ]		//ģ�鹦�ܺ�������
 * #define [DDD]_[MMM]_FID_[FFF]_WORD	wordof([TTT])	//ģ�鹦�ܺ����������ݽṹ�ֽڳ���
 * ����ģ�麯��ԭ�Ͷ�������
 * U16 [MMM]_FunctionEx(U16 ushFID,U16* pBuffer,U16 ushWords);
 */
extern U16 ParseFunction_Ex(void);

#endif	//__CMD_FUNCTION_EX_H__
