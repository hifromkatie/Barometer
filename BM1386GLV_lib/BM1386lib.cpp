#include "BM1386lib.h"
#include <Arduino.h>

#include <Wire.h>

static uint8_t read_i2c_register(uint8_t addr, uint8_t reg, int size, byte *data) {
	Wire.beginTransmission(addr);
	Wire.write((byte)reg);
	Wire.endTransmission(false);
	Wire.requestFrom(addr, (byte)size);
	for (int i=0; i<size; i++){
		data[i]=Wire.read();
	}
	return 0;
}

static void write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val) {
	Wire.beginTransmission(addr);
	Wire.write((byte)reg);
	Wire.write((byte)val);
	Wire.endTransmission();
}

boolean BM1386::begin(void){
	Wire.begin();
	Wire.beginTransmission(BM1386_ADDRESS);
	if (Wire.endTransmission() != 0) {
		return false;
	}
	//Take from Power Down mode to Reset; Regulator: ON, Processing: OFF
	write_i2c_register(BM1386_ADDRESS,0x12,01);
	//Take from Reset to standby; Regulator: ON, Processing: ON
	write_i2c_register(BM1386_ADDRESS,0x13,01);
	return true;		
}

float BM1386::getPressure(void){
	byte data[3];
	write_i2c_register(BM1386_ADDRESS,0x14,0b01100001);
	do {
		read_i2c_register(BM1386_ADDRESS, 0x19, 1, data);
	} while ((data[0] & 0b1) == 0);
	read_i2c_register(BM1386_ADDRESS,0x1A,3, data);
	
	return (((uint32_t)data[0]<<14)+((uint32_t)data[1]<<6)+((uint32_t)data[2]>>2));
}

float BM1386::getTemp(void){
	byte data[2];
	write_i2c_register(BM1386_ADDRESS,0x14,0b01100001);
	do {
		read_i2c_register(BM1386_ADDRESS, 0x19, 1, data);
	} while ((data[0] & 0b1) == 0);
	
	read_i2c_register(BM1386_ADDRESS,0x1D,2, data);
	return (((int16_t)data[0]<<8)+((int16_t)data[1]));
} 










