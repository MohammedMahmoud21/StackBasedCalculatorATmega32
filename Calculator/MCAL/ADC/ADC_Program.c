/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : ADC_Program.c																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/

#include "StdTypes.h"
#include "Utiles.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Cnfig.h"



/**************** Global Vars Definitions **************************/

static void (*ADC_ISR)(void)=NULL_PTR;





/********************************************************************************************************/

void MCAL_ADC_voidInit(const ADC_Config_t *Copy_pConfig)
{
	ADCSRA |= (Copy_pConfig->Pre);//set channel
	ADMUX = ((Copy_pConfig->Adjust)<<5)| ((Copy_pConfig->Volt)<<6);
}
void MCAL_ADC_voidSelectChannel(Channel_t Copy_Channel)
{
	if(ADC_FALSE == READ_BIT(ADCSRA,ADSC))
	{
		/*Select Channel*/
		ADMUX &= ~(ADC_REG_MASK <<4); 
		ADMUX |= Copy_Channel;
		/*Start Conversion*/
		SET_BIT(ADCSRA,ADSC);	
	}
	else
	{
		/*Noting*/
	}
	
	
}
ADC_Conv_Status_t 	 MCAL_ADC_ReadPeriodic(u16 *Copy_pu16Read)
{
	ADC_Conv_Status_t Local_State = NOK;
	if(ADC_FALSE == READ_BIT(ADCSRA,ADSC))
	{
		*Copy_pu16Read = ADCR;
		Local_State = OK;
	}
	else
	{
		Local_State = NOK;
	}

	return (Local_State);
}

void MCAL_ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADEN);
}
void MCAL_ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA,ADEN);
}

void MCAL_ADC_voidSetCallBack(void (*Copy_pFunc)(void))
{
	ADC_ISR = Copy_pFunc;
}


void MCAL_ADC_voidSetADCTrigSrc(ADC_Trigger_Source_t Copy_Source)
{
	SFIOR &= ~(ADC_REG_MASK << 5);
	SFIOR |= (Copy_Source << 5);
	if(ADC_FREE_RUNNING == Copy_Source)
	{
		SET_BIT(ADCSRA,ADATE);/*Enable Auto trigger*/
		SET_BIT(ADCSRA,ADSC); /*Start Conversion*/
	}
	else
	{
		/*Nothing*/
	}
	
	
}

/*************************** ISR *************************/

ISR(ADC_VECT)
{
	if(NULL_PTR == ADC_ISR)
	{
		/*Nothing*/
	}
	else
	{
		ADC_ISR();
	}
}





