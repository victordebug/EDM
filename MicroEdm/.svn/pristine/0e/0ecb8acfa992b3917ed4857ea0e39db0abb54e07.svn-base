#ifndef DAC_7611UB_H_20190115
#define DAC_7611UB_H_20190115

/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含DAC的初始化和驱动
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
#include "stm32f10x.h"
#include "gpio.h"


/*IO操作*/
#define HV_CS_H()            GPIO_SetBits(GPIOC,PC15_HV_CS)
#define HV_CS_L()		     GPIO_ResetBits(GPIOC,PC15_HV_CS)

#define HV_CLK_H()           GPIO_SetBits(GPIOC,PC14_HV_CLK)
#define HV_CLK_L()		     GPIO_ResetBits(GPIOC,PC14_HV_CLK)

#define HV_SDI_H()           GPIO_SetBits(GPIOC,PC13_HV_SDI)
#define HV_SDI_L()		     GPIO_ResetBits(GPIOC,PC13_HV_SDI)

#define HV_LD_H()            GPIO_SetBits(GPIOC,PC3_HV_LD)
#define HV_LD_L()		     GPIO_ResetBits(GPIOC,PC3_HV_LD)

#define HV_CLR_H()           GPIO_SetBits(GPIOC,PC2_HV_CLR)
#define HV_CLR_L()		     GPIO_ResetBits(GPIOC,PC2_HV_CLR)


/*开关*/
#define HV_ENA_H()           GPIO_SetBits(GPIOC,PC1_HV_ENA)
#define HV_ENA_L()		     GPIO_ResetBits(GPIOC,PC1_HV_ENA)


#define BIT_7611UB           12

#define HV_ON                0
#define HV_OFF  			 1


void dac_7611ub_config_init(void);

void dac_7611ub_trans(u32 vol);



/*放电电压的开关*/
void hv_enable(u8 en);








#endif


