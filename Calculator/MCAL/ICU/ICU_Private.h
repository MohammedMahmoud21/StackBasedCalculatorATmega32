/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : ICU_Private.h																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/

#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_

#define ICU_CONFIG_FALLING	0
#define ICU_CONFIG_RISING	1

#define ICR1         (*(volatile u16*)0x46)
#define ICR1L		 (*(volatile u8*)0x46)
#define ICR1H		 (*(volatile u8*)0x47)
#define TCCR1B       (*(volatile u8*)0x4E)
#define TIMSK		 (*(volatile u8*)0x59)

#define TIMER1_CAPT_VECT		__vector_6

#define ISR(vector,...)   void vector(void) __attribute__ ((signal)); __VA_ARGS__ \
void vector(void)

#define ICES1	6
#define TICIE1	5




#endif /* ICU_PRIVATE_H_ */