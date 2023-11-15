/*
 * parameter_universal.h
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#ifndef INC_PARAMETER_UNIVERSAL_H_
#define INC_PARAMETER_UNIVERSAL_H_

#include "main.h"
#include "cmsis_os.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "bajo_accelerometer_adxl355.h"
#include "bajo_inclinometer_adis16209.h"
#include "bajo_eeprom.h"
#include "bajo_serial.h"
#include "bajo_ttl.h"
#include "bajo_print.h"

#define	_SERIAL_USART				huart1
#define	_TTL_USART					huart2

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern IWDG_HandleTypeDef hiwdg;

extern RTC_HandleTypeDef hrtc;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;

/* Definitions for serialQueue */
extern osMessageQueueId_t serialQueueHandle;

/* Definitions for ttlQueue */
extern osMessageQueueId_t ttlQueueHandle;

/* Definitions for rtcBinarySem */
extern osSemaphoreId_t rtcBinarySemHandle;
extern osSemaphoreId_t intBinarySemHandle;
extern osSemaphoreId_t RS232BinarySemHandle;

/*
 * Variable stored in EEPROM
 */
extern uint8_t id;
extern uint8_t range_accelerometer;
extern uint8_t odr_accelerometer;
extern uint8_t autorun;
extern uint8_t raw;
extern int offsetx;
extern int offsety;
extern int offsetz;
extern uint8_t flagtemp;

#endif /* INC_PARAMETER_UNIVERSAL_H_ */
