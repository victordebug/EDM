#ifndef VOLTAGE_H_20190115
#define VOLTAGE_H_20190115


#include "stm32f10x.h"
/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ������ѹ�Ĳ����Ϳ��ƽӿ�
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

#define KIND_MOTOR_VG        0
#define KIND_EDM_VG		     1
#define VG_VALUE_WORD        wordof(u16)

#define NUM_TRANSFOR         10

typedef struct hv_switch
{
	u16 EN;
	u16 vol;
}HV_SWITCH_ANALY;

void voltage_init(void);

u16 VOL_GetStateEx(u16 pid, u16* pState);


u16 H_voltage_switch(HV_SWITCH_ANALY *m_data);










#endif

