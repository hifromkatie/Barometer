/*
	BM1386lib.h - Library for BM1386GLV, Piezo-resistive pressure sensor.
	created by Katie Dumont, 20 September 2020
*/

#ifndef _BM1386lib_h
#define _BM1386lib_h

#include "Arduino.h"

//Registers
#define BM1386_ADDRESS 0x5D
#define BM1386_CONTROL 0x14
#define BM1386_PRESSURE_H 0x1A
#define BM1386_PRESSURE_L 0x1B
#define BM1386_PRESSURE_XL 0x1C
#define BM1386_TEMPERATURE_H 0x1D
#define BM1386_TEMPERATURE_L 0x1E

//masks for register settings
#define BM1386_MODE_CONTROL_AVE_NUM_SINGLE	0b00011111 //Averaging number of measurements; 000:single
#define BM1386_MODE_CONTROL_AVE_NUM_8		0b01111111 //Averaging number of measurements; 011:8
//#define BM1386_MODE_CONTROL_DR_EN	0bxxx1xxxx //DRI pin for Data Ready; 1:EN
//#define BM1386_MODE_CONTROL_FULL_EN	0bxxxx1xxx //DRI pin for FULL; 1: EN
//#define BM1386_MODE_CONTROL_WTM_EN	0bxxxxx1xx //DRI pin for Water Mark; 1: EN
#define BM1386_MODE_CONTROL_MODE_STNBY	0b11111100 //Measurement mode setting; 00: Standby
#define BM1386_MODE_CONTROL_MODE_ONE		0b11111101 //Measurement mode setting; 01: One shot
#define BM1386_MODE_CONTROL_MODE_CONT		0b11111110 //Measurement mode setting; 10: Continuous
 

class BM1386 {
public:
	boolean begin(void);
	float getPressure(void); //ave8, no interupts, one shot
	float getTemp(void); 
	
};
	
#endif
