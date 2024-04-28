/*
 * DIO_Prg.c
 *
 * Created: 26/01/2024 03:55:02 ص
 *  Author: Fathy
 */ 

#include "StdTypes.h"
#include "MemMap.h"
#include "BitMath.h"

#include "DIO_Int.h"
#include "DIO_Priv.h"
#include "DIO_Cfg.h"


static void DIO_InitPin(DIO_Pin_t pin,DIO_PinStatus_t status)
{
	DIO_Port_t port = pin/8;
	u8 PinNum = pin%8;
	
	switch(status)
	{
		case INFREE:  
			switch (port)
			{
				case PA: 
					CLR_BIT(DDRA,PinNum);
					CLR_BIT(PORTA,PinNum);
					break;
				case PB:
					CLR_BIT(DDRB,PinNum);
					CLR_BIT(PORTB,PinNum);
					break;
				case PC:
					CLR_BIT(DDRC,PinNum);
					CLR_BIT(PORTC,PinNum);
					break;
				case PD:
					CLR_BIT(DDRD,PinNum);
					CLR_BIT(PORTD,PinNum);
					break;
			}		
			break;
			
		case INPULL:
			switch (port)
			{
				case PA:
				CLR_BIT(DDRA,PinNum);
				SET_BIT(PORTA,PinNum);
				break;
				case PB:
				CLR_BIT(DDRB,PinNum);
				SET_BIT(PORTB,PinNum);
				break;
				case PC:
				CLR_BIT(DDRC,PinNum);
				SET_BIT(PORTC,PinNum);
				break;
				case PD:
				CLR_BIT(DDRD,PinNum);
				SET_BIT(PORTD,PinNum);
				break;
			}
			break;
			
		case OUTPUT:
			switch (port)
			{
				case PA:
				SET_BIT(DDRA,PinNum);
				CLR_BIT(PORTA,PinNum);
				break;
				case PB:
				SET_BIT(DDRB,PinNum);
				CLR_BIT(PORTB,PinNum);
				break;
				case PC:
				SET_BIT(DDRC,PinNum);
				CLR_BIT(PORTC,PinNum);
				break;
				case PD:
				SET_BIT(DDRD,PinNum);
				CLR_BIT(PORTD,PinNum);
				break;
			}
			break;
	}
}


void DIO_WritePin(DIO_Pin_t pin,DIO_PinVoltage_t volt)
{
	DIO_Port_t port = pin/8;
	u8 PinNum = pin%8;
	
	if(volt==HIGH)
	{
		switch (port)
		{
			case PA:
			SET_BIT(PORTA,PinNum);
			break;
			case PB:
			SET_BIT(PORTB,PinNum);
			break;
			case PC:
			SET_BIT(PORTC,PinNum);
			break;
			case PD:
			SET_BIT(PORTD,PinNum);
			break;
		}
	}
	else
	{
		switch (port)
		{
			case PA:
			CLR_BIT(PORTA,PinNum);
			break;
			case PB:
			CLR_BIT(PORTB,PinNum);
			break;
			case PC:
			CLR_BIT(PORTC,PinNum);
			break;
			case PD:
			CLR_BIT(PORTD,PinNum);
			break;
		}
	}
}

DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_t pin)
{
	DIO_Port_t port = pin/8;
	u8 PinNum = pin%8;
	
	DIO_PinVoltage_t volt=LOW;
	switch (port)
	{
		case PA:
		volt=READ_BIT(PINA,PinNum);
		break;
		case PB:
		volt=READ_BIT(PINB,PinNum);
		break;
		case PC:
		volt=READ_BIT(PINC,PinNum);
		break;
		case PD:
		volt=READ_BIT(PIND,PinNum);
		break;		
	}
	return volt;	
}

void DIO_Init(void)
{
	DIO_Pin_t i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,DIO_PinsStatusArray[i]);
	}
}

void DIO_TogglePin(DIO_Pin_t pin)
{
	DIO_Port_t port=pin/8;
	u8 PinNum=pin%8;
	
	switch (port)
	{
		case PA:
		TOG_BIT(PORTA,PinNum);
		break;
		case PB:
		TOG_BIT(PORTB,PinNum);
		break;
		case PC:
		TOG_BIT(PORTC,PinNum);
		break;
		case PD:
		TOG_BIT(PORTD,PinNum);
		break;
	}
}

void DIO_WritePort(DIO_Port_t port,u8 data)
{
	switch (port)
	{
		case PA:
		PORTA=data;
		break;
		case PB:
		PORTB=data;
		break;
		case PC:
		PORTC=data;
		break;
		case PD:
		PORTD=data;
		break;
	}
}

u8 DIO_ReadPort(DIO_Port_t port)
{
	u8 data=0;
	
	switch (port)
	{
		case PA:
		data=PORTA;
		break;
		case PB:
		data=PORTB;
		break;
		case PC:
		data=PORTC;
		break;
		case PD:
		data=PORTD;
		break;
	}
	
	return data;
	
}