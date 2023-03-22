/*
 * LED_interface.h
 *
 *  Created on: Aug 25, 2022
 *      Author: k
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "STD_TYPES.h"
#include "DIO_Interface.h"

//LED values
#define high 1
#define low 0

//PORTS
#define portA 0
#define portB 1
#define portC 2
#define portD 3


void LED_init(u8 portID,u8 pinID);
void LED_ON(u8 portID,u8 pinID);
void LED_OFF(u8 portID,u8 pinID);
u8 LED_getledval(u8 portID,u8 pinID);

#endif /* LED_INTERFACE_H_ */
