#ifndef FILE_SYSTEM_H_20190304
#define FILE_SYSTEM_H_20190304

#include "stm32f10x.h"
/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ����Ҫ�����ļ�ϵͳ�ĳ�ʼ�������ú͸���
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

//�洢����ģ�������
#define NUM_FILE            1     


//����ģ���ʶ��ID
#define ID_DEVICE_NUM       0x01<<0


//����ģ��ĵ�ַ,4�ı���
#define ADDR_DEVICE_NUM     0x00




//���ݽ����ṹ��
typedef struct fileSystem_analy
{
	u16 userCtrlData;		//����λ
	u32 userData;           
}FILE_SYSTEM_ANALY;


typedef struct EEPROM_data
{
	u32 device_num;     //�豸���к�
	u32 crawl_speed;    //Z���������ٶ�
}EEPROM_DATA;



//�ļ�ϵͳ��ʼ������EEPROM���ݶ�ȡ������
u16 fileSystem_Init(void);




//�ļ�ϵͳ��������
u16 fileSystem_update(FILE_SYSTEM_ANALY *analy_data);



//��ȡEEPROM����
u16 fileSystem_get(EEPROM_DATA* data_get);
























#endif

