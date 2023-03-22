/*
 * DIO_PROGRAM.c
 *
 *  Created on: Aug 21, 2022
 *      Author: Ali
 */

#include "DIO_INTERFACE.h"


void DIO_SetPortDir(u8 PortID,u8 Direction)
{
	switch(PortID)
	{
		case PortA: DDRA=Direction; break;
		case PortB: DDRB=Direction; break;
		case PortC: DDRC=Direction; break;
		case PortD: DDRD=Direction; break;
	}
}
void DIO_SetPortVal(u8 PortID,u8 Value)

{
	switch(PortID)
	{
	case PortA: PORTA=Value; break;
	case PortB: PORTB=Value; break;
	case PortC: PORTC=Value; break;
	case PortD: PORTD=Value; break;
	}
}
u8 DIO_GetPortVal(u8 PortID)
{

	switch(PortID)
	{
	    case PortA: return PORTA;
		break;
	    case PortB: return PORTB;
		break;
	    case PortC: return PORTC;
		break;
	    case PortD: return PORTD;
		break;
	}
}
void DIO_SetPinDir(u8 PinID,u8 Direction, u8 PortID)
{
	if(Direction==INPUT)
	{
		switch(PortID)
		{
		    case PortA: CLR_BIT(DDRA, PinID); break;
		    case PortB: CLR_BIT(DDRB, PinID); break;
		    case PortC: CLR_BIT(DDRC, PinID); break;
		    case PortD: CLR_BIT(DDRD, PinID); break;
		}
	}
	else if(Direction==OUTPUT)
	{
		switch(PortID)
		{
		    case PortA: SET_BIT(DDRA, PinID); break;
		    case PortB: SET_BIT(DDRB, PinID); break;
		    case PortC: SET_BIT(DDRC, PinID); break;
		    case PortD: SET_BIT(DDRD, PinID); break;
		}
	}

}
void DIO_SetPinVal(u8 PinID,u8 Value, u8 PortID)
{
	if(Value==High)
	{
		switch(PortID)
		{
		    case PortA: SET_BIT(PORTA, PinID); break;
		    case PortB: SET_BIT(PORTB, PinID); break;
		    case PortC: SET_BIT(PORTC, PinID); break;
		    case PortD: SET_BIT(PORTD, PinID); break;
		}
	}
	else if(Value==Low)
	{
		switch(PortID)
		{
		    case PortA: CLR_BIT(PORTA, PinID); break;
		    case PortB: CLR_BIT(PORTB, PinID); break;
		    case PortC: CLR_BIT(PORTC, PinID); break;
		    case PortD: CLR_BIT(PORTD, PinID); break;
		}
	}
}
u8 DIO_GetPinVal(u8 PinID, u8 PortID)
{
	u8 s;
	switch(PortID)
	{
	    case PortA: s=GET_BIT(PINA, PinID);//3shan byb2a input fa ml register el esmo PIN.
	    return s;
		break;
	    case PortB: s=GET_BIT(PINB, PinID);
	    return s;
		break;
	    case PortC: s=GET_BIT(PINC, PinID);
	    return s;
		break;
	    case PortD: s=GET_BIT(PIND, PinID);
	    return s;
		break;

	}
}










