/*
 * EEPROM.h
 * Created: 4/26/2024 7:06:34 PM
 *  Author: thesuperstar3babsy
 */ 


#ifndef HEADERS_EEPROM_H_
#define HEADERS_EEPROM_H_

#include "../../STD_Types.h"


/************************************************************************/
/*      Read one byte from the given  address.                          */
/************************************************************************/
uint8 EEPROM_ui8ReadByteFromAddress(const uint16 u16Address);

/************************************************************************/
/*      Read block of bytes of the given size (size) and save the result to given array(dist array).                                                                */
/************************************************************************/
void EEPROM_vReadBlockFromAddress(const uint16 u16Address, uint8* dist,const uint16 size);

/************************************************************************/
/*       Write one byte to given address.                                   */
/************************************************************************/
void EEPROM_vWriteByteToAddress(const uint16 u16Address, const uint8 u8Data);

/************************************************************************/
/*   Write block of bytes  of the given size (size) to EEPROM at the given address(u16Address) from the given array (u8Data).                                                                   */
/************************************************************************/
void EEPROM_vWriteBlockToAddress(const uint16 u16Address, const uint8* u8Data,const uint16 size);

#endif /* HEADERS_EEPROM_H_ */
