// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   ParaInfo_V100.h
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################

#ifndef __PARA_INFO_V100_H__
#define __PARA_INFO_V100_H__
#include "stdtypes.h"

#define PARA_VERSION_V001     001   


typedef struct
{
	Uint16 	SN:					1;    //产品序列号
 	Uint16  ErrLog:				1;    //设备故障日志
	Uint16  MotorConfig:		1;    //电机初始化数据
	Uint16	rsvd:				13;
} FileUpdate_bit;

#define MAT_FILE_NUM				3

#define MAT_FILE_SN				    0
#define	MAT_FILE_LOG				1
#define MAT_FILE_MOTOR              2

#define PARA_FILE_NUM		MAT_FILE_NUM


#define PARA_READFILE_NUM			MAT_FILE_NUM
#define PARA_WRITEFILE_NUM			(MAT_FILE_NUM-1)

#endif
