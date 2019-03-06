#include "dma.h"
#include "adc.h"
#include "stm32f10x_dma.h"

void DMA_Config_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //Ê¹ÄÜ DMA Ê±ÖÓ
	DMA_DeInit(DMA1_Channel1); 											//DMA

	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; 	//DMA Peripheral ADC address
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&adc_Value[0]; 	//DMA Memory Storage basic address
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 					//DMA Set SRAM as direction
	DMA_InitStructure.DMA_BufferSize = NUM_CHANNEL; 										  //DMA Channel Buffer size
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







