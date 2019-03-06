#ifndef EEPROM_24LC16B_H_20190115
#define EEPROM_24LC16B_H_20190115

#include "stm32f10x.h"
/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ����EEPROM�ĳ�ʼ������д�ӿ�
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
/*
�洢����Ϣ��
�豸��һЩ�̶���Ϣ
��λ�����͵Ĳ���
һЩ���ϵı�־λ

*/





#define MAXROM_24LC16B    (2048)

#define ADDR_24LC16B      (0xA0)


void EEPROM_24LC16B_Init(void);
u8 EEPROM_24LC16B_ReadByte(u16 addr);
void EEPROM_24LC16B_WriteByte(u16 addr, u8 data);
void EEPROM_24LC16B_ReadBuf(u16 addr, u8 *buf, u16 len);
void EEPROM_24LC16B_WriteBuf(u16 addr, u8 *buf, u16 len);
void EEPROM_24LC16B_WritePage(u16 addr, u8 *buf);

u16 update_config(void);

void get_config(void);


#endif





















