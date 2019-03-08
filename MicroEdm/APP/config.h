#ifndef CONFIG_H_20190115
#define CONFIG_H_20190115


#include "AT24CXX.h"
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

#ifndef NULL 
#define NULL 0 
#endif 


/*状态灯*/
#define SYSTEM_IS_RUN                               (0x01<<0) //系统正常运行（待机）状态
#define SYSTEM_IS_ERROR                             (0x01<<1) //系统故障
#define SYSTEM_IS_WORK                              (0x01<<2) //系统工作状态

#define SIZE_U32_DATA                                sizeof(u32)



/*参数版本信息*/
#define PARA_VERSION    PARA_VERSION_V001
#define MAX_DATA_BYTE   AT24CXX_BYTE

























#endif




