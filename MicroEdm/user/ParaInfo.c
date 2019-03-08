// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   paraInfo.c
//
// TITLE:  Read and write parameters.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

///###########################################################################


#include "ParaInfo.h"
#include "Frame.h"
#include "config.h"

ParaInfo_t g_ParaInfo = 
{
	PARA_VERSION,
	PARA_FILE_NUM,
	(MAX_DATA_BYTE>>1),
	((MAX_DATA_BYTE>>1) - wordof(CmdFileInfo_t)),
};
ParaCtrl_t g_ParaCtrl;

void PARA_Init(void)
{
	MemSet((&g_ParaCtrl),0,wordof(g_ParaCtrl));
}

U16 PARA_Read(CmdFileInfo_p pPara,U16* pData)
{
	U16* pSrc;
	if(pPara->Id >= PARA_READFILE_NUM)
		return EPARA_ID;
	if(pPara->Offset >= g_FileInfoTable[pPara->Id].m_ulWords)
		return EPARA_OFFSET;
	pSrc = g_FileInfoTable[pPara->Id].m_pData;
	if(pPara->Words == 1)
	{
		pData[0] = pSrc[pPara->Offset];
		pData[1] = 0;
		return 2;
	}
	if((pPara->Offset & 0x0001) != 0)
		return EPARA_OFFSET;
	if(((pPara->Words & 0x0001) != 0)
			||(pPara->Words == 0)
			||(pPara->Words > (g_FileInfoTable[pPara->Id].m_ulWords - pPara->Offset))
			||(pPara->Words > g_ParaInfo.m_ushMaxReadWords))
		return EPARA_WORDS;
	MemCpy(pData,&pSrc[pPara->Offset],pPara->Words);
	
	return (pPara->Words);
}

U16 PARA_Write(CmdFileInfo_p pPara,U16* pData)
{
	U16* pDest;
	if(pPara->Id >= PARA_WRITEFILE_NUM)
		return EPARA_ID;
	if(pPara->Offset >= g_FileInfoTable[pPara->Id].m_ulWords)
		return EPARA_OFFSET;
	pDest = g_FileInfoTable[pPara->Id].m_pData;
	if(pPara->Words == 1)
	{
		pDest[pPara->Offset] = pData[0];
		return NOERROR;
	}
	if((pPara->Offset & 0x0001) != 0)
		return EPARA_OFFSET;
	if(((pPara->Words & 0x0001) != 0)
			||(pPara->Words == 0)
			||(pPara->Words > (g_FileInfoTable[pPara->Id].m_ulWords - pPara->Offset))
			||(pPara->Words > g_ParaInfo.m_ushMaxWriteWords))
		return EPARA_WORDS;
	MemCpy(&pDest[pPara->Offset],pData,pPara->Words);
	g_ParaCtrl.m_Update.all |= (1<<pPara->Id);
	return NOERROR;
}

U16 PARA_GetStateEx(U16 ushPID,U16* pBuffer)
{
	U16 ushWords;
	U16* pSrc;
	switch(ushPID)
	{
		case PARA_PID_CTRL:
		{
			pSrc = (U16*)(&g_ParaCtrl);
			ushWords = wordof(g_ParaCtrl);
			break;
		}	
		case PARA_PID_WORD:
		{
			U16 i;
			U32* pTable = (U32*) pBuffer;
			ushWords = 0;
			for(i = 0 ; i < PARA_FILE_NUM ; i++)
			{
				pTable[i] = g_FileInfoTable[i].m_ulWords;
				ushWords += wordof(U32);
			}
			return ushWords;
		}
		case PARA_PID_INFO:
		{
			pSrc = (U16*)(&g_ParaInfo);
			ushWords = wordof(g_ParaInfo);
			break;
		}
		default:
			return 0;
	}
	MemCpy(pBuffer,pSrc,ushWords);
	return ushWords;
}
