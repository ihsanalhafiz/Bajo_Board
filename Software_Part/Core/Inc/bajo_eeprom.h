/*
 * bajo_eeprom.h
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_EEPROM_H_
#define INC_BAJO_EEPROM_H_

#include "parameter_universal.h"

#define EEPROM_ADDRESS_for_write 0x50 /*A0=A1=A2=0*/
#define MEMORY_ADDRESS 0x08

void write_eeprom_byte(I2C_HandleTypeDef *hi2c,unsigned int position,uint8_t* data);
void write_eeprom_page(I2C_HandleTypeDef *hi2c,unsigned int position,uint8_t* data,uint8_t length);
unsigned int read_eeprom_byte(I2C_HandleTypeDef *hi2c,unsigned int position,uint8_t* data);
unsigned int read_eeprom_page(I2C_HandleTypeDef *hi2c,unsigned int position,uint8_t* data,uint8_t length);
void check_eeprom(UART_HandleTypeDef *uart,I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
uint32_t read_eeprom_union(I2C_HandleTypeDef *hi2c,unsigned int position);
void write_eeprom_union(I2C_HandleTypeDef *hi2c,unsigned int position,uint32_t data);
void InitEEPROM(void);

#endif /* INC_BAJO_EEPROM_H_ */
