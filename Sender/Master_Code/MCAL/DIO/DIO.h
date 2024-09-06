/*
 * DIO.h
 * Created: 4/26/2024 7:03:14 PM
 *  Author: thesuperstar3babsy
 */ 


#ifndef DIO_H_
#define DIO_H_
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_config_master.h"
#include "../../STD_Types.h"

/************************************************************************/
/* Set the direction of the given pin in the given port (direction 0 = input : 1 = output)                                                                     */
/************************************************************************/
void DIO_vsetPINDir(uint8 portname,uint8 pinnumber,uint8 direction);


/************************************************************************/
/*     Set the value of the given pin in the given port (outputvalue 0 = low : 1 = high)                                                                  */
/************************************************************************/
void DIO_write(uint8 portname,uint8 pinnumber,uint8 outputvalue);


/************************************************************************/
/*     : Returns 1 if the value of the given pin is high and zero if the value was low                  */
/************************************************************************/
uint8 DIO_u8read(uint8 portname,uint8 pinnumber);

/************************************************************************/
/*    Reverse the value of the given pin in the given port.                                    */
/************************************************************************/
void DIO_toggle(uint8 portname,uint8 pinnumber);

/************************************************************************/
/*            Write the value to all port pins.                                        */
/************************************************************************/
void DIO_write_port(uint8 portname,uint8 portvalue);

/************************************************************************/
/*    Clear the value of the high nibble of the given port.                               */
/************************************************************************/
void clear_high_nibble(uint8 portname) ;

void dio_write_highnibble(uint8 portname,uint8 value);


void DIO_vconnectpullup(uint8 portname ,uint8 pinnumber, uint8 connect_pullup);

#endif /* DIO_H_ */