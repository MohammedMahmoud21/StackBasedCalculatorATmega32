/********************************************************************************************************/
/* @author : Mohammed Elsayaad																			*/
/* @file   : SPI_Cnfig.h																				*/
/* @Date   : 12 May																						*/
/********************************************************************************************************/


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


#define SPI_LSB		1
#define SPI_MSB		2

#define SPI_MASTER	1
#define SPI_SLAVE	2

#define SPI_LOW_POLARTITY_SAMPLE_R_SETUP_F	4
#define SPI_LOW_POLARTITY_SAMPLE_F_SETUP_R	1

#define SPI_HIGH_POLARTITY_SAMPLE_F_SETUP_R	2
#define SPI_HIGH_POLARTITY_SAMPLE_R_SETUP_F	3

#define SPI_ASYNCH_ON		1
#define SPI_ASYNCH_OFF		2

#define SPI_PRE_2	4
#define SPI_PRE_4	6
#define SPI_PRE_16	1
#define SPI_PRE_64	2
#define SPI_PRE_8	5
/************************************************/
/* SPI */
/* SPI Control Register */
#define SPCR       (*(volatile u8*)0x2D)
/* SPI Status Register */
#define SPSR       (*(volatile u8*)0x2E)
/* SPI I/O Data Register */
#define SPDR       (*(volatile u8*)0x2F)

/* SPI Status Register - SPSR */
#define    SPIF         7
#define    WCOL         6
#define    SPI2X        0

/* SPI Control Register - SPCR */
#define    SPIE         7
#define    SPE          6
#define    DORD         5
#define    MSTR         4
#define    CPOL         3
#define    CPHA         2
#define    SPR1         1
#define    SPR0         0

#endif /* SPI_PRIVATE_H_ */