/*
 * LCD.c
 *
 *  Created on: Feb 4, 2024
 *      Author: abo32
 */

/* Includes */

#include <avr/io.h>
#include <util/delay.h>
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "LCD.h"


/* Global Variables */

uint8 LCD_DataPort ;
uint8 LCD_ControlPort ;
uint8 LCD_Mode ;


/* Function Definitions */


void LCD_SendCommand( uint8 Command ){
	GPIO_WritePinValue( LCD_ControlPort , RS , LOGIC_LOW );
	GPIO_WritePinValue( LCD_ControlPort , RW , LOGIC_LOW );

	if( LCD_Mode == Mode_4_BIT ){
		GPIO_WritePinValue( LCD_DataPort , D4 , RED_BIT( Command , 4 ) );
		GPIO_WritePinValue( LCD_DataPort , D5 , RED_BIT( Command , 5 ) );
		GPIO_WritePinValue( LCD_DataPort , D6 , RED_BIT( Command , 6 ) );
		GPIO_WritePinValue( LCD_DataPort , D7 , RED_BIT( Command , 7 ) );
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_HIGH );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_LOW );
		_delay_ms(1);
	}
	else{
		GPIO_WritePortValue( LCD_DataPort , Command );
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_HIGH );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_LOW );
		_delay_ms(1);
	}
}

void LCD_SendData( uint8 Data ){
	GPIO_WritePinValue( LCD_ControlPort , RS , LOGIC_HIGH );
	GPIO_WritePinValue( LCD_ControlPort , RW , LOGIC_LOW );

	if( LCD_Mode == Mode_4_BIT ){
		GPIO_WritePinValue( LCD_DataPort , D4 , RED_BIT( Data , 4 ) );
		GPIO_WritePinValue( LCD_DataPort , D5 , RED_BIT( Data , 5 ) );
		GPIO_WritePinValue( LCD_DataPort , D6 , RED_BIT( Data , 6 ) );
		GPIO_WritePinValue( LCD_DataPort , D7 , RED_BIT( Data , 7 ) );
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_HIGH );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_LOW );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_DataPort , D4 , RED_BIT( Data , 0 ) );
		GPIO_WritePinValue( LCD_DataPort , D5 , RED_BIT( Data , 1 ) );
		GPIO_WritePinValue( LCD_DataPort , D6 , RED_BIT( Data , 2 ) );
		GPIO_WritePinValue( LCD_DataPort , D7 , RED_BIT( Data , 3 ) );
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_HIGH );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_LOW );
		_delay_ms(1);
	}
	else{
		GPIO_WritePortValue( LCD_DataPort , Data );
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_HIGH );
		_delay_ms(1);
		GPIO_WritePinValue( LCD_ControlPort , E , LOGIC_LOW );
		_delay_ms(1);
	}
}

void LCD_LcdInit( uint8 Data_Port , uint8 Control_Port , uint8 Mode ){
	LCD_ControlPort = Control_Port ;
	LCD_DataPort = Data_Port ;
	LCD_Mode = Mode ;
	GPIO_SetPinDirection( LCD_ControlPort , RS , PIN_OUTPUT );
	GPIO_SetPinDirection( LCD_ControlPort , RW , PIN_OUTPUT );
	GPIO_SetPinDirection( LCD_ControlPort , E , PIN_OUTPUT );
	GPIO_SetPortDirection( LCD_DataPort , PORT_OUTPUT );
	_delay_ms(50);
	if( LCD_Mode == Mode_4_BIT ){
		/* 2 Line Mode , 8-bit , 5*7 font , Display On , Cursor On , Cursor Blink , Clear */
		LCD_SendCommand( MODE_4_FUNCTIONSET_P1 );
		LCD_SendCommand( MODE_4_FUNCTIONSET_P1 );
		LCD_SendCommand( MODE_4_FUNCTIONSET_P2 );
		_delay_ms(50);
		LCD_SendCommand( MODE_4_DISPLAYONOFF_P1 );
		LCD_SendCommand( MODE_4_DISPLAYONOFF_P2 );
		_delay_ms(50);
		LCD_SendCommand( MODE_4_CLEAR_P1 );
		LCD_SendCommand( MODE_4_CLEAR_P2 );
		_delay_ms(2);
		LCD_SendCommand( MODE_4_ENTRYMODESET_P1 );
		LCD_SendCommand( MODE_4_ENTRYMODESET_P2 );
	}
	else{
		/* 2 Line Mode , 8-bit , 5*7 font , Display On , Cursor On , Cursor Blink , Clear */
		LCD_SendCommand( MODE_8_FUNCTIONSET );
		_delay_ms(50);
		LCD_SendCommand( MODE_8_DISPLAYONOFF );
		_delay_ms(50);
		LCD_SendCommand( MODE_8_CLEAR );
		_delay_ms(2);
		LCD_SendCommand( MODE_8_ENTRYMODESET );
	}
}
void LCD_DisplayString( uint8 *Str ){
	uint8 Index ;
	for( Index = 0 ; Str[Index] != NULL_CHAR ; ++Index ){
		LCD_SendData( Str[Index] );
	}
}

void LCD_DisplayNumber( sint32 Number ){ // -123 => - 123 => "123"
	uint8 NumStr[20];
	uint8 Index = 0 ;
	if( Number < 0 ){
		LCD_SendData('-');
		Number *= -1 ;
	}
	while( Number != 0 ){
		uint8 reminder = Number % 10 ;
		NumStr[Index] = ( '0' + reminder ) ;
		Number /= 10 ;
		++Index ;
	}
	uint8 i ;
	for( i = Index - 1 ; NumStr[i] != NULL_CHAR ; --i ){
		LCD_SendData( NumStr[i] );
	}
}


void LCD_ClearLcd(){
	if( LCD_Mode == Mode_4_BIT ){
		LCD_SendCommand( MODE_4_CLEAR_P1 );
		LCD_SendCommand( MODE_4_CLEAR_P2 );
	}
	else{
		LCD_SendCommand( MODE_8_CLEAR );
	}
}

void LCD_MoveCursor( uint8 Row , uint8 Col ){
	if( ( Row == 1 ) && ( Col >= 0 && Col <= 15 ) ){
		LCD_SendCommand( LCD_FIRST_LINE + Col );
	}
	else if( ( Row == 2 ) && ( Col >= 0 && Col <= 15 ) ){
		LCD_SendCommand( LCD_SECOND_LINE + Col );
	}
}

void LCD_StoreCustomChar( uint8 Index , uint8 *CustomChar ){
	if( Index < 8 ){
		uint8 Counter ;
		LCD_SendCommand( LCD_CGRAM_ADDRESS + Index * 8 );
		for( Counter = 0 ; Counter < 8 ; ++Counter ){
			LCD_SendData( CustomChar[Counter] );
		}
		LCD_SendCommand( LCD_DDRAM_ADDRESS );
	}
}

void LCD_DisplayCustomChar( uint8 Index ){
	if( Index < 8 ){
		LCD_SendData( Index );
	}
}
