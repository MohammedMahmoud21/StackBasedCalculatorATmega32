/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : UART_Program.c																				*/
/* @Date   : 12 May																						*/									
/********************************************************************************************************/

/*--------------------------------------------------------------------------------------------*/
/*   INCLUDES   */
/*--------------------------------------------------------------------------------------------*/
#include "StdTypes.h"
#include "Utiles.h"

#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Private.h"

/*--------------------------------------------------------------------------------------------*/
/*   GLOBAL VARIABLES   */
/*--------------------------------------------------------------------------------------------*/

u8 UART_BaudRate_Array[BAUD_RATE_ARRAY_SIZE] = 
{
	103,
	8,
	68
};

static void (*TX_CallBack)(void) = NULL_PTR;
static void (*RX_CallBack)(void) = NULL_PTR;

/*************** Asynch Transmit Global Vars ****************************/

static u8 TX_Buffer[TX_BUFFER_SIZE];
static u8 TX_Flag=1;
static u8 TX_u8Iterator=0;

static u8 *RX_Buffer[RX_BUFFER_SIZE];
static u8 RX_u8DataCounter=0;
static u8 RX_u8Iterator=0;

/*--------------------------------------------------------------------------------------------*/
/*   FUNCTIONS BODY   */
/*--------------------------------------------------------------------------------------------*/


void MCAL_UART_voidInit(UART_Config_t *Copy_Config)
{
	
	UBRRL = (u8)UART_BaudRate_Array[Copy_Config->Baud];
	//UBRRH = (UART_BaudRate_Array[Copy_Config->Baud] & 0xff00);
	SET_BIT(UCSRC,URSEL);
	UCSRC |= ((Copy_Config->Mode)<<6) | ((Copy_Config->Parity)<<4) | ((Copy_Config->Stop)<<3) | ((Copy_Config->Data)<<1);
	// transmission speed
	CLR_BIT(UCSRA,U2X);
	//enable UART  receiver.
	SET_BIT(UCSRB,RXEN);
	//enable UART  transmitter .
	SET_BIT(UCSRB,TXEN);
}
void MCAL_UART_voidSendData(u8 Copy_u8Data)
{
	UDR = Copy_u8Data;
	while(!READ_BIT(UCSRA,UDRE));
}
u8 MCAL_UART_voidReceiveData(void)
{
	u8 Received = 0;
	while(0 == READ_BIT(UCSRA,RXC));
	Received = UDR;
	return (Received);
}
/********************************************************/

void MCAL_UART_voidAsynchInit(void)
{
	SET_BIT(UCSRB,TXCIE); /*Enable Transmit interrupt*/
	SET_BIT(UCSRB,RXCIE); /*Enable Rx interrupt*/
}

u8 MCAL_UART_u8SendByteAsynch(u8 Copy_u8Data)
{
	static u8 One_u8TimeFlag=0;
	u8 Local_u8Error=0;
	if(0 == One_u8TimeFlag)
	{
		TX_CallBack = &MCAL_UART_voidSendAsynchByteISR;
		One_u8TimeFlag=1;
	}
	else{;}
	if(1 == TX_Flag)
	{
		UDR = Copy_u8Data;
		TX_Flag=0;
	}
	else
	{
		if(TX_u8Iterator < TX_BUFFER_SIZE)
		{
			TX_Buffer[TX_u8Iterator] = Copy_u8Data;
			TX_u8Iterator++;	
		}
		else
		{
			Local_u8Error =1; /*Full Buffer*/
		}
		
	}
	return (Local_u8Error);
}



u8 MCAL_UART_u8IsDataAvalible(void)
{
	u8 Local_u8RetVal=0;
	if(RX_u8DataCounter > 0)
	{
		Local_u8RetVal = RX_u8DataCounter;
		RX_u8DataCounter--;
	}
	else
	{
		Local_u8RetVal =0; /*No data was written*/	
	}
	return (Local_u8RetVal);
}

u8 MCAL_UART_u8ReadByteAsynch(u8 *Copy_u8Data)
{
	static u8 One_u8TimeFlag=0;
	u8 Local_u8Error=0;
	if(0 == One_u8TimeFlag)
	{
		RX_CallBack = &MCAL_UART_voidReadAsynchByteISR;
		One_u8TimeFlag=1;
	}
	else{;}
	
	if(RX_u8Iterator < RX_BUFFER_SIZE)
	{
		RX_Buffer[RX_u8Iterator] = Copy_u8Data;
		RX_u8Iterator++;	
	}
	else
	{
		Local_u8Error =1; /*Full buffer*/
	}
	
	return (Local_u8Error);
}


/********************* Static APIs Definitions ******************************/

static void MCAL_UART_voidSendNoBLock(u8 Copy_u8Data)
{
	UDR = Copy_u8Data;
}

static u8 MCAL_UART_voidReadNoBLock(void)
{
	return (UDR);
}

static void MCAL_UART_voidSendAsynchByteISR(void)
{
	static u8 TX_u8ISRIterator=0;
	if(TX_u8ISRIterator < TX_u8Iterator)
	{
		UDR = TX_Buffer[TX_u8ISRIterator];
		TX_u8ISRIterator++;
	}
	else
	{
		TX_u8Iterator=0;
		TX_u8ISRIterator=0;
		TX_Flag=1;
	}
}

static void MCAL_UART_voidReadAsynchByteISR(void)
{
	static u8 RX_u8Counter=0;
	if(RX_u8Counter < RX_u8Iterator)
	{
		/*Put data in address*/
		RX_Buffer[RX_u8Counter][0] = UDR;
		RX_u8Counter++;
		RX_u8DataCounter++;
	}
	else if(RX_u8Counter < RX_BUFFER_SIZE)
	{
		;
	}
	else
	{
		RX_u8Counter = 0;
	}
}

/********************* CallBacks **************************/

void MCAL_UART_voidSetCallBackTx(void (*PF)(void))
{
	TX_CallBack = PF;
}
void MCAL_UART_voidSetCallBackRX(void (*PF)(void))
{
	RX_CallBack = PF;
}

/*************************ISR****************************/

ISR(USART_RXC_VECT)
{
	if(NULL_PTR != RX_CallBack)
	{
		RX_CallBack();
	}
	else{;}
}

ISR(USART_TXC_VECT)
{
	if(NULL_PTR != TX_CallBack)
	{
		TX_CallBack();
	}
	else{;}
}

