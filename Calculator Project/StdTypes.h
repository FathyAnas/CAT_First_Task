/*
 * StdTypes.h
 *
 * Created: 26/01/2024 03:11:31 ص
 *  Author: Fathy
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char  u8;
typedef signed char    s8;
typedef char           c8;

typedef unsigned short u16;
typedef signed short   s16;

typedef unsigned long  u32;
typedef signed long    s32;

#define NULL_PTR     ((void*)0)
#define NULL_CHAR    ('\0')


typedef enum 
{
	FALSE=0,
	TRUE=1
	}bool_t;
	
typedef enum
{
	OK,
	NOK,
	NULL_PT,
	OUT_OF_RANGE
	}error_t;

#define  MAX_u8   ((u8)255)
#define  MIN_u8   ((u8)0)

#define  MAX_S8   ((s8)127)
#define  MIN_S8   ((s8)-128)
#define  ZERO_S8  ((s8)0)

#define  MAX_u16  ((u16)65535)
#define  MIN_u16  ((u16)0)

#define  MAX_S16  ((s8)32767)
#define  MIN_S16  ((s8)-32768)
#define  ZERO_S16 ((s8)0)

#define  MAX_u32  ((u8)4294967295)
#define  MIN_u32  ((u8)0)

#define  MAX_S32  ((s32)2147483647)
#define  MIN_S32  ((s32)-2147483648)
#define  ZERO_S32 ((s32)0)



#endif /* STDTYPES_H_ */