#include "Frame.h"
#include "Command.h"
#include "UART.h"
#include "stdtypes.h"

u16 UnpackageFrame(void)
{
	u16 ushCheckSum = 0;
	u16 i = 0;
	u16 ushCheckSumIndex = (g_ushReceiveNum>>1)-1;
	/* if not use checksum */
	//UART_R_LENGTH -= COMMAND_SIZE;
	if(g_ushReceiveNum != UART_R_LENGTH + FRAME_SIZE + COMMAND_SIZE) //add COMMAND_SIZE --henry
		return BAD_COMMAND_UNKNOWN;
	while(i < ushCheckSumIndex)
	{
		ushCheckSum += g_ushReceiveBuffer[i];
		i++;
	}
	/* if use checksum */
	UART_R_LENGTH -= COMMAND_SIZE;
	if(ushCheckSum != g_ushReceiveBuffer[ushCheckSumIndex])
		return BAD_FRAME_CHECKSUM;
	return NOERROR;
}

void PackageFrame(void)
{
	u16 ushCheckSum = 0;
	u16 i = 0;
	u16 ushCheckSumIndex = FRAME_DATA_INDEX +  (g_ushSentNum>>1);
	g_ushSentBuffer[FRAME_HEAD_INDEX] = FRAME_HEAD;
	g_ushSentBuffer[FRAME_ADDRESS_INDEX] = (GET_DES_ADDRESS(g_ushReceiveBuffer)<<8)|(GET_SRC_ADDRESS(g_ushReceiveBuffer))  ;
	g_ushSentBuffer[FRAME_LENGTH_INDEX] = g_ushSentNum + COMMAND_SIZE;
	while (i < ushCheckSumIndex)
	{
		ushCheckSum += g_ushSentBuffer[i];
		i++;
	}
	g_ushSentBuffer[ushCheckSumIndex] = ushCheckSum;
	g_ushSentNum += (FRAME_SIZE+COMMAND_SIZE);
}



