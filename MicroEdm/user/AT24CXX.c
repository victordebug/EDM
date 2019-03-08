#include "AT24CXX.h"



void DELAY_MS(u32 time)
{
	u32 i=8*time;
	 while(i--);
}


//д�봮�в�������ʼλ
void AT24CXX_Start(void)
{
//��ʱ״̬ SCLK = X SDA = X 
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_TSU_STO;
	AT24CXX_SET_SDA_LOW;
	AT24CXX_TSU_STA;
//��ʱ״̬ SCK = 1 SDA = 1
 	AT24CXX_SET_SDA_HIGH;
	AT24CXX_THD_STA;
//��ʱ״̬ SCK = 1 SDA = 0
	AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 0 SDA�������ȡ����
}



//д�봮�в�����ֹͣλ
void AT24CXX_Stop(void)
{
//��ʱ״̬ SCK = 0 SDA = X
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_TSU_STO;
	AT24CXX_SET_SDA_HIGH;
	AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = 0
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_TSU_STO;
//��ʱ״̬ SCK = 1 SDA = 0
	AT24CXX_SET_SDA_LOW;
//��ʱ״̬ SCK = 1 SDA = 1
}



//�������ݣ�������ACK��ƽ = 0 �͵�ƽ = 1 �ߵ�ƽ
U16 AT24CXX_WriteData(U16 ushData)
{
	U16 retVal = 0;
	U16 mask = 0x80;
	__enable_irq();
//��������
//��ʱ״̬ SCK = 0 SDA = X
	while(mask != 0)
	{
		if((ushData & mask) == 0)
			AT24CXX_SET_SDA_HIGH;
		else
			AT24CXX_SET_SDA_LOW;
		AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
		AT24CXX_SET_SCLK_HIGH;
		AT24CXX_THIGH;
		mask>>=1;
//��ʱ״̬ SCK = 1 SDA = 0/1
		AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
	}
//���ACK����
//��ʱ״̬ SCK = 0 SDA = 0/1
	AT24CXX_SET_SDA_LOW;
	AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = X,���豸����ACKֵ����
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_THIGH;
//��ʱ״̬ SCK = 1 SDA = X,���豸����ACKֵ����
	if(AT24CXX_SDA_IS_HIGH)
		retVal = 1;
	AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 1
	__disable_irq();

	return retVal;	
}



U16 AT24CXX_WriteData0(U16 ushData)
{
	U16 retVal = 0;
	U16 mask = 0x80;
	__enable_irq();
//��������
//��ʱ״̬ SCK = 0 SDA = X
	while(mask != 0)
	{
		if((ushData & mask) == 0)
			AT24CXX_SET_SDA_HIGH;
		else
			AT24CXX_SET_SDA_LOW;
		AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
		AT24CXX_SET_SCLK_HIGH;
		AT24CXX_THIGH;
		mask>>=1;
//��ʱ״̬ SCK = 1 SDA = 0/1
		AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
	}
//���ACK����
//��ʱ״̬ SCK = 0 SDA = 0/1
	//AT24CXX_SET_SDA_HIGH; //command out by henry
	AT24CXX_SET_SDA_LOW;  //add by henry
	AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = X,���豸����ACKֵ����
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_THIGH;
//��ʱ״̬ SCK = 1 SDA = X,���豸����ACKֵ����
	if(AT24CXX_SDA_IS_HIGH)
		retVal = 1;
	AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 1
	__disable_irq();

	return retVal;	
}


//��ȡ���������ݣ�������ACK��ƽ = 0 �͵�ƽ = 1 �ߵ�ƽ
U16 AT24CXX_ReadData(U16 ushAck)
{
	U16 mask = 0x80;
	U16 Value = 0;
	__enable_irq();
//��ȡ����
//��ʱ״̬ SCK = 0 SDA = X
	//AT24CXX_SET_SDA_LOW;  //command out by henry
	AT24CXX_SET_SDA_HIGH;    //add by henry

	while(mask != 0)
	{
//��ʱ״̬ SCK = 0 SDA = X,���豸����ֵ����
		AT24CXX_SET_SCLK_LOW;  //add by henry
		AT24CXX_TLOW;
		AT24CXX_SET_SCLK_HIGH;
		AT24CXX_THIGH;
		if(AT24CXX_SDA_IS_HIGH)
			Value |= mask;
		mask>>=1;
//��ʱ״̬ SCK = 1 SDA = 0/1
		//AT24CXX_SET_SCLK_LOW; //command out by henry
	}
//����ACKֵ
//��ʱ״̬ SCK = 0 SDA = 1
	AT24CXX_SET_SCLK_LOW;   //add by henry

	if(ushAck == 0)
		AT24CXX_SET_SDA_HIGH;
	else
		AT24CXX_SET_SDA_LOW;
	
	AT24CXX_TLOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
	AT24CXX_SET_SCLK_HIGH;
	AT24CXX_THIGH;
//��ʱ״̬ SCK = 1 SDA = 0/1
	AT24CXX_SET_SCLK_LOW;
//��ʱ״̬ SCK = 0 SDA = 0/1
	__disable_irq();

	return Value;
}



U16 AT24CXX_CheckPara(U16 ushAddress, U16 ushByte)
{
	if((ushAddress & 0x03) != 0)
		return 0x81;
	if((ushByte & 0x3) != 0)
		return 0x82;
	if(ushAddress >= AT24CXX_BYTE)
		return 0x83;
	if(ushByte > (AT24CXX_BYTE-ushAddress) )
		return 0x84;
	return NOERROR;
}



// д�����ֽ�,Ŀ��λ�úͳ��ȱ���Ϊ4�ı���
U16 AT24CXX_Write(U16 ushAddress, U16 ushByte, U32* pSrc)
{
	U16 retVal = AT24CXX_CheckPara(ushAddress,ushByte);
	if(retVal != NOERROR)
		return retVal;

	while(ushByte != 0)
	{
		U16 i = 0;
		U16 ushCurByte = ushAddress + AT24CXX_PAGE_BYTE;
		ushCurByte &= (~AT24CXX_PAGE_MASK);
		ushCurByte -= ushAddress;
		if(ushCurByte > ushByte)//û�й�ҳ
			ushCurByte = ushByte;
		//ҳ��ʽд������
		AT24CXX_Start();
		if( AT24CXX_WriteData(AT24CXX_WRITE(ushAddress)) != 0 )
			return 0x90;
		if( AT24CXX_WriteData(ushAddress) != 0 )
			return 0x91;
		while( i<ushCurByte )
		{
			u16 flag = pSrc[i>>2]>>((i&0x3)<<3);
			if( AT24CXX_WriteData0(pSrc[i>>2]>>((i&0x3)<<3)) != 0 ) 
				return 0xA0;
			i++;
		}	
			
		AT24CXX_Stop();
		ushByte -= ushCurByte;
		ushAddress += ushCurByte;
		pSrc = (&pSrc[ushCurByte>>2]);
	}

	
	return retVal;
}



// ��������ֽ�,Ŀ��λ�úͳ��ȱ���Ϊ4�ı���
U16 AT24CXX_Read(U16 ushAddress, U16 ushByte, U32* pDes)
{
	U16 i = 0;
	U16 ack = 0;
	
	U16 retVal = AT24CXX_CheckPara(ushAddress,ushByte);
	if(retVal != NOERROR)
		return retVal;

	//ҳ��ʽ��ȡ����
	AT24CXX_Start();
	if(AT24CXX_WriteData(AT24CXX_WRITE(ushAddress)) != 0)
		return 0x90;
	if(AT24CXX_WriteData(ushAddress) != 0)
		return 0x91;
	AT24CXX_Start();
	if(AT24CXX_WriteData(AT24CXX_READ(ushAddress)) != 0)
		return 0x92;

	while(i<ushByte)
	{
		U32 value = AT24CXX_ReadData(ack);
		if((i&0x3) == 0)
			pDes[i>>2] = value;
		else
			pDes[i>>2] |= ( value<<( (i&0x3)<<3) );
		i++;
		if(i == (ushByte-1))
			ack = 1;//���һ���ֽ�ack = 1
	}		
	AT24CXX_Stop();	
	return NOERROR;
}



















