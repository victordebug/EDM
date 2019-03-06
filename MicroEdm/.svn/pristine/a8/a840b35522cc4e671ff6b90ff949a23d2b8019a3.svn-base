
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_DMA.h"
#include "uart.h"
#include "queue.h"
#include "Command.h"
#include "Frame.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "systick.h"
#include "includes.h"


//#define USART1_DR_Base 0x40013804//USART1寄存器地址
//#define SEND_BUFFER_SIZE 50

u16  g_ushUARTState; 
u16  m_ushDataSize; 
u16  m_ushSentCounter; 

u16 len_appData_buf = 0;

queueCDT UsartQueue;
queueCDT Usart5Queue;
void UART_Send(void);
void UART1_Send_Empty_Data(void);

static uint8_t gRecvFrameFinishFlag = 0;//一帧数据接收完成标志
/*usart1中断配置*/
static void NVIC_Usart1Config(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void UART1_RESET(void)
{       
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	g_ushReceiveNum = 0;      
	g_ushSentNum = 0;     
	m_ushSentCounter = 0;	
	USART_ITConfig(USART1, USART_IT_TC, DISABLE);          //ENABLE
	
}

/*usart1串口配置*/
int UartConfigation(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC Config
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1,ENABLE);	
	
	//GPIO Config
	/*configure USART1 Tx (PA.09) as alternate function push-pull*/
	GPIO_InitStructure.GPIO_Pin = TXD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*configure USART1 Rx (PA.10) as alternate function input floating*/
	GPIO_InitStructure.GPIO_Pin = RXD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  UART_DIR;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*USART1 mode config*/
	USART_ITConfig(USART1, USART_IT_TC, DISABLE);          //DISABLE
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //ENABLE	

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure );
	
	USART_ClockInitStructure.USART_Clock =USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL =USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA =USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit =USART_LastBit_Disable;
	USART_ClockStructInit(&USART_ClockInitStructure); 
	USART_ClockInit(USART1,&USART_ClockInitStructure);
	USART_Cmd(USART1,ENABLE);
	NVIC_Usart1Config();
	UART1_RESET();
	UART1_Send_Empty_Data();

	return 0;	
}


#if 0
/*Usart1 中断服务程序*/
void Uart1_ISR(void)
{
	while (USART_GetITStatus(USART1, USART_IT_RXNE) == RESET);
	EnQueue(&UsartQueue, USART_ReceiveData(USART1));
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
#endif


void Uart1_ISR(void)
{	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		UART_Receive();
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET) 
	{  	
		UART_Send();
		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}
}


/****************************************************
* 函数名:itoa
*描述:将整型数据转换成字符串
*
*参数:value:整型值
*         str:转换后的字符串
*         radix:表示进制如10进制，16进制，2进制，8进制
*
*返回:str转换后的字符串
*****************************************************/
static char *itoa(s32 value,u8 *str,s32 radix)
{
	const u8 table[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 *ptr = str;
	u8 *start = 0;
       u8 temp = 0;
	if (!value)
	{
		*ptr ++ = 0x30;
		*ptr  = 0;
		return (char *)str;
	}
	if (value < 0)
	{
		*ptr ++ = '-';
		value *= -1;
	}
	while(value)
	{  
		*ptr++ = table[value%radix];
		  value/=radix;
	}
	*ptr = 0;
	// in the below, we have to converse the string
       start = ((*str == '-') ? str+1 : str); //now start points the head of the string
       ptr--; //now prt points the end of the string
       while(start<ptr)
       {
           temp = *start; 
          *start = *ptr;
          *ptr = temp;
          start++;
          ptr--;
	} 
	return (char *)str;

}


/*usart1打印函数*/
void UartPrintf(u32 COM,u8 *Data,...)
{
	USART_TypeDef *USARTx = USART1;
	const char *s;
	s32 d;
	u8 buf[16];
	va_list ap;
	va_start(ap,Data);
	 
	if (COM == COM1)
	{
		USARTx = USART1;
	}

	USART_ClearFlag(USART1,USART_FLAG_TC);

	while (*Data != 0)
	{
		if (*Data == 0x5c) //'\'
		{
			switch( *++Data)
			{
				case 'r'://回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;
				case 'n'://换行符
					USART_SendData(USARTx, 0x0a);
					Data ++;
					break;
				default:
					Data ++;
					break;
			}
		}
		else if (*Data == '%')
		{
                    switch(*(++Data))
                    {
			case 's':
				s = va_arg(ap,const char *);
				for (;*s;s++)
				{
					USART_SendData(USARTx, *s);
					while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
				}
				Data ++;
				break;
			case 'd':
				d = va_arg(ap,s32);
				itoa(d,buf,10);
				for (s=buf;*s;s++)
				{
					USART_SendData(USARTx, *s);
					while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
				}
				Data ++;
				break;
			default:
				Data ++;
				break;
                   }	
		}
		else 
		{
			USART_SendData(USARTx, *Data++);
			while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		}

	}
	
	
	
}

void UART1_Send_Empty_Data(void)
{
	USART_SendData( USART1,00 );                           //Send a idle USART data
	while ( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET )     
	g_ushUARTState = RECEIVING_COMMAND;  
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

/****************************************************
* 函数名:UsartSendData
*描述:串口发送函数
*
*参数:RxBuf:发送字符串
*         RxLen:发送数据的长度
*
*返回:发送的数据长度
*****************************************************/
u32 UsartSendData(const u8 * SendBUf,const u32 SendLen)
{
   int i;
	 USART_ClearFlag(USART1,USART_FLAG_TC);
	 for (i = 0; i < SendLen; i ++)
 	{
 		USART_SendData(USART1, *SendBUf++);
 		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
 	}
	
	
	return i;
                 

}

/* UART SEND COMMAND */
void UART_Send(void)
{
	u16 ushData;
	if( g_ushUARTState != SENDING_COMMAND)
		return;

	if(m_ushSentCounter >= g_ushSentNum)
	{
	  while ( USART_GetFlagStatus( USART1, USART_FLAG_TC ) == RESET ) { } ;
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		g_ushUARTState = RECEIVING_COMMAND;
		g_ushReceiveNum = 0;
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);          //DISABLE
		return;
	}
	ushData = g_pSentBuffer[m_ushSentCounter>>1];
	if((m_ushSentCounter & 1) != 0)
		ushData >>= 8;
	else
		ushData &= 0xFF;
  USART1->DR = (ushData & (uint16_t)0x00FF);
	m_ushSentCounter ++;
}


/****************************************************
* 函数名:UsartRecvData
*描述:串口接收函数
*
*参数:RxBuf:接收字符串
*         RxLen:接收数据的最大长度
*         TimeOut:超时时间,0则永远等待，直到收到最大长度数据
*
*返回:成功返回接收到的数据长度，失败返回0
*****************************************************/
u32 UsartRecvData(u8 * RxBuf,u32 RxLen,u32 TimeOut)
{
	u32 tmpTime = 0;
	u32 OldTime = sysGetTickCounter();
	u8 ch;
	u32 i = 0;
	TIME_MODE timeMode = GetTimeMode();
	TimeOut *= timeMode;
	ClearQueueBuffer(&UsartQueue);
	  while (1)
	  {

		if (0 == DeQueue(&UsartQueue,&ch) )
		{
			RxBuf[i++] = ch;
			ch = 0;
			if (i == RxLen)
			{
				return RxLen;
			}
			tmpTime = sysGetTickCounter();
		}
		else 
		{
			if (i == 0)//如果没接到任何数据
			{
				if (sysGetTickCounter() - OldTime >= TimeOut && TimeOut != 0)
				{
					return 0;
				}
			}
			else
			{
				if (sysGetTickCounter() - tmpTime >= 2*(timeMode/1000) && TimeOut != 0)
				{
					return i;
				}
			}
		}
	}
}

/****************************************************
* 函数名:UsartRecvDataEx
*描述:串口接收函数，轮询方式读取
*
*参数:RxBuf:接收字符串
*     MaxRxLen:接收数据的最大长度
*     
*
*返回:成功返回接收到的数据长度，失败返回0
*日期:2014-1-17
*****************************************************/

u32 UsartRecvDataEx(u8 * RxBuf,u32 MaxRxLen)
{
		 u8 ch;
		 u32 i = 0; 
	  if (GetFrameFinishFlag() != COM_FRAME_FINISH)
		{
			  return 0;
		}
		while (i < MaxRxLen)
		{
			 if (0 == DeQueue(&UsartQueue,&ch))
			 {
					RxBuf[i++] = ch;
			 }
			 else
			 {
					 break; 
			 }
	  }
		ClearFrameFinishFlag();
		return i;
}


#if 0
void Uart_Test(void )
{

    u32 Len = 0;
    uint8_t * Rxbuf = (u8 *)malloc(1024 *5);
    if (Rxbuf == NULL)
    {
       // UartPrintf(COM1,"mallc error\r\n");
        return;
    }
	
      // UartConfigation();
      // UartPrintf(COM1,"开始UART测试\r\n");
        while(1)
        {
        	memset(Rxbuf,0,1024 *5);
          	Len = UsartRecvData(Rxbuf,1024 *5,10*1000);
		if (Len == 0)
			{
				UartPrintf(COM1,"接收数据超时\r\n");
               // UartPrintf(COM1,"\x55\x55\x55\x55");
			}
		if (Len > 0)
		{   
		       UartPrintf(COM1,"接收长度:%d,数据为:\r\n",Len);
			     UsartSendData(Rxbuf,Len);
			     UartPrintf(COM1,"\r\n--------------------------------------------------\r\n");
			     Len = 0;
		}
	       
        }
        free(Rxbuf);
}
#endif

//串口重定向
int fputc(int ch, FILE *f)  
{  
  USART_SendData(USART1, (uint8_t) ch);  
  /* Loop until the end of transmission */  
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)  
  {}  
  return ch;  
} 

void SetFrameFinishFlag(void)
{
	  gRecvFrameFinishFlag = 1;
}

void ClearFrameFinishFlag(void)
{
	 gRecvFrameFinishFlag = 0;
}

uint8_t GetFrameFinishFlag(void)
{
	  return gRecvFrameFinishFlag;
}

void UART_Receive(void)
{
	u16 usart1_get_data;  
	usart1_get_data = USART_ReceiveData(USART1);
	
	if( g_ushUARTState != RECEIVING_COMMAND ) 
		return;
	if(g_ushReceiveNum > MAX_LENGTH_R ) 
	{ 
		g_ushReceiveNum = 0; 
		return ;
	}
	if((g_ushReceiveNum&1)!=0 )                               //EVEN byte left shift 8 bits
		usart1_get_data <<= 8;   

	switch( g_ushReceiveNum )
	{
		 case 0:
		 {
			if( usart1_get_data == FRAME_HEAD_M )
			{
				g_pReceiveBuffer[FRAME_HEAD_INDEX] = FRAME_HEAD_M;
				g_ushReceiveNum++;
				break;	
			}
		}			 
		case 1:
		{
			if( usart1_get_data == FRAME_HEAD_E )
			{
				g_pReceiveBuffer[FRAME_HEAD_INDEX] |= FRAME_HEAD_E;
				g_ushReceiveNum++;
			}
			else
			{ 
				if((usart1_get_data >>8)!=FRAME_HEAD_M )
				g_ushReceiveNum = 0;
			}
			break;
		}
		case 2:
		{
			if( usart1_get_data == DEFAULT_ADDRESS	)
			{
				g_pReceiveBuffer[FRAME_ADDRESS_INDEX] = DEFAULT_ADDRESS	;
				g_ushReceiveNum++;
			}
			else
			{
				g_ushReceiveNum = 0;
				if( usart1_get_data == FRAME_HEAD_M ) 
					g_ushReceiveNum++;
			}
			break;	
		}			 
		case 3:
		{
			g_pReceiveBuffer[FRAME_ADDRESS_INDEX] |= usart1_get_data;
			g_ushReceiveNum++;
			break;
		}					
		case 4:
		{
			g_pReceiveBuffer[FRAME_LENGTH_INDEX] = usart1_get_data;
			g_ushReceiveNum++;
			break;	
		}					
		case 5:
		{
			g_pReceiveBuffer[FRAME_LENGTH_INDEX] |= usart1_get_data; 
			g_ushReceiveNum++; 
			m_ushDataSize = g_pReceiveBuffer[FRAME_LENGTH_INDEX];
			len_appData_buf = g_pReceiveBuffer[FRAME_LENGTH_INDEX];
			if((m_ushDataSize>MAX_LENGTH_R)||( m_ushDataSize < MIN_LENGTH))
				g_ushReceiveNum = 0;	 
			
			m_ushDataSize += 2;                  //  add checksum byte
			m_ushDataSize += 2;                  //  add command byte --henry
			break;
		}	
		default:   
		{   
			if((g_ushReceiveNum & 1) != 0) 	
				g_pReceiveBuffer[g_ushReceiveNum>>1] |= usart1_get_data;  
			else 	
				g_pReceiveBuffer[g_ushReceiveNum>>1] = usart1_get_data;	
			
			g_ushReceiveNum ++;   
			m_ushDataSize --;   
			if(m_ushDataSize == 0) 
			{				 
				g_ushUARTState = PROCESSING_COMMAND;   
				return;
			}
			break;			 
		}
	}
}

void UART_Module(void)
{
	u16 usart1_get_data;  
	u16 retVal = sizeof(u16);
	
	if(g_ushUARTState != PROCESSING_COMMAND)
		return;

	g_pSentBuffer[FRAME_COMMAND_INDEX] = CMD_ACK;
	g_ushSentNum = CMD_ACK_BYTE;

	retVal = UnpackageFrame();
	if(retVal == NOERROR)
	{
		retVal = CommandParse();
	}else if (retVal != NOERROR)
	{
		u32* pErrorID = (u32*)(&g_pSentBuffer[FRAME_DATA_INDEX]);
		g_pSentBuffer[FRAME_COMMAND_INDEX] = CMD_RETRY;
		(*pErrorID) = (0x00010000) | retVal; 
		g_ushSentNum = CMD_RETRY_BYTE;
	}
	
	PackageFrame();
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	OSTimeDlyHMSM(0, 0, 0, 1);	// delay 1ms
	g_ushUARTState = SENDING_COMMAND;	
	m_ushSentCounter = 1;   
	usart1_get_data = g_pSentBuffer[0]&0xFF; 		
	USART_SendData( USART1,usart1_get_data ); 	
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);          //ENABLE 
}

void Uart_Thread(void)
{
	while(1)
	{		
		OSTimeDlyHMSM(0,0,0,1);
		UART_Module();
	}
}








