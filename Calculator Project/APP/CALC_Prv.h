/*
 * CALC_Prv.h
 *
 * Created: 05/02/2024 03:54:01 م
 *  Author: Fathe
 */ 


#ifndef CALC_PRV_H_
#define CALC_PRV_H_

#define  INPUT_STR_SIZE 24

typedef enum {
	
	GETTING_INPUT,
	VERFING_INPUT,
	SEPARATING_INPUT,
	CALCULATING_RESULT,
	NEXT_INSREUCTION
	
	}CALC_state_t;

typedef enum {
	
	VALID,
	INVALID
	
}CALC_InputStatus_t;

typedef struct{
	
	s16 operand1_num;
	s16 operand2_num;
	u8 operand1_str[7];
	u8 operand2_str[7];
	u8 operation;
	
	}CALC_InputElements_t;


static void CALC_GetInput(void);
static void CALC_VerifyInput(void);
static void CALC_SeparateInput(void);
static void CALC_CalculatingResult(void);
static void CALC_NextInstruction(void);

static void CALC_Reset(void);

#endif /* CALC_PRV_H_ */