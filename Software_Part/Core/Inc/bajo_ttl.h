/*
 * bajo_ttl.h
 *
 *  Created on: Apr 8, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_TTL_H_
#define INC_BAJO_TTL_H_

#include "parameter_universal.h"

typedef struct
{
	uint8_t		rxBuffer[512];
	uint16_t	rxIndex;
	uint8_t		rxTmp;
	uint32_t	LastTime;
}TTL_t;

extern TTL_t TTL;

void TTL_Init(void);
void TTL_Callback(void);
void TTL_Process(char *buffer);

#endif /* INC_BAJO_TTL_H_ */
