#ifndef EDM_H_20190115
#define EDM_H_20190115

#include "stm32f10x.h"
#include "motor.h"
/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ�������ֵ�𻨲����Ľӿ�
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
//����ŵ���
#define ID_PWM_0       0
#define ID_PWM_1       1
#define ID_PWM_2       2
#define ID_PWM_3       3

//RC�ŵ���
#define ID_RC_0        0
#define ID_RC_1        1
#define ID_RC_2        2
#define ID_RC_3        3


//ʹ��λ
#define EN_PWM_0       (u16)(0x01<<0)
#define EN_PWM_1       (u16)(0x01<<1)
#define EN_PWM_2       (u16)(0x01<<2)
#define EN_PWM_3       (u16)(0x01<<3)

#define EN_PWM_ON      (u16)(0x0001)
#define EN_PWM_OFF     (u16)(0X0002)


#define EN_RC_0        (u16)(0x01<<0)
#define EN_RC_1        (u16)(0x01<<1)
#define EN_RC_2        (u16)(0x01<<2)
#define EN_RC_3        (u16)(0x01<<3)   

#define EN_RC_ON       (u16)(0x0001)
#define EN_RC_OFF      (u16)(0X0002)

#define RC_STATE_WORD  wordof(RC_STATE)
#define PWM_STATE_WORD wordof(u16)

#define STAT_PWM_0_DISCHARG   (u16)(0x1<<0)
#define STAT_PWM_1_DISCHARG   (u16)(0x1<<1)
#define STAT_PWM_2_DISCHARG   (u16)(0x1<<2)
#define STAT_PWM_3_DISCHARG   (u16)(0x1<<3)
#define STAT_PWM_0_SHORT      (u16)(0x1<<4)
#define STAT_PWM_1_SHORT      (u16)(0x1<<5)
#define STAT_PWM_2_SHORT      (u16)(0x1<<6)
#define STAT_PWM_3_SHORT      (u16)(0x1<<7)


#define STAT_RC_0_ENA         (u16)(0x1<<0)
#define STAT_RC_1_ENA         (u16)(0x1<<1)
#define STAT_RC_2_ENA         (u16)(0x1<<2)
#define STAT_RC_3_ENA         (u16)(0x1<<3)

#define OPTION_EDM_RC          0x0001
#define OPTION_EDM_PWM         0x0002

extern u16 en_pwm_command;



/*RC�ŵ�*/
typedef struct rc_state 
{
	u16 rc_status;
	u16 rc0_count;
	u16 rc1_count;
	u16 rc2_count;
	u16 rc3_count;
}RC_STATE;

typedef struct rc_edm
{
	u16 ID;   
	u16 command;		//����
	u16 short_threshold;   //��·��ֵ
}RC_EDM;


typedef struct analy_rc_edm
{
	u16 ID;   
	u16 short_threshold;   //��·��ֵ	
}ANALY_RC_EDM;

typedef struct stat_rc_edm
{
	u16 id;
	u16 pulse_stat;		//�ŵ�״̬
	u16 count;  		//�������
}STAT_RC_EDM;


/*����ŵ�*/
typedef struct pwm_edm
{
	u16 ID;	//���
	u16 command_pwm; //ʹ�ܿ�������Ĵ���
	u16 period_pwm;	 //��������
	u16 duty_pwm;	 //����ռ�ձ�
	u16 deadZone_pwm;//��������
	u16 pulse_command; //����ŵ�����
	u16 pulse_threshold; // ����ŵ��·��ֵ
}PWD_EDM;

typedef struct analy_pwm_edm
{
	u16 ID;	//���
	u16 period_pwm;	 //��������
	u16 duty_pwm;	 //����ռ�ձ�
	u16 deadZone_pwm;//��������	
	u16 pulse_threshold; // ����ŵ��·��ֵ	
}ANALY_PWM_EDM;



typedef struct anlay_EDM
{
	DC_MOTOR                 EDM_dc_motor;        //��ת���
	ANALY_RC_EDM             EDM_rc;              //RC�ŵ�����
	ANALY_PWM_EDM            EDM_pwm;             //����ŵ�����
	u16                      option_EDM;          //�ŵ緽ʽѡ��
	u16                      ID_z_motor;		  //Z�������
	u16                      uint;                //��λ
	u16                      ACC_high;            //���ټ��ٶ�
	u16                      ACC_low;             //���ټ��ٶ�
	u16                      HV;
	u32                      speed_high;          //����
	u32                      speed_low;           //����
	u32                      high_H0;             //�����׳�ʼλ��
	u32                      high_Hd;             //�������
	u32                      high_Hp;             //�����߶�
}ANALY_EDM;


ANALY_EDM *Data_analy_EDM = NULL;



u16 edm_rc(ANALY_RC_EDM *analy_rc);

u16 edm_rc_stop(ANALY_RC_EDM *analy_rc);

u16 edm_pwm(ANALY_PWM_EDM *analy_pwm);

u16 edm_pwm_stop(ANALY_PWM_EDM *analy_pwm);




#endif

