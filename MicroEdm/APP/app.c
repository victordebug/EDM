#include "app.h"
#include "systick.h"
#include "uart.h"
#include "includes.h"
#include "GPIO.h"
#include "Timer.h"
#include <stdio.h>
#include <math.h>
#include "fsmc.h"
#include "eeprom_24lc16b.h"
#include "voltage.h"
#include "ADC.h" 
#include "edm.h"
#include "data_analy.h"
#include "i2c.h"







U32 g_MS = 0;
u16 system_state = 0x00;


void mark_system_is_run(u16 mark_comm)
{
	if ((mark_comm & SYSTEM_IS_RUN) == SYSTEM_IS_RUN)
	{
		system_state |= SYSTEM_IS_RUN;
	}else 
	{
		system_state &= ~SYSTEM_IS_RUN;
	}

	if ((mark_comm & SYSTEM_IS_ERROR) == SYSTEM_IS_ERROR)
	{
		system_state |= SYSTEM_IS_ERROR;
	}else 
	{
		system_state &= ~SYSTEM_IS_ERROR;
	}

	if ((mark_comm & SYSTEM_IS_WORK) == SYSTEM_IS_WORK)
	{
		system_state |= SYSTEM_IS_WORK;
	}else 
	{
		system_state &= ~SYSTEM_IS_WORK;
	}


}


void Task_Comm(void * pArg)
{
   INT8U ret = 0;
	ret = OSTaskCreate(Task_Led,(void *)0,
			&led_task_stk[LED_TASK_STK_SIZE-1], LED_TASK_PRIO);
	if (ret != 0)
	{
		 printf("����Task_Led����ʧ��\r\n");
	}

	ret = OSTaskCreate(Task_Motor_Find_zero,(void *)0,
			&motor_find_zero_task_stk[MOTOR_FIND_ZERO_TASK_STK_SIZE-1], MOTOR_FIND_ZERO_PRIO);
	if (ret != 0)
	{
		 printf("����Task_Motor_Find_zero����ʧ��\r\n");
	}

	ret = OSTaskCreate(Task_Main,(void *)0,
			&main_task_stk[MAIN_TASK_STK_SIZE-1], MAIN_TASK_PRIO);
	if (ret != 0)
	{
		 printf("����Task_Main����ʧ��\r\n");
	}

	Uart_Thread();
}



void Task_Main(void * pArg)
{

	Z_MOTOR_MOVETO_ANALYSIS z_motor_analy;
	z_motor_analy.ID = 0;
	z_motor_analy.Dir = ANALY_Z_MOTOR_DIR_NEG;
	z_motor_analy.Unit = 0;
	z_motor_analy.A    = 1;
	z_motor_analy.V    = 5;
	z_motor_analy.Pos  = 350;

	z_motor_moveTo(&z_motor_analy);

	
	while (1)
	{
	  /*  printf("curMp:\r\n");
		printf("MpL:0x%0x\r\n", fpga_read(ADDR_Z0_CUR_MP_L));
		printf("MpH:0x%0x\r\n", fpga_read(ADDR_Z0_CUR_MP_H));

		printf("curV:\r\n");
		printf("VL:0x%0x\r\n", fpga_read(ADDR_Z0_CUR_V_L));
		printf("VH:0x%0x\r\n", fpga_read(ADDR_Z0_CUR_V_H));

		OSTimeDlyHMSM(0,0,1,0);*/

		u8 txt_buf[] = {"0x12345"};
		u8 buf_size = sizeof(txt_buf);
		u8 m_read_buf[8] = {0};
		char m_read_cBuf;

		EEPROM_24LC16B_WritePage(0x11 ,(u8 *)txt_buf);
		OSTimeDlyHMSM(0,0,1,0);
		
		EEPROM_24LC16B_ReadBuf(0x11, (u8 *)m_read_buf, buf_size);
		printf("read--->%s\r\n", m_read_buf);
		OSTimeDlyHMSM(0,0,1,0);

		printf("juge-->%d\r\n", (m_read_buf == "        0x12345"));

/*
		EEPROM_24LC16B_WriteByte(0x30, 'c');
		OSTimeDlyHMSM(0,0,1,0);

		m_read_cBuf = EEPROM_24LC16B_ReadByte(0x30);
		printf("read--->%c\r\n", m_read_cBuf);
		OSTimeDlyHMSM(0,0,1,0);
*/

	}
}

void Task_Led(void * pArg)
{
	
	while (1)
	{

		//�����⵽����������˶�������ϵͳ����״̬
		if((fpga_read(ADDR_Z0_MOTOR_STATUS)&0x1 == 1) || (fpga_read(ADDR_Z1_MOTOR_STATUS)&0x1 == 1) ||
			(fpga_read(ADDR_Z2_MOTOR_STATUS)&0x1 == 1) || (fpga_read(ADDR_Z3_MOTOR_STATUS)&0x1 == 1))
		{
			system_state |= SYSTEM_IS_WORK;
		}else
		{
			system_state &= ~SYSTEM_IS_WORK;;
		}


		
		if (system_state & SYSTEM_IS_RUN)
		{
			GPIO_SetBits(GPIOD,PD12_LED_ERROR);
			
			OSTimeDlyHMSM(0,0,0,100);
			if (system_state & SYSTEM_IS_WORK)  GPIO_ResetBits(GPIOD,PD13_LED_WORK);
			GPIO_ResetBits(GPIOD,PD11_LED_RUN);
			OSTimeDlyHMSM(0,0,0,100);
			if (system_state & SYSTEM_IS_WORK) GPIO_SetBits(GPIOD,PD13_LED_WORK);
			GPIO_SetBits(GPIOD,PD11_LED_RUN);

		}else if (system_state & SYSTEM_IS_ERROR)
		{
			GPIO_SetBits(GPIOD,PD11_LED_RUN);
			GPIO_SetBits(GPIOD,PD13_LED_WORK);
			
			OSTimeDlyHMSM(0,0,0,100);
			GPIO_ResetBits(GPIOD,PD12_LED_ERROR);
			GPIO_ResetBits(GPIOG,PG4_BEEP);
			OSTimeDlyHMSM(0,0,0,100);
			GPIO_SetBits(GPIOD,PD12_LED_ERROR);
			GPIO_SetBits(GPIOG,PG4_BEEP);
		}

	}
}
