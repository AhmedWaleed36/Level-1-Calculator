/*
 * BUTTON.h
 *
 *  Created on: Feb 1, 2024
 *      Author: abo32
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#define NO_INT_PULLUP			0
#define INT_PULLUP				1
#define PULLDOWN_CONNECTION		0
#define PULLUP_CONNECTION		1

/* Functions Prototypes */

void BUTTON_ButtonInit( uint8 Port_Id , uint8 Pin_Id , uint8 IntPullUpMode );

uint8 BUTTON_IsPressed( uint8 Port_Id , uint8 Pin_Id , uint8 IntPullUpMode , uint8 ConnectionMode  );


#endif /* BUTTON_BUTTON_H_ */
