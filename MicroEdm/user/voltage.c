#include "voltage.h"
#include "ADC.h"
#include "dac_7611ub.h"
#include "Command.h"
#include "stdtypes.h"


#define MOTOR_STANDARD_VG    24
#define EDM_STANDARD_VG      24

#define FULL_SCALE 		     4096				//12-bit resolution 


void voltage_init(void)
{
	ADC1_Init();
	dac_7611ub_config_init();
}


u16 VOL_GetStateEx(u16 pid, u16* pState)
{
	u32 result = 1;
	if (pid == KIND_MOTOR_VG)
	{
		result *= ADC_Value[1];
		result *= (u32)MOTOR_STANDARD_VG;
		result /= (u32)FULL_SCALE;

	}else if (pid == KIND_EDM_VG)
	{
		result *= ADC_Value[0];
		result *= (u32)EDM_STANDARD_VG;
		result /= (u32)FULL_SCALE;
	}
	pState[0] = result;   //result得值一定小于120
	
	return VG_VALUE_WORD;
}


/*
*每次变压分十次完成变压，电压最高目前是80V左右
*
*/
u16 H_voltage_switch(HV_SWITCH_ANALY *m_data)
{
	int i = 0;
	float32 count = 0.0;
	float32 grid_volage = 0.0;
	u16 get_vg[2] = 0;

	if (m_data->EN == HV_ON)
	{
		VOL_GetStateEx(KIND_EDM_VG, get_vg);  //获取放电电压

		//计算每次变化的电压值
		grid_volage = m_data->vol - get_vg[0];
		grid_volage /= 10.0;
	
	}else //当关闭的时候，电压先降到0V，再关闭电压阀
	{
		VOL_GetStateEx(KIND_EDM_VG, get_vg);
		grid_volage = get_vg[0] / 10.0;
		grid_volage *= -1;
	}	
	
	count = get_vg[0];
	for (i=0; i<NUM_TRANSFOR; i++)
	{
		count += grid_volage;
		dac_7611ub_trans(count * 1000);
		msleep(100);
	}


	

	hv_enable(m_data->EN);	 //使能放电开关

	return NOERROR;
}




