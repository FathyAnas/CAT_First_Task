/*
 * KEYPAD_Prg.c
 *
 * Created: 03/02/2024 04:33:47 م
 *  Author: Fathy
 */ 

#include "StdTypes.h"
#include "BitMath.h"
#include "DIO_Int.h"

#include "KEYPAD_Int.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_Prv.h"

#define  F_CPU   8000000
#include <util/delay.h>


void KEYPAD_Init (void)
{
	u8 i;
	for(i=0;i<KEYPAD_ROWS;i++)
	{
		DIO_WritePin(KEYPAD_FIRST_OUTPUT+i,HIGH);
	}
}
u8 KEYPAD_GetKey (void)
{
	u8 row,col,key=DEFAULT_KEY;
	for(row=0;row<KEYPAD_ROWS;row++)
	{
		DIO_WritePin(KEYPAD_FIRST_OUTPUT+row,LOW);
		for(col=0;col<KEYPAD_COLS;col++)
		{
			
			if(DIO_ReadPin(KEYPAD_FIRST_INPUT+col)==LOW)
			{
				key=KEYPAD_array[row][col];
				
				_delay_ms(5);
				while(DIO_ReadPin(KEYPAD_FIRST_INPUT+col)==LOW);
				_delay_ms(5);
			}
		}
		DIO_WritePin(KEYPAD_FIRST_OUTPUT+row,HIGH);
	}
	return key;
}