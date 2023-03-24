/*
 * main.c
 *
 *  Created on: Nov 4, 2022
 *      Author: George Ayman
 */

#include"keypad.h"
#include"lcd.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "SPI.h"
#include "DIO_Interface.h"
#include "UART.h"
#include "eeprom.h"
u8 compare(u8 *arr1,u8*arr2)
{
	if(strlen(arr1)==strlen(arr2))
	{
	u8 x=strlen(arr1);

	for (u8 i=0;i<x;i++)
	{
		if(!(arr1[i]==arr2[i]))
		{
			return 0;
		}
		else{}
	}
	return 1;
	}
	else{return 0;}
}
void save_user(u8 type,u8 id,u8 *pass);
u8 check_if_exist(u8 type,u8 id);
u8 check_user(u8 type,u8 id,u8*pass);
volatile u8 flag=0;
ISR (USART_RXC_vect)
{
	flag=1;
	/*LCD_clearScreen();
	LCD_displayString(" UART");
	_delay_ms(100000);
	UART_Flush();*/

}

ISR(INT2_vect)
{
	flag=2;
}

int main() {
	u8 user_no;
	u32 user_id[5];
	u32 user_pass[5];
	u8 mode;// lamp or ac or alarm ...
	u8 trails=0;// if exceeded 4 alarm on
	u8 volatile start=0;// to determine if there is a password or not
	u8 start_mode;//to let the user choose to enter or change password
	u32 compared_pass=0;
	u8 i;
	u8 pressed_key;
	u8 lamps_selection;
	u8 dimer_selection;
	u8 reg_selection;
	u8 correct_password_flag;
	u8 next_step=0;
	EEPROM_init();
	SPI_initMaster();
	LCD_init();
	DIO_SetPinDir(2, INPUT, PORTB);
	UART_init();
	SET_BIT(GICR,INT2);
	SET_BIT(MCUCSR,ISC2);
	PORTD=0xFF;
	sei();
	//LCD_displayStringRowColumn(0,2,"Welcome home");// to display in row 0 column 2
	u8 Text[10];
	while(1)
	{
		LCD_clearScreen();
		SPI_sendByte(10);

	while(flag==2)
	{
		SPI_sendByte(10);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,2,"Welcome Home!");
		_delay_ms(1000);
		if(next_step==0)
		{
		SPI_sendByte(10);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,2,"0-New user"); // we enter this if condition if there is no save password
		LCD_displayStringRowColumn(1,2,"1-Old user");
		start=KeyPad_getPressedKey();
		if (start==0)
		{
			SPI_sendByte(10);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"Choose user");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("1-U1 2-U2 3-U3 ");
			LCD_displayStringRowColumn(1,0,"4-U4 5-U5");
			user_no=KeyPad_getPressedKey();
			if(user_id[user_no-1]!=user_no  )
			{
			SPI_sendByte(10);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"Add Password"); // we enter this if condition if there is no save password
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"4 digits pass");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("Password: ");
			for(i=0;i<4;i++)
			{

				LCD_sendCommand(CURSOR_ON);
				_delay_ms(200);
				LCD_sendCommand(CURSOR_OFF);
				_delay_ms(500);

				pressed_key=KeyPad_getPressedKey();
				LCD_intgerToString(pressed_key);
				_delay_ms(200);
				LCD_displayStringRowColumn(0,10+i,"*"); //to diplay the number then change it to*
				user_pass[user_no-1]+=pressed_key; //let pressed key is 1 so 1+0=1
				user_pass[user_no-1]*=10;// then multipled by 10 so pass becomes 10 to add the next digit to it let it 2 it becomes 12 and so on
				user_id[user_no-1]=user_no;
				start=1;
			}
			user_pass[user_no-1]/=10;// if the password is 1234 the use_pass will be equal to 12340 after the for loop so we divide it by 10
			//save_user(1, user_id, user_pass);;
			}
			else if(user_id[user_no-1]==user_no  )
			{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"user exist");
			_delay_ms(500);
			break;
			}
		}
		else if (start==1)
		{
			SPI_sendByte(10);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"Choose user");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("1-U1 2-U2 3-U3 ");
			LCD_displayStringRowColumn(1,0,"4-U4 5-U5");
			user_no=KeyPad_getPressedKey();
			if (user_id[user_no-1]!=user_no)
			{
				LCD_displayString("User doesn't exist");
			}
			else{
				_delay_ms(500);
			LCD_clearScreen();
			LCD_displayString("1-Enter Password ");// make user enter already added password
			LCD_displayStringRowColumn(1,0,"2-Change Password");
			_delay_ms(1000);
			start_mode=KeyPad_getPressedKey();
			switch (start_mode)
			{
			case 1 :
				SPI_sendByte(10);
				trails=0;
				while(trails<4)
				{
				LCD_clearScreen();
				LCD_displayString("Password: ");
				pressed_key=KeyPad_getPressedKey();
				for(i=0;i<4;i++)
				{
					LCD_sendCommand(CURSOR_ON);
					_delay_ms(200);
					LCD_sendCommand(CURSOR_OFF);
					_delay_ms(500);
					pressed_key=KeyPad_getPressedKey();
					if((pressed_key>=0) && (pressed_key<=9))
					{
						 LCD_intgerToString(pressed_key);
						 _delay_ms(200);
						 LCD_displayStringRowColumn(0,10+i,"*");

					}
					compared_pass+=pressed_key;
					compared_pass*=10;
				}

				compared_pass/=10;
				if(compared_pass==user_pass[user_no-1])
				{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 2,"Welcome Home!");
					_delay_ms(500);
					//servo code
					SPI_sendByte(7); //open door
					_delay_ms(2000);
					compared_pass=0;
					trails=0;
					correct_password_flag=1;
					next_step=2; // to start select operating mode
					pressed_key=0;
					trails=5;
				}
				else
				{
					SPI_sendByte(10);
					LCD_clearScreen();
					LCD_displayString("Invalid Password ");
					_delay_ms(500);
					trails++;
					if (trails==4)
					{
						SPI_sendByte(6); //alarm
						LCD_clearScreen();
						LCD_displayString("trials exceeded ");
						_delay_ms(2000);
						//buzzer (alarm)

						LCD_sendCommand(LCD_DisOff_CursOff);
						start=0;
					}
				}
				}
				trails=0;
				break;
			case 2 :
				trails=0;
				while(trails<4)
				{
				SPI_sendByte(10);
				LCD_clearScreen();
				LCD_displayString("Old pass: ");// have to enter old first to change it
				_delay_ms(1000);
				pressed_key=KeyPad_getPressedKey();
				for(i=0;i<4;i++)
				{
					LCD_sendCommand(CURSOR_ON);
					_delay_ms(200);
					LCD_sendCommand(CURSOR_OFF);
					_delay_ms(1000);
					pressed_key=KeyPad_getPressedKey();
					if((pressed_key>=0) && (pressed_key<=9))
					{
						 LCD_intgerToString(pressed_key);
						 _delay_ms(200);
						 LCD_displayStringRowColumn(0,10+i,"*");

					}
					compared_pass+=pressed_key;
					compared_pass*=10;
				}
				compared_pass/=10;
				if(compared_pass==user_pass[user_no-1] )
				{
					SPI_sendByte(10);
					LCD_clearScreen();
					LCD_displayString("New pass: ");//start changing
					for(i=0;i<4;i++)
					{
						LCD_sendCommand(CURSOR_ON);
						_delay_ms(200);
						LCD_sendCommand(CURSOR_OFF);
						_delay_ms(500);
						pressed_key=KeyPad_getPressedKey();
						if((pressed_key>=0) && (pressed_key<=9))
						{
							 LCD_intgerToString(pressed_key);
							 _delay_ms(200);
							 LCD_displayStringRowColumn(0,10+i,"*");

						}
						user_pass[user_no-1]+=pressed_key;
						user_pass[user_no-1]*=10;

					}
					user_pass[user_no-1]/=10;
					trails=4;
					start=1;
				}
				else
				{
					SPI_sendByte(10);
					LCD_clearScreen();
					LCD_displayString("wrong pass");
					_delay_ms(500);
					trails++;
					if (trails==4)
					{
						SPI_sendByte(6);
						LCD_clearScreen();
						LCD_displayString("trials exceeded");
						_delay_ms(2000);
						LCD_sendCommand(LCD_DisOff_CursOff);
						trails=0;
						start=0;
						//buzzer (alarm)
					}
				}
				}
				trails=0;
				break;
			}
			}

		}
		}
		else if (next_step==2)
		{
			SPI_sendByte(10);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,2,"Choose mode");
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString("1-lamp  2-Alarm ");
			LCD_displayStringRowColumn(1,0,"3-Exit");
			_delay_ms(1000);
			mode=KeyPad_getPressedKey();
			switch (mode)
			{
			case 1://lamps
				SPI_sendByte(10);
				LCD_clearScreen();
				LCD_displayString("1-Dimer Lamp");
				LCD_displayStringRowColumn(1,0,"2-Reg Lamp");
				_delay_ms(1000);
				lamps_selection=KeyPad_getPressedKey();
				if (lamps_selection==1)
				{
					LCD_clearScreen();
					LCD_displayString("1-Lamp up");
					LCD_displayStringRowColumn(1,0,"2-Lamp down");
					_delay_ms(1000);
					dimer_selection=KeyPad_getPressedKey();
					switch(dimer_selection)
					{
					case 1:
					LCD_clearScreen();
					LCD_displayString("Lamp up");
					SPI_sendByte(8);
					_delay_ms(500);
					//add lamp up code here
						break;
					case 2:
					LCD_clearScreen();
					LCD_displayString("Lamp down");
					SPI_sendByte(9);
					_delay_ms(500);
					//add lamp down code here
						break;
					}
				}
				else if(lamps_selection==2)
				{
					SPI_sendByte(10);
					LCD_clearScreen();
					LCD_displayString("1-L1 2-L2 3-L3");
					LCD_displayStringRowColumn(1,0,"4-L4 5-L5");
					_delay_ms(1000);
					reg_selection=KeyPad_getPressedKey();
					switch(reg_selection)
					{
					case 1:
						LCD_clearScreen();
						LCD_displayString("lamp 1 on");
						SPI_sendByte(1);
						_delay_ms(2000);
						//add l1 code here
						break;
					case 2:
						LCD_clearScreen();
						LCD_displayString("lamp 2 on");
						SPI_sendByte(2);
						_delay_ms(2000);
						//add l2 code here
						break;
					case 3:
						LCD_clearScreen();
						LCD_displayString("lamp 3 on");
						SPI_sendByte(3);
						_delay_ms(2000);
						//add l3 code here
						break;
					case 4:
						LCD_clearScreen();
						LCD_displayString("lamp 4 on");
						SPI_sendByte(4);
						_delay_ms(2000);
						//add l4 code here
						break;
					case 5:
						LCD_clearScreen();
						LCD_displayString("lamp 5 on");
						SPI_sendByte(5);
						_delay_ms(2000);
						//add l5 code here
						break;
					}
				}
				break;

			case 2://alarm
				SPI_sendByte(10);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"1-Alarm on");
				SPI_sendByte(6);
				_delay_ms(1000);
				break;
			case 3:
				SPI_sendByte(10);
				next_step=0;
				flag=0;
				break;
			}
		}
		if(flag==0)
		{
			break;
		}
		SPI_sendByte(10);
	}
	while (flag==1)
	{
		UART_receiveString(Text);
		LCD_displayString(Text);
		if(compare(Text,"L1"))
		{
			SPI_sendByte(1);
		}
		else if(compare(Text,"L2"))
		{
			SPI_sendByte(2);
		}
		else if(compare(Text,"L3"))
		{
			SPI_sendByte(3);
		}
		else if(compare(Text,"L4"))
		{
			SPI_sendByte(4);
		}
		else if(compare(Text,"L5"))
		{
			SPI_sendByte(5);
		}
		else if(compare(Text,"AL"))
		{
			SPI_sendByte(6);
		}
		else if(compare(Text,"DO"))
		{
			SPI_sendByte(7);
		}
		else if(compare(Text,"DU"))
		{
			SPI_sendByte(8);
		}
		else if(compare(Text,"DD"))
		{
			SPI_sendByte(9);
		}
		UART_Flush();
		flag=0;
	}
	}
	return 0;
}

void save_user(u8 type,u8 id,u8 *pass)
{
	if(type==0)//admin
	{
		EEPROM_write(id,type,id*10);
		for(u8 i=0;i<4;i++)
		{
		EEPROM_write(pass,type,id*10+i+1);
		}
		EEPROM_read(type, id*10);
	}
	else
	{
		EEPROM_write(id,type,id*10);
	}
		for(u8 i=0;i<4;i++)
		{
			EEPROM_write(pass,type,id*10+i+1);
		}
	}

u8 check_user(u8 type,u8 id,u8*pass)
{
//	u8*arr[4];
	if(type==0)//admin
		{
			for(u8 i=0;i<4;i++)
			{
			if(pass[i]!=EEPROM_read(type,id*10+i+1))
				return 0;
			}
		}
		else
		{
			for(u8 i=0;i<4;i++)
			{
				if(pass[i]!=EEPROM_read(type,id*10+i+1))
								return 0;
			}
		}
	return 1;
}

u8 check_if_exist(u8 type,u8 id)
{
	u8 check;
	if(type==0)//admin
		{
		check=EEPROM_read(type,id*10);
		if (check==id)
		{
			return 1;
		}
		}
		else //user
		{
		check=EEPROM_read(type,id*10);
		if (check==id)
				{
					return 1;
				}
		}
	return 0;
}
