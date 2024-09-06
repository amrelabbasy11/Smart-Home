/*
 * LED.h
 * Created: 4/26/2024 7:14:16 PM
 *  Author: thesuperstar3babsy
 */ 


#ifndef LED_H_
#define LED_H_
#include "../../MCAL/DIO/DIO.h"
#include "../../STD_Types.h"


void LED_vInit(uint8 portname,uint8 pinnumber);

void LED_vTurnOn(uint8 portname,uint8 pinnumber);

void LED_vTurnOff(uint8 portname,uint8 pinnumber);

void LED_vToggle(uint8 portname,uint8 pinnumber);

uint8 LED_u8ReadStatus(uint8 portname,uint8 pinnumber);

#endif /* LED_H_ */