/*
 * bajo_eeprom.c
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */


#include "bajo_eeprom.h"
#include "parameter_universal.h"


void write_eeprom_byte(I2C_HandleTypeDef *hi2c, unsigned int position,
		uint8_t *data) {   //Menulis Per Byte Character
	HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1, position,
			1, data, 1, 5);
}

void write_eeprom_page(I2C_HandleTypeDef *hi2c, unsigned int position,
		uint8_t *data, uint8_t length) { //Menulis Per Page
	for (int i = 0; i < length; i++) {
		HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
				position, 1, (uint8_t*) &data[i], 1, 5);
		position++;
	}
}

unsigned int read_eeprom_byte(I2C_HandleTypeDef *hi2c, unsigned int position,
		uint8_t *data) {
	HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1, position,
			1, data, 1, 5); //read memory address 08
	return *data;
}

unsigned int read_eeprom_page(I2C_HandleTypeDef *hi2c, unsigned int position,
		uint8_t *data, uint8_t length) {

	int j;
	uint8_t data1[length];
	for (j = 0; j < length; j++) {
		HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
				position, 1, (uint8_t*) &data1[j], 1, 5); //read memory address 08
		position++;
		data[j] = data1[j];
	}
	return *data;
}

void check_eeprom(UART_HandleTypeDef *uart, I2C_HandleTypeDef *hi2c,
		uint16_t DevAddress, uint32_t Trials, uint32_t Timeout) {
	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(hi2c, DevAddress, Trials, Timeout);
	if (result != HAL_OK) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
			{
		HAL_UART_Transmit(&_SERIAL_USART, (uint8_t*) &"Failed Eeprom \r\n", 15,	10);
	}
	if (result == HAL_OK) {
		HAL_UART_Transmit(&_SERIAL_USART, (uint8_t*) "Found Eeprom \r\n", 25,1000);
	}
}

uint32_t read_eeprom_union(I2C_HandleTypeDef *hi2c, unsigned int position) {
	char four;
	char three;
	char two;
	char one;
	HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1, position,
			1, (uint8_t*) &four, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 1, 1, (uint8_t*) &three, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 2, 1, (uint8_t*) &two, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Read(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 3, 1, (uint8_t*) &one, 1, 100);
	osDelay(5);
	return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF)
			+ ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void write_eeprom_union(I2C_HandleTypeDef *hi2c, unsigned int position,
		uint32_t data) { //Menulis Per Page
	char four = (data & 0xFF);
	char three = ((data >> 8) & 0xFF);
	char two = ((data >> 16) & 0xFF);
	char one = ((data >> 24) & 0xFF);

	HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1, position,
			1, (uint8_t*) &four, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 1, 1, (uint8_t*) &three, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 2, 1, (uint8_t*) &two, 1, 100);
	osDelay(5);
	HAL_I2C_Mem_Write(hi2c, (uint16_t) EEPROM_ADDRESS_for_write << 1,
			position + 3, 1, (uint8_t*) &one, 1, 100);
	osDelay(5);
}

void InitEEPROM(void) {
	/*
	//read_eeprom_byte(&hi2c2, 0x00, &mode); //mode CPU :
	mode = BUOY;
	//operationmode = 0;
	//read_eeprom_byte(&hi2c1, 0x01, &idOBU); //ID OBU
	read_eeprom_byte(&hi2c1, 0x02, &idBUOY); //ID BUOY
	//read_eeprom_byte(&hi2c1, 0x03, &idCBT); //ID CBT
	read_eeprom_byte(&hi2c1, 0x04, &operationmode);
	read_eeprom_byte(&hi2c1, 0x05, &debug);
	read_eeprom_byte(&hi2c1, 0x06, &debugbt);
	read_eeprom_byte(&hi2c1, 0x07, &sendmodeiridium);
	read_eeprom_byte(&hi2c1, 0x08, &countertsunami);
	read_eeprom_byte(&hi2c1, 0x09, &calculationstatus);
	threshold = read_eeprom_union(&hi2c1, 0x0A);
	periodsampling = read_eeprom_union(&hi2c1, 0x10);
	periodsenddata = read_eeprom_union(&hi2c1, 0x14);
	periodsendloc = read_eeprom_union(&hi2c1, 0x18);
	periodsendbat = read_eeprom_union(&hi2c1, 0x1C);
	timebacknormal = read_eeprom_union(&hi2c1, 0x20);
	*/

	read_eeprom_byte(&hi2c2, 0x00, &id);
	read_eeprom_byte(&hi2c2, 0x01, &range_accelerometer);
	read_eeprom_byte(&hi2c2, 0x02, &odr_accelerometer);
	read_eeprom_byte(&hi2c2, 0x03, &autorun);
	read_eeprom_byte(&hi2c2, 0x04, &raw);
	offsetx = read_eeprom_union(&hi2c2, 0x05);
	offsety = read_eeprom_union(&hi2c2, 0x09);
	offsetz = read_eeprom_union(&hi2c2, 0x10);
	read_eeprom_byte(&hi2c2, 0x14, &flagtemp);
}
