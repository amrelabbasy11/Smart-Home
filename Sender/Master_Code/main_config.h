/*
 * main_config.h
 * Created: 4/26/2024 7:31:22 PM
 *  Author: thesuperstar3babsy
 */ 

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#include "STD_Types.h"

#define NOT_STORED                0xFF
#define NOT_SELECTED              0xFF

#define BLOCK_MODE_TIME		     (uint32)20000
#define CHARACTER_PREVIEW_TIME   (uint16)300
#define DEGREES_SYMBOL		     (uint8)0xDF

/* PIN Configuration */
#define PASS_SIZE         (uint8)4
#define TRIES_ALLOWED     (uint8)3
#define PASSWORD_SYMBOL   (uint8)'&'
#define ASCII_ZERO        (uint8)'0'

#define PASS_NOT_SET   (uint8)0xFF
#define PASS_SET       (uint8)0x01

/* eeprom adresses */

#define ADMIN_PASS_STATUS_ADDRESS   (uint16)0X100
#define GUEST_PASS_STATUS_ADDRESS   (uint16)0X101
#define EEPROM_ADMIN_ADDRESS        (uint16)0X102
#define EEPROM_GUEST_ADDRESS        (uint16)0X106
#define LOGIN_BLOCKED_ADDRESS       (uint16)0X10A
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define NO_MODE (uint8)0
#define ADMIN   (uint8)1
#define GUEST   (uint8)2
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE   (uint8)0
#define TRUE    (uint8)1
/*****************************************************************************************/

#define CHECK_ADMIN_MODE        (uint8)'0'
#define CHECK_GUEST_MODE        (uint8)'1'

#define SELECT_ROOM1            (uint8)'1'
#define SELECT_ROOM2            (uint8)'2'
#define SELECT_ROOM3            (uint8)'3'
#define SELECT_ROOM4            (uint8)'4'

#define ADMIN_MORE_OPTION       (uint8)'4'

#define SELECT_ROOM4_ADMIN      (uint8)'1'
#define SELECT_TV               (uint8)'2'
#define SELECT_AIR_CONDITIONING (uint8)'3'
#define ADMIN_RET_OPTION        (uint8)'4'

#define SELECT_SET_TEMPERATURE  (uint8)'1'
#define SELECT_AIR_COND_CTRL    (uint8)'2'
#define SELECT_AIR_COND_RET     (uint8)'0'

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT (uint16)3000
#define GUEST_TIMEOUT (uint16)2000
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            (uint8)1
#define MORE_MENU            (uint8)2
#define ROOM1_MENU           (uint8)3
#define ROOM2_MENU           (uint8)4
#define ROOM3_MENU           (uint8)5
#define ROOM4_MENU           (uint8)6
#define TV_MENU              (uint8)7
#define AIRCONDITIONING_MENU (uint8)8
#define AIRCOND_CTRL_MENU    (uint8)9
#define TEMPERATURE_MENU     (uint8)10
/*****************************************************************************************/

#endif /* MAIN_CONFIG_H_ */