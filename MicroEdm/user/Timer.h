#ifndef _TIMER_H
#define _TIMER_H

#include "stdtypes.h"

void Timer2_Init(void);
void Timer3_Init(void);
void Timer2_Reset(void);
void Timer3_Reset(void);

extern U32 g_MS;

typedef struct
{
	U32 m_ulStartMS;
	U32 m_ulPeriodMS;
} Timer_t;
typedef Timer_t* Timer_p;

#define TIMER_START(t)		((t).m_ulStartMS = g_MS)
#define TIMER_OVERFLOW(t)	((g_MS - (t).m_ulStartMS) >= (t).m_ulPeriodMS)

#define TIMER_STARTA(t)		((t)->m_ulStartMS = g_MS)
#define TIMER_OVERFLOWA(t)	((g_MS - (t)->m_ulStartMS) >= (t)->m_ulPeriodMS)

#define MS_1000		100000
#define MS_100		10000

#endif /*_TIMER_H */
