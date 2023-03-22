/*
 * LED_program.c
 *
 *  Created on: Aug 25, 2022
 *      Author: k
 */


#include "LED_interface.h"

void LED_init(u8 portID, u8 pinID)
{
	//DIO_setpin_dir(portID, pinID, output);
	DIO_SetPinDir(pinID,OUTPUT,portID);
}

void LED_ON(u8 portID,u8 pinID)
{
	//DIO_setpin_val(portID, pinID, high);
	DIO_SetPinVal(pinID,High, portID);
}

void LED_OFF(u8 portID,u8 pinID)
{
	//DIO_setpin_val(portID, pinID, low);
	DIO_SetPinVal(pinID,Low, portID);
}

u8 LED_getledval(u8 portID,u8 pinID)
{
	//DIO_getpin_val(portID, pinID,val);
	return DIO_GetPinVal(pinID, portID);

}
