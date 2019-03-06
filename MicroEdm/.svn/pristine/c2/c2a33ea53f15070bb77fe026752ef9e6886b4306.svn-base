#ifndef __SYS_TICK_H
#define __SYS_TICK_H

#include "stdint.h"

typedef enum 
{
	 TIME_MODE_MS = 1000,
	 TIME_MODE_US = 1000000
}TIME_MODE;

uint32_t sysTickInit(TIME_MODE mode);
uint64_t sysGetTickCounter(void);
void sysTickHandle(void);
void sleep(uint64_t sTimeout);
void msleep(uint64_t mTimeout);
TIME_MODE GetTimeMode(void);


#endif

