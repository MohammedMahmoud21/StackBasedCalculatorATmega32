/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : ICU_Interface.h																			*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/ 


#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_


typedef enum
{
	ICU_FALLING=0,
	ICU_RISING
	
}ICU_SenseControl_t;

void MCAL_ICU_voidInit(void);

void MCAL_ICU_voidSetSenseControl(ICU_SenseControl_t Copy_SenseType);
void MCAL_ICU_voidEnableICUIRQ(void);
void MCAL_ICU_voidDisableICUIRQ(void);
void MCAL_ICU_voidSetCallBack(void (*Copy_PF)(void));

#endif /* ICU_INTERFACE_H_ */