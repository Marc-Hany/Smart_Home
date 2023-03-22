#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "ADC.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LED_interface.h"
#include "Alarm.h"
#include "Door.h"
#include "ADC.h"
#include "SPI.h"





int main()
{
	DDRB |= (1<<PB0);
	uint16_t adc_result0;
	int temp;
	char buffer[10];
	u8 cmd=0;


	// initialize adc and lcd
	adc_init();
	LCD_init();


	LCD_clearScreen();
	LCD_goToRowColumn(0, 0);



	_delay_ms(50);
	OCR2 = 0; // Set the duty cycle to 50%
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
	OCR0=255;
	Alarm_Init();
	Alarm_OFF();
	Door_Init();
	SPI_initSlave();
	//u8 Recieve_string;
	DDRA |= (1<<PA2);
	DDRA |= (1<<PA3);
	DDRA |= (1<<PA4);
	DDRA |= (1<<PA7);
	DDRA |= (1<<PA6);
	PORTA &= (~(1 << PA6));

	while(1)
	{


		//	enable_spi();
		cmd=SPI_recieveByte();
		switch (cmd)
		{
		case 1:
			PORTA |= (1<<PA2);
			_delay_ms(5000);
			PORTA &= (~(1 << PA2));
			break;
		case 2:
			PORTA |= (1<<PA3);
			_delay_ms(5000);
			PORTA &= (~(1 << PA3));
			break;
		case 3:
			PORTA |= (1<<PA4);
			_delay_ms(5000);
			PORTA &= (~(1 << PA4));
			break;
		case 4:
			PORTA |= (1<<PA7);
			_delay_ms(5000);
			PORTA &= (~(1 << PA7));
			break;
		case 5:
			PORTA |= (1<<PA6);
			_delay_ms(5000);
			PORTA &= (~(1 << PA6));
			break;
		case 6:
			for(int i=0;i<10;i++)
			{
				Alarm_ON();
				_delay_ms(5000);
				Alarm_OFF();
				_delay_ms(5000);
			}
			break;
		case 7:
			// Open the servo to 90 degrees
			    OCR1A = 375; // This value is specific to the servo motor used
			    _delay_ms(5000); // Wait for 5 seconds

			    // Close the servo to 0 degrees
			    OCR1A = 0; // This value is specific to the servo motor used
			    _delay_ms(1000); // Wait for 1 second

			break;
		case 8:
			if (OCR0<255)
			{
				OCR0+=25;
			}
			 _delay_ms(500);
			 break;
		case 9:
			if (OCR0>0)
		   {
				  OCR0-=25;
		   }

		  _delay_ms(500);
		  break;
		case 10:
			adc_result0 = adc_read(0);      // read adc value at PA0

			temp=adc_result0/2.01;   // finding the temperature

			LCD_goToRowColumn(0, 0);
			itoa(temp,buffer,10);
			LCD_displayString(buffer);

			_delay_ms(1000);
			if(temp>=28)
			{

				PORTB=(1<<PINB0);

			}
			if (temp<=28)
			{


				PORTB=(0<<PINB0);

			}

		}



	}
}
