#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include "stdtypes.h"

 /* Define GPIO Allocation */
#define CHN_NUM					2
#define CHIPSEL_NUM				8
#define CHNSEL_NUM				8

extern u16 ADC_Value[CHN_NUM];
extern u16 ADC_ReadData[CHIPSEL_NUM * CHNSEL_NUM][CHN_NUM];

extern void ADC1_Init(void);
extern void ADC_Module(void);

#define ADCMODE_START  0
#define ADCMODE_END    1


typedef struct
{
	U32 State:				15;
	U32 SingleState:		15;
	U32 Mode:				2;

}ADC_Ctrl_Flag_bit;
typedef union
{
	ADC_Ctrl_Flag_bit bit;
	U32 all;
} ADC_Ctrl_Flag_t;
typedef struct
{
	ADC_Ctrl_Flag_t m_ulFlag;
	U32 m_ulResult;
	U16 m_ushIndex_CHN;
	U16 m_ushIndex_CHIP;
	U16 m_ushAdcValue[CHN_NUM];
} ADC_Ctrl_t;
typedef ADC_Ctrl_t* ADC_Ctrl_p;

#define ADCSTATE_IDLE   0
#define ADCSTATE_S1   1
#define ADCSTATE_S2   2
#define ADCSTATE_S3   3

#define SP_SYS_PID_ADCDATA(i)			(0+i)
#define SP_SYS_PID_ADCDATA0_WORD		wordof(U16)*32

#define SP_SYS_PID_ADCVALUE				0x0100
#define SP_SYS_PID_ADCVALUE_WORD		wordof(U16)*4

#define SP_SYS_PID_CTRL						0x0102
#define SP_SYS_PID_CTRL_WORD				wordof(ADC_Ctrl_t)

extern u16 ADC_GetStateEx(u16 ushPID,u16* pBuffer);

#endif  /* _ADC_H_ */

