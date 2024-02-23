

#define  PINA  (*(volatile unsigned char*)0x39)
#define  DDRA  (*(volatile unsigned char*)0x3a)
#define  PORTA (*(volatile unsigned char*)0x3b)

#define  F_CPU   8000000
#include <util/delay.h>

#define SET_BIT(X,N)       (X)=(X)|(1<<(N))
#define CLR_BIT(X,N)     (X)=(X)&(~(1<<(N)))

volatile char i,carry;

int main(void)
{
	DDRA  =0xff;
	PORTA =0x0;
	
	while (1) 
    {
		SET_BIT(PORTA,0);
		_delay_(1000);
		CLR_BIT_BIT(PORTA,0);
		_delay_(1000);
    }
}
