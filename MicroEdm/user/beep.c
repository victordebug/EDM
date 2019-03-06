#include "beep.h"
#include "stm32f10x.h"
#include "gpio.h"
#include "stdtypes.h"
#include "Command.h"

void beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = 	PG4_BEEP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}



u16 beep_ctrl(BEEP_ANALY *m_beep_ctrl)
{
	if (m_beep_ctrl->EN == BEEP_ON)
	{
		GPIO_SetBits(GPIOG,PG4_BEEP);
	}else
	{
		GPIO_ResetBits(GPIOG,PG4_BEEP);
	}

	return NOERROR;
}




