//this file deal with tick driver

#include "systick.h"
#include "misc.h"
#include <stdio.h>

uint32_t gTickCount = 0;
TIME_MODE gTimeMode = TIME_MODE_MS;
uint32_t sysTickInit(TIME_MODE mode)
{
	RCC_ClocksTypeDef RCC_ClocksStructure;
	RCC_GetClocksFreq(&RCC_ClocksStructure);
	SysTick_Config(RCC_ClocksStructure.SYSCLK_Frequency / mode);
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//NVIC_SetPriority(SysTick_IRQn, 0x0); 
	gTimeMode = mode;
	return 0;
}
uint64_t sysGetTickCounter(void)
{
	return gTickCount;
}

void sysTickHandle(void)
{
	  gTickCount++;
}
void sleep(uint64_t sTimeout)
{
	 uint32_t old = sysGetTickCounter();
	while (sysGetTickCounter() - old < sTimeout *gTimeMode);
}
void msleep(uint64_t mTimeout)
{
	uint32_t old = sysGetTickCounter();
	while (sysGetTickCounter() - old < mTimeout *(gTimeMode/1000));
}

TIME_MODE GetTimeMode(void)
{
	  return gTimeMode;
}
