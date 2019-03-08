#ifndef AT24CXX_H_20190308
#define AT24CXX_H_20190308

#include "stdtypes.h"
#include "gpio.h"
#include "Timer.h"

/*********************************************************************
* ��Ȩ���� (C)2018, �������ڿƼ����޹�˾
* 
* ����ժҪ�����ļ���Ҫ�����̼��汾��˵����һЩ���õĺ궨��ͽṹ��
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

//�����豸�б�
#define AT24C01		128
#define AT24C02		256
#define AT24C04		512
#define AT24C08		1024
#define AT24C16		2048



//ѡ��ʵ���豸
#define AT24CXX_BYTE		AT24C16
#define AT24CXX_MASK		(AT24CXX_BYTE-1)

#if (AT24CXX_BYTE < AT24C04)
#define AT24CXX_PAGE_BYTE		8
#else
#define AT24CXX_PAGE_BYTE		16
#endif
#define AT24CXX_PAGE_MASK		(AT24CXX_PAGE_BYTE-1)

//�豸��ַ
#define AT24CXX_ADDRESS			0xA0
#define AT24CXX_BLOCK_MASK		(0x700 & AT24CXX_MASK)
#define AT24CXX_BLOCK(addr)		(((addr) & AT24CXX_BLOCK_MASK) >> 7)	


//��������
#define	AT24CXX_READ(addr)	(AT24CXX_ADDRESS | AT24CXX_BLOCK(addr) | 0x01)
#define	AT24CXX_WRITE(addr)	(AT24CXX_ADDRESS | AT24CXX_BLOCK(addr))




//IO����
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




extern U16 AT24CXX_Write(U16 ushAddress, U16 ushByte, U32* pSrc);// д�����ֽ�
extern U16 AT24CXX_Read(U16 ushAddress, U16 ushByte, U32* pDes);	// ��ȡ����ֽ�





#endif

