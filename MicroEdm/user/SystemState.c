#include "SystemState.h"
#include "ADC.h"

TP_System_t g_System;

CU16 m_ushSysName[16] = 
{//SPIDER V1.1.0
	0x5053,0x4449,0x5245,0x5620,
	0x2E30,0x2E30,0x0030,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
};

Version_t m_KernelVersion = 
{
	PRINARY_VERSION,
	SUBLEVEL_VERSION,
	PATCHLEVEL_VERSION,
	RELEASELEVEL_VERSION
};



void SYS_Init(void)
{
	MemSet(&g_System, 0, sizeof(g_System));
}

u16 GetSystemName(u16 *pBuffer)
{
	u16 ushWord = wordof(m_ushSysName);
	MemCpy(pBuffer, &m_ushSysName, ushWord);
	return ushWord;
}

u16 GetSystemState(u16* pBuffer)
{
	TP_System_p pState = (TP_System_p)pBuffer;
	pState->m_ushMState = 0;
	pState->m_ushSState = 0;

	
	return TP_SYS_PID_SYSTEM_WORD;
}

u16 GetKernelVersion(u16 *pBuffer)
{
	u16 ushWord = wordof(m_KernelVersion);
	MemCpy(pBuffer, &m_KernelVersion, ushWord);
	return ushWord;
}

u16 SYS_GetStateEx(u16 ushPID,u16* pBuffer)
{
	u16 ushWord = 0;
	switch(ushPID)
	{
		case TP_SYS_PID_SYSTEM:
			ushWord = GetSystemState(pBuffer);
			break;
		case TP_SYS_PID_NAME:
			ushWord = GetSystemName(pBuffer);
			break;
		case TP_SYS_PID_VERSION:
			ushWord = GetKernelVersion(pBuffer);
			break;
	}
	return ushWord;
}




