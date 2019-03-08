// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   ParaInfo.h
//
// TITLE:  File is used to define each module MID.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################

#ifndef __PARAINFO_H__
#define __PARAINFO_H__

#include "config.h"
#include "ParaFilePub.h"

#if (PARA_VERSION == PARA_VERSION_V120)
	#include "ParaInfo_V100.h"
#else
	#error "PARA_VERSION is Undefined"
#endif

#define EPARA_ID				0xF801	//参数文件ID号参数错误
#define EPARA_OFFSET			0xF808	//参数文件内部起始偏移量参数错误
#define EPARA_WORDS				0xF810	//命令传递参数文件数据的长度参数错误

#ifndef PARA_FILE_NUM
	#error "PARA_FILE_NUM is Undifined"
#endif

#define AL_PARA_PID_CTRL				PARA_PID_CTRL						//参数更新控制信息
#define AL_PARA_PID_CTRL_WORD			wordof(ParaCtrl_t)					//4字节(0x04)
#define AL_PARA_PID_WORD				PARA_PID_WORD						//参数文件长度列表
#define AL_PARA_PID_WORD_WORD			PARA_PID_WORD_WORD(PARA_FILE_NUM)	//20字节(0x14)
#define AL_PARA_PID_INFO				PARA_PID_INFO						//参数文件版本信息
#define AL_PARA_PID_INFO_WORD			PARA_PID_INFO_WORD					//8字节(0x08)

//使用数据结构定义
typedef struct
{
	U16* m_pData;
	U32  m_ulWords;
} FileInfo_t;
typedef FileInfo_t* FileInfo_p;
#define FILEINFO(data)					{(U16*)(&data),wordof(data)}

typedef union
{
	FileUpdate_bit bit;
	U16 all;	
} FileUpdate_t;
typedef FileUpdate_t* FileUpdate_p;

typedef struct
{
	FileUpdate_t m_Update;
	U16 m_ushResult;
} ParaCtrl_t;
typedef ParaCtrl_t* ParaCtrl_p;

//模块外部属性定义
extern FileInfo_t g_FileInfoTable[PARA_FILE_NUM];
extern ParaInfo_t g_ParaInfo;
extern ParaCtrl_t g_ParaCtrl;

//模块外部接口定义
extern void PARA_Init(void);
extern U16  PARA_Read(CmdFileInfo_p pPara,U16* pData);
extern U16  PARA_Write(CmdFileInfo_p pPara,U16* pData);
extern U16  PARA_GetStateEx(U16 ushPID,U16* pBuffer);

#endif

