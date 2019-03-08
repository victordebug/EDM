// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   CMD_ParaFile.c
//
// TITLE:  Memory read and write parameters
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################

#include "Cmd.h"
#include "Uart.h"
#include "FileSystem.h"
#include "CMD_ParaFile.h"
#include "Command.h"

U16 ParseGetParaFile(void)
{
	U16* pData = UART_S_DATA_P;
	CmdFileInfo_p pReadData = (CmdFileInfo_p)UART_R_DATA_P;

	if(UART_R_LENGTH != CMD_GETPARA_BYTE)
		return ECMD_LENGTH;
    
	g_ParaCtrl.m_ushResult = PARA_Read(pReadData,pData);
	if(g_ParaCtrl.m_ushResult > CMD_AL_RETURNPARA_WORD)
		return g_ParaCtrl.m_ushResult;

	//g_Uart.m_pPort->m_ushSentByte = (g_ParaCtrl.m_ushResult<<1);   //command out by henry
	g_ParaCtrl.m_ushResult = NOERROR;
	UART_S_CMD = CMD_RETURNPARA;

	return g_ParaCtrl.m_ushResult;
}
U16 ParseSetParaFile(void)
{
	U16* pData = (U16*)UART_R_DATAn_P(wordof(CmdFileInfo_t));
	CmdFileInfo_p pWriteData = (CmdFileInfo_p)UART_R_DATA_P;

	if((UART_R_LENGTH > CMD_AL_SETPARA_BYTE) ||(UART_R_LENGTH < CMD_SETPARA_MIN_BYTE))
		return ECMD_LENGTH;

	if(g_FileCtrl.m_Requst.all != 0)
		return EFILE_WRITING;
	g_ParaCtrl.m_ushResult = PARA_Write(pWriteData,pData);

	return g_ParaCtrl.m_ushResult;
}
U16 ParseFileUpdate(void)
{
	FileUpdate_p pUpdate = (FileUpdate_p)UART_R_DATA_P;
	if(UART_R_LENGTH != CMD_FILEUPDATE_BYTE)
		return ECMD_LENGTH;

	return FILE_Update(pUpdate->all);
}
