/*
 * Types.h
 *
 *      Module: System
 *  Created on: 2013-3-7
 *      Author: AMSKY Technology Co.,Ltd
 *
 *	Table 13¨C1. GCC C/C++ 32-bit Processor Constants
 *				C Data Type 									Examples
 *	boolean (char, short, int) 								1, 0
 *	32-bit signed integer (int, long) 						123, -50
 *	32-bit unsigned integer (unsigned int, unsigned long) 	123u, 0xef8472a0
 *	64-bit signed integer (long long int) 					4294967296LL, -4294967296LL
 *	64-bit unsigned integer (unsigned long long int) 		4294967296ULL, 0xac458701fd64ULL
 *	32-bit floating-point (float) 							3.14f
 *	64-bit floating-point (double) 							2.78, 314e-2
 *	character (char) 										'x'
 *	string (const char*) 									"Hello World!"
 */

#ifndef __TYPES_H__
#define __TYPES_H__

/*
 * In the interest of portability, the HAL uses a set of standard type definitions in place of
 * the ANSI C built-in types. Table 14¨C2 describes these types, which are defined in the
 * header file alt_types.h.
 * Table 14¨C2. Standard Types
 * Type		Description
 * alt_8 	Signed 8-bit integer.
 * alt_u8 	Unsigned 8-bit integer.
 * alt_16 	Signed 16-bit integer.
 * alt_u16 	Unsigned 16-bit integer.
 * alt_32 	Signed 32-bit integer.
 * alt_u32 	Unsigned 32-bit integer.
 * alt_64 	Signed 64-bit integer.
 * alt_u64 	Unsigned 64-bit integer.
 */

//#include "alt_types.h"

typedef int 			int32;
typedef unsigned int 	Uint32;
typedef volatile Uint32	VUint32;

typedef short 			int16;
typedef unsigned short 	Uint16;
typedef float 			float32;
typedef double 			float64;

typedef float 			DB32;
typedef double 			DB64;

typedef	unsigned char 	U8;
typedef volatile U8 	VU8;
typedef	const U8 		CU8;

typedef	unsigned short 	U16;
typedef volatile U16 	VU16;
typedef	const U16 		CU16;

typedef unsigned long 	U32;
typedef volatile U32 	VU32;
typedef const U32 		CU32;


typedef	signed char 	S8;
typedef volatile S8 	VS8;
typedef	const S8 		CS8;

typedef signed short 	S16;
typedef volatile S16 	VS16;
typedef const S16 		CS16;

typedef signed long 	S32;
typedef volatile S32 	VS32;
typedef const S32 		CS32;


typedef U32 			QN;
#define QN_1(n)			(1UL << (n))
#define QN_MASK(n) 		(QN_1(n) - 1)

typedef U32 			Q27;
#define Q27_1			QN_1(27)
#define Q27_MASK		QN_MASK(27)
typedef U32 			Q26;
#define Q26_1			QN_1(26)
#define Q26_MASK		QN_MASK(26)
typedef U32 			Q25;
#define Q25_1			QN_1(25)
#define Q25_MASK		QN_MASK(25)
typedef U32 			Q24;
#define Q24_1			QN_1(24)
#define Q24_MASK		QN_MASK(24)
typedef U32 			Q23;
#define Q23_1			QN_1(23)
#define Q23_MASK		QN_MASK(23)
typedef U32 			Q22;
#define Q22_1			QN_1(22)
#define Q22_MASK		QN_MASK(22)
typedef U32 			Q21;
#define Q21_1			QN_1(21)
#define Q21_MASK		QN_MASK(21)
typedef U32 			Q20;
#define Q20_1			QN_1(20)
#define Q20_MASK		QN_MASK(20)
typedef U32 			Q19;
#define Q19_1			QN_1(19)
#define Q19_MASK		QN_MASK(19)
typedef U32 			Q18;
#define Q18_1			QN_1(18)
#define Q18_MASK		QN_MASK(18)
typedef U32 			Q17;
#define Q17_1			QN_1(17)
#define Q17_MASK		QN_MASK(17)
typedef U32 			Q16;
#define Q16_1			QN_1(16)
#define Q16_MASK		QN_MASK(16)
typedef U32				Q15;
#define Q15_1			QN_1(15)
#define Q15_MASK		QN_MASK(15)
typedef U32				Q14;
#define Q14_1			QN_1(14)
#define Q14_MASK		QN_MASK(14)
typedef U32				Q13;
#define Q13_1			QN_1(13)
#define Q13_MASK		QN_MASK(13)
typedef U32 			Q12;
#define Q12_1			QN_1(12)
#define Q12_MASK		QN_MASK(12)
typedef U32 			Q11;
#define Q11_1			QN_1(11)
#define Q11_MASK		QN_MASK(11)
typedef U32 			Q10;
#define Q10_1			QN_1(10)
#define Q10_MASK		QN_MASK(10)

typedef union Bit32
{
	U32		u32;
	U16 	u16[2];
	U8		u8[4];
	S32		s32;
	S16		s16[2];
	S8		s8[4];
	DB32	db32;
	QN		qn;
} Bit32_t;
typedef Bit32_t* Bit32_p;


#define MAX_U16			0xFFFF
#define MAX_U32			0xFFFFFFFF

#ifndef NULL
#define	NULL			0
#endif

#define NOERROR			0

#define byteof(x)		(sizeof(x))
#define wordof(x)		(sizeof(x)>>1)
#define dwordof(x)		(sizeof(x)>>2)

#define NIOS_ALIGNED_4 __attribute__ ((aligned(4)))


#endif // __TYPES_H__
