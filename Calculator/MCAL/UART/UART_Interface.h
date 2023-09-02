/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : UART_Program.c																				*/
/* @Date   : 12 May																						*/							
/********************************************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "StdTypes.h"

/*--------------------------------------------------------------------------------------------*/
/*   DEFINES   */
/*--------------------------------------------------------------------------------------------*/

typedef enum
{
	UART_9600,
	UART_115_2K,
	UART_14_4k,
	BAUD_RATE_ARRAY_SIZE
}UART_BaudRate_t;

typedef enum
{
	UART_ASYNCH,
	UART_SYNCH
}UART_Mode_t;	

typedef enum
{
	UART_NO_PARITY,
	UART_EVEN=2,
	UART_ODD

}UART_ParityMode_t;	

typedef enum
{
	UART_STOP_ONE=0,
	UART_STOP_TWO
}UART_StopBit_t;	

typedef enum
{
	UART_5BIT=0,
	UART_6BIT,
	UART_7BIT,
	UART_8BIT,
	UART_9BIT=7
}UART_DataSize_t;



typedef struct
{
	UART_BaudRate_t 	Baud;
	UART_Mode_t     	Mode;
	UART_ParityMode_t Parity;
	UART_StopBit_t      Stop;
	UART_DataSize_t		Data;
}UART_Config_t;

#define TX_BUFFER_SIZE	10
#define RX_BUFFER_SIZE	10

/*--------------------------------------------------------------------------------------------*/
/*   PROTOTYPES   */
/*--------------------------------------------------------------------------------------------*/

void MCAL_UART_voidInit(UART_Config_t *Copy_Config);
void MCAL_UART_voidSendData(u8 Copy_u8Data);
u8 MCAL_UART_voidReceiveData(void);


/************************************************/
void MCAL_UART_voidAsynchInit(void);
u8 MCAL_UART_u8SendByteAsynch(u8 Copy_u8Data);

u8 MCAL_UART_u8IsDataAvalible(void);
u8 MCAL_UART_u8ReadByteAsynch(u8 *Copy_u8Data);


/*************************************************/
void MCAL_UART_voidSetCallBackTx(void (*PF)(void));
void MCAL_UART_voidSetCallBackRX(void (*PF)(void));
#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
