/*
 * bajo_serial.c
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#include "bajo_serial.h"
#include "parameter_universal.h"

SERIAL_t SERIAL;

void SERIAL_Init(void) {
	SERIAL.rxIndex = 0;
	HAL_UART_Receive_DMA(&_SERIAL_USART, &SERIAL.rxTmp, 1);
}

void SERIAL_Callback(void) {
	if (SERIAL.rxIndex < sizeof(SERIAL.rxBuffer) - 2) {
		SERIAL.rxBuffer[SERIAL.rxIndex] = SERIAL.rxTmp;
		SERIAL.rxIndex++;
	}
	if (SERIAL.rxTmp == 13) {
		osMessageQueuePut(serialQueueHandle, &SERIAL.rxBuffer, 0U, 0U);
		memset(SERIAL.rxBuffer, 0, sizeof(SERIAL.rxBuffer));
		SERIAL.rxIndex = 0;
	}
	HAL_UART_Receive_DMA(&_SERIAL_USART, &SERIAL.rxTmp, 1);
}

void SERIAL_Process(char *buffer) {
	char *strx;
	strx = strstr(buffer, "AT+"); //GPGGA

	if (strx != NULL) {
		if (strstr((char*) buffer, "STOP")) {
			adxl355_stop_measurement();
			serial_printf("stop\r\n");
		}
		if (strstr((char*) buffer, "START")) {
			adxl355_start_measurement();
			serial_printf("start\r\n");
		}
		if (strstr((char*) buffer, "ID=")) {
			id = parsingdataserial(buffer, "ID=");
			if(id>100) 	serial_printf("ERROR - ID max 100\r\n");
			else{
				write_eeprom_byte(&hi2c2, 0x00, &id);
				serial_printf("OK\r\n");
			}
		}
		if (strstr((char*) buffer, "ID?")) {
			serial_printf("ID:%d\r\n", id);
		}
		if (strstr((char*) buffer, "RANGE=")) {
			uint32_t range = parsingdataserial(buffer, "RANGE=");
			if(range>3){
				serial_printf("ERROR - Range value 1=2g 2=4g 3=8g\r\n");
			}
			else{
				range_accelerometer = range;
				write_eeprom_byte(&hi2c2, 0x01, &range_accelerometer);
				adxl355_range(range_accelerometer);

				if(range_accelerometer == 1) serial_printf("OK range=2g\r\n");
				if(range_accelerometer == 2) serial_printf("OK range=4g\r\n");
				if(range_accelerometer == 3) serial_printf("OK range=8g\r\n");
			}
		}
		if (strstr((char*) buffer, "RANGE?")) {
			serial_printf("RANGE:%d\r\n", range_accelerometer);
		}
		if (strstr((char*) buffer, "ODR=")) {
			odr_accelerometer = parsingdataserial(buffer, "ODR=");
			write_eeprom_byte(&hi2c2, 0x02, &odr_accelerometer);
			adxl355_odr(odr_accelerometer);
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "ODR?")) {
			serial_printf("ODR:%d\r\n", odr_accelerometer);
		}
		if (strstr((char*) buffer, "AUTO=")) {
			autorun = parsingdataserial(buffer, "AUTO=");
			write_eeprom_byte(&hi2c2, 0x03, &autorun);
			if(autorun == 1){
				adxl355_start_measurement();
			}
			if(autorun == 0){
				adxl355_stop_measurement();
			}
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "AUTO?")) {
			serial_printf("AUTO:%d\r\n", autorun);
		}
		if (strstr((char*) buffer, "ACCRESET")) {
			serial_printf("Reset ADXL355\r\n");
			adxl355_reset();
		}
		if (strstr((char*) buffer, "ST1=")) {
			uint8_t st1;
			st1 = parsingdataserial(buffer, "ST1=");
			if(st1 == 0) {
				adxl355_st1(0);
				serial_printf("ST1 OFF\r\n");
			}
			if(st1 == 1) {
				adxl355_st1(1);
				serial_printf("ST1 ON\r\n");
			}
			if(st1 > 1) serial_printf("wrong value\r\n");
		}
		if (strstr((char*) buffer, "ST2=")) {
			uint8_t st2;
			st2 = parsingdataserial(buffer, "ST2=");
			if(st2 == 0) {
				adxl355_st2(0);
				serial_printf("ST2 OFF\r\n");
			}
			if(st2 == 1) {
				adxl355_st2(1);
				serial_printf("ST2 ON\r\n");
			}
			if(st2 > 1) serial_printf("wrong value\r\n");
		}
		if (strstr((char*) buffer, "RAW=")) {
			raw = parsingdataserial(buffer, "RAW=");
			write_eeprom_byte(&hi2c2, 0x04, &raw);
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "RAW?")) {
			serial_printf("RAW:%d\r\n", raw);
		}

		if (strstr((char*) buffer, "OFFSETX=")) {
			offsetx = parsingdataserialint(buffer, "OFFSETX=");
			write_eeprom_union(&hi2c2, 0x05, offsetx);
			adxl355_offset_x(offsetx);
			serial_printf("OK, %d, %x\r\n", offsetx, offsetx);
		}
		if (strstr((char*) buffer, "OFFSETX?")) {
			serial_printf("OFFSETX:%d\r\n", offsetx);
		}
		if (strstr((char*) buffer, "OFFSETY=")) {
			offsety = parsingdataserialint(buffer, "OFFSETY=");
			write_eeprom_union(&hi2c2, 0x09, offsety);
			adxl355_offset_y(offsety);
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "OFFSETY?")) {
			serial_printf("OFFSETY:%d\r\n", offsety);
		}
		if (strstr((char*) buffer, "OFFSETZ=")) {
			offsetz = parsingdataserialint(buffer, "OFFSETZ=");
			write_eeprom_union(&hi2c2, 0x10, offsetz);
			adxl355_offset_z(offsetz);
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "OFFSETZ?")) {
			serial_printf("OFFSETZ:%d\r\n", offsetz);
		}

		if (strstr((char*) buffer, "INCDATA=")) {
			flagtemp = parsingdataserial(buffer, "INCDATA=");
			write_eeprom_byte(&hi2c2, 0x14, &flagtemp);
			serial_printf("OK\r\n");
		}
		if (strstr((char*) buffer, "INCDATA?")) {
			serial_printf("INCDATA:%d\r\n", flagtemp);
		}

		/////////////////////////////////////////////////////
		/*
		 * ADIS16209 Command
		 */
		if (strstr((char*) buffer, "INCSTATUS?")) {
			uint8_t buf2[2];
			adis16209_read_reg(0x3C, buf2, 2);
			serial_printf("inclino status: %x %x\r\n",buf2[0], buf2[1]);
		}
		if (strstr((char*) buffer, "INCX?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x0C, buf3, 2);
			serial_printf("inclino x: %x %x\r\n",buf3[0], buf3[1]);
		}
		if (strstr((char*) buffer, "INCY?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x0E, buf3, 2);
			serial_printf("inclino y: %x %x\r\n",buf3[0], buf3[1]);
		}
		if (strstr((char*) buffer, "INCROT?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x10, buf3, 2);
			serial_printf("inclino rot: %x %x\r\n",buf3[0], buf3[1]);
		}
		if (strstr((char*) buffer, "INCSUPOUT?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x02, buf3, 2);
			serial_printf("inclino supp out: %x %x\r\n",buf3[0], buf3[1]);
		}
		if (strstr((char*) buffer, "INCRESET")) {
			serial_printf("inclino reset...\r\n");
			adis16209_reset();
		}

		if (strstr((char*) buffer, "INCREV?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x46, buf3, 2);
			serial_printf("inclino revision: %x %x\r\n",buf3[0], buf3[1]);
		}
		if (strstr((char*) buffer, "INCMSC?")) {
			uint8_t buf3[2];
			adis16209_read_reg(0x34, buf3, 2);
			serial_printf("inclino MSC_OUT: %x %x\r\n",buf3[0], buf3[1]);
		}

		if (strstr((char*) buffer, "REBOOT")) {
			serial_printf("Reboot....\r\n");
			NVIC_SystemReset();
		}
	}
	else serial_printf("Wrong Command\r\n");
/*
	if (strstr((char*) buffer, "STOP")) {
		adxl355_stop_measurement();
	}
*/
}

uint32_t parsingdataserial(char *buffer, char *keyword) {
	char *data;
	char *str = strstr((char*) buffer, keyword);
	strtok_r(str, "=", &str);
	//data = strtok_r(str, "\r", &str);
	data = str;
	return atoi(data);
}

int parsingdataserialint(char *buffer, char *keyword) {
	char *data;
	char *str = strstr((char*) buffer, keyword);
	strtok_r(str, "=", &str);
	//data = strtok_r(str, "\r", &str);
	data = str;
	return atoi(data);
}

