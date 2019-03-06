#include "i2c.h"
#include "stm32f10x.h"
#include "gpio.h"

/*
注意：
* I2C写的引脚是PA4，写的值和实际输入的值相反，例如，给EEPROM传输0的时候，P14引脚输出1
* I2C读的引脚是PA5，读去数据的时候PA4必须设置为低电平，不影响读取的电平
*/



static void i2c_delay_us(u32 time)
{
	u32 i=8*time;
	 while(i--);
}

void my_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = PA4_EEPROM_SDA_WRITE | PA6_EEPROM_SCLK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,PA4_EEPROM_SDA_WRITE | PA6_EEPROM_SCLK);

	GPIO_InitStructure.GPIO_Pin = PA5_EEPROM_SDA_READ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,PA5_EEPROM_SDA_READ);

	I2C_SDA_H();
	I2C_SCL_H();
}


          			 
void my_I2C_Start(void)
{
	I2C_SDA_H();
	I2C_SCL_H();
	i2c_delay_us(6);
	I2C_SDA_L();
	i2c_delay_us(6);
	I2C_SCL_L();
	i2c_delay_us(6);

}


void my_I2C_Stop(void)
{

	I2C_SDA_L();
	I2C_SCL_L();
	i2c_delay_us(6);
	I2C_SCL_H();
	i2c_delay_us(6);
	I2C_SDA_H();
	i2c_delay_us(6);

}


void my_I2C_Send_Byte(u8 txd)
{
    u8 t;   	    
    I2C_SCL_L();
    for(t=0;t<8;t++)
    {               
		if((txd<<t)&0x80)
		{
			I2C_SDA_H();
		}else 
		{
			I2C_SDA_L();
		}  
		i2c_delay_us(4);  
		I2C_SCL_H();
		i2c_delay_us(6); 
		I2C_SCL_L();	
		i2c_delay_us(6);
    }	

}


u8 my_I2C_Read_Byte(unsigned char ack)
{
	unsigned char i,receive = 0;
	I2C_SDA_H();
	
    for(i=0;i<8;i++ )
	{
        I2C_SCL_L();
        i2c_delay_us(6);
		I2C_SCL_H();
		i2c_delay_us(2); 
        receive<<=1;
        if(READ_SDA)receive++;   
		i2c_delay_us(2); 
    }	
	I2C_SCL_L();
	i2c_delay_us(4); 
	
    if (!ack)
        my_I2C_NAck(); 
    else
        my_I2C_Ack();    
    return receive;

}

/*
*1-->接受应答失败
*0-->接受应答成功
*/
u8 my_I2C_Wait_Ack(void)
{
	u8 ack = 0;
	I2C_SDA_L();
	i2c_delay_us(6);	   
	I2C_SCL_H();
	i2c_delay_us(6);	 

	if (READ_SDA) 
	{
		ack = 1;
	}else
	{
		ack = 0;
	}
	I2C_SCL_L(); 
	i2c_delay_us(4);
	
	return ack;  
}



void my_I2C_Ack(void) //希望继续
{
	I2C_SCL_L();
	I2C_SDA_L();
	i2c_delay_us(6);
	I2C_SCL_H();
	i2c_delay_us(6);
	I2C_SCL_L();
	i2c_delay_us(6);
}



void my_I2C_NAck(void) //希望停止传输
{
	I2C_SCL_L();
	I2C_SDA_H();
	i2c_delay_us(6);
	I2C_SCL_H();
	i2c_delay_us(6);
	I2C_SCL_L();
	i2c_delay_us(6);

}





