/*
 * Alarm.h
 *
 *  Created on: 6 Nov 2022
 *      Author: Marc hany
 */

#ifndef ALARM_H_
#define ALARM_H_
#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"

#define DDR DDRC
#define PORT PORTC
#define PIN PC0

void Alarm_Init();
void Alarm_ON();
void Alarm_OFF();

#endif /* ALARM_H_ */
