/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : ICU_Program.c																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/

#include "StdTypes.h"
#include "Utiles.h"

/**************/

#include "ICU_Interface.h"
#include "ICU_Private.h"

/*****************************************************************/

static void (*ICU_PF)(void) = NULL_PTR;

/******************** External  APIs Implementatio**************************************/

void MCAL_ICU_voidInit(void)
{
	#if ICU_SENSE_CONTROL == ICU_CONFIG_FALLING
		SET_BIT(TCCR1B,ICES1);
	#elif ICU_SENSE_CONTROL == ICU_CONFIG_RISING
		CLR_BIT(TCCR1B,ICES1);
	#else
		#error "ICU CONFIG ERROR"
	#endif
	SET_BIT(TIMSK,TICIE1);
}

void MCAL_ICU_voidSetSenseControl(ICU_SenseControl_t Copy_SenseType)
{
	if(ICU_RISING == Copy_SenseType)
	{
		SET_BIT(TCCR1B,ICES1);
	}
	else if(ICU_FALLING == Copy_SenseType)
	{
		CLR_BIT(TCCR1B,ICES1);
	}
	else
	{
		/*Error */
	}
}

void MCAL_ICU_voidEnableICUIRQ(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void MCAL_ICU_voidDisableICUIRQ(void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void MCAL_ICU_voidSetCallBack(void (*Copy_PF)(void))
{
	ICU_PF = Copy_PF;
}


ISR(TIMER1_CAPT_VECT)
{
	if(NULL_PTR != ICU_PF)
	{
		ICU_PF();
	}
	else
	{
		/*Error*/
	}
}