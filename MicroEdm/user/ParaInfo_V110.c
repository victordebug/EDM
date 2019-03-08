// AMSKY File $Revision: /AutoLoadV120/ $
// Checkin $Date: March 6, 2012$
//###########################################################################
//###########################################################################
//
// FILE:   ParaInfoV110.c
//
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================

///###########################################################################

#include "ParaInfo.h"
#include "Error.h"

FileInfo_t g_FileInfoTable[PARA_FILE_NUM] = 
{
	FILEINFO(g_ulSN),
	FILEINFO(g_ErrLogFile),
	FILEINFO(g_MotorConfig),
	{0,0},						// £”‡ø’º‰
};
