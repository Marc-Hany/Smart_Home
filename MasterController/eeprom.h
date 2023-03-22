/*
 * eeprom.h
 *
 *  Created on: Nov 6, 2022
 *      Author: k
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C_Interface.h"
#include <util/delay.h>

void EEPROM_init(void);
void EEPROM_write(u8,u8,u8);
u8 EEPROM_read(u8,u8);



#endif /* EEPROM_H_ */
