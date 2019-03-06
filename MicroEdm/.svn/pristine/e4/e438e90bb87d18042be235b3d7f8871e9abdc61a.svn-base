#include "Command.h"
#include "Frame.h"
#include "cmd.h"
#include "ADC.h"
#include "CMD_GetStateEx.h"
#include "data_analy.h"
#include "voltage.h"
#include "edm.h"
#include "motor.h"
#include "eeprom_24lc16b.h"
#include "beep.h"

u16  g_ushReceiveBuffer[MAX_LENGTH_R] ; 
u16  g_ushSentBuffer[MAX_LENGTH_S]; 
u16* g_pReceiveBuffer = (u16*)g_ushReceiveBuffer;
u16* g_pSentBuffer = (u16*)g_ushSentBuffer;
u8* g_pSentBufferU8 = (u8*)g_ushSentBuffer;

u16  g_ushReceiveNum; 
u16  g_ushSentNum;


U16 ParseCmd1()
{
	U16* pPara = (U16*)UART_R_DATA_P;
	if(UART_R_LENGTH != CMD_CMD1_BYTE)
		return ECMD_LENGTH;
	return NOERROR;
}

U16 ParseCmd2()
{
	U16* pPara = (U16*)UART_R_DATA_P;
	if(UART_R_LENGTH != CMD_CMD2_BYTE)
		return ECMD_LENGTH;
	return NOERROR;
}

u16 CommandParse(void)                  //command parse
{
	u16 retVal = BAD_COMMAND;
	DC_MOTOR_ANALYSIS *motor_analy = NULL;
	Z_MOTOR_EN_ANALY *m_motor_EN_analy = NULL;
	Z_MOTOR_MOVE_ANALYSIS *z_motor_move_analy = NULL;
	Z_MOTOR_MOVETO_ANALYSIS *z_motor_moveto_analy = NULL;
	Z_MOTOR_STOP_ANALYSIS *z_motor_stop_analy = NULL;
	BEEP_ANALY *m_beep_ctrl = NULL;
	HV_SWITCH_ANALY *m_switch_HV = NULL;	
	ANALY_PWM_EDM *analy_pwm = NULL;
	ANALY_RC_EDM *analy_rc = NULL;

	
	switch(UART_R_CMD)
	{	
		case CMD_GETSTATE_EX:
			retVal = ParseGetState_Ex();
			break;
//		case CMD_FUNCTION_EX:
//			retVal = ParseFunction_Ex();
//			break;	
		case CMD_DC_MOTOR_MOVE:
			motor_analy = (DC_MOTOR_ANALYSIS*)UART_R_DATA_P;
			retVal = DC_motor_move(motor_analy);
			break;
		case CMD_DC_MOTOR_STOP:
			motor_analy = (DC_MOTOR_ANALYSIS*)UART_R_DATA_P;
			retVal = DC_motor_stop(motor_analy);
			break;
		case CMD_Z_MOTOR_EN:
			m_motor_EN_analy = (Z_MOTOR_EN_ANALY *)UART_R_DATA_P;
			retVal = z_motor_en(m_motor_EN_analy);
			break;
		case CMD_Z_MOTOR_MOVE:
			z_motor_move_analy = (Z_MOTOR_MOVE_ANALYSIS *)UART_R_DATA_P;
			retVal = z_motor_move(z_motor_move_analy);
			break;
		case CMD_Z_MOTOR_MOVETO:
			z_motor_moveto_analy = (Z_MOTOR_MOVETO_ANALYSIS *)UART_R_DATA_P;
			retVal = z_motor_moveTo(z_motor_moveto_analy);
			break;
		case CMD_Z_MOTOR_FINDZERO:
			retVal = z_motor_findZero();
			break;
		case CMD_Z_MOTOR_STOP:
			z_motor_stop_analy = (Z_MOTOR_STOP_ANALYSIS *)UART_R_DATA_P;
			retVal = z_motor_stop(z_motor_stop_analy);
			break;
		case CMD_BEEP:
			m_beep_ctrl = (BEEP_ANALY*)UART_R_DATA_P;
			retVal = beep_ctrl(m_beep_ctrl);
			break;
		case CMD_EDM_SWITCH:
			m_switch_HV = (HV_SWITCH_ANALY *)UART_R_DATA_P;
			retVal = H_voltage_switch(m_switch_HV);
			break;
		case CMD_EDM_PWM_RUN:
			analy_pwm = (ANALY_PWM_EDM *)UART_R_DATA_P;
			retVal = edm_pwm(analy_pwm);
			break;
		case CMD_EDM_PWM_STOP:
			analy_pwm = (ANALY_PWM_EDM *)UART_R_DATA_P;
			retVal = edm_pwm_stop(analy_pwm);
			break;
		case CMD_EDM_RC_RUN:
			analy_rc = (ANALY_RC_EDM *)UART_R_DATA_P;
			retVal = edm_rc(analy_rc);
			break;
		case CMD_EDM_RC_STOP:
			analy_rc = (ANALY_RC_EDM *)UART_R_DATA_P;
			retVal = edm_rc_stop(analy_rc);
			break;
		case CMD_UPDATE_CONFIG:
			retVal = update_config();
			break;
		default:
			break;
	}
	return retVal;
}












