
#define  PINB (*(volatile unsigned char*)0x36)
#define  DDRB (*(volatile unsigned char*)0x37)
#define  PORTB (*(volatile unsigned char*)0x38)

#define  F_CPU   8000000
#include <util/delay.h>
volatile char i,carry;

int main(void)
{
	DDRB  =0xff;
	PORTB =0x0;
	
	while (1) 
    {
		for(i=0;i<8;i++)
		{
			PORTB=PORTB|(1<<i);
			_delay_ms(100);
		}
		for(i=7;i>=0;i--)
		{
			PORTB=PORTB&(~(1<<i));
			_delay_ms(100);
		}
    }
}
