/*
 * LCD_Int.c
 *
 * Created: 28/01/2024 07:49:33 ص
 *  Author: Fathy
 */ 

#include "StdTypes.h"
#include "BitMath.h"
#include "DIO_Int.h"
#include "LCD_Cfg.h"
#include "LCD_Int.h"
#include "LCD_priv.h"

#define  F_CPU   8000000
#include <util/delay.h>


#if LCD_DATA_LENTH == _4_BITS
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(LCD_D7,READ_BIT(ins,7));
	DIO_WritePin(LCD_D6,READ_BIT(ins,6));
	DIO_WritePin(LCD_D5,READ_BIT(ins,5));
	DIO_WritePin(LCD_D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(LCD_D7,READ_BIT(ins,3));
	DIO_WritePin(LCD_D6,READ_BIT(ins,2));
	DIO_WritePin(LCD_D5,READ_BIT(ins,1));
	DIO_WritePin(LCD_D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(LCD_D7,READ_BIT(data,7));
	DIO_WritePin(LCD_D6,READ_BIT(data,6));
	DIO_WritePin(LCD_D5,READ_BIT(data,5));
	DIO_WritePin(LCD_D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(LCD_D7,READ_BIT(data,3));
	DIO_WritePin(LCD_D6,READ_BIT(data,2));
	DIO_WritePin(LCD_D5,READ_BIT(data,1));
	DIO_WritePin(LCD_D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);  // Function set
	WriteIns(LCD_DISPLAY_CURSOR);  // display ON/OFF control
	WriteIns(0x01);  // Clear
	_delay_ms(1);
	WriteIns(0x06);  // Entry mode	
}
#elif LCD_DATA_LENTH == _8_BITS

static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);  // Function set
	WriteIns(LCD_DISPLAY_CURSOR);  // display ON/OFF control
	WriteIns(0x01);  // Clear
	_delay_ms(1);
	WriteIns(0x06);  // Entry mode
	
}
#endif

void LCD_WriteChar(u8 data)
{
	WriteData(data);
}
void LCD_WriteNumber(s32 num)
{
	s32 n=num;
	u8 str[12],i,len,flag_sign=0;
	if(num == 0)
	{
		LCD_WriteChar('0');
	}
	if(num<0)
	{
		flag_sign=1;
		num=-num;
	}
	for(len=0;n;len++)
	{
		n/=10;
	}
	if(flag_sign==1)
	{
		str[0]='-';
		len++;
	}
	for(i=0;num;i++)
	{
		str[len-i-1]=(num%10)+'0';
		num/=10;
	}
	str[len]=0;
	
	LCD_WriteString(str);
}

void LCD_WriteBinary(u8 num)
{
	u8 str[(sizeof(num)*8)+1],i;
	for(i=0;i<(sizeof(num)*8);i++)
	{
		str[(sizeof(num)*8)-1-i]=(num%2)+'0';
		num=num>>1;
	}
	str[i]='\0';
	LCD_WriteString(str);
	
}
void LCD_WriteHex(u8 num)
{
	u8 str[(sizeof(num)*2)+1],i;
	for (i=0;i<(sizeof(num)*2);i++)
	{
		switch(num%16)
		{
			case 0  ... 9  : str[(sizeof(num)*2)-1-i]=(num%16)+'0'; break;
			case 10 ... 15 : str[(sizeof(num)*2)-1-i]=(num%16)+'A'-10; break;
		}
		num=num>>4;
	}
	str[i]='\0';
	LCD_WriteString(str);
	
}

void LCD_WriteString(u8 *str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}

void LCD_WriteString_CharByChar(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		WriteData(str[i]);
		_delay_ms(100);
	}
}


void LCD_SetCursor(u8 row,u8 col)
{
	if(row == 1)
	{
		WriteIns(0x80|(col-1));
	}
	else if(row==2)
	{
		WriteIns(0x80|0x40|(col-1));
	}
}

void LCD_ClearDisplay(void)
{
	WriteIns(0x01);  
	_delay_ms(1);
}

void LCD_SnakeWordDisplay(u8*str)
{
	u8 i=0,j=0;
	
	for(j=0;j<LCD_LENTH;j++)
	{
		LCD_ClearDisplay();
		for(i=0;str[i];i++)
		{
			if((i+j) > LCD_LENTH-1)
			{
				LCD_SetCursor(1,j+i+1-LCD_LENTH);
			}
			else
			{
				LCD_SetCursor(1,j+i+1);
			}
			
			LCD_WriteChar(str[i]);
		}
		_delay_ms(150);
	}
}
// 
// void LCD_Arrow(void)
// {
// 	u8 i;
// 	LCD_SetCursor(1,1);
// 	LCD_WriteChar(MAN);
// 	LCD_WriteChar(LEFT_BOW);
// 	
// 	LCD_SetCursor(1,15);
// 	LCD_WriteChar(RIGH_BOW);
// 	LCD_WriteChar(MAN);
// 	
// 	for(i=3;i<LCD_LENTH-1;i++)
// 	{
// 		LCD_SetCursor(1,i);
// 		LCD_WriteChar(ARROW);
// 		_delay_ms(100);
// 		LCD_SetCursor(1,i);
// 		LCD_WriteChar(' ');
// 	}
// 	LCD_WriteChar(' ');
// 	LCD_WriteChar(DEAD_MAN);
// 	_delay_ms(1000);
// 	
// 
// }

void LCD_AddCustom(u8 position,u8*data)
{
	u8 i;
	WriteIns(0x40+(position*8));
	for(i=0;i<8;i++)
	{			
		WriteData(data[i]);
	}
	WriteIns(0x80);
}