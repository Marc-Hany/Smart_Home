/*
 * SPI.h
 *
 *  Created on: Sep 13, 2019
 *      Author: Joseph Hanna
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const unsigned char data);
unsigned char SPI_recieveByte(void);
void SPI_SendString(const unsigned char *Str);
void SPI_receiveString(char *Str);

#endif /* SPI_H_ */
