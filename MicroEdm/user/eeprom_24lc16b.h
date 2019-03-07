#ifndef EEPROM_24LC16B_H_20190115
#define EEPROM_24LC16B_H_20190115

#include "stm32f10x.h"
/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含EEPROM的初始化、读写接口
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
/*
存储的信息：
设备的一些固定信息
上位机发送的参数
一些故障的标志位

*/





#define MAXROM_24LC16B    (2048)

#define MAXLEN_24LC16B    (512)

#define ADDR_24LC16B      (0xA0)


void EEPROM_24LC16B_Init(void);
u8 EEPROM_24LC16B_ReadByte(u16 addr);
void EEPROM_24LC16B_WriteByte(u16 addr, u8 data);
void EEPROM_24LC16B_ReadBuf(u16 addr, u32 *buf, u16 len);
void EEPROM_24LC16B_WriteBuf(u16 addr, u32 *buf, u16 len);
void EEPROM_24LC16B_WritePage(u16 addr, u8 *buf);

u16 update_config(void);

void get_config(void);


#endif






















