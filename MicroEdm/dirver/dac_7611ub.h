#ifndef DAC_7611UB_H_20190115
#define DAC_7611UB_H_20190115

/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ����DAC�ĳ�ʼ��������
* ��ǰ�汾��
* �� �ߣ�henry
* ������ڣ�2019�� �� ��
*
* �޸ļ�¼1���޸���ʷ��¼�������޸����ڡ��޸��߼��޸�����
* �޸����ڣ�
* �� �� �ţ�
* �� �� �ˣ�
* �޸����ݣ�
**********************************************************************/
#include "stm32f10x.h"
#include "gpio.h"


/*IO����*/
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


/*����*/
#define HV_ENA_H()           GPIO_SetBits(GPIOC,PC1_HV_ENA)
#define HV_ENA_L()		     GPIO_ResetBits(GPIOC,PC1_HV_ENA)


#define BIT_7611UB           12

#define HV_ON                0
#define HV_OFF  			 1


void dac_7611ub_config_init(void);

void dac_7611ub_trans(u32 vol);



/*�ŵ��ѹ�Ŀ���*/
void hv_enable(u8 en);








#endif


