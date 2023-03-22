


#include "keypad.h"

/***** Function Prototypes for keypad internal (private) functions *****/

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number);


/************************** Functions Definitions **********************/
unsigned char KeyPad_getPressedKey(void){
	unsigned char col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			DDRA = (0b00010000<<col); //01000000
			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the rows pins
			 */
			PORTA = (~(0b00010000<<col)); //11101111 11011111

			for(row=0;row<N_row;row++) /* loop for rows */
			{
				if(!(PINA & (1<<row))) /* if the switch is press in this row */
				{
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
				}
			}
		}
	}
}


static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number)
{
	switch (button_number)
		{
		case 1:		return 7;
		break;
		case 2:		return 8;
		break;
		case 3:		return 9;
		break;
		case 4:		return '/';
		break;
		case 5:		return 4;
		break;
		case 6:		return 5;
		break;
		case 7:		return 6;
		break;
		case 8:		return '*';
		break;
		case 9:		return 1;
		break;
		case 10:	return 2;
		break;
		case 11:	return 3;
		break;
		case 12:	return '-';
		break;
		case 13:	return 'c';
		break;
		case 14:	return 0;
		break;
		case 15:	return '=';
		break;
		case 16:	return '+';
		break;
		}
}

