#ifndef BEEP_H_20190115
#define BEEP_H_20190115

#include "stm32f10x.h"
/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含蜂鸣器的初始化和驱动
* 当前版本：
* 作 者：henry
* 完成日期：2019年 月 日
*
* 修改记录1：修改历史记录，包括修改日期、修改者及修改内容
* 修改日期：
* 版 本 号：
* 修 改 人：
* 修改内容：
**********************************************************************/


#define BEEP_ON   0x0000
#define BEEP_OFF  0x0001

typedef struct beep_analy
{
	u16 EN;
}BEEP_ANALY;


void beep_init(void);

u16 beep_ctrl(BEEP_ANALY *m_beep_ctrl);

#endif



