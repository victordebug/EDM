#ifndef __CMD_H__
#define __CMD_H__

#include "Frame.h"


/********************************************************************/
#define ECMD_BASE						0x8000
/*通讯命令可能返回的通用错误码*/
#define ECMD_COMMAND					0x0001	//非法的命令码
#define ECMD_VALUE						0x0002	//错误的命令数据
#define ECMD_LENGTH						0x0004	//错误的命令数据长度
#define ECMD_TIME_OUT					0x0008	//接收命令超时
#define ECMD_FRAME_HEAD					0x0010	//错误的帧头
#define ECMD_FRAME_ADDRESS				0x0020	//错误的帧地址
#define ECMD_FRAME_LENGTH				0x0040	//错误的帧长度
#define ECMD_FRAME_CHECKSUM				0x0080	//错误的帧校验和
#define ECMD_NO_FUNCTION				0x00F0	//没有定义的接口
#define ECMD_UNKNOWN					0x00FF	//未知错误

/*通讯通用命令*/
/********************************************************************/
#define CMD_DEBUG						0xC002
#define CMD_DEBUG_BYTE			sizeof(u32)

#define CMD_ACK							0x01C0	//正确应答
#define CMD_ACK_BYTE					0

#define CMD_RETRY						0x01C1 	//错误应答
#define CMD_RETRY_BYTE			sizeof(u32)

#endif /*_COMMAND_H_*/


