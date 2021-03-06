#ifndef EDM_H_20190115
#define EDM_H_20190115

#include "stm32f10x.h"
#include "motor.h"
/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含两种电火花产生的接口
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
//脉冲放电编号
#define ID_PWM_0       0
#define ID_PWM_1       1
#define ID_PWM_2       2
#define ID_PWM_3       3

//RC放电编号
#define ID_RC_0        0
#define ID_RC_1        1
#define ID_RC_2        2
#define ID_RC_3        3


//使能位
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



/*RC放电*/
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
	u16 command;		//命令
	u16 short_threshold;   //短路阈值
}RC_EDM;


typedef struct analy_rc_edm
{
	u16 ID;   
	u16 short_threshold;   //短路阈值	
}ANALY_RC_EDM;

typedef struct stat_rc_edm
{
	u16 id;
	u16 pulse_stat;		//放电状态
	u16 count;  		//脉冲计数
}STAT_RC_EDM;


/*脉冲放电*/
typedef struct pwm_edm
{
	u16 ID;	//编号
	u16 command_pwm; //使能控制命令寄存器
	u16 period_pwm;	 //脉冲周期
	u16 duty_pwm;	 //脉冲占空比
	u16 deadZone_pwm;//脉冲死区
	u16 pulse_command; //脉冲放电命令
	u16 pulse_threshold; // 脉冲放电短路阈值
}PWD_EDM;

typedef struct analy_pwm_edm
{
	u16 ID;	//编号
	u16 period_pwm;	 //脉冲周期
	u16 duty_pwm;	 //脉冲占空比
	u16 deadZone_pwm;//脉冲死区	
	u16 pulse_threshold; // 脉冲放电短路阈值	
}ANALY_PWM_EDM;



typedef struct anlay_EDM
{
	DC_MOTOR_ANALYSIS        EDM_dc_motor;        //旋转电机
	ANALY_RC_EDM             EDM_rc;              //RC放电配置
	ANALY_PWM_EDM            EDM_pwm;             //脉冲放电配置
	u16                      option_EDM;          //放电方式选择
	u16                      ID_z_motor;		  //Z轴电机编号
	u16                      uint;                //单位
	u16                      ACC_high;            //高速加速度
	u16                      ACC_low;             //低速加速度
	u16                      HV;
	u32                      speed_high;          //高速
	u32                      speed_low;           //低速
	u32                      high_H0;             //电机打孔初始位置
	u32                      high_Hd;             //工件厚度
	u32                      high_Hp;             //超出高度
}ANALY_EDM;




u16 edm_rc(ANALY_RC_EDM *analy_rc);

u16 edm_rc_stop(ANALY_RC_EDM *analy_rc);

u16 edm_pwm(ANALY_PWM_EDM *analy_pwm);

u16 edm_pwm_stop(ANALY_PWM_EDM *analy_pwm);




#endif


