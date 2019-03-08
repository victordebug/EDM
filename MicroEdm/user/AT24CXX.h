#ifndef AT24CXX_H_20190308
#define AT24CXX_H_20190308

#include "stdtypes.h"
#include "gpio.h"
#include "Timer.h"

/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：本文件主要包含固件版本的说明和一些公用的宏定义和结构体
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

//允许设备列表
#define AT24C01		128
#define AT24C02		256
#define AT24C04		512
#define AT24C08		1024
#define AT24C16		2048



//选择实际设备
#define AT24CXX_BYTE		AT24C16
#define AT24CXX_MASK		(AT24CXX_BYTE-1)

#if (AT24CXX_BYTE < AT24C04)
#define AT24CXX_PAGE_BYTE		8
#else
#define AT24CXX_PAGE_BYTE		16
#endif
#define AT24CXX_PAGE_MASK		(AT24CXX_PAGE_BYTE-1)

//设备地址
#define AT24CXX_ADDRESS			0xA0
#define AT24CXX_BLOCK_MASK		(0x700 & AT24CXX_MASK)
#define AT24CXX_BLOCK(addr)		(((addr) & AT24CXX_BLOCK_MASK) >> 7)	


//操作命令
#define	AT24CXX_READ(addr)	(AT24CXX_ADDRESS | AT24CXX_BLOCK(addr) | 0x01)
#define	AT24CXX_WRITE(addr)	(AT24CXX_ADDRESS | AT24CXX_BLOCK(addr))




//IO操作
#define AT24CXX_SET_SCLK_LOW		GPIO_ResetBits(GPIOA,PA6_EEPROM_SCLK)
#define AT24CXX_SET_SCLK_HIGH		GPIO_SetBits(GPIOA,PA6_EEPROM_SCLK)
#define AT24CXX_SET_SDA_LOW			GPIO_SetBits(GPIOA,PA4_EEPROM_SDA_WRITE) 
#define AT24CXX_SET_SDA_HIGH		GPIO_ResetBits(GPIOA,PA4_EEPROM_SDA_WRITE)
#define AT24CXX_SDA_IS_HIGH			(GPIO_ReadInputDataBit(GPIOA ,PA5_EEPROM_SDA_READ) != 0)

#define AT24CXX_TSU_STA				DELAY_MS(5)
#define AT24CXX_THD_STA				DELAY_MS(5)
#define AT24CXX_TSU_STO				DELAY_MS(5)
#define AT24CXX_TLOW				DELAY_MS(5)
#define AT24CXX_THIGH				DELAY_MS(5)




extern U16 AT24CXX_Write(U16 ushAddress, U16 ushByte, U32* pSrc);// 写入多个字节
extern U16 AT24CXX_Read(U16 ushAddress, U16 ushByte, U32* pDes);	// 读取多个字节





#endif

