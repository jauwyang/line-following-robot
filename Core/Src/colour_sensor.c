#include "colour_sensor.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>


static const uint16_t infinitySensor = 10000;

static const tapeColourBounds relativeRed = {
	.red = {-1 , -1},
	.green = {40, infinitySensor},
	.blue = {40, infinitySensor},
	.tapeColour = RED,
};

static const uint16_t greenTapeAverageRequirement = 100;

//static const tapeColourBounds relativeGreen = {
//	.red = {-1 , -1},
//	.green = {200, 300},
//	.blue = {200, 300},
//	.tapeColour = GREEN,
//};

static const tapeColourBounds relativeBlue = {
	.red = {40, infinitySensor},
	.green = {40, infinitySensor},
	.blue = {-1, -1},
	.tapeColour = BLUE,
};


void readRawColourSensors(rgb_cap_t rawSensorReadings[]){
	rgb_cap_t cap = {0};
	for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
		tcs9548a_select_channel(i);
		cap = apds9960_read_rgb(APDS9960_I2C_ADDR);

		rawSensorReadings[i] = cap;
	}
}


bool isInChannelBounds(uint16_t singleChannelReading, channelBounds bounds){
	return singleChannelReading > bounds.lowerBound && singleChannelReading < bounds.upperBound;
}

uint16_t getAverageChannelValues(rgb_cap_t sensorReading){
	return (sensorReading.red + sensorReading.green + sensorReading.blue)/3;
}

bool isColourDetected(enum Colour tapeColour, rgb_cap_t sensorReading){
	switch (tapeColour){
		case RED: {
			uint16_t diffG = sensorReading.red - sensorReading.green;
			uint16_t diffB = sensorReading.red - sensorReading.blue;

			return (isInChannelBounds(diffG, relativeRed.green) &&
					isInChannelBounds(diffB, relativeRed.blue));
		}
		case GREEN: {
			return getAverageChannelValues(sensorReading) < greenTapeAverageRequirement;
		}
		case BLUE: {
			uint16_t diffR = sensorReading.blue - sensorReading.red;
			uint16_t diffG = sensorReading.blue - sensorReading.green;

			return (isInChannelBounds(diffR, relativeBlue.red) &&
					isInChannelBounds(diffG, relativeBlue.green));
		}
		default:
			printf("UNDEFINED COLOUR"); // left to crash
			return false;
	}
}


void processColourSensorReadings(bool processedSensorReadings[], rgb_cap_t rawSensorReadings[], enum Colour targetColourName){
	/**
	 * This converts the raw sensor readings to an array of true/false depending whether the target colour has
	 * been detected.
	 * 
	 * @param processedSensorReadings Output of sensors
	 * @param rawSensorReadings Array of the raw colour sensors value readings.
	 * @param arraySize Size of the array.
	 * @param targetColourName Enum value specifying which colour to detect.
	 * @return Array of processed sensor readings
	 */

	// detect for a specific colour given the desired colourName
	for (uint32_t i = 0; i < SENSOR_COUNT; i++){
		processedSensorReadings[i] = isColourDetected(targetColourName, rawSensorReadings[i]);
	}
}


uint32_t countMatchingSensorColourDetections(enum Colour targetColourName){
	rgb_cap_t rawSensorReadings[SENSOR_COUNT];
	readRawColourSensors(rawSensorReadings);

	bool processedSensorReadings[SENSOR_COUNT];
	processColourSensorReadings(processedSensorReadings, rawSensorReadings, targetColourName);

	uint32_t colourCount = 0;
	for (uint32_t i = 0; i < SENSOR_COUNT; i++){
		if (processedSensorReadings[i] == true){
			colourCount++;
		}
	}
	return colourCount;
}


double getPositionOfColourSource(enum Colour targetColourName){
	/**
	 * This function determines/estimates the relative position of the colour  w.r.t. the robot
	 * This is needed since multiple sensors might detect the colour at once, so find the average location.
	 *
	 * @param processedSensorReadings[] Array of sensor values that processed whether
	 * 							        they have/have not detected the target colour.
	 * @param arraySize Size of the array.
	 * @return getPositionOfLine Returns value relative to position of source to robot.
	 */

	rgb_cap_t rawSensorReadings[SENSOR_COUNT];
	readRawColourSensors(rawSensorReadings);

	bool processedSensorReadings[SENSOR_COUNT];
	processColourSensorReadings(processedSensorReadings, rawSensorReadings, targetColourName);

	double detectedColourIndicesSum = 0;
	double detectedColourCount = 0;

	for (uint32_t i = 0; i < SENSOR_COUNT; i++){
		if (processedSensorReadings[i] == true) {
			detectedColourIndicesSum = detectedColourIndicesSum + i;
			detectedColourCount++;
		}
	}
	if (detectedColourCount == 0) {
		return -1;
	}
	double colourSourceLocation = detectedColourIndicesSum / detectedColourCount;

	return colourSourceLocation;
}
