#include "MemoryCopy.h"

void MemCpy(void *dest, const void *src, U16 ushWords)
{
	U16* pDes = (U16*)dest;
	U16* pSrc = (U16*)src;
	U16 i = 0;
	while(i < ushWords)
	{
		pDes[i] = pSrc[i];
		i++;
	}
}
void MemSet(void *dest, U16 c, U16 ushWords)
{
	U16* pDes = (U16*)dest;
	U16 i = 0;
	while(i < ushWords)
	{
		pDes[i] = c;
		i++;
	}
}
