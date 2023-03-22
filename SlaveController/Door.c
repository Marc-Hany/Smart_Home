/*
 * Door.c
 *
 *  Created on: 6 Nov 2022
 *      Author: Marc hany
 */
#include "Door.h"

void Door_Init(void)
{
	Servo_Init();		//Initialise servo motor
}

void Door_Close()
{
	// Close the servo to 0 degrees
	OCR1A = 0; // This value is specific to the servo motor used
	_delay_ms(1000); // Wait for 1 second
}

void Door_Open()
{
	// Open the servo to 90 degrees
	OCR1A = 375; // This value is specific to the servo motor used
	_delay_ms(5000); // Wait for 5 seconds

	// Close the servo to 0 degrees
	OCR1A = 0; // This value is specific to the servo motor used
	_delay_ms(1000); // Wait for 1 second
}


