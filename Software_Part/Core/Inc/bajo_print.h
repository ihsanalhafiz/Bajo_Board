/*
 * bajo_print.h
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_PRINT_H_
#define INC_BAJO_PRINT_H_

#include "parameter_universal.h"

void serial_printf(const char *fmt, ...);
void ttl_printf(const char *fmt, ...);
void serial_println(const char *str);
void serial_puts(const char *str);

#endif /* INC_BAJO_PRINT_H_ */
