/*
 * KEYPAD_Cfg.h
 *
 * Created: 03/02/2024 04:35:56 م
 *  Author: Fathe
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define KEYPAD_FIRST_INPUT   PIND2
#define KEYPAD_FIRST_OUTPUT  PINB4 

#define KEYPAD_ROWS	4
#define KEYPAD_COLS	4

//#define DEFAULT_KEY 'T'

u8 KEYPAD_array [KEYPAD_ROWS][KEYPAD_COLS] = {  {'7','8','9','/'},
												{'4','5','6','*'},
												{'1','2','3','-'},
												{'c','0','=','+'} };



#endif /* KEYPAD_CFG_H_ */