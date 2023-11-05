#include "colour_sensor.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>


//>>>> COLOUR FREQUENCY RANGE<<<<//
static const colourFrequency Red = { 1, 0 };
static const colourFrequency Green = { 2, 0 };
static const colourFrequency Blue = { 3, 0 };
static const colourFrequency Black = { 4, 0 };

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

bool isBlack(uint32_t rawColourFrequency){
	if (rawColourFrequency > Black.lowerBoundFrequency &&
		rawColourFrequency < Black.upperBoundFrequency){
		return true;
	}
}



void readRawColourSensors(uint32_t *rawSensorReadings, uint32_t sensorCount){
	//TODO: insert sensor readings algorithm [HENCHEL]
	//TODO: need to add this function to header file
}


void processColourSensorReadings(bool *processedSensorReadings, uint32_t *rawSensorReadings, uint32_t sensorCount, enum Colour targetColourName){
	/**
	 * This converts the raw sensor readings to an array of true/false depending whether the target colour has
	 * been detected.
	 *
	 * @param rawSensorReadings Array of the raw colour sensors value readings.
	 * @param arraySize Size of the array.
	 * @param targetColourName Enum value specifying which colour to detect.
	 * @return Array of processed sensor readings
	 */

	// detect for a specific colour given the desired colourName
	switch (targetColourName){
		case RED:
			for (uint32_t i = 0; i < sensorCount; i++){
				processedSensorReadings[i] = isRed(rawSensorReadings[i]);
			}
			break;
		case GREEN:
			for (uint32_t i = 0; i < sensorCount; i++){
				processedSensorReadings[i] = isGreen(rawSensorReadings[i]);
			}
			break;
		case BLUE:
			for (uint32_t i = 0; i < sensorCount; i++){
				processedSensorReadings[i] = isBlue(rawSensorReadings[i]);
			}
			break;
		default:
			printf("UNDEFINED COLOUR");
	}
}


uint32_t countMatchingSensorColourDetections(uint32_t sensorCount, enum Colour targetColourName){
	uint32_t rawSensorReadings[sensorCount];
	readRawColourSensors(*rawSensorReadings, sensorCount);

	bool processedSensorReadings[sensorCount];
	processColourSensorReadings(*processedSensorReadings, *rawSensorReadings, sensorCount, targetColourName);

	uint32_t colourCount = 0;
	for (uint32_t i = 0; i < sensorCount; i++){
		if (processedColourSensorReadings[i] == true){
			colourCount++;
		}
	}
	return colourCount;
}


double getPositionOfColourSource(uint32_t sensorCount, enum Colour targetColourName){
	/**
	 * This function determines/estimates the relative position of the colour  w.r.t. the robot
	 * This is needed since multiple sensors might detect the colour at once, so find the average location.
	 *
	 * @param processedSensorReadings[] Array of sensor values that processed whether
	 * 							        they have/have not detected the target colour.
	 * @param arraySize Size of the array.
	 * @return getPositionOfLine Returns value relative to position of source to robot.
	 */

	uint32_t rawSensorReadings[sensorCount];
	readRawColourSensors(*rawSensorReadings, sensorCount);

	bool processedSensorReadings[sensorCount];
	processColourSensorReadings(*processedSensorReadings, *rawSensorReadings, sensorCount, targetColourName);

	double detectedColourIndicesSum = 0;
	double detectedColourCount = 0;

	for (uint32_t i = 0; i < sensorCount; i++){
		if (processedSensorReadings[i] == true) {
			detectedColourIndicesSum = detectedColourIndicesSum + i;
			detectedColourCount++;
		}
	}
	double colourSourceLocation = detectedColourIndicesSum / detectedColourCount;

	return colourSourceLocation;
}
