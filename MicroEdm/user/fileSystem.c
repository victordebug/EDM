// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012
//###########################################################################
//###########################################################################
//
// FILE:   FileSystem.c
//
// TITLE:  Parameter Management.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################



#include "FileSystem.h"
#include "CMD.h"
#include "AT24CXX.h"

FileCtrl_t g_FileCtrl;

FileWritePara_t m_FileWritePara;
U16 m_ushWriteData[8];

void FILE_Init(void)
{
	MemSet(&g_FileCtrl,0,wordof(g_FileCtrl));
	g_FileCtrl.m_ushState = FILE_UNINIT;
	g_FileCtrl.m_Flag.all = MAX_U16;
	g_FileCtrl.m_Flag.bit.rsvd = 0;

	MemSet(&m_FileWritePara,0,wordof(m_FileWritePara));
	MemSet(m_ushWriteData,0,wordof(m_ushWriteData));
}
U16 FILE_Update(U16 ushUpdate)
{
	if(g_FileCtrl.m_ushState != FILE_IDLE)
		return EFILE_BUSY;

	g_FileCtrl.m_Requst.all |= ushUpdate;
	g_FileCtrl.m_Requst.bit.rsvd = 0;
	g_FileCtrl.m_ushOffset = 0;
	return NOERROR;
}
U16 FILE_StartWrite(FileWritePara_p pPara,U16* pData)
{
	if(g_FileCtrl.m_ushState != FILE_IDLE)
		return EFILE_BUSY;

	if(pPara->m_ushPos >= AT24CXX_BYTE)
		return EFILE_WRITEPOS;
	if((pPara->m_ushPos & 3) != 0)
		return EFILE_WRITEPOS;
	if((pPara->m_ushWord & 1) != 0)
		return EFILE_WRITEWORD;
	if(pPara->m_ushWord > ((AT24CXX_BYTE - pPara->m_ushPos)>>1))
		return EFILE_WRITEWORD;
	if((pPara->m_ushWord == 0) || (pPara->m_ushWord > wordof(m_ushWriteData)))
		return EFILE_WRITEWORD;
	
	MemCpy(&m_FileWritePara,pPara,wordof(m_FileWritePara));
	MemCpy(m_ushWriteData,pData,pPara->m_ushWord);

	g_FileCtrl.m_ushState = FILE_WRITE;
	g_FileCtrl.m_ushOffset = 0;
	return NOERROR;
}

U32 FILE_CheckSum(U32* pData,U16 ushByte)
{
	U16 ushDW = (ushByte >> 2);
	U32 ulCheckSum = MAX_U32;
	while(ushDW != 0)
	{
		ushDW--;
		ulCheckSum -= pData[ushDW];
	}
	return ulCheckSum;
}
void FILE_Uninit_Func(void)
{
	U32* pData;
	U16 ushByte;
	U16 ushAddress = FILE_BASE_ADDRESS;		//文件基地址
	U16 ushID = 0;
	
	if(g_FileCtrl.m_Flag.all == 0)
	{//全部参数初始化完成
		U16 ushFlag = g_FileCtrl.m_Requst.all;
		if(g_FileCtrl.m_Requst.all != 0)
		{
			if(g_FileCtrl.m_Requst.bit.SN == 1)
				SN_InitPara();
			if(g_FileCtrl.m_Requst.bit.ErrLog == 1)
				ErrLog_Init();
			if(g_FileCtrl.m_Requst.bit.MotorConfig == 1)
				MotorConfig_Init();
		}
		MemSet(&g_FileCtrl,0,wordof(g_FileCtrl));
		g_FileCtrl.m_Flag.all = ushFlag;
		return;
	}
	while(ushID < PARA_FILE_NUM)
	{
		pData = (U32*)g_FileInfoTable[ushID].m_pData;
		ushByte = (U16)g_FileInfoTable[ushID].m_ulWords;
		ushByte <<= 1;
		if((g_FileCtrl.m_Flag.all & (1<<ushID)) != 0)
			break;
		ushAddress += ushByte;
		ushAddress += byteof(U32);	//校验和位置
		ushID++;
	}
	if(ushID >= PARA_FILE_NUM)		//程序保护，条件永假
		return;
	ushAddress += g_FileCtrl.m_ushOffset;
	if(g_FileCtrl.m_ushOffset < ushByte)
	{
		ushByte -= g_FileCtrl.m_ushOffset;
		if(ushByte > byteof(U32))
			ushByte = byteof(U32);
		if(AT24CXX_Read(ushAddress,ushByte,&pData[g_FileCtrl.m_ushOffset>>2])!= NOERROR)
			return;
		g_FileCtrl.m_ushOffset += ushByte;
	}
	else
	{
		U32 ulCheckSum;
		if(AT24CXX_Read(ushAddress,byteof(ulCheckSum),&ulCheckSum)!= NOERROR)
			return;
		if(FILE_CheckSum(pData,ushByte) != ulCheckSum)
			g_FileCtrl.m_Requst.all |= (1<<ushID);
		g_FileCtrl.m_ushOffset = 0;
		g_FileCtrl.m_Flag.all &= (~(1<<ushID));
	}
}
void FILE_Write_Func(void)
{
	U16 ushByte = m_FileWritePara.m_ushWord;
	U16 ushAddress = m_FileWritePara.m_ushPos + g_FileCtrl.m_ushOffset;		//文件基地址
	ushByte <<= 1;
	if(g_FileCtrl.m_ushOffset < ushByte)
	{
		ushByte -= g_FileCtrl.m_ushOffset;
		if(ushByte > byteof(U32))
			ushByte = byteof(U32);
		if(AT24CXX_Write(ushAddress,ushByte,(U32*)(&m_ushWriteData[g_FileCtrl.m_ushOffset>>1])) == NOERROR)
			g_FileCtrl.m_ushOffset += ushByte;
		return;
	}
	g_FileCtrl.m_ushOffset = 0;
	g_FileCtrl.m_ushState = FILE_IDLE;
}
void FILE_Idle_Func(void)
{
	U16 ushID = 0;
	if(g_FileCtrl.m_Requst.all == 0)
		return;
	while(ushID < PARA_FILE_NUM)
	{
		if((g_FileCtrl.m_Requst.all & (1<<ushID)) != 0)
		{
			g_FileCtrl.m_ushState = (ushID+1);
			g_FileCtrl.m_ushOffset = 0;
			return;
		}
		ushID++;
	}
	g_FileCtrl.m_Requst.all = 0;
}
void FILE_Default_Func(void)
{
	U32* pData;
	U16 ushByte;
	U16 i = 0;
	U16 ushAddress = FILE_BASE_ADDRESS;		//文件基地址
	U16 ushID = g_FileCtrl.m_ushState-1;
	if(ushID >= PARA_FILE_NUM)
	{
		MemSet(&g_FileCtrl,0,wordof(g_FileCtrl));
		return;
	}
	while(i <= ushID)
	{
		pData = (U32*)g_FileInfoTable[i].m_pData;
		ushByte = (U16)g_FileInfoTable[i].m_ulWords;
		ushByte <<= 1;
		if(i == ushID)
			break;
		i++;
		ushAddress += ushByte;
		ushAddress += byteof(U32);	//校验和位置
	}
	ushAddress += g_FileCtrl.m_ushOffset;
	if(g_FileCtrl.m_ushOffset < ushByte)
	{
		ushByte -= g_FileCtrl.m_ushOffset;
		if(ushByte > byteof(U32))
			ushByte = byteof(U32);
		if(AT24CXX_Write(ushAddress,ushByte,&pData[g_FileCtrl.m_ushOffset>>2])!= NOERROR)
			return;
		g_FileCtrl.m_ushOffset += ushByte;
	}
	else
	{
		U32 ulCheckSum = FILE_CheckSum(pData,ushByte);
		if(AT24CXX_Write(ushAddress,byteof(ulCheckSum),&ulCheckSum)!= NOERROR)
			return;
		g_FileCtrl.m_ushOffset = 0;
		g_FileCtrl.m_Requst.all &= (~(1<<ushID));
		g_FileCtrl.m_ushState = FILE_IDLE;
	}
}
void FILE_Module(void)
{
	if(g_FileCtrl.m_ushState == FILE_UNINIT)
		g_SystemState.bit.InitPara = 0;  
	else
		g_SystemState.bit.InitPara = 1;  
	switch(g_FileCtrl.m_ushState)
	{
		case FILE_UNINIT:
			FILE_Uninit_Func();
			break;
		case FILE_WRITE:
			FILE_Write_Func();
			break;
		case FILE_IDLE:
			FILE_Idle_Func();
			break;
		default:
			FILE_Default_Func();
			break;
	}
}
/****************************************************************************/
U16 FILE_GetStateEx(U16 ushPID,U16* pBuffer)
{
	U16 ushWord = 0;
	if(ushPID != AL_FILE_PID_CTRL)
		return 0;
	ushWord = wordof(g_FileCtrl);
	MemCpy(pBuffer,(&g_FileCtrl),ushWord);
	return ushWord;
}

U16 FILE_FunctionEx(U16 ushFID,U16* pBuffer,U16 ushWords)
{
	switch(ushFID)
	{
		case AL_FILE_FID_UPDATE:
		{
			FileUpdate_p pReq = (FileUpdate_p)pBuffer;
			if(ushWords != AL_FILE_FID_UPDATE_WORD)
				return BAD_COMMAND_LENGTH;
			pReq->bit.rsvd = 0;
			g_FileCtrl.m_Requst.all |= pReq->all;
			return NOERROR;
		}
		case AL_FILE_FID_WRITE:
		{
			FileWritePara_p pPara = (FileWritePara_p)pBuffer;
			U16* pData = (&pBuffer[wordof(FileWritePara_t)]);
			if(ushWords != AL_FILE_FID_WRITE_WORD(pPara))
				return BAD_COMMAND_LENGTH;
			return FILE_StartWrite(pPara,pData);
		}
	}
	return BAD_NO_FUNCTION;
}
