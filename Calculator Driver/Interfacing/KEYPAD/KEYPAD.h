/*
 * KEYPAD.h
 *
 *  Created on: Feb 6, 2024
 *      Author: abo32
 */

#ifndef INTERFACING_KEYPAD_KEYPAD_H_
#define INTERFACING_KEYPAD_KEYPAD_H_

/* Directions */

#define HALF_INPUT_OUTPUT	0b11110000
#define HALF_OUTPUT_INPUT	0b00001111

/* Keypad */

#define KEYPAD_ROWS		4
#define KEYPAD_COLS		4

/* Pressing */

#define KEY_BUTTON_PRESSED	LOGIC_LOW
#define KEYPAD_INIT_PORT	0b11111111

/* Debouncing Time */

#define DEBOUNCING_TIME		20


void KEYPAD_KeypadInit( uint8 Port_Id , uint8 PortMode );

uint8 KEYPAD_GetPressedKeyValue(uint8 Port_Id );



#endif /* INTERFACING_KEYPAD_KEYPAD_H_ */
