/*
 * LCD_Int.h
 *
 * Created: 28/01/2024 07:49:53 ص
 *  Author: Fathy
 */ 

#ifndef LCD_INT_H_
#define LCD_INT_H_

void LCD_Init(void);

void LCD_WriteChar(u8);
void LCD_WriteNumber(s32);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteString(u8*str);
void LCD_WriteString_CharByChar(u8*str);

void LCD_SetCursor(u8 row,u8 col);
void LCD_ClearDisplay(void);
void LCD_SnakeWordDisplay(u8*str);
void LCD_Arrow(void);

void LCD_AddCustom(u8 position,u8*data);

#endif /* LCD_INT_H_ */