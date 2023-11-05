//#include "IR_sensor.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>


//>>>> COLOUR FREQUENCY RANGE<<<<//
//static const colourFrequency Red = { 1, 0 };
//static const colourFrequency Green = { 2, 0 };
//static const colourFrequency Blue = { 3, 0 };
//static const colourFrequency Black = { 4, 0 };

//bool isRed(uint32_t rawColourFrequency){
//	if (rawColourFrequency > Red.lowerBoundFrequency &&
//		rawColourFrequency < Red.upperBoundFrequency){
//		return true;
//	}
//}
//
//bool isGreen(uint32_t rawColourFrequency){
//	if (rawColourFrequency > Green.lowerBoundFrequency &&
//		rawColourFrequency < Green.upperBoundFrequency){
//		return true;
//	}
//}
//
//bool isBlue(uint32_t rawColourFrequency){
//	if (rawColourFrequency > Blue.lowerBoundFrequency &&
//		rawColourFrequency < Blue.upperBoundFrequency){
//		return true;
//	}
//}
//
//bool isBlack(uint32_t rawColourFrequency){
//	if (rawColourFrequency > Black.lowerBoundFrequency &&
//		rawColourFrequency < Black.upperBoundFrequency){
//		return true;
//	}
//}



void IR_readRawColourSensors(uint32_t *rawSensorReadings, uint32_t sensorCount){
	//TODO: insert sensor readings algorithm [HENCHEL]
	//TODO: need to add this function to header file
}


uint32_t IR_countMatchingSensorColourDetections(uint32_t sensorCount){
	uint32_t IR_rawSensorReadings[sensorCount];
	IR_readRawColourSensors(*rawSensorReadings, sensorCount);

	uint32_t colourCount = 0;
	for (uint32_t i = 0; i < sensorCount; i++){
		if (IR_rawSensorReadings[i] == true){
			colourCount++;
		}
	}
	return colourCount;
}


double IR_getPositionOfColourSource(uint32_t sensorCount){
	uint32_t rawSensorReadings[sensorCount];
	readRawColourSensors(*rawSensorReadings, sensorCount);

	double detectedColourIndicesSum = 0;
	double detectedColourCount = 0;

	for (uint32_t i = 0; i < sensorCount; i++){
		if (rawSensorReadings[i] == true) {
			detectedColourIndicesSum = detectedColourIndicesSum + i;
			detectedColourCount++;
		}
	}
	double colourSourceLocation = detectedColourIndicesSum / detectedColourCount;

	return colourSourceLocation;
}
