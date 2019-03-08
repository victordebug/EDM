// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012
//###########################################################################
//###########################################################################
//
// FILE:   FileSystem.h
//
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################


#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "stdtypes.h"
#include "ParaInfo.h"

#define EFILE_BUSY						0xF101
#define EFILE_WRITING					0xF102
#define EFILE_WRITEPOS					0xF110
#define EFILE_WRITEWORD					0xF111
#define BAD_COMMAND_LENGTH				0xF103
#define BAD_NO_FUNCTION					0xF104

#define FILE_BASE_ADDRESS				0

typedef struct
{
	FileUpdate_t m_Requst;
	FileUpdate_t m_Flag;
	U16 m_ushState;
	U16 m_ushOffset;
} FileCtrl_t;
typedef FileCtrl_t* FileCtrl_p;

extern FileCtrl_t g_FileCtrl;

#define FILE_UNINIT				0xFFFF
#define FILE_IDLE				0x0000
#define FILE_WRITE				0x8000

extern void FILE_Init(void);
extern void FILE_Module(void);
extern U16 	FILE_Update(U16 ushUpdate);

#define AL_FILE_PID_CTRL			0x0000								//参数更新控制信息
#define AL_FILE_PID_CTRL_WORD		wordof(FileCtrl_t)					//4字节(0x04)
extern U16 FILE_GetStateEx(U16 ushPID,U16* pBuffer);

typedef struct
{
	U16 m_ushPos;		//必须为4的倍数
	U16 m_ushWord;		//必须为2的倍数 <=8
} FileWritePara_t;

typedef FileWritePara_t* FileWritePara_p;

#define AL_FILE_FID_UPDATE					0
#define AL_FILE_FID_UPDATE_WORD				wordof(U32)
#define AL_FILE_FID_WRITE					0x8000
#define AL_FILE_FID_WRITE_WORD(pPara)		(wordof(FileWritePara_t)+pPara->m_ushWord)

extern U16 FILE_FunctionEx(U16 ushFID,U16* pBuffer,U16 ushWords);

#endif
