/*
 * Servo.h
 *
 *  Created on: 6 Nov 2022
 *      Author: Marc hany
 */

#ifndef SERVO_H_
#define SERVO_H_

#define F_CPU 8000000UL								/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
/*Min angle=-90
Max angle=90
Postition0=0, OCR1A=182*/
#define Max_Angle 90
#define Min_Angle 90
#define Position0 0
#define Position_OCR1A 182

void Servo_Init(void);
void Servo_Clockwise(u8 angle);
void Servo_Counterclockwise(u8 angle);

#endif /* SERVO_H_ */
