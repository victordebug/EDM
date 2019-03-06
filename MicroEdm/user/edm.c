#include "edm.h"
#include "fsmc.h"
#include "Command.h"
#include "stdtypes.h"
#include "motor.h"




u16 en_pwm_command = 0;  
u16 en_rc_command = 0;

/*RC*/
u16 edm_rc(ANALY_RC_EDM *analy_rc)
{
	RC_EDM *m_rc_edm = NULL;
		
	switch (analy_rc->ID)
	{
		case ID_RC_0:
			en_rc_command |= EN_RC_0;
			break;
		case ID_RC_1:
			en_rc_command |= EN_RC_1;
			break;
		case ID_RC_2:
			en_rc_command |= EN_RC_2;
			break;
		case ID_RC_3:
			en_rc_command |= EN_RC_3;
			break;
		default :
			break;
	}

	m_rc_edm->ID = analy_rc->ID;
	m_rc_edm->command = en_rc_command;
	m_rc_edm->short_threshold = analy_rc->short_threshold;

	FPGA_EDM_RC(m_rc_edm);

	return NOERROR;
}

u16 edm_rc_stop(ANALY_RC_EDM *analy_rc)
{
	RC_EDM *m_rc_edm = NULL;
	
	switch (analy_rc->ID)
	{
		case ID_RC_0:
			en_rc_command &= ~EN_RC_0;
			break;
		case ID_RC_1:
			en_rc_command &= ~EN_RC_1;
			break;
		case ID_RC_2:
			en_rc_command &= ~EN_RC_2;
			break;
		case ID_RC_3:
			en_rc_command &= ~EN_RC_3;
			break;
		default :
			break;
	}

	m_rc_edm->ID = analy_rc->ID;
	m_rc_edm->command = en_rc_command;

	FPGA_EDM_RC(m_rc_edm);

	return NOERROR;

}


/*����ŵ�*/
u16 edm_pwm(ANALY_PWM_EDM *analy_pwm)
{
	PWD_EDM *pwm_edm;

	switch (analy_pwm->ID)
	{
		case ID_PWM_0:
			en_pwm_command |= EN_PWM_0;
			break;
		case ID_PWM_1:
			en_pwm_command |= EN_PWM_1;
			break;
		case ID_PWM_2:
			en_pwm_command |= EN_PWM_2;
			break;
		case ID_PWM_3:
			en_pwm_command |= EN_PWM_3;
			break;
		default :
			break;
	}
	pwm_edm->command_pwm = en_pwm_command;
	pwm_edm->pulse_command = en_pwm_command;
	pwm_edm->period_pwm = analy_pwm->period_pwm;
	pwm_edm->duty_pwm = analy_pwm->duty_pwm;
	pwm_edm->deadZone_pwm = analy_pwm->deadZone_pwm;
	pwm_edm->ID = analy_pwm->ID;
	pwm_edm->pulse_threshold = analy_pwm->pulse_threshold;

	FPGA_EDM_PWM(pwm_edm);

	return NOERROR;
}


u16 edm_pwm_stop(ANALY_PWM_EDM *analy_pwm)
{
	PWD_EDM *pwm_edm;
	
	switch (analy_pwm->ID)
	{
		case ID_PWM_0:
			en_pwm_command &= ~EN_PWM_0;
			break;
		case ID_PWM_1:
			en_pwm_command &= ~EN_PWM_1;
			break;
		case ID_PWM_2:
			en_pwm_command &= ~EN_PWM_2;
			break;
		case ID_PWM_3:
			en_pwm_command &= ~EN_PWM_3;
			break;
		default :
			break;
	}
	pwm_edm->command_pwm = en_pwm_command;
	pwm_edm->pulse_command = en_pwm_command;
	pwm_edm->ID = analy_pwm->ID;

	FPGA_EDM_PWM(pwm_edm);

	return NOERROR;
}






/*
*����һ���ŵ��ܽӿڣ��ŵ������̣߳�
*��λ��ͨ���·������������ת������ŵ�ѡ��Ȳ�������λ��ʵ�������ŵ�����
*/
void Task_EDM(void * pArg)
{
	Z_MOTOR_STOP_ANALYSIS    z_stop_analy;
	Z_MOTOR_MOVE_ANALYSIS    m_z_motor_move_analy;
	Z_MOTOR_MOVETO_ANALYSIS  m_z_motor_moveTo_analy;
	DC_MOTOR                 m_dc_motor;
	HV_SWITCH_ANALY          m_HV_switch;

	while (1)
	{
		//���Ѱ��
		z_motor_findZero(Data_analy_EDM->ID_z_motor);
		OSTimeDlyHMSM(0,0,1,0);
	
		//��������ƶ�����ʼ��ȫλ��H0
		m_z_motor_moveTo_analy.ID  = Data_analy_EDM->ID_z_motor;
		m_z_motor_moveTo_analy.Dir = ANALY_Z_MOTOR_DIR_MAX;
		m_z_motor_moveTo_analy.A   = Data_analy_EDM->ACC_high;
		m_z_motor_moveTo_analy.V   = Data_analy_EDM->speed_high;
		m_z_motor_moveTo_analy.Pos = Data_analy_EDM->high_H0;
		z_motor_moveTo(&m_z_motor_moveTo_analy);
		OSTimeDlyHMSM(0,0,1,0);
		
		//��ת�������ת��
		DC_motor_move(&Data_analy_EDM->EDM_dc_motor);
		
		//�ŵ�����
		if (Data_analy_EDM->option_EDM == OPTION_EDM_RC)
		{
			edm_rc(&Data_analy_EDM->EDM_rc);
		}else if (Data_analy_EDM->option_EDM == OPTION_EDM_PWM)
		{
			edm_pwm(&Data_analy_EDM->EDM_pwm);
		}
		OSTimeDlyHMSM(0,0,1,0);
		
		//�ŵ�ģ�鿪�ش�
		m_HV_switch.EN = HV_ON;
		m_HV_switch.vol = Data_analy_EDM->HV;
		H_voltage_switch(&m_HV_switch);
		OSTimeDlyHMSM(0,0,1,0);
		
		//�����������������������ƶ�
		m_z_motor_move_analy.ID  = Data_analy_EDM->ID_z_motor;
		m_z_motor_move_analy.Dir = ANALY_Z_MOTOR_DIR_MAX;
		m_z_motor_move_analy.A   = Data_analy_EDM->ACC_low;
		m_z_motor_move_analy.V   = Data_analy_EDM->speed_low;
		z_motor_move(&m_z_motor_move_analy);
		

		//
		
		//�������ָ������,���ֹͣ�����س�ʼ�߶�
		
		//�����⵽��·�����ֹͣ�����˸߶�Df




		//�������
		OSTaskSuspend(EDM_TASK_PRIO);
	}

}
