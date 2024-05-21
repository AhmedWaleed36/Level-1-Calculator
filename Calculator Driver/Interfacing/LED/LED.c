/*
 * LED.c
 *
 *  Created on: Feb 1, 2024
 *      Author: abo32
 */

/* Includes */

#include <avr/io.h>
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "LED.h"


/* Function Definitions */


void LED_LedInit( uint8 Port_Id , uint8 Pin_Id ){
	GPIO_SetPinDirection( Port_Id , Pin_Id , PIN_OUTPUT );
}

/****************************************************************************************/

void LED_LedOn( uint8 Port_Id , uint8 Pin_Id ){
	GPIO_WritePinValue( Port_Id , Pin_Id , LOGIC_HIGH );
}

/****************************************************************************************/

void LED_LedOff( uint8 Port_Id , uint8 Pin_Id ){
	GPIO_WritePinValue( Port_Id , Pin_Id , LOGIC_LOW );
}
