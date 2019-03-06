#include "led.h"
#include "gpio.h"
#include "stm32f10x.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = 	PD11_LED_RUN | PD12_LED_ERROR | PD13_LED_WORK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_SetBits(GPIOD,PD11_LED_RUN);
	GPIO_SetBits(GPIOD,PD12_LED_ERROR);
	GPIO_SetBits(GPIOD,PD13_LED_WORK);

}



void led_SWITCH(u8 led_kind,     u8 led_switch)
{
	if (led_kind == LED_RUN)
	{
		if (led_switch == LED_ON)
		{
			GPIO_ResetBits(GPIOD,PD11_LED_RUN);
		}else if (led_switch == LED_OFF)
		{
			GPIO_SetBits(GPIOD,PD11_LED_RUN);
		}
	}else if (led_kind == LED_ERROR)
	{
		if (led_switch == LED_ON)
		{
			GPIO_ResetBits(GPIOD,PD12_LED_ERROR);
		}else if (led_switch == LED_OFF)
		{
			GPIO_SetBits(GPIOD,PD12_LED_ERROR);
		}

	}else if (led_kind == LED_WORK)
	{
		if (led_switch == LED_ON)
		{
			GPIO_ResetBits(GPIOD,PD13_LED_WORK);
		}else if (led_switch == LED_OFF)
		{
			GPIO_SetBits(GPIOD,PD13_LED_WORK);
		}

	}
}














