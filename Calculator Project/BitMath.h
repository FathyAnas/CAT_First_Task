/*
 * BitMath.h
 *
 * Created: 26/01/2024 03:38:43 ص
 *  Author: Fathy
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_

#define CLR_BIT(X,N)     (X)=(X)&(~(1<<(N)))
#define READ_BIT(X,N)          (((X)>>(N))&1)
#define TOG_BIT(X,N)       (X)=(X)^(1<<(N))
#define SET_BIT(X,N)       (X)=(X)|(1<<(N))



#endif /* BITMATH_H_ */