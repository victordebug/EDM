#ifndef __CAIR_LIST_H__
#define __CAIR_LIST_H__
/*
 * 文件用于定义各个模块的MID，MID按照下面格式定义:
 * #define [DDD]_MID_[MMM]		0x[XX]00	//模块名称
 */

#define CAIR_MID_SYSTEM					0x0000		//system state module
#define CAIR_MID_SPRAY					0x1000		//
#define CAIR_MID_ADC					0x2000		//
#define CAIR_MID_SI						0xC000		//system indication module
#define CAIR_MID_VOLTAGE                0x3000
#define CAIR_MID_MOTOR_SENSOR           0x3002
#define CAIA_MID_FPGA_VERSION           0x3004
#define CAIA_MID_RC_STAT                0x3006
#define CAIA_MID_PWM_STAT               0x3008
#define CAIA_MID_Z_MOTOR_STAT           0x300a


#endif /* _CAPM_LIST_H */

