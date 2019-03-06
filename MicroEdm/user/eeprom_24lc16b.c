#include "eeprom_24lc16b.h"
#include "i2c.h"
#include "stdtypes.h"


void EEPROM_24LC16B_Init(void)
{
	my_I2C_Init();
}

u8 EEPROM_24LC16B_ReadByte(u16 addr)
{
	u8 temp = 0;

	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//д����
	}while (my_I2C_Wait_Ack());

	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	my_I2C_Start();
	my_I2C_Send_Byte(ADDR_24LC16B + 1);//������
	my_I2C_Wait_Ack();
	
	temp = my_I2C_Read_Byte(0);
	my_I2C_Stop();

	return temp;
}





void EEPROM_24LC16B_WriteByte(u16 addr, u8 data)
{
	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//д����
	}while (my_I2C_Wait_Ack());
	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	my_I2C_Send_Byte(data);
	my_I2C_Wait_Ack();
	my_I2C_Stop();
}



void EEPROM_24LC16B_ReadBuf(u16 addr, u8 *buf, u16 len)
{
	u16 i = 0;
	__enable_irq();

	if((len>0)&&(addr+len)>=(MAXROM_24LC16B-1))
		return;
	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//д����
	}while (my_I2C_Wait_Ack());
	
	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();
	
	my_I2C_Start();
	my_I2C_Send_Byte(ADDR_24LC16B + 1);//������

	for (i=0; i<(len-1); i++)
	{
		*buf = my_I2C_Read_Byte(1);
		buf ++;
	}

	*buf = my_I2C_Read_Byte(0);
	my_I2C_Stop();
	__disable_irq(); 

}




void EEPROM_24LC16B_WriteBuf(u16 addr, u8 *buf, u16 len)
{
	u16 i = 0;
	__enable_irq();

	if((len>0)&&(addr+len)>=(MAXROM_24LC16B-1))
		return;

	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//д����
	}while (my_I2C_Wait_Ack());

	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	for (i=0; i<len; i++)
	{
		my_I2C_Send_Byte(*buf);
		my_I2C_Wait_Ack();
		buf ++;

	}
	my_I2C_Stop();
	__disable_irq(); 

}



void EEPROM_24LC16B_WritePage(u16 addr, u8 *buf)
{
	u8 cnt=16;
	if((addr+16)%256<16)
		return;

	do
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//д����
	}
	while (my_I2C_Wait_Ack());
	
	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	while(cnt--)
	{
		my_I2C_Send_Byte(*buf++);
		my_I2C_Wait_Ack();
	}
	my_I2C_Stop();	
	
}


u16 update_config(void)
{

	return NOERROR;
}



void get_config(void)
{


}



