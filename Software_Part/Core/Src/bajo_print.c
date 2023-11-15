/*
 * bajo_print.c
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#include "bajo_print.h"
#include "parameter_universal.h"

void serial_printf(const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	char string[200];
	if (0 < vsprintf(string, fmt, argp)) {
		HAL_UART_Transmit(&_SERIAL_USART, (uint8_t*) string, strlen(string),
				0xffffff);
	}
	va_end(argp);
}

void ttl_printf(const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	char string[200];
	if (0 < vsprintf(string, fmt, argp)) {
		HAL_UART_Transmit(&_TTL_USART, (uint8_t*) string, strlen(string),
				0xffffff);
	}
	va_end(argp);
}

//untuk mengirim data (khusus data string) ke RS-232
void serial_println(const char *str){
	HAL_UART_Transmit(&_TTL_USART, (uint8_t*) str, strlen(str), 0xffffff);
}

//untuk mengirim data (khusus data string) ke RS-232
void serial_puts(const char *str){
	HAL_UART_Transmit(&_SERIAL_USART, (uint8_t*) str, strlen(str), 0xffffff);
}
