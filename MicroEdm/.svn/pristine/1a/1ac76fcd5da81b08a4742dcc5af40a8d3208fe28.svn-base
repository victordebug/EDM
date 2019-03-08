#include "eeprom_24lc16b.h"
#include "i2c.h"
#include "stdtypes.h"
#include "config.h"


void EEPROM_24LC16B_Init(void)
{
	my_I2C_Init();
}

u8 EEPROM_24LC16B_ReadByte(u16 addr)
{
	u8 temp = 0;
	__enable_irq();

	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//写命令
	}while (my_I2C_Wait_Ack());

	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	my_I2C_Start();
	my_I2C_Send_Byte(ADDR_24LC16B + 1);//读命令
	my_I2C_Wait_Ack();
	
	temp = my_I2C_Read_Byte(0);
	my_I2C_Stop();
	
	__disable_irq();
	
	return temp;
}





void EEPROM_24LC16B_WriteByte(u16 addr, u8 data)
{
	__enable_irq();
	
	do 
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//写命令
	}while (my_I2C_Wait_Ack());
	my_I2C_Send_Byte(addr);
	my_I2C_Wait_Ack();

	my_I2C_Send_Byte(data);
	my_I2C_Wait_Ack();
	my_I2C_Stop();

	__disable_irq(); 
}








/*
addr:写的起始地址
buf:32位数组
len:读取的长度
*/
void EEPROM_24LC16B_ReadBuf(u16 addr, u32 *buf, u16 len)
{
	u16 i,j = 0;
	u32 data_u32 = 0;
	u8  data_u8 = 0;

	if (len > MAXLEN_24LC16B)
		return;

	for (i=0; i<len; i++)
	{
		data_u32 = 0;
		for (j=0; j<SIZE_U32_DATA; j++)
		{
			data_u8   = EEPROM_24LC16B_ReadByte(addr++);
			data_u32 |= (data_u8&0xff)<<(8*j);
			OSTimeDlyHMSM(0,0,0,10);
		}

		buf[i] = data_u32;
	}
	

}



/*
addr:写的起始地址
buf:32位数组
len:数组的长度
*/
void EEPROM_24LC16B_WriteBuf(u16 addr, u32 *buf, u16 len)
{
	u16 i = 0;
	u16 j = 0;
	u32 data_u32 = 0;
	u8  data_u8 = 0;

	if (len > MAXLEN_24LC16B)
		return;
	

	for (i=0; i<len; i++)
	{
		data_u32 = buf[i];
		for (j=0; j<SIZE_U32_DATA; j++)
		{
			data_u8 = (data_u32>>(8*j)) & 0xff;
			EEPROM_24LC16B_WriteByte(addr++, data_u8);
			OSTimeDlyHMSM(0,0,0,10);
		}
	}

}



void EEPROM_24LC16B_WritePage(u16 addr, u8 *buf)
{
	u8 cnt=16;
	if((addr+16)%256<16)
		return;

	do
	{
		my_I2C_Start();
		my_I2C_Send_Byte(ADDR_24LC16B);//写命令
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



