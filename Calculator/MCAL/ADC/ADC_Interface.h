/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : ADC_Interface.h																			*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


typedef enum
{
	ADC_AREF=0,
	ADC_VCC,
	ADC_INTERNAL_256
}VoltageRef_t;

typedef enum
{
	ADC_CH0=0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7
}Channel_t;

typedef enum
{
	ADC_DIV_2=1,
	ADC_DIV_4,
	ADC_DIV_8,
	ADC_DIV_16,
	ADC_DIV_32,
	ADC_DIV_64,
	ADC_DIV_128
}PreScaller_t;

typedef enum
{
	ADC_RIGHT=0,
	ADC_LEFT
}ADC_Adjust_t;

typedef struct
{
	PreScaller_t Pre;
	VoltageRef_t Volt;
	ADC_Adjust_t Adjust;
}ADC_Config_t;

typedef enum
{
	OK,
	NOK
}ADC_Conv_Status_t;

typedef enum
{
	ADC_FREE_RUNNING=0,
	ADC_ANALOG_COMP,
	ADC_EXT0,
	ADC_TIMER_COMP0,
	ADC_TIMER_OVF0,
	ADC_TIMER_COMP1,
	ADC_TIMER_OVF1,
	ADC_TIMER_CAPT1
}ADC_Trigger_Source_t;

/************************************ External APIs Decleration ***************************************************/

void 				 MCAL_ADC_voidInit(const ADC_Config_t *Copy_pConfig);
ADC_Conv_Status_t 	 MCAL_ADC_ReadPeriodic(u16 *Copy_pu16Read);
void 				 MCAL_ADC_voidSelectChannel(Channel_t Copy_Channel);
void 			     MCAL_ADC_voidEnable(void);
void 				 MCAL_ADC_voidDisable(void);
void 				 MCAL_ADC_voidSetCallBack(void (*Copy_pFunc)(void));
void 				 MCAL_ADC_voidSetADCTrigSrc(ADC_Trigger_Source_t Copy_Source);

#endif