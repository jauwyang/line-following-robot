#include "colour_sensor.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

static const colourFrequency Red = { 1, 0 };
static const colourFrequency Green = { 2, 0 };
static const colourFrequency Blue = { 3, 0 };


bool isRed(uint32_t rawColourFrequency){
	if (rawColourFrequency > Red.lowerBoundFrequency &&
		rawColourFrequency < Red.upperBoundFrequency){
		return true;
	}
}


bool isGreen(uint32_t rawColourFrequency){
	if (rawColourFrequency > Green.lowerBoundFrequency &&
		rawColourFrequency < Green.upperBoundFrequency){
		return true;
	}
}


bool isBlue(uint32_t rawColourFrequency){
	if (rawColourFrequency > Blue.lowerBoundFrequency &&
		rawColourFrequency < Blue.upperBoundFrequency){
		return true;
	}
}


uint32_t* processColourSensorReadings(uint32_t rawSensorReadings[], uint32_t arraySize, enum Colour targetColourName){
	/**
	 * This converts the raw sensor readings to an array of true/false depending whether the target colour has
	 * been detected.
	 *
	 * @param rawSensorReadings Array of the raw colour sensors value readings.
	 * @param arraySize Size of the array.
	 * @param targetColourName Enum value specifying which colour to detect.
	 * @return Array of processed sensor readings
	 */
	uint32_t processedSensorReadings[arraySize];

	// detect for a specific colour given the desired colourName
	switch (targetColourName){
		case RED:
			for (uint32_t i = 0; i < arraySize; i++){
				processedSensorReadings[i] = isRed(rawSensorReadings[i]);
			}
			break;
		case GREEN:
			for (uint32_t i = 0; i < arraySize; i++){
				processedSensorReadings[i] = isGreen(rawSensorReadings[i]);
			}
			break;
		case BLUE:
			for (uint32_t i = 0; i < arraySize; i++){
				processedSensorReadings[i] = isBlue(rawSensorReadings[i]);
			}
			break;
		default:
			printf("UNDEFINED COLOUR");
			return NULL;
	}

	return *processedSensorReadings;
}


double getPositionOfLine(uint32_t processedSensorReadings[], uint32_t arraySize){
	/**
	 * This function determines/estimates the relative position of the line w.r.t. the robot
	 * This is needed since multiple sensors might detect the line at once, so find the average location.
	 *
	 * @param processedSensorReadings[] Array of sensor values that processed whether
	 * 							        they have/have not detected the target colour.
	 * @param arraySize Size of the array.
	 * @return getPositionOfLine Returns value relative to position of line to robot.
	 */
	double detectedColourIndicesSum = 0;
	double detectedColourCount = 0;

	for (uint32_t i = 0; i < arraySize; i++){
		if (processedSensorReadings[i] == true) {
			detectedColourIndicesSum = detectedColourIndicesSum + i;
			detectedColourCount++;
		}
	}
	double getPositionOfLine = detectedColourIndicesSum / detectedColourCount;

	return getPositionOfLine;
}
