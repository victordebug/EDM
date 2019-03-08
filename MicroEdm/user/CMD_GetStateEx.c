#include "CMD_GetStateEx.h"
#include "Cmd.h"
#include "Command.h"
#include "Prog_List.h"
#include "SystemState.h"
#include "ADC.h"
#include "uart.h"
#include "fsmc.h"

/********************************************************************/
// GETSTATE_EX
u16 ParseGetState_Ex(void)
{
	CMD_GetStateEx_p pPara = (CMD_GetStateEx_p)UART_R_DATA_P;
	u16* pState = UART_S_DATA_P;

	u16 ushWord = 0;
	if( len_appData_buf != CMD_GETSTATE_EX_BYTE )
		return ECMD_LENGTH;

	switch(pPara->m_ushMID)
	{
		case CAIR_MID_SYSTEM:
			ushWord = SYS_GetStateEx(pPara->m_ushPID,pState);
			break;
//		case CAIR_MID_ADC:
//			ushWord = ADC_GetStateEx(pPara->m_ushPID,pState);
//			break;
		case CAIR_MID_VOLTAGE:
			ushWord = VOL_GetStateEx(pPara->m_ushPID,pState);
			break;
		case CAIR_MID_MOTOR_SENSOR:
			ushWord = SENSOR_GetStateEx(pPara->m_ushPID,pState);
			break;
		case CAIA_MID_RC_STAT:
			ushWord = RC_STAT_GetStateEx(pPara->m_ushPID,pState);
			break;
		case CAIA_MID_PWM_STAT:
			ushWord = PWM_GetStateEx(pPara->m_ushPID,pState);
			break;
		case CAIA_MID_Z_MOTOR_STAT:
			ushWord = ZMOTOR_STAT_GetStateEx(pPara->m_ushPID,pState);
			break;
		
		default :
			break;

	}
	if(ushWord == 0)
		return ECMD_NO_FUNCTION;

	UART_S_CMD = CMD_RETURNSTATE_EX;
	g_ushSentNum = (ushWord<<1);
	return NOERROR;
}

	
		
	
