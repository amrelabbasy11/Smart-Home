/*
 * keypad_driver.h
 * Created: 4/26/2024 7:15:46 PM
 *  Author: thesuperstar3babsy
 */ 

#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

#define NOT_PRESSED 0xff
#include "../../MCAL/DIO/DIO.h"

void keypad_vInit(void);

/************************************************************************/
/*     Returns the pressed key or return NOT_PRESSED if no keys are pressed.           */
/************************************************************************/
uint8 keypad_u8check_press(void);

#endif /* KEYPAD_DRIVER_H_ */