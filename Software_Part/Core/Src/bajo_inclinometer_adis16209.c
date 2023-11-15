/*
 * bajo_inclinometer_adis16209.c
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#include "bajo_inclinometer_adis16209.h"
#include "parameter_universal.h"

uint8_t adis16209_read_reg(uint8_t reg, uint8_t* data, uint16_t len)
{
	uint8_t ret;
	uint8_t reg16[2];
	reg16[1] = 0x00;
	reg16[0] = reg & 0x7F ;
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	ret = HAL_SPI_Transmit(&_SPI_INC, reg16,  2, 10000);  // send address
	ret = HAL_SPI_Receive(&_SPI_INC, data, 2, 10000);  // receive the data
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_SET);   // pull the pin high

	return ret;
}

uint8_t adis16209_write_reg(uint8_t reg, uint8_t* data, uint16_t len)
{
	uint8_t ret;
	uint8_t data1[2], data2[2];
	data1[1] = data[1];
	data1[0] = reg | 0x40 ;
	data2[1] = data[0];
	data2[0] = (reg+1) | 0x40;

	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	ret = HAL_SPI_Transmit(&_SPI_INC, data1,  2, 10000);  // send address
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
	osDelay(25);
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	ret = HAL_SPI_Transmit(&_SPI_INC, data2,  2, 10000);  // send address
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
	return ret;
}

int adis16209_x_inc(){
	int data;
	uint8_t buf[2];

	adis16209_read_reg(XINCL_OUT, buf, 2);
	data = ((buf[0] & 0x3F)<<8) | buf[1];

	return data;
}

void adis16209_reset(){
	uint8_t data1[2], data2[2];
	data1[1] = 0x01;
	data1[0] = 0xB6 ;
	data2[1] = 0x00;
	data2[0] = 0xB7;

	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	HAL_SPI_Transmit(&_SPI_INC, data1,  2, 10000);  // send address
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
	osDelay(50);
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	HAL_SPI_Transmit(&_SPI_INC, data2,  2, 10000);  // send address
	HAL_GPIO_WritePin(INC_CS_GPIO_Port, INC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
}
