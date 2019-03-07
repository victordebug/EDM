#include "motor.h"
#include "fsmc.h"
#include "stdtypes.h"
#include "data_analy.h"
#include "command.h"
#include "Cmd.h"
#include "app.h"

//步进电机本地定义
ZSCAN_MOTOR *zscan_motor0 = NULL;
ZSCAN_MOTOR *zscan_motor1 = NULL;
ZSCAN_MOTOR *zscan_motor2 = NULL;
ZSCAN_MOTOR *zscan_motor3 = NULL;

//旋转电机本地定义
DC_MOTOR *dc_motor0 = NULL;
DC_MOTOR *dc_motor1 = NULL;
DC_MOTOR *dc_motor2 = NULL;
DC_MOTOR *dc_motor3 = NULL;


u32 DC_motor_rotat2bit(u16 speed);	/*将转速转换成寄存器值*/
S32 ZSCAN_MM2MP(DB32 dbMM);
DB32 ZSCAN_MP2MM(S32 lMP);
Q27 ZSCAN_MMpS2SV(DB32 dbMMpS);
U32 ZSCAN_MMpS2SVV(DB32 dbMMpSS);
u32 ZScan_CalcSubMP(U32 ulV, U32 ulA, U32 ulPos, u16 dir, u32 mp_cur);

OS_STK motor_find_zero_task_stk[MOTOR_FIND_ZERO_TASK_STK_SIZE]; 



/*电机初始化*/
u16 motor_init(void)
{
	//Z轴电机
	fpga_write(ADDR_Z0_MOTOR_CTRL, 0x00);	    //命令寄存器全置零
	fpga_write(ADDR_Z0_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零
	fpga_write(ADDR_Z0_MOTOR_DIAG, (0x01<<2));	//诊断寄存器的setMaxMP
	fpga_write(ADDR_Z0_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零

	fpga_write(ADDR_Z1_MOTOR_CTRL, 0x00);	    //命令寄存器全置零
	fpga_write(ADDR_Z1_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零
	fpga_write(ADDR_Z1_MOTOR_DIAG, (0x01<<2));	//诊断寄存器的setMaxMP
	fpga_write(ADDR_Z1_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零

	fpga_write(ADDR_Z2_MOTOR_CTRL, 0x00);	    //命令寄存器全置零
	fpga_write(ADDR_Z2_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零
	fpga_write(ADDR_Z2_MOTOR_DIAG, (0x01<<2));	//诊断寄存器的setMaxMP
	fpga_write(ADDR_Z2_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零

	fpga_write(ADDR_Z3_MOTOR_CTRL, 0x00);	    //命令寄存器全置零
	fpga_write(ADDR_Z3_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零
	fpga_write(ADDR_Z3_MOTOR_DIAG, (0x01<<2));	//诊断寄存器的setMaxMP
	fpga_write(ADDR_Z3_MOTOR_DIAG, 0x00);	    //诊断寄存器全置零


	//旋转电机
	fpga_write(ADDR_COMMAND_DCMOTION, (0x1<<4));//使能旋转电机
	fpga_write(ADDR_Z0_DCMOTOR_K, 0);
	fpga_write(ADDR_Z1_DCMOTOR_K, 0);
	fpga_write(ADDR_Z2_DCMOTOR_K, 0);
	fpga_write(ADDR_Z3_DCMOTOR_K, 0);

	return 0;
}


//旋转电机移动
u16 DC_motor_move(DC_MOTOR_ANALYSIS *motor_analy)
{
	u32 flag_speed = 0;
	DC_MOTOR *dc_motor = NULL;

	if(UART_R_LENGTH != CMD_DC_MOTOR_MOVE_BYTE)
		return ECMD_LENGTH;
	
	flag_speed = DC_motor_rotat2bit(motor_analy->speed_motor);

	dc_motor->ID_motor = motor_analy->ID;
	dc_motor->EN_motor = EN_MOTOR_ON;
	dc_motor->speed_motor = flag_speed;
	FPGA_dcMotor_set(dc_motor);

	return NOERROR;
}



//旋转电机停止移动
u16 DC_motor_stop(DC_MOTOR_ANALYSIS *motor_analy)
{
	DC_MOTOR *dc_motor = NULL;
	
	if(UART_R_LENGTH != CMD_DC_MOTOR_STOP_BYTE)
		return ECMD_LENGTH;

	dc_motor->ID_motor = motor_analy->ID;
	dc_motor->EN_motor = EN_MOTOR_ON;
	dc_motor->speed_motor = 0;
	FPGA_dcMotor_set(dc_motor);

	return NOERROR;

}


u16 z_motor_en(Z_MOTOR_EN_ANALY *m_date)
{

	if (m_date->z0_EN)
	{
		fpga_write(ADDR_Z0_MOTOR_CTRL, 0xF3);	//命令寄存器驱动器使能和脉冲使能
	}else 
	{
		fpga_write(ADDR_Z0_MOTOR_CTRL, 0x00);	//命令寄存器驱动器使能和脉冲使能
	}

	if (m_date->z1_EN)
	{
		fpga_write(ADDR_Z1_MOTOR_CTRL, 0xF3);	//命令寄存器驱动器使能和脉冲使能
	}else 
	{
		fpga_write(ADDR_Z1_MOTOR_CTRL, 0x00);	//命令寄存器驱动器使能和脉冲使能
	}

	if (m_date->z2_EN)
	{
		fpga_write(ADDR_Z2_MOTOR_CTRL, 0xF3);	//命令寄存器驱动器使能和脉冲使能
	}else 
	{
		fpga_write(ADDR_Z2_MOTOR_CTRL, 0x00);	//命令寄存器驱动器使能和脉冲使能
	}

	if (m_date->z3_EN)
	{
		fpga_write(ADDR_Z3_MOTOR_CTRL, 0xF3);	//命令寄存器驱动器使能和脉冲使能
	}else 
	{
		fpga_write(ADDR_Z3_MOTOR_CTRL, 0x00);	//命令寄存器驱动器使能和脉冲使能
	}
	
	return NOERROR;
}


//无目的地的移动模式
//将数据换算成寄存器的数据
u16 z_motor_move(Z_MOTOR_MOVE_ANALYSIS_p z_motor_analy)
{
	Z_MOTOR z_motor;    //设置指针
	u32 m_acc_speed = 0;   //加速度
	u32 m_speed = 0;    //速度
	u32 motor_crawl_speed = 0; //爬行速度

	//数据转换
	m_acc_speed = ZSCAN_MMpS2SVV(z_motor_analy->A);
	m_speed = ZSCAN_MMpS2SV(z_motor_analy->V);
	
	//清零操作
	z_motor.motor_control.all_command = 0x00;
	z_motor.motor_diagnose.all_diag   = 0x00;
	z_motor.crawl_speed_H             = 0x00;
	z_motor.crawl_speed_L             = 0x00;
	z_motor.location_speedCut_H       = 0x00;
	z_motor.location_speedCut_L       = 0x00;
	z_motor.location_target_H         = 0x00;
	z_motor.location_target_L         = 0x00;
	
	
	//启动位清零
	z_motor.ID_motor = z_motor_analy->ID;
	z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_START_MOVE;
	FPGA_zmotor_set(&z_motor);
	
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_SERVO_ENABLE;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_PULSE_ENABLE;
	if (z_motor_analy->Dir == ANALY_Z_MOTOR_DIR_MAX)
	{
		z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_DIR;
	}else if (z_motor_analy->Dir == ANALY_Z_MOTOR_DIR_MIN)
	{
		z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_DIR;
	}
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_START_MOVE;
	z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_STOP;
	z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_SUB;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_TRIGGER_ADD;
	z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_POS;

	z_motor.acc_motor = (u16)(m_acc_speed & 0xffff);
	z_motor.speed_L = (u16)(m_speed & 0xffff);
	z_motor.speed_H = (u16)(m_speed >> 16) & 0xff;

	FPGA_zmotor_set(&z_motor);	

	return NOERROR;
}

//有目的地的移动模式
u16 z_motor_moveTo(Z_MOTOR_MOVETO_ANALYSIS *z_motor_analy)
{
	Z_MOTOR z_motor;    //设置变量
	Z_MOTOR_STAT z_stat_motor;  //状态变量
	u32 m_acc_speed = 0;   //加速度
	u32 m_speed = 0;    //速度
	u32 m_location_targ = 0;   //目标位置
	u32 map_cur = 0;   //当前位置
	u32 m_s = 0;   //总距离
	u32 m_location_sub = 0;  //减速位置
	u32 motor_crawl_speed = 0; //爬行速度

	
	//获取当前位置
	ZMOTOR_STAT_GetStateEx(z_motor_analy->ID ,(u16*)&z_stat_motor);
	map_cur = z_stat_motor.location_cur_L & 0xffff;
	map_cur += (z_stat_motor.location_cur_H << 16) & 0xff0000;

	//数据转换
	m_acc_speed = ZSCAN_MMpS2SVV(z_motor_analy->A);
	m_speed = ZSCAN_MMpS2SV(z_motor_analy->V);
	m_location_targ = ZSCAN_MM2MP(z_motor_analy->Pos);
	motor_crawl_speed = ZSCAN_MMpS2SV(MOTOR_CRAWL_SPEED);
	
	//启动位清零
	z_motor.ID_motor = z_motor_analy->ID;
	z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_START_MOVE;
	FPGA_zmotor_set(&z_motor);
	
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_SERVO_ENABLE;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_PULSE_ENABLE;
	if (z_motor_analy->Dir== ANALY_Z_MOTOR_DIR_MAX)
	{
		z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_DIR;
		m_s = m_location_targ + map_cur;
	}else if (z_motor_analy->Dir == ANALY_Z_MOTOR_DIR_MIN)
	{
		z_motor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_DIR;
		m_s = map_cur - m_location_targ;
	}

	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_START_MOVE;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_TRIGGER_STOP;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_TRIGGER_SUB;
	z_motor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_TRIGGER_ADD;

	m_location_sub = ZScan_CalcSubMP(m_speed, m_acc_speed, m_s, z_motor_analy->Dir, map_cur); //计算出减速位置

	z_motor.acc_motor = (u16)(m_acc_speed & 0xffff);
	z_motor.crawl_speed_L = (u16)motor_crawl_speed & 0xffff;
	z_motor.crawl_speed_H = (u16)(motor_crawl_speed >> 16) & 0xff;
	z_motor.speed_L = (u16)(m_speed & 0xffff);
	z_motor.speed_H = (u16)(m_speed >> 16) & 0xff;
	z_motor.location_speedCut_L = m_location_sub & 0xffff;
	z_motor.location_speedCut_H = (u16)(m_location_sub >> 16) & 0x3f;
	z_motor.location_target_L = (u16)(m_location_targ & 0xffff);
	z_motor.location_target_H = (u16)(m_location_targ >> 16) & 0x3f;

	FPGA_zmotor_set(&z_motor);	

	return NOERROR;
}


/*步进电机停止*/
/*
	立即停止
	减速停止
*/
u16 z_motor_stop(Z_MOTOR_STOP_ANALYSIS *z_stop_analy)
{
	Z_MOTOR m_zMotor;

	//clean
	
	
	m_zMotor.ID_motor = z_stop_analy->ID;
	if (z_stop_analy->stop_mode == STOP_TO_ZERO_VALUE)  //减速停止
	{
		m_zMotor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_STOP;
		m_zMotor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_SUB;
		m_zMotor.speed_L = 0;
		m_zMotor.speed_H = 0;
	}else if (z_stop_analy->stop_mode == STOP_AT_ONCE)   //立即停止
	{
		m_zMotor.motor_diagnose.all_diag &= ~BIT_Z_MOTOR_DIGN_E_STOP;
		FPGA_zmotor_set(&m_zMotor);  //先将诊断寄存器的紧急停止位清零

		m_zMotor.motor_diagnose.all_diag |= BIT_Z_MOTOR_DIGN_E_STOP;
		m_zMotor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_SERVO_ENABLE;
		m_zMotor.motor_control.all_command |= BIT_Z_MOTOR_CTRL_PULSE_ENABLE;
		m_zMotor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_STOP;
		m_zMotor.motor_control.all_command &= ~BIT_Z_MOTOR_CTRL_TRIGGER_SUB;
		m_zMotor.speed_L = 0;
		m_zMotor.speed_H = 0;
	}

	FPGA_zmotor_set(&m_zMotor);
	return NOERROR;
}

/**
*电机如果不在零位，慢速向零位移动，直到零位传感器响应停止
*如果运行相当长时间还没有响应零位，立即停止并警示
*
*电机如果在零位，先向最大限位移动一定距离，再向零位移动，
*直到触碰零位传感器，这样做是为了减小误差
*/
u16 z_motor_findZero(u16 ID_motor)
{
	u16 index_motor = 0;
	u16 i = 0;
	Z_MOTOR_STOP_ANALYSIS z_stop_analy;
	Z_MOTOR_MOVE_ANALYSIS m_z_motor_analy;

	if (ID_motor >= ID_Z_MOTOR_MAX)
		return 1;

	index_motor = 0x01<<ID_motor;

	if ((fpga_read(ADDR_SENSOR) & index_motor) == index_motor)//如果电机在零位
	{
		//电机向正方向移动
		m_z_motor_analy.ID = ID_motor;
		m_z_motor_analy.Dir = ANALY_Z_MOTOR_DIR_MAX;
		m_z_motor_analy.Unit = 0;
		m_z_motor_analy.A = 1;
		m_z_motor_analy.V = 3;
		z_motor_move(&m_z_motor_analy);	

		sleep(3); //运动3秒

		//电机停止
		z_stop_analy.ID = ID_motor;
		z_stop_analy.stop_mode = STOP_AT_ONCE;
		z_motor_stop(&z_stop_analy);
	}

	//电机向反方向移动
	m_z_motor_analy.Dir = ANALY_Z_MOTOR_DIR_MIN;
	m_z_motor_analy.V = 1;
	z_motor_move(&m_z_motor_analy); 


	while((fpga_read(ADDR_SENSOR) & index_motor) != index_motor)  //直到触碰零位传感器再退出
	{
		if (i++ > MAX_TIME_FIND_ZERO) //超时处理
		{
			mark_system_is_run(SYSTEM_IS_ERROR);
			break;
		}
		sleep(1);
	}

	z_motor_stop(&z_stop_analy);

}


u32 DC_motor_rotat2bit(u16 speed)
{
	u32 flag_bit_speed = speed;
	flag_bit_speed *= DC_MAX_BIT;
	flag_bit_speed /= DC_MAX_SPEED;

	return flag_bit_speed;
}

S32 ZSCAN_MM2MP(DB32 dbMM)
{
	dbMM += 0.000001;
	return (S32)(dbMM * ZSCAN_DEBUG_PARAM);
}

DB32 ZSCAN_MP2MM(S32 lMP)
{
	DB32 dbMP = (DB32)lMP;
	return (DB32)(dbMP / ZSCAN_DEBUG_PARAM);
}

Q27 ZSCAN_MMpS2SV(DB32 dbMMpS)
{
	Q27 q27SV;
	DB32 dbRet = (ZSCAN_MPACC_MAX / 10.0E6);
	DB32 dbSV = dbMMpS;
	dbSV *= ZSCAN_DEBUG_PARAM;
	dbSV *= dbRet;
	q27SV = (Q27)dbSV;
	return q27SV;
}

U32 ZSCAN_MMpS2SVV(DB32 dbMMpSS)
{
	DB32 dbSVV;
	dbSVV = dbMMpSS*(65536);
	dbSVV /= (10.0E6);
	dbSVV *= ZSCAN_DEBUG_PARAM;
	dbSVV /= (10.0E6);
	dbSVV *= ZSCAN_MPACC_MAX;
	dbSVV *= 2;

	return (U32)dbSVV;
}


u32 ZScan_CalcAddS(u32 ulSV, u32 ulSA)
{
	DB32 ADDSV;
	ADDSV = ulSV * (65536);
	ADDSV /= ulSA;
	ADDSV /=(536870912);
	ADDSV *= ulSV;
	ADDSV /=2;
	ADDSV *= 2;

	return (u32)ADDSV;	
}


u32 ZScan_CalcSubMP(U32 ulV, U32 ulA, U32 ulPos, u16 dir, u32 mp_cur)
{
	u32 ulAddS;
	
	ulAddS = ZScan_CalcAddS(ulV, ulA);
	if(dir == ANALY_Z_MOTOR_DIR_MAX)
	{
		if ( ulAddS >= (ulPos - mp_cur) / 2 )
		{
			if((ulPos - mp_cur) == 1)
				return ulPos;
			return ((ulPos + mp_cur)/ 2);
		}
		else
			return (ulPos - ulAddS);
	}
	else
	{
		if ( ulAddS >= (mp_cur - ulPos) / 2 )
			return ((mp_cur + ulPos)/ 2);
		else
			return (ulPos + ulAddS);
	}
}



void Task_Motor_Find_zero(void * pArg)
{
	int i = 0;
	while (1)
	{
		for (i=0; i<ID_Z_MOTOR_MAX; i++)   //将四个Z轴电机归零
		{
			z_motor_findZero(i);
			OSTimeDlyHMSM(0,0,1,0);
		}
		
		OSTaskSuspend(MOTOR_FIND_ZERO_PRIO);
	}
}


