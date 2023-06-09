
#include "lcd.h"
#include "stdlib.h"

void LCD_init(void)
{
	LCD_DATA_PORT_DIR = 0x3f; /* Configure the data port as output port */
	DDRB |= (1 << PB0) | (1 << PB1);
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	LCD_sendCommand(HOME);
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */

	LCD_sendCommand(CURSOR_OFF); /* cursor off */

	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(unsigned char command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	// Output the data
	    PORTB = ((command & 0x03) << PB0); // Output bits 0 and 1 on PB0 and PB1 respectively
	    PORTC = ((command & 0xFC) << (PC2 - 2)); // Output bits 2 to 7 on PC2 to PC7 respectively
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayCharacter(unsigned char data)
{
	SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	// Output the data
	    PORTB = ((data & 0x03) << PB0); // Output bits 0 and 1 on PB0 and PB1 respectively
	    PORTC = ((data & 0xFC) << (PC2 - 2)); // Output bits 2 to 7 on PC2 to PC7 respectively
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(unsigned char row,unsigned char col)
{
	unsigned char Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;

	}
	   /*ADDRESS = COL+(0X40*ROW)*/
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(unsigned char row,unsigned char col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data) // from 500 to "500"
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
