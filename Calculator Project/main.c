#include "StdTypes.h"

#include "DIO_Int.h"
#include "KEYPAD_Int.h"
#include "LCD_Int.h"
#include "CALC_Int.h"

int main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	CALC_Init();
	
	while(1)
	{
			CALC_Runnable();	
	}
}

