/*
 * bajo_serial.h
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_SERIAL_H_
#define INC_BAJO_SERIAL_H_

#include "parameter_universal.h"

typedef struct
{
	uint8_t		rxBuffer[512];
	uint16_t	rxIndex;
	uint8_t		rxTmp;
	uint32_t	LastTime;
}SERIAL_t;

extern SERIAL_t SERIAL;

void SERIAL_Init(void);
void SERIAL_Callback(void);
void SERIAL_Process(char *buffer);
uint32_t parsingdataserial(char *buffer, char *keyword);
int parsingdataserialint(char *buffer, char *keyword);

#endif /* INC_BAJO_SERIAL_H_ */
