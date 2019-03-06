
#ifndef _UART_H
#define _UART_H
#include <stdint.h>
#include "stm32f10x.h"  
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "GPIO.h"

#define COM1 0x01

#define COM_FRAME_FINISH 1
#define COM_FRAME_CLEAR 0


/* define PA9 PA10 as UART Pin */
#define  RXD                  GPIO_Pin_10;
#define  TXD                  GPIO_Pin_9;
#define  UART_DIR			  GPIO_Pin_8;

#define UART_SET_REC_MODE			GPIO_ResetBits(GPIOA,UART_DIR)
#define UART_SET_SEND_MODE			GPIO_SetBits(GPIOA,UART_DIR)

typedef uint32_t u32;
typedef uint8_t  u8;

extern u16 len_appData_buf;


//void System_RCC_Configuration(void);
//void System_NVIC_Configuration(void);

int UartConfigation(void);
void Uart1_ISR(void);
void UartPrintf(u32 COM,u8 *Data,...);
u32 UsartSendData(const u8 * SendBUf,const u32 SendLen);
u32 UsartRecvData(u8 * RxBuf,u32 RxLen,u32 TimeOut);
u32 UsartRecvDataEx(u8 * RxBuf,u32 MaxRxLen);
void SetFrameFinishFlag(void);
void ClearFrameFinishFlag(void);
uint8_t GetFrameFinishFlag(void);

void Uart_Test(void );

void UART_Receive(void);
extern void UART_Module(void);
extern void Uart_Thread(void);
//void DMA_Test(void );

#endif



