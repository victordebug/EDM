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
#define ID_DEVICE_NUM       0
#define ID_CRAWL_SPEED      1

//����ģ��ĵ�ַ,4�ı���
#define ADDR_DEVICE_NUM     0x00
#define ADDR_CRAWL_SPEED    0x04



//�����汾��Ϣ
typedef struct para_manage
{
	u16 para_verion;     //�����汾
	u16 para_num;        //��������
	u16 para_len;        //�������ȣ��ֽڣ�
}PARA_MANAGE;


//���ݽ����ṹ��
typedef struct fileSystem_analy
{
	u16 userCtrlData;		//����λ
	u32 userData;           
}FILE_SYSTEM_ANALY;


typedef struct EEPROM_data
{
	u32 device_num;          //�豸���к�
	u32 uint_Motor;          //�����ʼ��λ
	u32 crawlSpeed_Motor;    //Z���������ٶ�
	u32 lowSpeed_Motor;      //���٣����ڵ��Ѱ����λʱ
	u32 highSpeed_Motor;     //���٣����ڵ������λ����׳�ʼλ��
	u32 acc_Motor;           //���ٶ�
}EEPROM_DATA;
	
extern EEPROM_DATA *eeprom_data;


//�ļ�ϵͳ��ʼ������EEPROM���ݶ�ȡ������
u16 fileSystem_Init(void);




//�ļ�ϵͳ��������
u16 fileSystem_set(FILE_SYSTEM_ANALY *analy_data);



//��ȡEEPROM����
u16 fileSystem_get(EEPROM_DATA* data_get);



//�����ļ�����
u16 fileConfig_update(EEPROM_DATA* data_get);


//�����汾��Ϣ�Ļ�ȡ
u16 paraConfig_GetStateEx(u16 ushPID,u16* pBuffer);

















#endif

