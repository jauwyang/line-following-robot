#include "IR_sensor_version/IR_sensor.h"

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

uint32_t IR_countMatchingSensorColourDetection(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount) {
	uint32_t colourCount = 0;
	for (uint8_t i = 0; i < sensorCount; i++) {
		if (IR_rawSensorReadings[i]) {
			colourCount++;
		}
	}
	return colourCount;
}


double IR_getPositionOfColourSource(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount){
	double detectedColourIndicesSum = 0;
	double detectedColourCount = 0;

	for (uint8_t i = 0; i < sensorCount; i++){
		if (IR_rawSensorReadings[i]) {
			detectedColourIndicesSum = detectedColourIndicesSum + i;
			detectedColourCount++;
		}
	}

	return detectedColourIndicesSum / detectedColourCount;
}
