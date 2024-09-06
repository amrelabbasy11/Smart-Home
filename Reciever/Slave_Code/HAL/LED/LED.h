/*
 * LED.h
 * Created: 4/26/2024 8:08:47 PM
 *  Author: thesuperstar3bbasy
 */ 


#ifndef LED_H_
#define LED_H_
#include "../../MCAL/DIO/DIO.h"
#include "../../STD_Types.h"

/*
	Function Name        : LED_vInit
	Function Returns     : void
	Function Arguments   : uint8 portname,uint8 pinnumber
	Function Description : Initialize the pin as an output pin to connect the led.
*/
void LED_vInit(uint8 portname,uint8 pinnumber);

/*
	Function Name        : LED_vTurnOn
	Function Returns     : void
	Function Arguments   : uint8 portname,uint8 pinnumber
	Function Description : Turn on the led connected to the given pin and port.
*/
void LED_vTurnOn(uint8 portname,uint8 pinnumber);//

/*
	Function Name        : LED_vTurnOff
	Function Returns     : void
	Function Arguments   : uint8 portname,uint8 pinnumber
	Function Description : Turn off the led connected to the given pin and port.
*/
void LED_vTurnOff(uint8 portname,uint8 pinnumber);

/*
	Function Name        : LED_vToggle
	Function Returns     : void
	Function Arguments   : uint8 portname,uint8 pinnumber
	Function Description : Toggle the led connected to the given pin and port.
*/
void LED_vToggle(uint8 portname,uint8 pinnumber);//

/*
	Function Name        : LED_u8ReadStatus
	Function Returns     : uint8
	Function Arguments   : uint8 portname,uint8 pinnumber
	Function Description : Returns 0 if the led connected to the given port and pin is off or return 1 if it was on.
*/
uint8 LED_u8ReadStatus(uint8 portname,uint8 pinnumber);

#endif /* LED_H_ */