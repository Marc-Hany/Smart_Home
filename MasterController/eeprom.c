/*
 * eeprom.c
 *
 *  Created on: Nov 6, 2022
 *      Author: k
 */

#include "eeprom.h"

void EEPROM_init(void)
{
	M_I2C_Void_I2CInit();
	_delay_ms(2000);
}

void EEPROM_write(u8 data,u8 P_address,u8 B_address)
{
	M_I2C_Void_I2CStartCondition();
	M_I2C_Void_I2CSendSlaveAddressWrite(0x50 | P_address );
	M_I2C_Void_I2CSendByte(B_address);
	M_I2C_Void_I2CSendByte(data);
	M_I2C_Void_I2CStopCondition();
}

u8 EEPROM_read(u8 P_address,u8 B_address)
{
	u8 data=0;
	M_I2C_Void_I2CStartCondition();
	M_I2C_Void_I2CSendSlaveAddressWrite(0x50 | P_address );
	M_I2C_Void_I2CSendByte(B_address);
	M_I2C_Void_I2CRepeatedStart();
	M_I2C_Void_I2CSendSlaveAddressRead(0x50 | P_address );
	data=M_I2C_Void_I2CReadByte();
	M_I2C_Void_I2CStopCondition();
	return data;
}

