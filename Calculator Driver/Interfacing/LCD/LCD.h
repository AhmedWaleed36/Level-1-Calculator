/*
 * LCD.h
 *
 *  Created on: Feb 4, 2024
 *      Author: abo32
 */

#ifndef INTERFACING_LCD_LCD_H_
#define INTERFACING_LCD_LCD_H_


/* Modes */

#define Mode_4_BIT		0
#define Mode_8_BIT		1

/* Control Pins */

#define RS	PIN0_ID
#define RW	PIN1_ID
#define E	PIN2_ID

/* Data Pins */

#define D0		PIN0_ID
#define D1		PIN1_ID
#define D2		PIN2_ID
#define D3		PIN3_ID
#define D4		PIN4_ID
#define D5		PIN5_ID
#define D6		PIN6_ID
#define D7		PIN7_ID

/* Operation */

#define INSTRUCTION_CODE	0
#define DATA_CODE			1
#define READING_OPERATION	1
#define WRITING_OPERATION	0

/* Commands */

#define MODE_8_FUNCTIONSET		0b00111000
#define MODE_8_DISPLAYONOFF 	0b00001100
#define MODE_8_CLEAR			0b00000001
#define MODE_8_ENTRYMODESET		0b00000110

#define MODE_4_FUNCTIONSET_P1	0b00100000
#define MODE_4_FUNCTIONSET_P2	0b10000000
#define MODE_4_DISPLAYONOFF_P1	0b00000000
#define MODE_4_DISPLAYONOFF_P2	0b11110000
#define MODE_4_CLEAR_P1			0b00000000
#define MODE_4_CLEAR_P2			0b00010000
#define MODE_4_ENTRYMODESET_P1	0b00000000
#define MODE_4_ENTRYMODESET_P2	0b01100000

#define LCD_FIRST_LINE			0b10000000
#define LCD_SECOND_LINE			0b11000000
#define LCD_DDRAM_ADDRESS		0b10000000
#define LCD_CGRAM_ADDRESS		0b01000000



/* Function Prototypes */

void LCD_SendCommand( uint8 Command );

void LCD_SendData( uint8 Data );

void LCD_LcdInit( uint8 Data_Port , uint8 Control_Port , uint8 Mode );

void LCD_DisplayString( uint8 *Str );

void LCD_DisplayNumber( sint32 Number );

void LCD_MoveCursor( uint8 Row , uint8 Col );

void LCD_ClearLcd();

void LCD_StoreCustomChar( uint8 Index , uint8 *CustomChar );

void LCD_DisplayCustomChar( uint8 Index );


#endif /* INTERFACING_LCD_LCD_H_ */
