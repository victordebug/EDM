#include "ADC.h"
#include "stm32f10x_adc.h"
#include "GPIO.h"
#include "MemoryCopy.h"
#include "Timer.h"

#define ADCVREF 			3300				//ADC reference voltage 3.3V = 3300mV
#define TEMPREF             25  				//TEMP SENSOR measure reference voltage 2.5 * AMP_GAIN = 25V
#define AMP_GAIN			11					//Error Amplifier
#define FULL_SCALE 		    4096				//12-bit resolution 

#define UPRESISTOR    2000				    //2000 Ohm
#define DOWNRESISTOR  100					//100  Ohm
#define SUMRESISTOR   ( DOWNRESISTOR + UPRESISTOR )
#define UPPERPOWER	  2600
#define LOWERPOWER	  2300

u16 PowerErr ;
u16 ADC_Value[CHN_NUM];
u16 ADC_ReadData[CHIPSEL_NUM * CHNSEL_NUM][CHN_NUM];
ADC_Ctrl_t g_AdcCtrl;
Timer_t m_AdcTimer;

/**
  * @brief  Configure the ADC1 GPIO reset and clock control.
  * @param  None
  * @retval None
  */
static void ADC1_RCC_Config(void)
{
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1,ENABLE);	
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //??DMA??
}

/**
  * @brief  Configure the ADC1 External interrupt/event controller  .
  * @param  None
  * @retval None
  */
static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  PA0_ADC_LVHMONITOR  | PA1_ADC_MOTOR;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}

/**
  * @brief  Configure the ADC .
  * @param  None
  * @retval None
  */
static void ADC1_Config_Init(void) 
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_DeInit(ADC1);
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = CHN_NUM;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
	
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1,ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));	
}



/**
  * @brief  Configure DMA.
  * @param  None
  * @retval None
  */
static void DMA_Config_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1); 																	//DMA 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; 	//DMA Peripheral ADC address
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_Value[0]; 	//DMA Memory Storage basic address
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 					//DMA Set SRAM as direction
	DMA_InitStructure.DMA_BufferSize = CHN_NUM; 										  //DMA Channel Buffer size
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //DMA Peripheral address \
																															//register do not increase 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 		//Enable DMA Memory address \
																															//increase automatically
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //DMA Peripheral\
																																			//data size is half word
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //DMA Memory data size is
																																			//half word
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 						//DMA mode is Circular storage
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 					//DMA channel do not have m2m transmit
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); 				
}

/**
  * @brief  Power Detect.
  * @param  None
  * @retval None
  */
static void PowerDet(void)
{
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  DMA_Cmd(DMA1_Channel1,ENABLE);
}

/**
  * @brief  Initialize the ADC1 .
  * @param  None
  * @retval None
  */
void ADC1_Init(void)
{
	 
	MemSet(&g_AdcCtrl, 0, sizeof(g_AdcCtrl));
	ADC1_RCC_Config();
	ADC1_GPIO_Config();
	ADC1_Config_Init();
	DMA_Config_Init();
	PowerDet();
}

/**
  * @brief  Acquire Vacuum Degree in the box.
  * @param  None
  * @retval None
  */


void ADC_Module(void)
{
	if(g_AdcCtrl.m_ulFlag.bit.State == ADCSTATE_IDLE)
		return;
	
	switch(g_AdcCtrl.m_ulFlag.bit.State)
	{
		case ADCSTATE_S1:
			//ADC_S1();
		  break;
		
		case ADCSTATE_S2:
			//ADC_S2();
		  break;
				
		case ADCSTATE_S3:
			//ADC_S3();
		  break;
		default:
			break;
	}
	
}

u16 ADC_GetStateEx(u16 ushPID,u16* pBuffer)
{
	u16 ushWord = 0;
	U16 i;
	switch(ushPID)
	{
		case SP_SYS_PID_ADCDATA(0):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 0;i<32;i++)
			{
				pBuffer[i] = ADC_ReadData[i][0];
			}
			break;
		case SP_SYS_PID_ADCDATA(1):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 32;i<64;i++)
			{
				pBuffer[i] = ADC_ReadData[i][0];
			}
			break;
		case SP_SYS_PID_ADCDATA(2):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 0;i<32;i++)
			{
				pBuffer[i] = ADC_ReadData[i][1];
			}
			break;
		case SP_SYS_PID_ADCDATA(3):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 32;i<64;i++)
			{
				pBuffer[i] = ADC_ReadData[i][1];
			}
			break;
			
			
			case SP_SYS_PID_ADCDATA(4):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 0;i<32;i++)
			{
				pBuffer[i] = ADC_ReadData[i][2];
			}
			break;
		case SP_SYS_PID_ADCDATA(5):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 32;i<64;i++)
			{
				pBuffer[i] = ADC_ReadData[i][2];
			}
			break;
		case SP_SYS_PID_ADCDATA(6):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 0;i<32;i++)
			{
				pBuffer[i] = ADC_ReadData[i][3];
			}
			break;
		case SP_SYS_PID_ADCDATA(7):
			ushWord = SP_SYS_PID_ADCDATA0_WORD;
			for(i = 32;i<64;i++)
			{
				pBuffer[i] = ADC_ReadData[i][3];
			}
			break;
			
		case SP_SYS_PID_ADCVALUE:
			ushWord = SP_SYS_PID_ADCVALUE_WORD;
			for(i = 0;i<4;i++)
			{
				pBuffer[i] = ADC_Value[i];
			}
			break;
		case SP_SYS_PID_CTRL:
			ushWord = SP_SYS_PID_CTRL_WORD;
			MemCpy(pBuffer, &g_AdcCtrl, ushWord);
			break;
	}
	return ushWord;
}


	














