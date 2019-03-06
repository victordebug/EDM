#ifndef _SYSTEMSTATE_H
#define _SYSTEMSTATE_H

#include "stm32f10x.h"
#include "stdtypes.h"
#include "MemoryCopy.h"

#define VERSION_RELEASE		0			//Release?
#define VERSION_ALEPH		1			//Aleph?
#define VERSION_BETA(n)		(2+(n)-1)	//Beta?

typedef struct Version
{
	u16	Primary:	8;	//????
	u16	Sub:		8;	//?????
	u16	Patch:		8;	//???????
	u16	Release:	8;	//???????
} Version_bit;
typedef union
{
	Version_bit bit;
	u32 all;
}Version_t;
typedef Version_t* Version_p;

#define PRINARY_VERSION				1
#define SUBLEVEL_VERSION			1
#define PATCHLEVEL_VERSION			2
#define RELEASELEVEL_VERSION		VERSION_RELEASE



typedef struct
	{

		U32 Temp0:				4;
		U32 Temp1:				4;
		U32 Temp2:				4;
		U32 Temp3:				4;
		U32 rsvd:					16;
	}TP_SysState_Flag_bit;
typedef union
{
	TP_SysState_Flag_bit bit;
	U32 all;
} TP_SysState_Flag_t;
typedef struct
{
	U16 m_ushMState;
	U16 m_ushSState;
	TP_SysState_Flag_t m_ulFlag;
} TP_System_t;
typedef TP_System_t* TP_System_p;
extern TP_System_t g_System;
 
void Sys_GetSystemState(u32* pBuffer );

#define TP_SYS_PID_SYSTEM			0x0000
#define TP_SYS_PID_SYSTEM_WORD		wordof(TP_System_t)

#define TP_SYS_PID_NAME				0x0004
#define TP_SYS_PID_NAME_WORD		wordof(U16)*16

#define TP_SYS_PID_VERSION			0x0008
#define TP_SYS_PID_VERSION_WORD		wordof(Version_t)



extern void SYS_Init(void);
extern u16 SYS_GetStateEx(u16 ushPID,u16* pBuffer);

#endif /* _SYSTEMSTATE_H */
