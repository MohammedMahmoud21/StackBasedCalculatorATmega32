/***************************************************************************************/
/***************************************************************************************/
/**************************** Author : Mohammed Elsayaad *******************************/
/**************************** Date : 9 June,2023         *******************************/
/**************************** Describtion: DIO Functions interface file   **************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "StdTypes.h"

typedef enum
{
	DIO_PORTA=0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
} PORT_TYPE ;

typedef enum
{
	LOW,
	HIGH
} Logic_TYPE;

typedef enum
{
	INFREE,
	INPULL,
	OUTPUT
} MODE_TYPE;
typedef enum 
{
	PA0=0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	
	PB0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	PC7,
	
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	PIN_TOTAL_NUMBER
} PIN_TYPE;


extern void DIO_voidInit(void);
extern void DIO_voidSetPinDirection(PIN_TYPE Copy_xPin,MODE_TYPE Copy_xMode);
extern void DIO_voidWritePin(PIN_TYPE Copy_xPin, Logic_TYPE Copy_xLogic);
extern void DIO_voidTogglePin(PIN_TYPE Copy_xPin);
extern Logic_TYPE DIO_xReadPinStatus(PIN_TYPE Copy_xPin);

extern void DIO_voidWritePort(PORT_TYPE Copy_xPort, u8 Copy_u8Value);





#endif /* DIO_INTERFACE_H_ */