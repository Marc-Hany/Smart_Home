/*
 * DIO_INTERFACE.h
 *
 *  Created on: Aug 21, 2022
 *      Author: Ali
 */


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Register.h"
#include <util/delay.h>


//Ports ID'S
#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3

//Pins ID'S
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define INPUT 0
#define OUTPUT 1

#define PortHigh 0xff
#define PortLow 0x00

#define High 1
#define Low  0

//Functions Prototypes
u8 DIO_GetPinVal(u8 PinID, u8 PortID);
void DIO_SetPinVal(u8 PinID,u8 Value, u8 PortID);
void DIO_SetPinDir(u8 PinID,u8 Direction, u8 PortID);
u8 DIO_GetPortVal(u8 PortID);
void DIO_SetPortVal(u8 PortID,u8 Value);
void DIO_SetPortDir(u8 PortID,u8 Direction);



#endif /* DIO_INTERFACE_H_ */
