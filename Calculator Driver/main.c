/*
 * main.c
 *
 *  Created on: Feb 1, 2024
 *      Author: abo32
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LIBRARY/Macros.h"
#include "LIBRARY/Std_Types.h"
#include "GPIO/GPIO.h"
#include "Interfacing/LED/LED.h"
#include "Interfacing/BUTTON/BUTTON.h"
#include "Interfacing/LCD/LCD.h"
#include "Interfacing/KEYPAD/KEYPAD.h"

uint8 neg = 0, neg2 = 0;

float32 calc(float32 num1, uint8 i, float32 num2, uint8 error);
void runcalc();
void Print_Floating(float operation);

int main() {
	LCD_LcdInit( PORTA_ID, PORTB_ID, Mode_8_BIT);
	KEYPAD_KeypadInit(PORTC_ID, HALF_INPUT_OUTPUT);
	uint8 a[] = "Welcome";
//	uint8 b[] = "By :";
//	uint8 c[] = "Ahmed Waleed";
	uint8 i;
	LCD_MoveCursor(1, 4);
	for (i = 0; i < 7; i++) {
		LCD_SendData(a[i]);
		_delay_ms(100);
		LCD_MoveCursor(1, 4 + i + 1);
	}
//	_delay_ms(500);
//	LCD_ClearLcd();
//	LCD_MoveCursor(1, 6);
//	for (i = 0; i < 4; i++) {
//		LCD_SendData(b[i]);
//		_delay_ms(100);
//		LCD_MoveCursor(1, 6 + (i + 1));
//	}
//	LCD_MoveCursor(2, 1);
//	for (i = 0; i < 13; i++) {
//		LCD_SendData(c[i]);
//		_delay_ms(100);
//		LCD_MoveCursor(2, 1+ i + 1);
//	}
	LCD_MoveCursor(1, 0);
	_delay_ms(500);
	LCD_ClearLcd();
	runcalc();
}

void runcalc() {

	float32 num1 = 0, num2 = 0, counter = 0, ans = 0;
	uint8 c = 0, operator = 0, com1 = 0, com2 = 0, error = 0, ans_flag = 0;

	while (1) {
		c = KEYPAD_GetPressedKeyValue(PORTC_ID);
		if (c == NULL_LCD)
			continue;

		// to clear lcd when c is clicked
		if (c == 'c') {
			LCD_ClearLcd();
			num1 = 0, num2 = 0;
			com1 = 0, com2 = 0;
			error = 0, operator = 0;
			counter = 0, neg = 0, neg2 = 0, ans = 0, ans_flag = 0;
			continue;
		}
		// handling ans

		if ((c == '+' || c == '-' || c == '*' || c == '/')
				&& ans > -100000000000 && ans_flag == 1) {
			LCD_ClearLcd();
			num1 = 0, num2 = 0;
			com1 = 0, com2 = 0;
			error = 0, operator = 0;
			neg = 0, neg2 = 0;
			operator = c;

//			if (ans < 0)
//				neg = 1;
			if (ans != (int) ans) {
				Print_Floating(ans);

			} else {
				LCD_DisplayNumber((int) ans);
			}
			LCD_SendData(c);
			num1 = ans;
			com1 = 1;
			c = KEYPAD_GetPressedKeyValue(PORTC_ID);

		}

		// to avoid starting with / or *
		if ((c == '*' || c == '/') && counter == 0) {
			error = 1;
		}
		// to check if the number is positive or negative
		if ((c == '-' || c == '+') && counter == 0) {
			if (c == '-')
				neg = 1;
			LCD_SendData(c);
			continue;
		}

		// Getting first number
		if (com1 == 0) {
			while (1) {
				if ((c == '+' || c == '-' || c == '*' || c == '/')
						&& counter != 0) {
					LCD_SendData(c);
					operator = c;
					com1 = 1;
					c = KEYPAD_GetPressedKeyValue(PORTC_ID);
					while (c == NULL_LCD) {
						c = KEYPAD_GetPressedKeyValue(PORTC_ID);
					}
					// to check if number two positive or negative
					if (operator == '*' || operator == '/' || c == '-'
							|| c == '+') {
						if (c == '-' || c == '+') {
							if (c == '-') {
								neg2 = 1;
								LCD_SendData(c);
							} else if (c == '+') {
								LCD_SendData(c);
							}
							else if(c=='*'||c=='/'){
								error = 1;}
							c = KEYPAD_GetPressedKeyValue(PORTC_ID);
						}
					}
					break;
				}
				counter++;
				LCD_SendData(c);
				num1 = (c - '0') + (num1 * 10);
				c = KEYPAD_GetPressedKeyValue(PORTC_ID);
				if (c == NULL_LCD)
					break;
			}
		}
		if (operator == '*' || operator == '/') {
			if (c == '-' || c == '+') {
				if (c == '-') {
					neg2 = 1;
					LCD_SendData(c);
				} else if (c == '+') {
					LCD_SendData(c);
				}

				c = KEYPAD_GetPressedKeyValue(PORTC_ID);
			}
			else if(c=='*'||c=='/'){
				error = 1;}
		}
		// Getting number 2
		if (com1 == 1 && com2 == 0) {
			while (1) {
				if (c == '=') {
					LCD_SendData(c);
					LCD_MoveCursor(2, 0);
					ans = calc(num1, operator, num2, error);
					ans_flag = 1;
					com2 = 1;
					break;
				}

				if (c == NULL_LCD)
					break;
				LCD_SendData(c);
				num2 = (c - '0') + (num2 * 10);
				c = KEYPAD_GetPressedKeyValue(PORTC_ID);
			}
		}
	}

}

float32 calc(float32 num1, uint8 i, float32 num2, uint8 error) {
	if (neg == 1) {
		num1 *= (-1);
	}
	if (neg2 == 1) {
		num2 *= -1;
	}
	switch (i) {
	case '+':

		if (error == 1) {
			LCD_DisplayString((uint8*) "Error");
			return -100000000000;
		} else {
			if (num1 + num2 != (int) num1 + num2) {
				//handling floating point numbers
				Print_Floating(num1 + num2);
			}
			LCD_DisplayNumber(num1 + num2);
		}
		return num1 + num2;
		break;

	case '-':

		if (error == 1) {
			LCD_DisplayString((uint8*) "Error");
			return -100000000000;
		} else if (num1 == num2) {
			LCD_SendData('0');
			return 0;
		} else {
			if (num1 - num2 != (int) num1 - num2) {
				//handling floating point numbers
				Print_Floating(num1 - num2);
			} else
				LCD_DisplayNumber(num1 - num2);
			return num1 - num2;
		}
		break;

	case '*':

		if (error == 1) {
			LCD_DisplayString((uint8*) "Error");
			return -100000000000;

		} else if (num1 * num2 < 10000000) {
			if (num1 * num2 == (int) num1 * num2) {
				LCD_DisplayNumber(num1 * num2);
			} else {
				//handling floating point numbers
				Print_Floating(num1 * num2);
			}
			return num1 * num2;
		}

		else {
			LCD_DisplayString((uint8*) "EXCEED LIMIT");
			return -100000000000;
		}
		break;

	case '/':

		if (error == 1) {
			LCD_DisplayString((uint8*) "Error");
			return -100000000000;
		} else if (num2 == 0) {
			LCD_DisplayString((uint8*) "INFINITY");
			return -100000000000;
		} else {
			//handling floating point numbers
			Print_Floating(num1 / num2);
			return num1 / num2;
		}
		break;

	}
	return 0;
}

void Print_Floating(float operation) {
	if (operation < 0 && operation > -1) {
		LCD_SendData('-');
		LCD_SendData('0');
	} else {
		LCD_DisplayNumber((int) (operation));
	}

	LCD_SendData('.');
	if ((operation) - (int) (operation) == 0.0000000) {
		LCD_SendData('0');
	} else if (operation < 0)
		LCD_DisplayNumber(((operation) - (int) (operation)) * -1000);
	else
		LCD_DisplayNumber(((operation) - (int) (operation)) * 1000);

}
