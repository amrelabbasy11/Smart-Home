/*
 * main.c
 * Created: 4/26/2024 6:53:50 PM
 * Author : thesuperstar3babsy
 */ 
#include "main_config.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/EEPROM/EEPROM.h"
#include "MCAL/TIMER/timer_driver.h"
#include "HAL/KEYPAD/keypad_driver.h"
#include "MCAL/SPI/SPI.h"
#include "HAL/LED/LED.h"
#include "menu.h"
#include <avr/io.h>

volatile uint16 session_counter = 0;//indicate session time
//stores if the session is still valid or outdated
uint8 timeout_flag = FALSE;

int main(void)
{
	/* The average temperature of the room */
	uint8 temperature = 0;
	/* The entered right number of the temperature */
	uint8 temp_ones = NOT_SELECTED;
	/* The entered left number of the temperature */
	uint8 temp_tens = NOT_SELECTED;
	uint8 login_mode = NO_MODE; //Store the current user mode admin or guest or not logged in
	uint8 block_mode_flag = FALSE;//is true if the login is blocked or false if not blocked
	uint8 key_pressed = NOT_PRESSED;//
	/* Init Led For Guest - Admin - Block */
	LED_vInit(ADMIN_LED_PORT,ADMIN_LED_PIN);
	LED_vInit(GUEST_LED_PORT,GUEST_LED_PIN);
	LED_vInit(BLOCK_LED_PORT,BLOCK_LED_PIN);
	LCD_vInit();
	keypad_vInit();
	SPI_vInitMaster();
	/* ---------------------------------------------------*/
	/* Welcome screen and Team informations */
	LCD_vSend_string("Hey guys!");
	LCD_movecursor(2,1);
	LCD_vSend_string("Welcome");
	_delay_ms(1200);
	LCD_clearscreen();
	LCD_movecursor(1,3);
	LCD_vSend_string("Who We Are?");
    LCD_movecursor(2,5);
    LCD_vSend_string("TEAM 3");
    _delay_ms(1500);
    LCD_clearscreen();
    LCD_movecursor(1,6);
    LCD_vSend_string("Amr");
    LCD_movecursor(2,4);
    LCD_vSend_string("Abdullah");
    _delay_ms(1200);
    LCD_clearscreen();
	LCD_movecursor(1,5);
	LCD_vSend_string(" Fatma");
    LCD_movecursor(2,6);
    LCD_vSend_string(" Saja");
	_delay_ms(1500);
	LCD_clearscreen();
	LCD_movecursor(1,5); 
    LCD_vSend_string(" Ahmed");
	LCD_movecursor(2,5);
	LCD_vSend_string("Mostafa");
	_delay_ms(1500);
	LCD_clearscreen();
   	LCD_movecursor(1,4);
	LCD_vSend_string(" Elkamash");
	LCD_movecursor(2,6);
	LCD_vSend_string("Marwan");
	_delay_ms(1500);
	LCD_clearscreen();

	/*Setting Admin and Guest passwords if not set */
	//read the state of the the passwords of the admin and guest if both are set or not set
	if ( (EEPROM_ui8ReadByteFromAddress(ADMIN_PASS_STATUS_ADDRESS)!=PASS_SET) || (EEPROM_ui8ReadByteFromAddress(GUEST_PASS_STATUS_ADDRESS)!=PASS_SET) )
	{
		//printing login menu
		LCD_vSend_string("Login for");
		LCD_movecursor(2,1);
		LCD_vSend_string("first time");
		_delay_ms(1000);
		LCD_clearscreen();
		LCD_vSend_string("Set Admin pass");
		LCD_movecursor(2,1);
		LCD_vSend_string("Admin pass:");
		/* setting Admin password */
		uint8 pass_counter=0; //the counter of the characters of the password (Number Of Character of the passwors)
		//the array where it stored the password	
		uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED}; 
		while (pass_counter<PASS_SIZE)
		{
			key_pressed = NOT_PRESSED;
			while (key_pressed == NOT_PRESSED)//repeat till the user press any key
			{
				key_pressed = keypad_u8check_press();//if the user pressed any button in keypad save the value in key_pressed
			}
			
			pass[pass_counter]=key_pressed;
			LCD_vSend_char(key_pressed);
			_delay_ms(CHARACTER_PREVIEW_TIME);//Halt the system for the given time in (ms)
			LCD_movecursor(2,12+pass_counter);//move the lcd cursor to the previous location to write the password symbol over the character
			LCD_vSend_char(PASSWORD_SYMBOL); // to display &
			_delay_ms(100);
			pass_counter++;//increase the characters count
		}
		EEPROM_vWriteBlockToAddress(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);//save the entire password as a block to the EEPROM
		EEPROM_vWriteByteToAddress(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);//write the status of pass as it is set
		LCD_clearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		LCD_vSend_string("Pass Is Saved");
		_delay_ms(500);
		LCD_clearscreen();
		
		/*setting guest password */
		pass_counter=0;
		LCD_vSend_string("Enter Guest Pass");
		LCD_movecursor(2,1);
		LCD_vSend_string("Guest Pass:");
		while (pass_counter<PASS_SIZE)
		{
			key_pressed = NOT_PRESSED;
			while (key_pressed == NOT_PRESSED)
			{
				/* save in key_pressed if the user pressed any button*/
				key_pressed = keypad_u8check_press();
			}
            //add the entered character to the pass array
			pass[pass_counter]=key_pressed;
			LCD_vSend_char(key_pressed);
			_delay_ms(CHARACTER_PREVIEW_TIME);
			LCD_movecursor(2,12+pass_counter);
			LCD_vSend_char(PASSWORD_SYMBOL); 
			_delay_ms(100);
			pass_counter++;
		}
		EEPROM_vWriteBlockToAddress(EEPROM_GUEST_ADDRESS,pass,PASS_SIZE);
		EEPROM_vWriteByteToAddress(GUEST_PASS_STATUS_ADDRESS,PASS_SET);
		LCD_clearscreen();
		LCD_vSend_string("Pass Is Saved");
		_delay_ms(500);
		LCD_clearscreen();
		EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);
	}
	else//this code of else run only if the system is not running for the first time (ADMIN and GUEST passwords are set)
	{
		block_mode_flag = EEPROM_ui8ReadByteFromAddress(LOGIN_BLOCKED_ADDRESS); //read the blocked location from EEPROM
	}
	while (1)
	{
		key_pressed = NOT_PRESSED;
		uint8 pass_tries_count=0;//stores how many times the user tried to log in to the system and failed
		
		if ( timeout_flag==TRUE )//check for timeout
		{//if timeout flag was raised
			timer0_stop();//stop the timer that increase the session counter
			session_counter = 0;//clear session counter
			timeout_flag=FALSE;//clear time out flag
			login_mode=NO_MODE;//log the user out
			key_pressed = NOT_PRESSED;
			LED_vTurnOff(GUEST_LED_PORT,GUEST_LED_PIN);//turnoff the led of the guest
			LED_vTurnOff(ADMIN_LED_PORT,ADMIN_LED_PIN);//turnoff the led of the admin
			LCD_clearscreen();
			LCD_vSend_string("Session Timeout");//print session timeout message
			_delay_ms(1000);
		}
		while (login_mode==NO_MODE)//The user can only leave the loop only in case of he was logged in as guest or admin
		{
			if(block_mode_flag==TRUE)//if the login process was blocked wait till the end of the block period
			{
				LCD_clearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				LCD_vSend_string("Login blocked");
				LCD_movecursor(2,1);
				LCD_vSend_string("wait 20 seconds");
				LED_vTurnOn(BLOCK_LED_PORT,BLOCK_LED_PIN);//Turn on the led of Blocked
				_delay_ms(BLOCK_MODE_TIME);//Halt the system for the given time in (ms)
				pass_tries_count = 0; //Clear the count on number of wrong tries
				block_mode_flag = FALSE;//Disable block of runtime
				LED_vTurnOff(BLOCK_LED_PORT,BLOCK_LED_PIN);//Turn off the led of Blocked
				EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);//write false at blocked location in EEPROM
			}
			LCD_clearscreen();
			LCD_vSend_string("Select mode :");
			LCD_movecursor(2,1);
			LCD_vSend_string("0:ADMIN 1:GUEST");
			while(key_pressed==NOT_PRESSED)
			{
				key_pressed = keypad_u8check_press();
			}
			if ( key_pressed!=CHECK_ADMIN_MODE && key_pressed!=CHECK_GUEST_MODE )
			{
				LCD_clearscreen();
				LCD_vSend_string("Wrong input.");
				key_pressed = NOT_PRESSED;
				_delay_ms(1000);
				continue;//return to the loop of login #while (login_mode==NO_MODE)# line 128
			}

			uint8 pass_counter=0;
			uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			uint8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			
			switch(key_pressed)
			{
				/* Admin login */
				case CHECK_ADMIN_MODE:
				while(login_mode!=ADMIN)
				{
					key_pressed = NOT_PRESSED;
					LCD_clearscreen();
					LCD_vSend_string("Admin mode");
					LCD_movecursor(2,1);
					LCD_vSend_string("Enter Pass:");
					_delay_ms(200);
					pass_counter=0;//counts the number of entered characters
					
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NOT_PRESSED)
						{
							key_pressed = keypad_u8check_press();
						}
						pass[pass_counter]=key_pressed;
						LCD_vSend_char(key_pressed);
						_delay_ms(CHARACTER_PREVIEW_TIME);
						LCD_movecursor(2,12+pass_counter);
						LCD_vSend_char(PASSWORD_SYMBOL);
						_delay_ms(100);
						pass_counter++;
						key_pressed = NOT_PRESSED;
					}
					EEPROM_vReadBlockFromAddress(EEPROM_ADMIN_ADDRESS,stored_pass,PASS_SIZE);

					/*compare the passwords*/
					if ((ui8ComparePass(pass,stored_pass,PASS_SIZE)) == TRUE)
					{
						login_mode = ADMIN;//set the login mode to admin mode
						pass_tries_count=0;//clear the counter of wrong tries
						LCD_clearscreen();
						LCD_vSend_string("Right pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Admin mode");
						_delay_ms(500);
						LED_vTurnOn(ADMIN_LED_PORT,ADMIN_LED_PIN);//led of admin
						timer0_initializeCTC();//start the timer that counts the session time of waiting.
						LCD_clearscreen();
					}
					else
					{
						pass_tries_count++;//increase the number of wrong tries 
						login_mode = NO_MODE;//set the mode as not logged in
						LCD_clearscreen();
						LCD_vSend_string("Wrong Pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Tries left:");
						LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
						_delay_ms(1000);
						LCD_clearscreen();
						if (pass_tries_count>=TRIES_ALLOWED)
						{
							EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);//write to the EEPROM TRUE to the the block mode address
							block_mode_flag = TRUE;//turn on block mode
							//break the loop of admin login
							break;
						}
					}
				}
				break;
				/* Guest login */
				case  CHECK_GUEST_MODE:
				while(login_mode != GUEST)
				{
					key_pressed = NOT_PRESSED;
					LCD_clearscreen();
					LCD_vSend_string("Guest mode");
					LCD_movecursor(2,1);
					LCD_vSend_string("Enter pass:");
					_delay_ms(200);
					pass_counter=0;
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NOT_PRESSED)
						{
							key_pressed = keypad_u8check_press();
						}
						pass[pass_counter]=key_pressed;
						LCD_vSend_char(key_pressed);//print the entered character
						_delay_ms(CHARACTER_PREVIEW_TIME);
						LCD_movecursor(2,12+pass_counter);
						LCD_vSend_char(PASSWORD_SYMBOL); 
						_delay_ms(100);
						pass_counter++;
						key_pressed = NOT_PRESSED;
					}
					EEPROM_vReadBlockFromAddress(EEPROM_GUEST_ADDRESS,stored_pass,PASS_SIZE);

					/*compare passwords*/
					if (ui8ComparePass(pass,stored_pass,PASS_SIZE)==TRUE)//in case of right password
					{
						login_mode = GUEST;
						pass_tries_count=0;//clear the counter of wrong tries
						LCD_clearscreen();
						LCD_vSend_string("Right pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Guest mode");
						_delay_ms(500);
						LED_vTurnOn(GUEST_LED_PORT,GUEST_LED_PIN);//turn the led of gust mode
						timer0_initializeCTC();
						LCD_clearscreen();
					}
					else
					{
						pass_tries_count++;
						login_mode = NO_MODE;
						LCD_clearscreen();
						LCD_vSend_string("Wrong pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Tries left:");
						LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
						_delay_ms(1000);
						LCD_clearscreen();
						if (pass_tries_count>=TRIES_ALLOWED)
						{
							EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);
							block_mode_flag = TRUE;
							break;
						}
					}
				}
				break;
			}
			
		}
		
		uint8 show_menu = MAIN_MENU;
		
		while(timeout_flag != TRUE)
		{
			key_pressed = NOT_PRESSED;
			switch (show_menu)
			{
				case MAIN_MENU:
				do
				{
					/*print main Menu */
					LCD_clearscreen();
					LCD_vSend_string("1:RM1   2:RM2");
					LCD_movecursor(2,1);
					if(login_mode==ADMIN)
					{
						/* Only printed if the logged in user is an admin*/
						LCD_vSend_string("3:RM3   4:More ");
					}
					else if(login_mode==GUEST)
					{
						/* Only printed if the logged in user is an admin*/
						LCD_vSend_string("3:RM3   4:RM4");
					}
					/*******************************************************/
					
					key_pressed = u8GetKeyPressed(login_mode);
					/* We use it to avoid the duplication og press */
					_delay_ms(100);
					/* 
					switch(key_pressed){
						case SELECT_ROOM1 : 
						show_menu = ROOM1_MENU;
						break;
						case SELECT_ROOM2 :
						show_menu = ROOM2_MENU;
						break;
						case SELECT_ROOM3 :
						show_menu = ROOM3_MENU;
						break;
						case SELECT_ROOM4 :
						show_menu = ROOM4_MENU;
						break;
					}
					*/
					if (key_pressed == SELECT_ROOM1)
					{
						/* Set the next menu to be shown to room1 menu */
						show_menu = ROOM1_MENU;
					}
					else if (key_pressed == SELECT_ROOM2)
					{
						show_menu = ROOM2_MENU;
					}
					else if (key_pressed == SELECT_ROOM3)
					{
						show_menu = ROOM3_MENU;
					}
					else if (key_pressed == SELECT_ROOM4 && login_mode == GUEST)//If key pressed is 4 and the logged in user is guest
					{
						show_menu = ROOM4_MENU;
					}
					else if (key_pressed == ADMIN_MORE_OPTION && login_mode == ADMIN)//If key pressed is 4 and the logged in user is admin
					{
						show_menu = MORE_MENU;
					}
					else if(key_pressed != NOT_PRESSED)
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while ( ((key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE) );
				/* in case of valid key or time is out */
				break;
				
				case MORE_MENU:
				do
				{
					/* print more than Menu */
					LCD_clearscreen();
					LCD_vSend_string("1:RM4   2:TV   ");
					LCD_movecursor(2,1);
					LCD_vSend_string("3:AIR Cond.4:RETURN");
					key_pressed = u8GetKeyPressed(login_mode);
					_delay_ms(100);
					
					if (key_pressed == SELECT_ROOM4_ADMIN)
					{
						show_menu = ROOM4_MENU;
					}
					else if (key_pressed == SELECT_TV)
					{
						/* Set the menu to be shown to TV menu*/
						show_menu = TV_MENU;
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING)
					{
						show_menu = AIRCONDITIONING_MENU;
					}
					else if (key_pressed == ADMIN_RET_OPTION)
					{
						show_menu = MAIN_MENU;
					}
					else if(key_pressed != NOT_PRESSED)
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while (( (key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE));
				
				break;
				
				case AIRCONDITIONING_MENU:
				do
				{
					/* print more Menu */
					LCD_clearscreen();
					LCD_vSend_string("1:Set temperature ");
					LCD_movecursor(2,1);
					LCD_vSend_string("2:Control  0:RET");
					key_pressed = u8GetKeyPressed(login_mode);
					_delay_ms(100);
					
					if (key_pressed == SELECT_SET_TEMPERATURE)
					{
						show_menu = TEMPERATURE_MENU;
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)
					{
						show_menu = AIRCOND_CTRL_MENU;
					}
					else if (key_pressed == SELECT_AIR_COND_RET)
					{
						show_menu = MORE_MENU;
					}
					else if(key_pressed != NOT_PRESSED)
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));
				break;
				
				case ROOM1_MENU:
				vMenuOption(ROOM1_MENU,login_mode);
				show_menu = MAIN_MENU;
				break;
				
				case ROOM2_MENU:
				vMenuOption(ROOM2_MENU,login_mode);
				show_menu = MAIN_MENU;
				break;
				
				case ROOM3_MENU:
				vMenuOption(ROOM3_MENU,login_mode);
				show_menu = MAIN_MENU;
				break;
				
				case ROOM4_MENU:
				vMenuOption(ROOM4_MENU,login_mode);
				if (login_mode == GUEST)
				{
					show_menu = MAIN_MENU;
				}
				else
				{
					show_menu = MORE_MENU;
				}
				break;
				
				case TV_MENU:
				vMenuOption(TV_MENU,login_mode);
				show_menu = MORE_MENU;
				break;
				
				case AIRCOND_CTRL_MENU:
				vMenuOption(AIRCOND_CTRL_MENU,login_mode);
				show_menu = AIRCONDITIONING_MENU;
				break;
				
				case TEMPERATURE_MENU:
				temperature = 0;
				while (temperature==0 && timeout_flag == FALSE)
				{
					key_pressed = NOT_PRESSED;
					LCD_clearscreen();
					LCD_vSend_string("Set temperature.:  ");
					LCD_vSend_char(DEGREES_SYMBOL); 
					LCD_vSend_char('C');
					LCD_movecursor(1,11);
					_delay_ms(200);
					key_pressed = u8GetKeyPressed(login_mode);
					_delay_ms(250);

					if (timeout_flag == TRUE) 
					{
						break;
					}
					if (key_pressed <'0' || key_pressed >'9')
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong !");
						_delay_ms(500);
						continue;
					}
					else
					{
						LCD_vSend_char(key_pressed);
						temp_tens = key_pressed-ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					key_pressed = u8GetKeyPressed(login_mode);
					/* To avoid The duplication*/
					_delay_ms(250);
					
					if (timeout_flag == TRUE)
					{
						break;
					}
					if ((key_pressed <'0' || key_pressed >'9'))
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
						continue;//repeat the loop that ask for the temperature
					}
					else
					{
						LCD_vSend_char(key_pressed);
						temp_ones = key_pressed-ASCII_ZERO;
						key_pressed = NOT_PRESSED;
					}
					temperature = temp_tens*10 + temp_ones;//set the value of the temperature from the given separated values
					SPI_ui8TransmitRecive(SET_TEMPERATURE);//Sending the code of set temperature
					_delay_ms(200);
					SPI_ui8TransmitRecive(temperature);//sending the entered temperature
					LCD_clearscreen();
					LCD_vSend_string("Temperature Sent");
					_delay_ms(500);
				}
				show_menu = AIRCONDITIONING_MENU;
				break;
			}
		}
	}
}
 
 /* Interrupt Service Routine -> Indicate that the process is done or Not */
ISR(TIMER0_COMP_vect)
{
	session_counter++;
}