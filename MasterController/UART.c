/*
 * UART.c
 *
 *  Created on: Sep 12, 2019
 */


#include "UART.h"



void UART_init(void)
{
	/*Setting Baud Rate*/
		u16 Baud=12; // 16MHz, rate= 9600 bps
		UBRRH=(u8)(Baud>>8);
		UBRRL=(u8)Baud;

		/*Enable Receiver and Transmitter*/
		SET_BIT(UCSRB,RXEN);
		SET_BIT(UCSRB,TXEN);
		SET_BIT(UCSRB,RXCIE);//set recieving interrupt
		SET_BIT(SREG,SREG_I); //set global interruot flag
		/*Setting Frame Format*/
		SET_BIT(UCSRC,URSEL); //Select UCSRC Reg.
		CLEAR_BIT(UCSRC,USBS); //2 stop Bits
		CLEAR_BIT(UCSRC,UMSEL);
		(UCSRC) |= (3 << (UCSZ0));// 3=8 Bits SIze
		/*Normal Speed*/
		UCSRA=0;
}

void UART_sendByte(const unsigned char data)
{
	//u8 UDRE=5; //Data Registry Empty Flag Bit
	while(!(UCSRA&(1<<UDRE))); //Polling Until Register is Empty
	UDR=data; //Place Transmitted Data Inside Data Reg.
}

unsigned char UART_recieveByte(void)
{
	while (BIT_IS_CLEAR(UCSRA,RXC));// Polling Until There is Data to be Read
	return UDR; //Return Received Data
}

void UART_sendString(const unsigned char *Str)
{
	int i=0;
	while (*(Str+i)!='\0')
	{
		UART_sendByte(*(Str+i));
		i++;
	}

}

void UART_receiveString(unsigned char *Text)
{
	unsigned char i = 0;
	u8 temp;
	for(int i=0;i<2;i++)
	{
		temp=UART_recieveByte();
		UART_sendByte(temp);
		Text[i]=temp;
		//LCD_displayCharacter(temp);
	}
	UART_Flush();

}

void UART_Flush( void )// Empty the Receiving Reg.
{
	unsigned char dummy;
	while ( BIT_IS_SET(UCSRA,RXC) ) dummy = UDR;
}
