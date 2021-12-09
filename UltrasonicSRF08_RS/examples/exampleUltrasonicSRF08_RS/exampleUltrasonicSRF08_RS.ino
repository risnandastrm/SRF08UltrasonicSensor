/*
 * 
 * Explanation of what your example does
 * 
 */
 
#include <UltrasonicSRF08_RS.h>

// -- -- Define I2C address, gain, location, and unit
#define CENTER_ADDRESS 0xE0
#define GAIN_REGISTER 0x0F                    // int(0x0F)*43mm + 43mm = 68.8mm (maks reading)
#define LOCATION_REGISTER 0x8C
#define UNIT 'c'                              // c for cm, i for inch, m for microseconds
// -- -- Sensor Initialization
UltrasonicSRF08_RS centerUltrasonic(CENTER_ADDRESS, GAIN_REGISTER, LOCATION_REGISTER, UNIT);

void setup() {
	// Setup Serial communication to print result on Serial Monitor
	Serial.begin(9600);

	// Initial
	centerUltrasonic.begin();
}

void loop() {
	// Request
    centerUltrasonic.requestToRead();

	// Read distance
    int distanceCenter = centerUltrasonic.readRange();
  
	// Check result
	Serial.println(distanceCenter);
}