/*
 * bajo_ttl.c
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#include "bajo_ttl.h"
#include "parameter_universal.h"

TTL_t TTL;
uint8_t		ttlBuffer[100];

void TTL_Init(void) {
	TTL.rxIndex = 0;
	HAL_UART_Receive_DMA(&_TTL_USART, &TTL.rxTmp, 1);
}

void TTL_Callback(void) {

	if (TTL.rxIndex < sizeof(TTL.rxBuffer) - 2) {
		TTL.rxBuffer[TTL.rxIndex] = TTL.rxTmp;
		TTL.rxIndex++;
	}
	if (TTL.rxTmp == 10) {
		memset(ttlBuffer, 0, sizeof(ttlBuffer));
		for(uint8_t i = 0;i<(TTL.rxIndex-1);i++){
			ttlBuffer[i] = TTL.rxBuffer[i];
		}
		osMessageQueuePut(ttlQueueHandle, &ttlBuffer, 0U, 0U);
		memset(TTL.rxBuffer, 0, sizeof(TTL.rxBuffer));

		TTL.rxIndex = 0;
	}
	HAL_UART_Receive_DMA(&_TTL_USART, &TTL.rxTmp, 1);
}

void TTL_Process(char *buffer) {

	if (strstr((char*) buffer, "TEWS+VERSION?")) {
		serial_printf("VERSION: %d\r\n", 1);
	}

}

