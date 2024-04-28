/*
 * LCD_priv.h
 *
 * Created: 28/01/2024 09:28:25 ص
 *  Author: Fathy
 */ 

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

      /*        LCD Mode         */
#define  _4_BITS		4
#define  _8_BITS		8

	  /* Display & cursor status */
#define  DISPLAY_OFF                   0x08
#define  DISPLAY_ON_CURSOR_OFF		   0x0C
#define  DISPLAY_ON_CURSOR_BLINK       0x0F
#define  DISPLAY_ON_CURSOR_NO_BLINK    0x0E

static void WriteIns(u8 data);
static void WriteData(u8 data);


#endif /* LCD_PRIV_H_ */