#ifndef __FRAME_H__
#define __FRAME_H__

#include "stm32f10x.h"

/*
 * CMD = HEAD + ADDRESS + LENGTH + COMMAND + DATA + CHECKSUM
 */

#define FRAME_HEAD_M				(0x4D)
#define FRAME_HEAD_E				(0x4500)
#define FRAME_HEAD					(FRAME_HEAD_M | FRAME_HEAD_E)

#define PC_ADDRESS					(0x01)
#define DEFAULT_ADDRESS			    0xB1

#define FRAME_SIZE					8 
#define COMMAND_SIZE				2
#define CHECKSUM_SIZE				2	
#define MAX_COMMAND_SIZE		    96
#define MAX_DATA_SIZE				84

#define FRAME_HEAD_INDEX			0
#define FRAME_ADDRESS_INDEX			1
#define FRAME_LENGTH_INDEX			2
#define FRAME_COMMAND_INDEX			3
#define FRAME_DATA_INDEX		    4
 
#define MAX_LENGTH					(MAX_DATA_SIZE+COMMAND_SIZE)
#define MIN_LENGTH					COMMAND_SIZE
                                                            
#define GET_DES_ADDRESS(buffer)		(buffer[FRAME_ADDRESS_INDEX] & 0xFF)
#define GET_SRC_ADDRESS(buffer)		((buffer[FRAME_ADDRESS_INDEX]>>8) & 0xFF)

extern u16 UnpackageFrame(void);
extern void PackageFrame(void);

#define RECEIVING_COMMAND			0x00		
#define SENDING_COMMAND				0x01		
#define PROCESSING_COMMAND		    0x80		

#endif /* _FRAMEPROTOCOL_H*/
