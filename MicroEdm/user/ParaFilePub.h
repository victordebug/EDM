// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   ParaFilePub.h
//
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################

#ifndef __PARAFILE_PUB_H__
#define __PARAFILE_PUB_H__

#include "stdtypes.h"
typedef struct
{
	Uint16	Id:			4;
	Uint16	Offset:		12;
	Uint16	Words;
} CmdFileInfo_t;
typedef CmdFileInfo_t* CmdFileInfo_p;

#define CMD_GETPARA					0xC080
#define CMD_GETPARA_BYTE			byteof(CmdFileInfo_t)
#define CMD_RETURNPARA				0xC081

#define CMD_SETPARA					0xC082
#define CMD_SETPARA_MIN_BYTE		byteof(CmdFileInfo_t)

#define CMD_FILEUPDATE				0xC0EE
#define CMD_FILEUPDATE_BYTE			byteof(U32)

/*****************************************************************************/
#define PARA_PID_CTRL				0x0000				//参数更新控制信息

#define PARA_PID_WORD				0x0001				//参数文件长度列表
#define PARA_PID_WORD_WORD(n)		(wordof(U32)*n)	

typedef struct
{
	U16 	m_ushVersion;
	U16		m_ushNum;
	U16		m_ushMaxReadWords;
	U16		m_ushMaxWriteWords;
} ParaInfo_t;
typedef ParaInfo_t* ParaInfo_p;

#define PARA_PID_INFO				0x0002				//参数文件版本信息
#define PARA_PID_INFO_WORD			wordof(ParaInfo_t)

#endif
