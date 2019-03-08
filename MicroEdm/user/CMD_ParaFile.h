// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   CMD_ParaFile.h
//
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

//###########################################################################



#ifndef __CMD_PARAFILE_H__
#define __CMD_PARAFILE_H__

#include "stdtypes.h"
#include "ParaInfo.h"

#define CMD_AL_RETURNPARA_WORD		(MAX_DATA_BYTE>>1)
#define CMD_AL_SETPARA_BYTE			MAX_DATA_BYTE

extern U16 ParseSetParaFile(void);
extern U16 ParseGetParaFile(void);

#endif

