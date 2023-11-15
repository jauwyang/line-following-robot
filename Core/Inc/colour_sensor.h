#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

static const uint8_t SENSOR_COUNT = 5;

enum Colour {
	RED,
	GREEN,
	BLUE,
};

typedef struct _colourFrequency {

	uint32_t upperBoundFrequency;
	uint32_t lowerBoundFrequency;

} colourFrequency;

bool isRed(uint32_t rawColourFrequency);
bool isGreen(uint32_t rawColourFrequency);
bool isBlue(uint32_t rawColourFrequency);


void readRawColourSensors(uint32_t rawSensorReadings[]);

void processColourSensorReadings(bool processedSensorReadings[], uint32_t rawSensorReadings[], enum Colour targetColourName);

uint32_t countMatchingSensorColourDetections(enum Colour targetColourName);

double getPositionOfColourSource(enum Colour targetColourName);

#endif //COLOUR_SENSOR_H
