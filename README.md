# Bajo Board

The Bajo Board or accelerometer sensor system is an integrated sensor system consisting of accelerometer, inclinometer and seismometer sensors. The accelerometer sensor is used to detect vibrations and carry out seismic imaging. The inclinometer sensor is used to detect tilt from monitoring stations. The seismometer sensor is used to calculate the SI value to detect early if there is an earthquake or tectonic activity and send a warning if an earthquake with MMI level 5 or above is detected. It requires voltage input with industry standart 24V, and will provide interface in RS232.

# Block Diagram System

![block diagram](https://github.com/ihsanalhafiz/Bajo_Board/blob/master/Images/diagramblok.png)

The accelerometer sensor system has three main sensor elements, namely the accelerometer sensor, inclinometer and seismometer. In the picture above, a comprehensive block design for the accelerometer sensor system is designed which consists of the sensors used and supporting components such as power supply, digital components and communication components. The ADXL355 accelerometer sensor is a 3-axis accelerometer sensor based on MEMS which is usually used to detect vibrations and one of them is for seismic imaging according to the datasheet. The ADIS16209 inclinometer sensor is a sensor for detecting 2-axis tilt, namely x and y, which is intended to detect the tilt of the OBU installation in the CBT system, as well as to monitor whether there is a change in tilt when the OBU has been deployed and is operating. The D7S seismometer sensor is an Omron vibration sensor that can be integrated to detect earthquake vibrations by calculating the SI value of an earthquake event. This sensor is also equipped with an interruption process when there is an earthquake event with an MMI of 5 and above, so that by detecting the SI value an earthquake can be detected and a warning sent.

# Hardware Part


# Software Part
