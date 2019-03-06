#ifndef __CMD_GETSTATEEX_H__
#define __CMD_GETSTATEEX_H__

#include "stm32f10x.h"
#define CMD_GETSTATE_EX						  0xC0D0
#define CMD_GETSTATE_EX_BYTE				sizeof(CMD_GetStateEx_t)
#define CMD_RETURNSTATE_EX					0xC0D1

typedef struct
{  
	u16 m_ushMID;	//内核模块编号
	u16 m_ushPID;	//模块属性编号
} CMD_GetStateEx_t;
typedef CMD_GetStateEx_t* CMD_GetStateEx_p;

/*
 * 各模块MID定义在[DDD]_List.h文件中，按照下面格式定义:
 * #define [DDD]_MID_[MMM]		0x[XX]00	//模块名称
 * 各模块PID定义在模块对应头文件中，按照下面格式定义:
 * #define [DDD]_[MMM]_PID_[PPP]		0x[YYYY]		//模块属性名称
 * #define [DDD]_[MMM]_PID_[PPP]_WORD	wordof([TTT])	//模块属性字节长度
 * 各个模块函数原型定义如下
 * U16 [MMM]_GetStateEx(U16 ushPID,U16* pBuffer);
 */
extern u16 ParseGetState_Ex(void);

#endif //__CMD_GETSTATEEX_H__
