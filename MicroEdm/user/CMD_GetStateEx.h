#ifndef __CMD_GETSTATEEX_H__
#define __CMD_GETSTATEEX_H__

#include "stm32f10x.h"
#define CMD_GETSTATE_EX						  0xC0D0
#define CMD_GETSTATE_EX_BYTE				sizeof(CMD_GetStateEx_t)
#define CMD_RETURNSTATE_EX					0xC0D1

typedef struct
{  
	u16 m_ushMID;	//�ں�ģ����
	u16 m_ushPID;	//ģ�����Ա��
} CMD_GetStateEx_t;
typedef CMD_GetStateEx_t* CMD_GetStateEx_p;

/*
 * ��ģ��MID������[DDD]_List.h�ļ��У����������ʽ����:
 * #define [DDD]_MID_[MMM]		0x[XX]00	//ģ������
 * ��ģ��PID������ģ���Ӧͷ�ļ��У����������ʽ����:
 * #define [DDD]_[MMM]_PID_[PPP]		0x[YYYY]		//ģ����������
 * #define [DDD]_[MMM]_PID_[PPP]_WORD	wordof([TTT])	//ģ�������ֽڳ���
 * ����ģ�麯��ԭ�Ͷ�������
 * U16 [MMM]_GetStateEx(U16 ushPID,U16* pBuffer);
 */
extern u16 ParseGetState_Ex(void);

#endif //__CMD_GETSTATEEX_H__
