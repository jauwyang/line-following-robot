#ifndef LINE_FOLLOWING_ROBOT_IR_SENSOR_H
#define LINE_FOLLOWING_ROBOT_IR_SENSOR_H

#include <stdint.h>

static const double SENSOR_COUNT = 5;

typedef struct {
	uint32_t upperBoundFrequency;
	uint32_t lowerBoundFrequency;
} colourFrequency;

uint32_t IR_countMatchingSensorColourDetections(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount);
double IR_getPositionOfColourSource(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount);

#endif // LINE_FOLLOWING_ROBOT_IR_SENSOR_H
