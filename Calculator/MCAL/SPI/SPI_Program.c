/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : SPI_Cnfig.h																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/


/******************* Lib Includes ******************************/
#include "StdTypes.h"
#include "BitMath.h"
/******************* Driver Includes **********************/
#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Cnfg.h"
#include "DIO_interface.h"

/***********************************************************************************/

void SPI_voidInit(void)
{
	//enable
	SET_BIT(SPCR,SPE);
	/**************** Mode **********************/
	#if	  SPI_MODE == SPI_MASTER
		DIO_voidSetPinDirection(PB5,OUTPUT); //MOSI
		DIO_voidSetPinDirection(PB6,INFREE); //MISO
		DIO_voidSetPinDirection(PB7,OUTPUT); //clk
		SET_BIT(SPCR,MSTR);
	#elif SPI_MODE	== SPI_SLAVE
		CLR_BIT(SPCR,MSTR);
	#else
		#error "Error SPI Config"
	#endif
	/*************Big or littel endian**************/
	#if	  SPI_DATA_ORDER    == SPI_MSB
		CLR_BIT(SPCR,DORD);
	#elif SPI_DATA_ORDER	== SPI_LSB
		SET_BIT(SPCR,DORD);
	#else
		#error "Error SPI Config"
	#endif
	/**************Clock phase and polarity*************************/
	#if	  SPI_TRANSMITE_MODE    == SPI_LOW_POLARTITY_SAMPLE_R_SETUP_F
	/*Nothing*/
	#elif SPI_TRANSMITE_MODE	== SPI_LOW_POLARTITY_SAMPLE_F_SETUP_R
		CLR_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	#elif SPI_TRANSMITE_MODE	== SPI_HIGH_POLARTITY_SAMPLE_F_SETUP_R
		SET_BIT(SPCR,CPOL);
		CLR_BIT(SPCR,CPHA);
	#elif SPI_TRANSMITE_MODE	== SPI_HIGH_POLARTITY_SAMPLE_R_SETUP_F
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	#else
		#error "Error SPI Config"
	#endif
	
	/************************************************/
	
	#if   SPI_ASYNCH_MODE		== SPI_ASYNCH_ON
		SET_BIT(SPCR,SPIE);
	#elif SPI_ASYNCH_MODE		== SPI_ASYNCH_OFF
	/*Nothing*/
		CLR_BIT(SPCR,SPIE);
	#else
		#error "Error SPI Config"
	#endif
	/************* SPI Prescaller **************/
	#if	  SPI_PRESCALLER    == SPI_PRE_2
		SET_BIT(SPSR,SPI2X);
	#elif SPI_PRESCALLER	== SPI_PRE_4
	/*Nothing*/
	#elif SPI_PRESCALLER	== SPI_PRE_8
		SET_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		SET_BIT(SPSR,SPI2X);
	#elif SPI_PRESCALLER	== SPI_PRE_16
		SET_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
	#elif SPI_PRESCALLER	== SPI_PRE_64
		CLR_BIT(SPCR,SPR0);
		SET_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
	#else
		#error "Error SPI Config"
	#endif
	
	
}

u8   SPI_u8SendReceive_Polling(u8 Copy_u8Data)
{
	u8 Received = 0;
	SPDR = Copy_u8Data;
	while(0 == GET_BIT(SPSR,SPIF)); /*W8 for data to be sent*/
	Received = SPDR;
	return (Received);
}


void  SPI_u8SendSlave(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
}

u8   SPI_u8Receive_Slave_Polling(void)
{
	while(!GET_BIT(SPSR,SPIF)); /*W8 for data to be sent*/
	return (SPDR);
}



