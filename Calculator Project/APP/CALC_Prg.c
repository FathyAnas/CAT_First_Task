/*
 * CALC_Prg.c
 *
 * Created: 05/02/2024 03:47:23 م
 *  Author: Fathy
 */ 


#include "StdTypes.h"
#include "BitMath.h"

#define  F_CPU   8000000
#include <util/delay.h>
#include <string.h>
#include <stdlib.h> 

#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"

#include "CALC_Int.h"
#include "CALC_Prv.h"

/***********************************************************       Globl var      ****************************************************************/
static u8 CALC_InputStr[INPUT_STR_SIZE]; // 10 for max u16, 2 for 2(-ve sign), one for the operator, null
static u8 CALC_InputStrIndex; 
static s32 CALC_Result;
static CALC_InputElements_t CALC_InputElements;
static CALC_state_t CALC_status=GETTING_INPUT;

/***********************************************************    Init function    ****************************************************************/
void CALC_Init(void)
{
	LCD_SetCursor(1,5);
	LCD_WriteString_CharByChar((u8*)"Welcome");
	LCD_SetCursor(2,2);
	LCD_WriteString_CharByChar((u8*)"To Calculator");
	_delay_ms(1000);
	LCD_SetCursor(2,1);
	LCD_WriteString((u8*)"                ");
	LCD_SetCursor(2,1);
	LCD_WriteString_CharByChar((u8*)"By : Fathy Anas");
	_delay_ms(1000);
	LCD_ClearDisplay();
}

/***********************************************************    Runnable Function    ****************************************************************/

void CALC_Runnable(void)
{
	switch(CALC_status)
	{
		case GETTING_INPUT :
			CALC_GetInput();
			break;
		case VERFING_INPUT :
			CALC_VerifyInput();
			break;
		case SEPARATING_INPUT :
			CALC_SeparateInput();
			break;
		case CALCULATING_RESULT :
			CALC_CalculatingResult();
			break;
		case NEXT_INSREUCTION :
			CALC_NextInstruction();
			break;			
	}
}

static void CALC_GetInput(void)
{
	u8 key=DEFAULT_KEY;
	key=KEYPAD_GetKey();
	if(key==DEFAULT_KEY)
	{
		// do nothing
	}
	else if (key=='=')
	{
		CALC_InputStr[CALC_InputStrIndex]=NULL_CHAR;
		CALC_status=VERFING_INPUT;
		//verify
	} 
	else if (key=='c')
	{
		// reset 
		CALC_Reset();
	}
	else
	{
		CALC_InputStr[CALC_InputStrIndex]=key;
		CALC_InputStrIndex++;
		LCD_WriteChar(key);
	}
}

static void CALC_VerifyInput(void)
{
	CALC_InputStatus_t status = VALID;
	u8 i,opCount=0;
	
	/* If the first char is operation except '-' for the negative sign */
	if(CALC_InputStr[0]=='*' || CALC_InputStr[0]=='/' || CALC_InputStr[0]=='+' )
	{
		// operation first
		status=INVALID; 
	}
	
	for(i=1;CALC_InputStr[i];i++)
	{
		if(CALC_InputStr[i]=='*' || CALC_InputStr[i]=='/' || CALC_InputStr[i]=='+' || CALC_InputStr[i]=='-' )
		{
			opCount++;
			if (opCount==2 
				&& (!(CALC_InputStr[i]=='-' && (CALC_InputStr[i-1]=='*' || CALC_InputStr[i-1]=='/' || CALC_InputStr[i-1]=='+' || CALC_InputStr[i-1]=='-') ))			)
			{
				// invalid 
				status=INVALID;
			}
			if (opCount>2)
			{
				// invalid
				status=INVALID;
			}
		}
	}
	if(CALC_InputStr[i-1]=='*' || CALC_InputStr[i-1]=='/' || CALC_InputStr[i-1]=='+' || CALC_InputStr[i-1]=='-')
	{
		// operation first
		status=INVALID;
	}
	
	if (status == VALID)
	{
		CALC_status=SEPARATING_INPUT;
	}
	else
	{
		LCD_SetCursor(2,1);
		LCD_WriteString((u8*)"Invalid input");
		_delay_ms(1000);
		CALC_Reset();
		
		CALC_status=GETTING_INPUT;
	}
}

static void CALC_SeparateInput(void)
{
	u8 i,j;
	for (i=0;;i++)
	{
		if((CALC_InputStr[i]=='*' || CALC_InputStr[i]=='/' || CALC_InputStr[i]=='+' || CALC_InputStr[i]=='-' ) && i!=0 )
		{
			break;
			CALC_InputElements.operand1_str[i]=NULL_CHAR;
		}
		CALC_InputElements.operand1_str[i] = CALC_InputStr[i];
	}
	CALC_InputElements.operation=CALC_InputStr[i];
	i++;
	for (j=0;CALC_InputStr[i];j++,i++)
	{
		CALC_InputElements.operand2_str[j] = CALC_InputStr[i];
	}
	CALC_InputElements.operand2_str[j]=NULL_CHAR;
	
	CALC_InputElements.operand1_num = atoi((c8 *)CALC_InputElements.operand1_str);
	CALC_InputElements.operand2_num = atoi((c8 *)CALC_InputElements.operand2_str);
	
	CALC_status=CALCULATING_RESULT;
	
}

static void CALC_CalculatingResult(void)
{
	switch(CALC_InputElements.operation)
	{
		case '+':
			CALC_Result=(s32)CALC_InputElements.operand1_num + CALC_InputElements.operand2_num;
			break;
		case '-':
			CALC_Result=(s32)CALC_InputElements.operand1_num - CALC_InputElements.operand2_num;
			break;
		case '*':
			CALC_Result=(s32)CALC_InputElements.operand1_num * CALC_InputElements.operand2_num;
			break;
		case '/':
			if( CALC_InputElements.operand2_num!=0)
			{
				CALC_Result=(s32)CALC_InputElements.operand1_num / CALC_InputElements.operand2_num;
			}
			else
			{
				LCD_SetCursor(2,1);
				LCD_WriteString((u8*)"Error:devision/0");
				_delay_ms(1000);
				CALC_Reset();
				CALC_status=NEXT_INSREUCTION;
				return;
			}		
			break;
	}
	LCD_SetCursor(2,1);
	LCD_WriteChar('=');
	LCD_WriteNumber(CALC_Result);
	_delay_ms(1000);
	
	CALC_status=NEXT_INSREUCTION;
}

static void CALC_NextInstruction(void)
{
	u8 key=KEYPAD_GetKey();
	s32 result_copy=CALC_Result;
	if (key=='c')
	{
		CALC_Reset();
		CALC_status=GETTING_INPUT;
	}
	else if (key=='+' || key=='-' || key=='*' || key=='/')
	{
		CALC_Reset();
		itoa(result_copy,(c8 *)CALC_InputStr,10);
		CALC_InputStrIndex=strlen((const c8 *)CALC_InputStr);
		CALC_InputStr[CALC_InputStrIndex++]=key;
		CALC_InputStr[CALC_InputStrIndex]=NULL_CHAR;
		
		LCD_WriteString(CALC_InputStr);
		CALC_status=GETTING_INPUT;
	}
	else if (key>='0' && key <='9')
	{
		CALC_Reset();
		CALC_InputStr[CALC_InputStrIndex]=key;
		CALC_InputStrIndex++;
		LCD_WriteChar(key);
		CALC_status=GETTING_INPUT;
	}
}
static void CALC_Reset(void)
{
	u8 i;
	
	LCD_ClearDisplay();
	CALC_InputStrIndex=0;
	CALC_Result=0; 
	CALC_InputElements.operand1_num=0;
	CALC_InputElements.operand2_num=0;
	CALC_InputElements.operation=NULL_CHAR;
	for (i=0;i<INPUT_STR_SIZE;i++)
	{
		if(i<7)
		{
			CALC_InputElements.operand1_str[i]=NULL_CHAR;
			CALC_InputElements.operand2_str[i]=NULL_CHAR;
		}
		CALC_InputStr[i]=NULL_CHAR;
	}

}