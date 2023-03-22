/*
 * Servo.c
 *
 *  Created on: 6 Nov 2022
 *      Author: Marc hany
 */

#include "Servo.h"

void Servo_Init(void)
{
	// Set the direction of the servo pin as output
	    DDRD |= (1 << PD5);

	    // Set up Timer/Counter1 (TC1) for PWM generation on the servo pin
	    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	    ICR1 = 4999; // Set the TOP value to generate a frequency of 50 Hz

	    // Set the initial duty cycle to correspond to 0 degree angle
	    OCR1A = 0; // This value is specific to the servo motor used
}
void Servo_Clockwise(u8 angle)
{
	if(angle>Max_Angle)
	{
		angle=Max_Angle;
	}
	else
	{
		OCR1A = (1.2912*angle)+Position_OCR1A;  //Servo rotates in clockwise direction, min angle=0 max angle=90
	}

}

void Servo_Counterclockwise(u8 angle)
{
	if(angle>Max_Angle)
	{
		angle=Max_Angle;
	}
	else
	{
		OCR1A = (-1.2912*angle)+Position_OCR1A;  //Servo rotates in counterclockwise direction, min angle=-90 max angle=0
	}

}


