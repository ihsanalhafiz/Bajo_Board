# Bajo Board (Low Cost Seismic Imaging Sensor Systems based on MEMS Accelerometer)

The Bajo Board or accelerometer sensor system is an integrated sensor system consisting of accelerometer, inclinometer and seismometer sensors. The accelerometer sensor is used to detect vibrations and carry out seismic imaging. The inclinometer sensor is used to detect tilt from monitoring stations. The seismometer sensor is used to calculate the SI value to detect early if there is an earthquake or tectonic activity and send a warning if an earthquake with MMI level 5 or above is detected. It requires voltage input with industry standart 24V, and will provide interface in RS232.

# [Updated] Deploy location and results

## Deploy location
This board was deployed in the pilot project Indonesia Cable Based Tsunameter in NTT, Indonesia in 2 locations. These sensors are used for the seismic imaging, so it receives the accelerometer raw data and not directly converted to earthquake magnitude. that is the ongoing research. 

![deploy](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/deployLocation.png)

reference

M. A. Purwoadi, Y. Anantasena, W. W. Pandoe, J. Widodo and A. E. Sakya, "Introduction to Indonesian Cable-based Subsea Tsunameter," 2023 IEEE Underwater Technology (UT), Tokyo, Japan, 2023, pp. 1-6, doi: 10.1109/UT49729.2023.10103368.

## Results from earthquakes
these results show accelerometer raw data from earthquakes.
### First earthquake
![firstEarthquake](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/15082023NTT.jpg)
![responseFisrt](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/NTT.jpeg)

### Second earthquake
![secondEarthquake](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/28082023Balisea.jpg)
![responseSecond](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/Balisea.jpeg)

# Block Diagram System

![block diagram](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/diagramblok.png)

The accelerometer sensor system has three main sensor elements, namely the accelerometer sensor, inclinometer and seismometer. In the picture above, a comprehensive block design for the accelerometer sensor system is designed which consists of the sensors used and supporting components such as power supply, digital components and communication components. The ADXL355 accelerometer sensor is a 3-axis accelerometer sensor based on MEMS which is usually used to detect vibrations and one of them is for seismic imaging according to the datasheet. The ADIS16209 inclinometer sensor is a sensor for detecting 2-axis tilt, namely x and y, which is intended to detect the tilt of the OBU installation in the CBT system, as well as to monitor whether there is a change in tilt when the OBU has been deployed and is operating. The D7S seismometer sensor is an Omron vibration sensor that can be integrated to detect earthquake vibrations by calculating the SI value of an earthquake event. This sensor is also equipped with an interruption process when there is an earthquake event with an MMI of 5 and above, so that by detecting the SI value an earthquake can be detected and a warning sent.

# Hardware Part

![board](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/board.jpg)


![boardwithcasing](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/boardwithcasing.jpg)

![case](https://www.budind.com/wp-content/uploads/2019/01/hban2851a-1024x663.jpg)
[Link to buy the case AN-2851-AB](https://www.digikey.com/en/products/detail/bud-industries/AN-2851-AB/5775342)

## PCB Design
![top](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/topPic.png)
![bottom](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/bottomPic.png)

[Gerber File](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Hardware_Part/SeismicAccelerometerSystem_Gerber.zip)

[Bill of Materials](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Hardware_Part/BoM.xlsx)

[Centroid File](https://github.com/ihsanalhafiz/Bajo_Board/tree/master/Hardware_Part/CentroidFile)

# Software Part

![pinout](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/pinout.png)

## List Bajo EEPROM Variable
No. | Address | Variables | Expected Value | Number of Bytes | Information
:---: | :---: | --- | --- | :---: | ---
1 | 0x00 | id | 0 - 100 | 1 | ID of the sensor
2 | 0x01 | range_accelerometer | 1, 2, or 3 (2g, 4g, 8g) | 1 | Sensor reading range
3 | 0x02 | odr_accelerometer | 0 - 10 (4000hz - 4hz) | 1 | Output accelerometer data output
4 | 0x03 | autorun | 1 (auto run) or 0 (manual run/need command) | 1 | Autorun or manual accelerometer sensor
5 | 0x04 | raw | 1 (decimal) or 0 (micro g) | 1 | Accelerometer output data unit
6 | 0x05 | offsetx | ± 32768 | 4 | Offset value for x calibration
7 | 0x09 | offsety | ± 32768 | 4 | Offset value for y calibration
8 | 0x10 | offsetz | ± 32768 | 4 | Offset value for z calibration

## List of Bajo Serial Process
No. | Command | Syntax | Response/Output | Function/Description
--- | --- | --- | --- | ---
1 | STOP | AT+STOP | "stop" | Stops ADXL355 sensor Measurement
2 | START | AT+START | "start" | Starting Measurement of ADXL355 sensor
3 | ID= | AT+ID=<1-100> | "OK" | Enter the Bajo Board ID in the EEPROM
4 | ID? | AT+ID? | "ID: (ID value)" | View Bajo Board ID data
5 | RANGE= | AT+RANGE=<1-3> | "OK" | Setting the ADXL355 sensor range value <br /> 1 = Range 2g <br /> 2 = Range 4g <br /> 3 = Range 8g
6 | RANGE? | AT+RANGE? | "RANGE:(range value)" | View the ADXL355 sensor range
7 | ODR= | AT+ODR=<1-10> | "OK" | Setting the Output Data Rate (ODR) value of the ADXL355 sensor <br /> 0 = 4000Hz <br /> 1 = 2000Hz <br /> 2 = 1000Hz <br /> 3 = 500Hz <br /> 4 = 250Hz <br /> 5 = 125Hz <br /> 6 = 62Hz <br /> 7 = 31Hz <br /> 8 = 16Hz <br /> 9 = 8Hz <br /> 10 = 4Hz
8 | ODR? | AT+ODR? | "ODR: (odr value)" | View the ADXL355 sensor Data Rate Output
9 | AUTO= | AT+AUTO=<1-2> | "OK" | Setting the autorun value <br /> 1 = Start measuring the ADXL355 sensor <br /> 2 = Stop measuring the ADXL355 sensor
10 | AUTO? | AT+AUTO? | "AUTO: (autorun value)" | See Autorun
11 | ACCRESET | AT+ACCRESET | "Reset ADXL355" | Returns ADXL355 sensor settings to original
12 | ST1= | AT+ST1=<0-1> | "ST1 OFF" when value is 0 <br /> "ST1 ON" when value is 1 <br /> "wrong value" when value is more than 1 | ADXL355 sensor Self Test Mode <br /> 0 = Selftest is turned off (low) <br /> 1 = Selftest is turned on (high)
13 | ST2= | AT+ST2=<0-1> | "ST2 OFF" when value is 0 <br /> "ST2 ON" when value is 1 <br /> "wrong value" when value is more than 1 | ADXL355 sensor Self Test Mode <br /> 0 = Selftest is turned off (low) <br /> 1 = Selftest is turned on (high) <br /> Provides an electrostatic force on the ADXL355 mechanical sensor which impacts changes in output from its response to pressure. The response (change in power) that is visible is the difference in output V when ST2 is high and ST2 is low. After the Selftest is carried out, set the two ST pins to low to return to normal operation
14 | RAW= | AT+RAW=<0-1> | "OK" | Setting the ADXL355 sensor data output type <br /> 0 = mg output <br /> 1 = raw output
15 | RAW? | AT+RAW? | "RAW: (RAW value)" | View the ADXL355 sensor data output type
16 | OFFSETX= | AT+OFFSETX=<-32000 to 32000> | "OK, (offset value without minus)" | Set the ADXL355 sensor offset value on the X axis, the offset value interval is -32000 to 32000
17 | OFFSETX? | AT+OFFSETX? | "OFFSETX:(offset value)" | View the offset value of the ADXL355 sensor on the X axis
18 | OFFSETY= | AT+OFFSETY=<-32000 to 32000> | "OK, (offset value without minus)" | Set the ADXL355 sensor offset value on the Y axis, the offset value interval is -32000 to 32000
19 | OFFSETY? | AT+OFFSETY? | "OFFSETY:(offset value)" | View the offset value of the ADXL355 sensor on the Y axis
20 | OFFSETZ= | AT+OFFSETZ=<-32000 to 32000> | "OK, (offset value without minus)" | Set the ADXL355 sensor offset value on the Z axis, the offset value interval is -32000 to 32000
21 | OFFSETZ? | AT+OFFSETZ? | "OFFSETZ:(offset value)" | View the offset value of the ADXL355 sensor on the Z axis
22 | TEMP= | AT+TEMP=<0-1> | "OK" |Set the TEMP output on the ADXL355 sensor <br /> 0 = TEMP output is displayed <br /> 1 = TEMP output is not displayed
23 | TEMP? | AT+TEMP? | "TEMP:(TEMP status value)" | View the TEMP output status on the ADXL355 sensor
24 | INCSTATUS? | AT+INCSTATUS? | "inclino status: (inclino status value in hexadecimal of 2 bytes)" | View the status of the ADIS16209 sensor
25 | INCX? | AT+INCX? | "inclino x: (x-axis value in hexadecimal of 2 bytes)" | View the x-axis degree value of the ADIS16209 sensor
26 | INCY? | AT+INCY? | "inclino y: (y-axis value in hexadecimal of 2 bytes)" | View the y-axis degree value of the ADIS16209 sensor
27 | INCROT? | AT+INCROT? | "inclino rot: (rotation value in hexadecimal of 2 bytes)" | View the rotation degree value of the ADIS16209 sensor
28 | INCSUPOUT? | AT+INCSUPOUT? | "inclino supp out: (rotation value in hexadecimal of 2 bytes)" | View the digital supply voltage measurement value on the VDD pin of the ADIS16209 sensor

# License
![license](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/oshw_facts.png)
29 | INCRESET | AT+INCRESET | "inclino reset…." | Reset the ADIS16209 sensor settings
30 | INCREV | AT+INCREV | "inclino revision: (revision status value in hexadecimal of 2 bytes)" | View the Revision status of the ADIS16209 sensor
31 | INCMSC? | AT+INCMSC? | "inclino MSC_OUT: (MSC status value in hexadecimal of 2 bytes))" | View the data ready and control cell status of the ADIS 16209 sensor
32 | REBOOT | AT+REBOOT | "Reboot..." | Perform a System Reset
