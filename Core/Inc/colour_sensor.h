#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "color/apds9960.h"

static const uint8_t SENSOR_COUNT = 5;

enum Colour {
	RED,
	GREEN,
	BLUE,
};

// currentChannel - otherChannel
// (+) if currentChannel is larger
// (-) if current Channel
typedef struct _channelBounds {
	uint16_t lowerBound;
	uint16_t upperBound;
} channelBounds;

typedef struct _tapeColourBounds{
	channelBounds red;
	channelBounds green;
	channelBounds blue;
	enum Colour tapeColour;
} tapeColourBounds;


void readRawColourSensors(rgb_cap_t rawSensorReadings[]);

bool isInChannelBounds(uint16_t singleChannelReading, channelBounds bounds);

uint16_t getAverageChannelValues(rgb_cap_t sensorReading);

bool isColourDetected(enum Colour tapeColour, rgb_cap_t sensorReading);

void processColourSensorReadings(bool processedSensorReadings[], rgb_cap_t rawSensorReadings[], enum Colour targetColourName);

void printRawRGBColours(UART_HandleTypeDef huart2);

void printProcessedColours(enum Colour colourTape, UART_HandleTypeDef huart2);

uint32_t countMatchingSensorColourDetections(enum Colour targetColourName);

double getPositionOfColourSource(enum Colour targetColourName);

#endif //COLOUR_SENSOR_H
