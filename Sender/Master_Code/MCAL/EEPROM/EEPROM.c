/*
 * EEPROM.c
 * Created: 4/26/2024 7:07:04 PM
 *  Author: thesuperstar3babsy
 */ 

#include "EEPROM.h"
#include <avr/io.h>

uint8 EEPROM_ui8ReadByteFromAddress(const uint16 u16Address)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1) ;
	/* Set up address register */
	EEAR = u16Address;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_vReadBlockFromAddress(const uint16 uiAddress, uint8* dist,const uint16 size)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)	;
	uint16 counter = 0;//the counter of bytes that are read
	while (counter < size) //loop until move all bytes to the given array
	{
		/* Set up address register */
		EEAR = uiAddress + counter;
		/* Start EEPROM read by writing EERE */
		EECR |= (1 << EERE);
		/* move data from data register to the array */
		*(dist + counter) = EEDR;
		/* increase the bytes counter */
		counter++;
	}
}

void EEPROM_vWriteByteToAddress(const uint16 uiAddress, const uint8 uiData)
{

	/* Wait for completion of previous write process*/
	while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1);
	/* Set up address register */
	EEAR = uiAddress;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EERE);
	if (EEDR != uiData)//compare the value read to the value to be written
	{//if they are not equal then write the data
		EEDR = uiData;//move the data to EEDR
		/* Write logical one to EEMWE */
		EECR |= (1 << EEMWE);
		/* Start EEPROM write by setting EEWE */
		EECR |= (1 << EEWE);
	}
	else
	{
       /* No Thing */
	}

}

void EEPROM_vWriteBlockToAddress(const uint16 uiAddress, const uint8* uiData,const uint16 size)
{
	uint16 counter = 0;//Bytes write counter
	while (counter < size)
	{
		/* Wait for completion of previous write process*/
		while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
		;
		/* Set up address register */
		EEAR = uiAddress + counter;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EERE);
		if (EEDR != (*(uiData + counter)))//compare the value read to the value to be written
		{//if they are not equal then write the data
			EEDR = *(uiData + counter);//move the data to EEDR

			/* Write logical one to EEMWE */
			EECR |= (1 << EEMWE);
			/* Start EEPROM write by setting EEWE */
			EECR |= (1 << EEWE);
		}
		else
		{

		}
		counter++;//increase bytes counter
	}
}