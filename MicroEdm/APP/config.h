#ifndef CONFIG_H_20190115
#define CONFIG_H_20190115


#include "AT24CXX.h"
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

#ifndef NULL 
#define NULL 0 
#endif 


/*״̬��*/
#define SYSTEM_IS_RUN                               (0x01<<0) //ϵͳ�������У�������״̬
#define SYSTEM_IS_ERROR                             (0x01<<1) //ϵͳ����
#define SYSTEM_IS_WORK                              (0x01<<2) //ϵͳ����״̬

#define SIZE_U32_DATA                                sizeof(u32)



/*�����汾��Ϣ*/
#define PARA_VERSION    PARA_VERSION_V001
#define MAX_DATA_BYTE   AT24CXX_BYTE

























#endif




