#include "includes.h"

void Systick_Init(void)
{
	//RCC_ClocksTypeDef RCC_ClocksStructure;
	//RCC_GetClocksFreq(&RCC_ClocksStructure);
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);
}

void BSP_init(void)
{
	 Systick_Init();
}
