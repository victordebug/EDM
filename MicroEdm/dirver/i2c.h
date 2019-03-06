#ifndef I2C_H_20190115
#define I2C_H_20190115


#include "gpio.h"
/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ����GPIOģ��ʵ��I2C�ĳ�ʼ��������
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
/*IO����*/
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

