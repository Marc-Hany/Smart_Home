/*
 * Alarm.c
 *
 *  Created on: 6 Nov 2022
 *      Author: Marc hany
 */
#include "Alarm.h"


void Alarm_Init()
{
	DDR |= (1<<PIN);
}
void Alarm_ON()
{
	PORT &= (~(1 << (PIN)));				//Alarm ON
}
void Alarm_OFF()
{
	PORT |= (1<<PIN);	         			//Alarm OFF
}
