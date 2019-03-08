#ifndef FILE_SYSTEM_H_20190304
#define FILE_SYSTEM_H_20190304

#include "stm32f10x.h"
/*********************************************************************
* 版权所有 (C)2018, 杭州数腾科技有限公司
* 
* 内容摘要：主要包含文件系统的初始化、配置和更新
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

//存储数据模块的数量
#define NUM_FILE            1     


//各个模块的识别ID
#define ID_DEVICE_NUM       0
#define ID_CRAWL_SPEED      1

//各个模块的地址,4的倍数
#define ADDR_DEVICE_NUM     0x00
#define ADDR_CRAWL_SPEED    0x04



//参数版本信息
typedef struct para_manage
{
	u16 para_verion;     //参数版本
	u16 para_num;        //参数数量
	u16 para_len;        //参数长度（字节）
}PARA_MANAGE;


//数据解析结构体
typedef struct fileSystem_analy
{
	u16 userCtrlData;		//控制位
	u32 userData;           
}FILE_SYSTEM_ANALY;


typedef struct EEPROM_data
{
	u32 device_num;          //设备序列号
	u32 uint_Motor;          //电机初始单位
	u32 crawlSpeed_Motor;    //Z轴电机爬行速度
	u32 lowSpeed_Motor;      //低速，用于电机寻找零位时
	u32 highSpeed_Motor;     //高速，用于电机从零位到打孔初始位置
	u32 acc_Motor;           //加速度
}EEPROM_DATA;
	
extern EEPROM_DATA *eeprom_data;


//文件系统初始化，将EEPROM数据读取到本地
u16 fileSystem_Init(void);




//文件系统更新配置
u16 fileSystem_set(FILE_SYSTEM_ANALY *analy_data);



//获取EEPROM数据
u16 fileSystem_get(EEPROM_DATA* data_get);



//配置文件更新
u16 fileConfig_update(EEPROM_DATA* data_get);


//参数版本信息的获取
u16 paraConfig_GetStateEx(u16 ushPID,u16* pBuffer);

















#endif

