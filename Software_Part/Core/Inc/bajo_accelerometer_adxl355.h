/*
 * bajo_accelerometer_adxl355.h
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#ifndef INC_BAJO_ACCELEROMETER_ADXL355_H_
#define INC_BAJO_ACCELEROMETER_ADXL355_H_

#include "parameter_universal.h"

#define _SPI	hspi1

#define MASK(x)		((unsigned char)(1<<x))

typedef struct{
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
} bitwise_t;

/* ADXL355 registers addresses */
#define DEVID_AD                 0x00
#define DEVID_MST                0x01
#define PARTID                   0x02
#define REVID                    0x03
#define STATUS                   0x04
typedef struct {
  uint8_t data_rdy            	: 1;
  uint8_t fifo_full            	: 1;
  uint8_t fifo_ovr              : 1;
  uint8_t activity            	: 1;
  uint8_t nvm_busy           	: 1;
  uint8_t res                   : 3;
} adxl355_status_reg_t;

#define FIFO_ENTRIES             0x05
#define TEMP2                    0x06
#define TEMP1                    0x07
#define XDATA3                   0x08
#define XDATA2                   0x09
#define XDATA1                   0x0A
#define YDATA3                   0x0B
#define YDATA2                   0x0C
#define YDATA1                   0x0D
#define ZDATA3                   0x0E
#define ZDATA2                   0x0F
#define ZDATA1                   0x10
#define FIFO_DATA                0x11
#define OFFSET_X_H               0x1E
#define OFFSET_X_L               0x1F
#define OFFSET_Y_H               0x20
#define OFFSET_Y_L               0x21
#define OFFSET_Z_H               0x22
#define OFFSET_Z_L               0x23
#define ACT_EN                   0x24
#define ACT_THRESH_H             0x25
#define ACT_THRESH_L             0x26
#define ACT_COUNT                0x27
#define FILTER                   0x28
typedef struct {
  uint8_t odr                      : 4;
  uint8_t hpf                      : 3;
  uint8_t res                      : 1;
} filter_t;

#define FIFO_SAMPLES             0x29
#define INT_MAP                  0x2A
typedef struct {
  uint8_t rdy_en1                  : 1;
  uint8_t full_en1                 : 1;
  uint8_t ovr_en1                  : 1;
  uint8_t act_en1                  : 1;
  uint8_t rdy_en2                  : 1;
  uint8_t full_en2                 : 1;
  uint8_t ovr_en2                  : 1;
  uint8_t act_en2                  : 1;
} int_map_t;

#define SYNC                     0x2B
#define RANGE                    0x2C
typedef struct {
  uint8_t range                  : 2;
  uint8_t res                 	 : 4;
  uint8_t int_pol                : 1;
  uint8_t i2c_hs                 : 1;
} range_t;

#define POWER_CTL                0x2D
typedef struct {
  uint8_t standby                : 1;
  uint8_t temp_off               : 1;
  uint8_t drdy_off               : 1;
  uint8_t res	                 : 5;
} power_ctl_t;

#define SELF_TEST                0x2E
typedef struct {
  uint8_t st1                	 : 1;
  uint8_t st2               	 : 1;
  uint8_t res	                 : 6;
} self_test_t;

#define RESET                    0x2F



/**************************** Configuration parameters **********************/

/* Temperature parameters */
#define ADXL355_TEMP_BIAS       (float)1852.0      /* Accelerometer temperature bias(in ADC codes) at 25 Deg C */
#define ADXL355_TEMP_SLOPE      (float)-9.05       /* Accelerometer temperature change from datasheet (LSB/degC) */

/* Accelerometer parameters */
#define ADXL_RANGE     2     /* ADXL362 sensitivity: 2, 4, 8 [g] */

#define ACT_VALUE          50     /* Activity threshold value */

#define INACT_VALUE        50     /* Inactivity threshold value */

#define ACT_TIMER          100    /* Activity timer value in ms */

#define INACT_TIMER        10     /* Inactivity timer value in seconds */

typedef enum {
  ADXL355_ODR_4000hz   	= 0,
  ADXL355_ODR_2000hz  	= 1,
  ADXL355_ODR_1000hz  	= 2,
  ADXL355_ODR_500hz  	= 3,
  ADXL355_ODR_250hz  	= 4,
  ADXL355_ODR_125hz  	= 5,
  ADXL355_ODR_62hz  	= 6,
  ADXL355_ODR_31hz  	= 7,
  ADXL355_ODR_16hz  	= 8,
  ADXL355_ODR_8hz  		= 9,
  ADXL355_ODR_4hz  		= 10
} adxl355_odr_t;

typedef enum {
  ADXL355_RANGE_2g   	= 1,
  ADXL355_RANGE_4g  	= 2,
  ADXL355_RANGE_8g  	= 3,
} adxl355_range_t;

typedef union{
  adxl355_status_reg_t                    	adxl355_status_reg;
  range_t									range;
  power_ctl_t								power_ctl;
  self_test_t								self_test;
  int_map_t									int_map;
  filter_t									filter;

  bitwise_t                                 bitwise;
  uint8_t                                   byte;
} adxl355_reg_t;


uint8_t adxl355_read_reg( uint8_t reg, uint8_t* data, uint16_t len);
uint8_t adxl355_write_reg( uint8_t reg, uint8_t* data, uint16_t len);
uint8_t adxl355_start_measurement();
uint8_t adxl355_stop_measurement();
uint8_t adxl355_range(uint8_t data);
uint8_t adxl355_range_read( range_t* val);
uint8_t adxl355_odr( uint8_t data);
uint8_t adxl355_status();
int adxl355_x_axis();
int adxl355_y_axis();
int adxl355_z_axis();
int adxl355_temperature();
void adxl355_reset();
void adxl355_st1(uint8_t st1);
void adxl355_st2(uint8_t st2);
void adxl355_offset_x(int x);
void adxl355_offset_y(int y);
void adxl355_offset_z(int z);
uint16_t adxl355_x_axis_u();
uint16_t adxl355_y_axis_u();
uint16_t adxl355_z_axis_u();
float CalculateRoll(float y, float z);
float CalculatePitch(float x, float y, float z);
void adxl355_readData(float *finalX, float *finalY, float *finalZ, float *temp, uint8_t range);

#endif /* INC_BAJO_ACCELEROMETER_ADXL355_H_ */
