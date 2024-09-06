/*
 * SPI.h
 * Created: 4/26/2024 7:10:03 PM
 *  Author: thesuperstar3babsy
 */ 

#ifndef SPI_H_
#define SPI_H_

#include "../../STD_Types.h"
#include "../../STD_MESSAGES.h"
#include "../../std_macros.h"

#define SPI_SCK   7
#define SPI_MISO  6
#define SPI_MOSI  5
#define SPI_SS    4

/************************************************************************/
/*                Initialize the master.                               */
/************************************************************************/
void SPI_vInitMaster (void);

/************************************************************************/
/*				   Initialize the slave.                                  */
/************************************************************************/
void SPI_vInitSlave (void);

/************************************************************************/
/*    Send data in case of master or receive data and send response in case of slave.              */
/************************************************************************/
uint8 SPI_ui8TransmitRecive (uint8 data);

#endif /* SPI_H_ */
