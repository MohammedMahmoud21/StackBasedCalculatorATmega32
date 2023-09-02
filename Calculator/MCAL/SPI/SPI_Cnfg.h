/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : SPI_Cnfig.h																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/


#ifndef SPI_CNFG_H_
#define SPI_CNFG_H_


/**
*	Options:
			SPI_ASYNCH_ON
			SPI_ASYNCH_OFF	
*/

#define SPI_ASYNCH_MODE		SPI_ASYNCH_OFF

/**
*	Options:
			SPI_LSB		
			SPI_MSB		
*/

#define SPI_DATA_ORDER	SPI_MSB
/**
*	Options:
			SPI_MASTER		
			SPI_SLAVE		
*/
#define SPI_MODE	SPI_MASTER

/************************************************************************/
/* 
	Options:
			SPI_LOW_POLARTITY_SAMPLE_R_SETUP_F
			SPI_LOW_POLARTITY_SAMPLE_F_SETUP_R
			
			SPI_HIGH_POLARTITY_SAMPLE_F_SETUP_R
			SPI_HIGH_POLARTITY_SAMPLE_R_SETUP_F
*/
/************************************************************************/

#define SPI_TRANSMITE_MODE	SPI_HIGH_POLARTITY_SAMPLE_R_SETUP_F

/************************************************************************/
/* 
	Options:
			SPI_PRE_2
			SPI_PRE_4
			SPI_PRE_8
			SPI_PRE_16
			SPI_PRE_64
*/
/************************************************************************/

#define SPI_PRESCALLER	SPI_PRE_64

#endif /* SPI_CNFG_H_ */