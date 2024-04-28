/*
 * LCD_Cfg.h
 *
 * Created: 28/01/2024 07:50:38 ص
 *  Author: Fathy
 */ 

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


/* LCD Pins configuration */
#define  RS        PINA1
#define  EN        PINA2

//choose LCD port for 8-bit mode
#define  LCD_PORT  PC
//choose LCD pins for 4-bit mode
#define  LCD_D4    PINA3
#define  LCD_D5    PINA4
#define  LCD_D6    PINA5
#define  LCD_D7    PINA6

// Set cursor & display 
#define  LCD_DISPLAY_CURSOR      DISPLAY_ON_CURSOR_OFF         // (DISPLAY_OFF,DISPLAY_ON_CURSOR_OFF,DISPLAY_ON_CURSOR_BLINK,DISPLAY_ON_CURSOR_NO_BLINK)

// LCD Mode (_4_BITS or _8_BITS)
#define  LCD_DATA_LENTH          _4_BITS 


#define LCD_LENTH  16


#endif /* LCD_CFG_H_ */