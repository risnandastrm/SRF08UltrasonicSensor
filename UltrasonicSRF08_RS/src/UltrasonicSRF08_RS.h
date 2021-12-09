/*
  UltrasonicSRF08_RS.h - Library for calculating Ultrasonic sensor SRF08.
  Created by Risnanda S., February 02, 2020.
  Released into the public domain.
*/
#ifndef UltrasonicSRF08_RS_H
#define UltrasonicSRF08_RS_H

#include "Arduino.h"

// Read
#define SOFTWARE_REVISION 0x00
#define LIGHT_SENSOR      0x01
// Write
#define COMMAND_REGISTER  0x00
#define MAX_GAIN_REGISTER 0x01
#define RANGE_REGISTER    0x02
// Units
#define INCHES            0x50
#define CENTIMETERS       0x51
#define MICROSECONDS      0x52

class UltrasonicSRF08_RS{
	public:
		UltrasonicSRF08_RS(int address, int analogueGain, int rangeLocation, char unit);
		void begin();
		void changeAddress(int oldAddress, int newAddress);
		void requestToRead();
		int readRange();

	private:
		// Main variable
		uint8_t _unit,
				_address,
				_analogueGain,
				_rangeLocation;
		int _value;
};

#endif