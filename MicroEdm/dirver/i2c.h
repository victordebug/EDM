#ifndef I2C_H_20190115
#define I2C_H_20190115


#include "gpio.h"
/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含GPIO模拟实现I2C的初始化和驱动
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
/*IO操作*/
#define I2C_SCL_H()   GPIO_SetBits(GPIOA,PA6_EEPROM_SCLK)
#define I2C_SCL_L()   GPIO_ResetBits(GPIOA,PA6_EEPROM_SCLK)
#define I2C_SDA_H()   GPIO_ResetBits(GPIOA,PA4_EEPROM_SDA_WRITE)
#define I2C_SDA_L()   GPIO_SetBits(GPIOA,PA4_EEPROM_SDA_WRITE) 


#define READ_SDA      GPIO_ReadInputDataBit(GPIOA ,PA5_EEPROM_SDA_READ)


void my_I2C_Init(void);            			 
void my_I2C_Start(void);				
void my_I2C_Stop(void);	  			
void my_I2C_Send_Byte(u8 txd);			
u8 my_I2C_Read_Byte(unsigned char ack);
u8 my_I2C_Wait_Ack(void); 				
void my_I2C_Ack(void);					
void my_I2C_NAck(void);				



#endif


