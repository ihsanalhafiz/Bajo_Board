/*
 * bajo_inclinometer_adis16209.h
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_INCLINOMETER_ADIS16209_H_
#define INC_BAJO_INCLINOMETER_ADIS16209_H_

#include "parameter_universal.h"

#define _SPI_INC	hspi2

#define PROD_ID 	0x4A
#define XINCL_OUT	0x0C
#define YINCL_OUT	0x0E
#define ROT_OUT		0x10

uint8_t adis16209_read_reg(uint8_t reg, uint8_t* data, uint16_t len);
uint8_t adis16209_write_reg(uint8_t reg, uint8_t* data, uint16_t len);
int adis16209_x_inc();
void adis16209_reset();

#endif /* INC_BAJO_INCLINOMETER_ADIS16209_H_ */
