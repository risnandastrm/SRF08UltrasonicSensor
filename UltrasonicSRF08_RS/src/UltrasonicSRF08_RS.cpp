/*
  UltrasonicSRF08_RS.h - Library for calculating Ultrasonic sensor SRF08.
  Created by Risnanda S., February 02, 2020.
  Released into the public domain.
*/
#include "Arduino.h"
#include "UltrasonicSRF08_RS.h"
#include <Wire.h>

UltrasonicSRF08_RS::UltrasonicSRF08_RS(int address, int analogueGain, int rangeLocation, char unit){
	// I2C initialization
	UltrasonicSRF08_RS::begin();
	
	_unit = (uint8_t)(unit);
	// _address = (uint8_t)(address) >> 1;
	_address = (uint8_t)(address) / 2;
    _analogueGain = (uint8_t)(analogueGain);
    _rangeLocation = (uint8_t)(rangeLocation);
}

void UltrasonicSRF08_RS::begin(){
	// I2C Initialization
	Wire.begin();
}

void UltrasonicSRF08_RS::changeAddress(int oldAddress, int newAddress){
	// Change scale in i2c protocol
	oldAddress = oldAddress >> 1;

	// Change address
	Wire.beginTransmission(oldAddress);
	Wire.write(byte(COMMAND_REGISTER));
	Wire.write(byte(0xA0));
	Wire.endTransmission();

	Wire.beginTransmission(oldAddress);
	Wire.write(byte(COMMAND_REGISTER));
	Wire.write(byte(0xAA));
	Wire.endTransmission();

	Wire.beginTransmission(oldAddress);
	Wire.write(byte(COMMAND_REGISTER));
	Wire.write(byte(0xA5));
	Wire.endTransmission();
	 
	Wire.beginTransmission(oldAddress);
	Wire.write(byte(COMMAND_REGISTER));
	Wire.write(newAddress);
	Wire.endTransmission();
}

void UltrasonicSRF08_RS::requestToRead(){
	// step 1: instruct sensor to read echoes
    Wire.beginTransmission(_address);			// transmit to device #112 (0x70)
    Wire.write(byte(COMMAND_REGISTER));			// sets register pointer to the command register (0x00)

	// step 2: select unit
	if(_unit == 'i'){
		Wire.write(byte(INCHES));      			// command sensor to measure in "inches" (0x50)
	} else if(_unit == 'c'){
		Wire.write(byte(CENTIMETERS));			// command sensor to measure in "centimeters" (0x51)
	} else if(_unit == 'm'){
		Wire.write(byte(MICROSECONDS));      	// command sensor to measure in "microseconds" (0x52)
	}

	// step 3: write analogue gain and range location if available
	if(_analogueGain && _rangeLocation){
		Wire.write(_analogueGain);
        Wire.write(_rangeLocation);
	}

    Wire.endTransmission();      				// stop transmitting
}

int UltrasonicSRF08_RS::readRange(){
	// step 4: instruct sensor to return a particular echo reading
    Wire.beginTransmission(_address); 			// transmit to device #112
    Wire.write(byte(RANGE_REGISTER));			// sets register pointer to echo #1 register (0x02)
    Wire.endTransmission();      				// stop transmitting
	
    // step 5: request reading from sensor
    Wire.requestFrom(_address, 2);    			// request 2 bytes from slave device #112
	
    // step 6: receive reading from sensor
    if(Wire.available() >= 2) { 				// if two bytes were received
      _value = Wire.read();  					// receive high byte (overwrites previous reading)
      _value = _value << 8;    					// shift high byte to be high 8 bits
      _value |= Wire.read(); 					// receive low byte as lower 8 bits
    }
	
	// step 7: return value
	return _value;
}