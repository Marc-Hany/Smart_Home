/*
 * I2C_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "I2C_Config.h"
#include "I2C_Interface.h"
#include "I2C_Private.h"

void M_I2C_Void_I2CInit(void)
{
#if   I2C_MODE   ==   I2C_MASTER_MODE
	/* TO SELECT F_SCL -> 400 KHZ */
	TWBR_REG = 12;
#elif I2C_MODE   ==   I2C_SLAVE_MODE
	TWAR_REG = (SLAVE_ADDRESS << 1 ) | GENERAL_CALL_RESPONSE ;
#endif
	/* TO ENABLE I2C CIRCUIT */
	SET_BIT(TWCR_REG,TWEN_BIT);
}
void M_I2C_Void_I2CStartCondition(void)
{
	SET_BIT(TWCR_REG,TWSTA_BIT);  /* TO MAKE A START CONDITION */
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != START_CONDITION_HAS_BEEN_TRANSMITTED);
}
void M_I2C_Void_I2CStopCondition(void)
{
	SET_BIT(TWCR_REG,TWSTO_BIT);  /* TO MAKE A STOP CONDITION */
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
}
void M_I2C_Void_I2CRepeatedStart(void)
{
	SET_BIT(TWCR_REG,TWSTA_BIT);  /* TO CLEAR STA BIT ACCORDING TO TABLE */
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != REPEATED_START_CONDITION_HAS_BEEN_TRANSMITTED);
}
void M_I2C_Void_I2CSendSlaveAddressWrite(u8 Copy_U8_Address)
{
	TWDR_REG = Copy_U8_Address << 1;
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != SLAVE_ADDRESS_W_TRANSMITTED_ACK_REC);
}
void M_I2C_Void_I2CSendSlaveAddressRead(u8 Copy_U8_Address)
{
	TWDR_REG = (Copy_U8_Address << 1) | 1;
	CLR_BIT(TWCR_REG,TWSTA_BIT);  /* TO CLEAR STA BIT ACCORDING TO TABLE */
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != SLAVE_ADDRESS_R_TRANSMITTED_ACK_REC);
}
void M_I2C_Void_I2CSendByte(u8 Copy_U8_Data)
{
	TWDR_REG = Copy_U8_Data;
	CLR_BIT(TWCR_REG,TWSTA_BIT);  /* TO CLEAR STA BIT ACCORDING TO TABLE */
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */
	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != BYTE_TRANSMITTED_ACK_REC);
}
u8   M_I2C_Void_I2CReadByte(void)
{
	CLR_BIT(TWCR_REG,TWSTA_BIT);  /* TO CLEAR STA BIT ACCORDING TO TABLE */
	SET_BIT(TWCR_REG,6);
	SET_BIT(TWCR_REG,TWINT_BIT);  /* TO CLEAR THE FLAG */

	while(GET_BIT(TWCR_REG,TWINT_BIT) == I2C_STILL_PROCESSING);
	while((TWSR_REG & 0xF8) != BYTE_REC_ACK_TRANSMITTED);

	return 	TWDR_REG;
}
