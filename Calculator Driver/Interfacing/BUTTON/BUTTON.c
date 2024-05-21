/*
 * BUTTON.c
 *
 *  Created on: Feb 1, 2024
 *      Author: abo32
 */

/* Includes */

#include <avr/io.h>
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "BUTTON.h"


/* Function Definitions */


void BUTTON_ButtonInit( uint8 Port_Id , uint8 Pin_Id , uint8 IntPullUpMode ){
	GPIO_SetPinDirection( Port_Id , Pin_Id , PIN_INPUT );
	if( IntPullUpMode == INT_PULLUP ){
		GPIO_WritePinValue( Port_Id , Pin_Id , LOGIC_HIGH );
	}
}

/****************************************************************************************/

uint8 BUTTON_IsPressed( uint8 Port_Id , uint8 Pin_Id , uint8 IntPullUpMode , uint8 ConnectionMode  ){
	uint8 ButtonState ;
	if( ConnectionMode == PULLDOWN_CONNECTION && IntPullUpMode == NO_INT_PULLUP ){
		if( GPIO_ReadPinValue(Port_Id,Pin_Id) ){
			ButtonState = LOGIC_HIGH ;
		}
		else{
			ButtonState = LOGIC_LOW ;
		}
	}
	else if( ConnectionMode == PULLUP_CONNECTION ){
		if( GPIO_ReadPinValue(Port_Id,Pin_Id) ){
			ButtonState = LOGIC_LOW ;
		}
		else{
			ButtonState = LOGIC_HIGH ;
		}
	}
	return ButtonState ;
}

