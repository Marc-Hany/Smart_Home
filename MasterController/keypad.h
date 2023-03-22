

#ifndef KEYPAD_H_
#define KEYPAD_H_


/************************** Module Configurations **********************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

#include <avr/io.h>
#include <util/delay.h>




/************************** Functions Prototypes ***********************/

/*
 * Function responsible for getting the pressed keypad key
 */
unsigned char KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
