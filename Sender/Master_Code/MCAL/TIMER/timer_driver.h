/*
 * timer_driver.h
 * Created: 4/26/2024 7:08:22 PM
 *  Author: thesuperstar3babsy
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../std_macros.h"
#include "../../STD_Types.h"

/************************************************************************/
/*      Initialize and start the timer0 for compare match.                                                                */
/************************************************************************/
void timer0_initializeCTC(void);

/************************************************************************/
/*                   Stop timer0.                                       */
/************************************************************************/
void timer0_stop(void);

/*
	Function Name        : timer_initializefastpwm
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer0 for FastPWM mode.
*/
/************************************************************************/
/*          Initialize timer0 for FastPWM mode.                          */
/************************************************************************/
void timer_initializefastpwm(void);

/************************************************************************/
/*      Set duty cycle to the given duty percentage.                             */
/************************************************************************/
void change_dutycycle(float64 duty);


#endif /* TIMER_DRIVER_H_ */
