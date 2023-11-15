/*
 * bajo_accelerometer_adxl355.c
 *
 *  Created on: Apr 7, 2021
 *      Author: ihsan
 */

#include "bajo_accelerometer_adxl355.h"
#include "parameter_universal.h"

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
uint8_t adxl355_read_reg(uint8_t reg, uint8_t* data, uint16_t len)
{
	uint8_t ret;
	reg = (reg<<1) | 0x01;  /* set read operation= to enter Read mode you have to set the 8th bit of the first byte sent to 1.*/
	HAL_GPIO_WritePin(GPIOA, ACC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	ret = HAL_SPI_Transmit(&_SPI, &reg, 1, 10000);  // send address
	ret = HAL_SPI_Receive(&_SPI, data, len, 10000);  // receive the data
	HAL_GPIO_WritePin(GPIOA, ACC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
	return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
uint8_t adxl355_write_reg(uint8_t Reg, uint8_t* data, uint16_t len)
{
  uint8_t ret;
	Reg = (Reg<<1) | 0x00;
	HAL_GPIO_WritePin(GPIOA, ACC_CS_Pin, GPIO_PIN_RESET);   // pull the pin low
	ret = HAL_SPI_Transmit(&_SPI, &Reg, 1, 10000);
	ret = HAL_SPI_Transmit(&_SPI, data, len, 10000);
	HAL_GPIO_WritePin(GPIOA, ACC_CS_Pin, GPIO_PIN_SET);   // pull the pin high
  return ret;
}

//###########################################################################################################

uint8_t adxl355_start_measurement()
{
	uint8_t ret;
	uint8_t val = 0x00;
	ret = adxl355_write_reg(POWER_CTL, (uint8_t*)&val, 1);
	return ret;
}

uint8_t adxl355_stop_measurement()
{
	uint8_t ret;
	uint8_t data=1;
	//power_ctl_t power_ctl;
	//power_ctl.standby = 1;
	ret = adxl355_write_reg(POWER_CTL, (uint8_t*)&data, 1);
	return ret;
}

uint8_t adxl355_range( uint8_t data)
{
	//range_t range;
	uint8_t ret;
	//range.range = data;
	//ret = adxl355_write_reg(RANGE, (uint8_t*)&range, 1);
	ret = adxl355_write_reg(RANGE, &data, 1);
	return ret;
}

uint8_t adxl355_range_read( range_t* val)
{
	uint8_t ret;
	ret = adxl355_read_reg(RANGE, (uint8_t*)&val, 1);
	return ret;
}

uint8_t adxl355_odr( uint8_t data)
{
	//filter_t filter;
	uint8_t ret;
	//filter.odr = data;
	//ret = adxl355_write_reg( FILTER, (uint8_t*)&filter, 1);
	ret = adxl355_write_reg( FILTER, (uint8_t*)&data, 1);
	return ret;
}

uint8_t adxl355_status()
{
	uint8_t val;
	adxl355_read_reg( STATUS, (uint8_t*)&val, 1);
	val &= 0x01;
	return val;
}

int adxl355_x_axis()
{
	uint8_t data1, data2, data3;
	uint32_t data123 = 0;
	int finaldata = 0;
	int intdata = 0;
	float tempf;

	adxl355_read_reg( XDATA1, (uint8_t*)&data1, 1);
	adxl355_read_reg( XDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( XDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<16)|(data2<<8)|(data1);
	//data123 = (data3<<12)| (data2<<4);
	data123 = data123>>4;
	data123 &= 0x000FFFFF;
	//serial_printf("X321: %x,%x,%x\r\n", data3, data2, data1);

	if((data123 & 0x00080000)  == 0x00080000) intdata = (data123 | 0xFFF00000);
	else intdata = data123;
/*
	if(range_accelerometer == ADXL355_RANGE_2g){
		tempf = ((float)intdata / 256000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_4g){
		tempf = ((float)intdata / 128000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_8g){
		tempf = ((float)intdata / 64000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	*/
	//else
	if(raw == 0){
		if(range_accelerometer == ADXL355_RANGE_2g){
			tempf = ((float)intdata / 256000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_4g){
			tempf = ((float)intdata / 128000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_8g){
			tempf = ((float)intdata / 64000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
	}
	else{
		return intdata;
	}
	return 0;
}

int adxl355_y_axis()
{
	uint8_t data1, data2, data3;
	uint32_t data123 = 0;
	int finaldata = 0;
	int intdata = 0;
	float tempf;

	adxl355_read_reg( YDATA1, (uint8_t*)&data1, 1);
	adxl355_read_reg( YDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( YDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<16)|(data2<<8)|(data1);
	data123 = data123>>4;
	//data123 = (data3<<12)| (data2<<4);
	data123 &= 0x000FFFFF;
	//serial_printf("Y321: %x,%x,%x\r\n", data3, data2, data1);

	if((data123 & 0x00080000)  == 0x00080000) intdata = (data123 | 0xFFF00000);
	else intdata = data123;
/*
	if(range_accelerometer == ADXL355_RANGE_2g){
		tempf = ((float)intdata / 256000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_4g){
		tempf = ((float)intdata / 128000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_8g){
		tempf = ((float)intdata / 64000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else return 0;
	*/
	if(raw == 0){
		if(range_accelerometer == ADXL355_RANGE_2g){
			tempf = ((float)intdata / 256000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_4g){
			tempf = ((float)intdata / 128000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_8g){
			tempf = ((float)intdata / 64000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
	}
	else{
		return intdata;
	}
	return 0;
}

int adxl355_z_axis()
{
	uint8_t data1, data2, data3;
	uint32_t data123 = 0;
	int finaldata = 0;
	int intdata = 0;
	float tempf;

	adxl355_read_reg( ZDATA1, (uint8_t*)&data1, 1);
	adxl355_read_reg( ZDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( ZDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<16)|(data2<<8)|(data1);
	data123 = data123>>4;
	//data123 = (data3<<12);
	data123 &= 0x000FFFFF;

	//serial_printf("Z321: %x,%x,%x\r\n", data3, data2, data1);

	if((data123 & 0x00080000)  == 0x00080000) intdata = (data123 | 0xFFF00000);
	else intdata = data123;

	if(raw == 0){
		if(range_accelerometer == ADXL355_RANGE_2g){
			tempf = ((float)intdata / 256000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_4g){
			tempf = ((float)intdata / 128000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
		else if (range_accelerometer == ADXL355_RANGE_8g){
			tempf = ((float)intdata / 64000.0)*1000000.0;
			finaldata = (int)tempf;
			return finaldata;
		}
	}
	else{
		return intdata;
	}
/*
	if(range_accelerometer == ADXL355_RANGE_2g){
		tempf = ((float)intdata / 256000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_4g){
		tempf = ((float)intdata / 128000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else if (range_accelerometer == ADXL355_RANGE_8g){
		tempf = ((float)intdata / 64000.0)*1000000.0;
		finaldata = (int)tempf;
		return finaldata;
	}
	else return 0;
	*/
	return 0;
}

int adxl355_temperature(){
	int temp;
	uint8_t data1, data2;
	uint16_t data12;
	float f32temp;

	adxl355_read_reg( TEMP2, (uint8_t*)&data2, 1);
	adxl355_read_reg( TEMP1, (uint8_t*)&data1, 1);

	data12 = (data2 << 8) | data1;
	f32temp = (((((float)data12 - ADXL355_TEMP_BIAS)) / ADXL355_TEMP_SLOPE) + 25.0)*100.0;
	temp = (int)f32temp;

	return temp;
}

void adxl355_reset(){
	adxl355_write_reg(RESET,(uint8_t*)0x52, 1);
}

void adxl355_st1(uint8_t st1){
	uint8_t bufst1;
	adxl355_read_reg(SELF_TEST,&bufst1, 1);
	if(st1 == 0) bufst1 &= 0xFE;
	if(st1 == 1) bufst1 |= 0x01;
	adxl355_write_reg(SELF_TEST,&bufst1, 1);
}

void adxl355_st2(uint8_t st2){
	uint8_t bufst2;
	adxl355_read_reg(SELF_TEST,&bufst2, 1);
	if(st2 == 0) bufst2 &= 0xFE;
	if(st2 == 1) bufst2 |= 0x01;
	adxl355_write_reg(SELF_TEST,&bufst2, 1);
}

void adxl355_offset_x(int x){
	uint8_t xH;
	uint8_t xL;
	xH = (x>>12) & 0xff;
	xL = (x>>4) & 0xff;

	adxl355_write_reg(OFFSET_X_H,&xH, 1);
	adxl355_write_reg(OFFSET_X_L,&xL, 1);
	//serial_printf("xH %x, xL %x\r\n", xH, xL);
}

void adxl355_offset_y(int y){
	uint8_t yH;
	uint8_t yL;
	yH = (y>>12) & 0xff;
	yL = (y>>4) & 0xff;

	adxl355_write_reg(OFFSET_Y_H,&yH, 1);
	adxl355_write_reg(OFFSET_Y_L,&yL, 1);
}

void adxl355_offset_z(int z){
	uint8_t zH;
	uint8_t zL;
	zH = (z>>12) & 0xff;
	zL = (z>>4) & 0xff;

	adxl355_write_reg(OFFSET_Z_H,&zH, 1);
	adxl355_write_reg(OFFSET_Z_L,&zL, 1);

}

uint16_t adxl355_x_axis_u()
{
	uint8_t data2, data3;
	uint16_t data123 = 0;

	adxl355_read_reg( XDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( XDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<8)|(data2);
	return data123;
}

uint16_t adxl355_y_axis_u()
{
	uint8_t data2, data3;
	uint16_t data123 = 0;

	adxl355_read_reg( YDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( YDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<8)|(data2);
	return data123;
}

uint16_t adxl355_z_axis_u()
{
	uint8_t data2, data3;
	uint16_t data123 = 0;

	adxl355_read_reg( ZDATA2, (uint8_t*)&data2, 1);
	adxl355_read_reg( ZDATA3, (uint8_t*)&data3, 1);

	data123 = (data3<<8)|(data2);
	return data123;
}

float CalculateRoll(float y, float z){
    float Roll;
    return Roll= (atan2(y, z) * 180.0/M_PI)*100.0;
}

float CalculatePitch(float x, float y, float z){
    float Pitch;
    return Pitch = (atan2(-x, sqrt(y*y + z*z)) * 180.0/M_PI)*100.0;
}

//membaca data sekaligus 11 byte untuk data temp dan data accelerometer Ax,Ay,Az
//temperatur dlm deg celcius, Accelerometer dalam satuan g
void adxl355_readData(float *finalX, float *finalY, float *finalZ, float *temp, uint8_t range)
{
	uint8_t rawData[11];
	uint16_t temperatur;
	uint32_t x,y,z;
	int X,Y,Z;
	float scalefactor;

	memset(rawData, 0x00, sizeof(rawData));
	adxl355_read_reg(TEMP2, rawData, 11);   //0x06 = address awal TEMP2
	//
	if(range==1) scalefactor=3.9;			//2G
	else if(range==2) scalefactor=7.8;	//4G
	else if(range==3) scalefactor=15.6;	//8G
	else scalefactor=7.8;    //default dibuat 4G jika nilai range_accelerometer tdk ditentukan
	//========
	temperatur = ((rawData[0] << 8) | rawData[1]);
	*temp = (float)(temperatur - ADXL355_TEMP_BIAS) / ADXL355_TEMP_SLOPE + 25.0;
	//========
	x = 0;
	x |= (rawData[4] >> 4);
	x |= (rawData[3] << 4);
	x |= (rawData[2] << 12);
	//x = ((x & 0x00080000) ? (x | 0xFFF00000) : x);
	x &= 0x000FFFFF;
	if((x & 0x00080000)  == 0x00080000) x = (x | 0xFFF00000);
	X = (int)x;
	*finalX=(scalefactor*X)/1000000.0; //satuannya g
	//========
	y = 0;
	y |= (rawData[7] >> 4);
	y |= (rawData[6] << 4);
	y |= (rawData[5] << 12);
	//y = ((y & 0x00080000) ? (y | 0xFFF00000) : y);
	y &= 0x000FFFFF;
	if((y & 0x00080000)  == 0x00080000) y = (y | 0xFFF00000);
	Y = (int)y;
	*finalY=(scalefactor*Y)/1000000.0;
	//========
	z = 0;
	z |= (rawData[10] >> 4);
	z |= (rawData[9] << 4);
	z |= (rawData[8] << 12);
	//z = ((z & 0x00080000) ? (z | 0xFFF00000) : z);
	z &= 0x000FFFFF;
	if((z & 0x00080000)  == 0x00080000) z = (z | 0xFFF00000);
	Z = (int)z;
	*finalZ=(scalefactor*Z)/1000000.0;
}
