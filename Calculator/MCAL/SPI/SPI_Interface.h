/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : SPI_Cnfig.h																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "StdTypes.h"

/************** External APIs Declerations ****************************/

extern void SPI_voidInit(void);
/************************************************************************/
/*@Description: Master API to send and receive using polling tech       */
/************************************************************************/
extern u8   SPI_u8SendReceive_Polling(u8 Copy_u8Data); 
/************************************************************************/
/*@Description: Slave API to receive using polling tech					*/
/************************************************************************/
extern u8   SPI_u8Receive_Slave_Polling(void);
extern void  SPI_u8SendSlave(u8 Copy_u8Data);
/****************************** For Asynch Sending **************************************/
extern u8 SPI_u8ReceiveNoBlock(void);
extern u8 SPI_u8SendAsynch(u8 Copy_u8Data);
extern u8 SPI_u8ReceiveAsynch(u8 *Copy_pu8Data);


#endif /* SPI_INTERFACE_H_ */