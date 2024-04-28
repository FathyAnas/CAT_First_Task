/*
 * DIO_Priv.h
 *
 * Created: 26/01/2024 03:59:54 ص
 *  Author: Fathy
 */ 


#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_


extern DIO_PinStatus_t DIO_PinsStatusArray[TOTAL_PINS];

static void DIO_InitPin(DIO_Pin_t pin,DIO_PinStatus_t status);



#endif /* DIO_PRIV_H_ */