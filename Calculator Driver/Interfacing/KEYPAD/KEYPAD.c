/*
 * KEYPAD.c
 *
 *  Created on: Feb 6, 2024
 *      Author: abo32
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../../LIBRARY/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "KEYPAD.h"


uint8 KeyPadConnectionMode ;

const uint8 KEYPAD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = { { '7' , '8' , '9' , '/' } ,
													 { '4' , '5' , '6' , '*' } ,
													 { '1' , '2' , '3' , '-' } ,
													 { 'c' , '0' , '=' , '+' } };



void KEYPAD_KeypadInit( uint8 Port_Id , uint8 PortMode ){
	KeyPadConnectionMode = PortMode ;
	GPIO_SetPortDirection( Port_Id ,KeyPadConnectionMode );
	GPIO_WritePortValue( Port_Id , KEYPAD_INIT_PORT );
}

uint8 KEYPAD_GetPressedKeyValue( uint8 Port_Id ){
	uint8 KeyValue = 0b11111111 ;
	uint8 Flag = 0 ;

	if( KeyPadConnectionMode == HALF_INPUT_OUTPUT ){
		uint8 Col = 0 , Row = 0 ;
		for( Col = 0 ; Col < KEYPAD_COLS ; ++Col ){
			GPIO_WritePinValue( Port_Id , Col + KEYPAD_COLS , LOGIC_LOW );
			for( Row = 0 ; Row < KEYPAD_ROWS ; ++Row ){
				if( GPIO_ReadPinValue( Port_Id , Row ) == KEY_BUTTON_PRESSED ){
					_delay_ms( DEBOUNCING_TIME );
					if( GPIO_ReadPinValue( Port_Id , Row ) == KEY_BUTTON_PRESSED ){
						KeyValue = KEYPAD_MAP[Row][Col] ;
						while( GPIO_ReadPinValue( Port_Id , Row ) == KEY_BUTTON_PRESSED );
						Flag = 1 ;
						break;
					}
				}
			}
			GPIO_WritePinValue( Port_Id , Col + KEYPAD_COLS , LOGIC_HIGH );
			if( Flag == 1 ){
				break;
			}
		}
	}
	else if( KeyPadConnectionMode == HALF_OUTPUT_INPUT ){
		uint8 Col = 0 , Row = 0 ;
		for( Row = 0 ; Row < KEYPAD_ROWS ; ++Row ){
			GPIO_WritePinValue( Port_Id , Row , LOGIC_LOW );
			for( Col = 0 ; Col < KEYPAD_COLS ; ++Col ){
				if( GPIO_ReadPinValue( Port_Id , Col + KEYPAD_COLS ) == KEY_BUTTON_PRESSED ){
					_delay_ms( DEBOUNCING_TIME );
					if( GPIO_ReadPinValue( Port_Id , Col + KEYPAD_COLS ) == KEY_BUTTON_PRESSED ){
						KeyValue = KEYPAD_MAP[Row][Col] ;
						while( GPIO_ReadPinValue( Port_Id , Col + KEYPAD_COLS ) == KEY_BUTTON_PRESSED );
						Flag = 1 ;
						break;
					}
				}
			}
			GPIO_WritePinValue( Port_Id , Row , LOGIC_HIGH );
			if( Flag == 1 ){
				break;
			}
		}
	}
	return KeyValue ;
}

