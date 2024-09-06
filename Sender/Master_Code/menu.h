/*
 * menu.h
 * Created: 4/26/2024 7:20:24 PM
 *  Author: thesuperstar3babsy
 */ 

#ifndef MENU_H_
#define MENU_H_

#include "main_config.h"
#include "STD_MESSAGES.h"
#include "STD_Types.h"
#include "HAL/KEYPAD/keypad_driver.h"
#include "MCAL/SPI/SPI.h"
#include "HAL/LCD/LCD.h"

/************************************************************************/
/*      Compare two arrays of bytes and return True in case they are identical and return false in case they are different .                                                                */
/************************************************************************/
uint8 ui8ComparePass(const uint8* pass1,const uint8* pass2,const uint8 size);

/************************************************************************/
/*     Show the sub menus of room 1 ,room 2 ,room 3,room 4 , tv                                                                 */
/************************************************************************/
void vMenuOption(const uint8 u8SelectedRoom,const uint8 u8LoginMode);

/************************************************************************/
/*    Wait the user to press key then return the key pressed or return (NOT_PRESSED = 0xFF) in case of timeout.                                                                   */
/************************************************************************/
uint8 u8GetKeyPressed(const uint8 u8LoginMode);

#endif /* MENU_H_ */