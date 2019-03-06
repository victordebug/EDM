#include "dac_7611ub.h"

void dac_7611ub_config_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = PC1_HV_ENA | PC2_HV_CLR |PC3_HV_LD |
									PC13_HV_SDI | PC14_HV_CLK |PC15_HV_CS;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��

	HV_LD_L();
	HV_CS_H();
	HV_CLK_H();
	HV_SDI_L();

}

static void dac_delay(u32 ms)
{
	while(ms --);
}

void dac_7611ub_clock(void)
{
	HV_CLK_L();
	dac_delay(10);
	HV_CLK_H();
	dac_delay(10);
}

void dac_7611ub_trans(u32 vol)
{
	u8 i = 0;
	u32 j = 0;


//CLR����
	HV_CLR_L();
	dac_delay(10);
	HV_CLR_H();

//ת��
	vol <<= 4;
	HV_LD_H();
	HV_CS_L();
	HV_CLK_L();
	dac_delay(10);
	for (i=0; i<BIT_7611UB; i++)
	{
		j = vol;
		HV_CLK_L();
		if (j&0x8000)
		{
			HV_SDI_H();
		}else
		{
			HV_SDI_L();
		}
		dac_delay(10);
		HV_CLK_H();
		dac_delay(10);
		vol <<= 1;
	}

	HV_CLK_H();
	dac_delay(5);
	HV_CS_H();
	dac_delay(10);
	HV_LD_L();
	dac_delay(10);
	HV_LD_H();
}


void hv_enable(u8 en)
{
	if (en == HV_ON)
	{
		HV_ENA_H();
	}else if (en == HV_OFF)
	{
		HV_ENA_L();
	}
}






