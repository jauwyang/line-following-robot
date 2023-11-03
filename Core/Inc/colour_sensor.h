#ifndef COLOUR_SENSOR_H
#define COLOUR_SENSOR_H

enum Colour {
	RED,
	GREEN,
	BLUE,
};

typedef struct {
	uint32_t upperBoundFrequency;
	uint32_t lowerBoundFrequency;
} colourFrequency;

bool isRed(uint32_t rawColourFrequency);

bool isGreen(uint32_t rawColourFrequency);

bool isBlue(uint32_t rawColourFrequency);

uint32_t* processColourSensorReadings(uint32_t rawSensorReadings[], uint32_t arraySize, enum Colour targetColourName);

double getPositionOfLine(uint32_t processedSensorReadings[], uint32_t arraySize);

#endif //COLOUR_SENSOR_H
