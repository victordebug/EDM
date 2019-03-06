#ifndef __APP_H
#define __APP_H

#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif



/*******************设置任务优先级*******************/
#define MAIN_TASK_PRIO        2
#define LED_TASK_PRIO         3
#define MOTOR_FIND_ZERO_PRIO  4
#define EDM_TASK_PRIO         5
/************设置栈大小(单位 OS_STK ) ************/
#define LED_TASK_STK_SIZE              0x50
#define MAIN_TASK_STK_SIZE             0x0FFF
#define MOTOR_FIND_ZERO_TASK_STK_SIZE  0x0FFF 
#define EDM_TASK_STK_SIZE              0x0FFF

OS_STK led_task_stk[LED_TASK_STK_SIZE]; //定义栈
OS_STK main_task_stk[MAIN_TASK_STK_SIZE]; //定义栈
OS_STK motor_find_zero_task_stk[MOTOR_FIND_ZERO_TASK_STK_SIZE]; 
OS_STK EDM_task_stk[EDM_TASK_STK_SIZE];





#define MAX_TIME_FIND_ZERO      60    //寻位最长时间


extern u16 system_state;


void mark_system_is_run(u16 mark_comm);

void Task_Comm(void * pArg);	
void Task_Main(void * pArg);	
void Task_Led(void * pArg);

	
#ifdef __cplusplus
}
#endif

#endif

