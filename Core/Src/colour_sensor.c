#include "colour_sensor.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>


static const uint16_t infinitySensor = 10000;

static const tapeColourBounds relativeRed = {
	.red = {-1 , -1},
	.green = {60, infinitySensor},
	.blue = {60, infinitySensor},
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
		HAL_Delay(5);
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
		case RED:
			return (isInChannelBounds(sensorReading.green, relativeRed.green) &&
					isInChannelBounds(sensorReading.blue, relativeRed.blue));
		case GREEN:
			return getAverageChannelValues(sensorReading) < greenTapeAverageRequirement;
		case BLUE:
			return (isInChannelBounds(sensorReading.red, relativeBlue.red) &&
					isInChannelBounds(sensorReading.green, relativeBlue.green));
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


//void printRawRGBColours(UART_HandleTypeDef *huart2){
//	// idk if this works
//	rgb_cap_t rawSensorReadings[SENSOR_COUNT];
//	readRawColourSensors(rawSensorReadings);
//
//	char msg_top[] = "\nSensor  |    1    |    2    |    3    |    4    |    5    |\r\n";
//	char line[] = "---------------------------------------\r\n";
//	char readings[256] = "(R,G,B) |  ";
//
//	for (uint32_t i = 0; i < SENSOR_COUNT; i++) {
//		rgb_cap_t cap = rawSensorReadings[i];
//		char rgbMsg[256];
//		sprintf(rgbMsg, "(%hu, %hu, %hu)  |  ", cap.red, cap.green, cap.blue);
//		strcat(readings, rgbMsg);
//	}
//	strcat(readings, "\r\n\r\n\r\n");
////	size_t totalLength = strlen(msg_top) + strlen(line) + strlen(readings) + strlen("\n\n\n") + 1;
////	char *msg = (char *)malloc(totalLength * sizeof(char));
////	memset(msg, '\0', totalLength);
////	strcat(msg_top, line);
////	strcat(msg_top, readings);
////	strcat(msg_top, "\n\n\n");
////	strcat(msg, msg_top);
//
////	strcat(msg, msg_top);
////	strcat(msg, line);
////	strcat(msg, readings);
////	strcat(msg, "\n\n\n");
//
////	HAL_UART_Transmit(huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
//
//	HAL_UART_Transmit(huart2, (uint8_t *)msg_top, strlen(msg_top), HAL_MAX_DELAY);
//	HAL_UART_Transmit(huart2, (uint8_t *)line, strlen(line), HAL_MAX_DELAY);
//	HAL_UART_Transmit(huart2, (uint8_t *)readings, strlen(readings), HAL_MAX_DELAY);
//
////	free(msg);
//}
//
//
//void printProcessedColours(enum Colour colourTape, UART_HandleTypeDef *huart2){
//	// uint32_t DELAY = 0x000FFFFFU;
//	rgb_cap_t rawSensorReadings[SENSOR_COUNT];
//	readRawColourSensors(rawSensorReadings);
//
//	bool processedSensorReadings[SENSOR_COUNT];
//	processColourSensorReadings(processedSensorReadings, rawSensorReadings, colourTape);
//
//	char *colourName[] = {"RED", "GRN", "BLU"};
//
//	char msg[] = "Sensor  |  1  |  2  |  3  |  4  |  5  |\r\n";
//	char line[] = "---------------------------------------\r\n";
//	char readings[256];
//	strcat(readings, colourName[colourTape]);
//	strcat(readings, "     |  ");
//
//	for (uint32_t i = 0; i < SENSOR_COUNT; i++) {
//		strcat(readings, processedSensorReadings[i] ? "X  |  " : "-  |  ");
//	}
//
//	strcat(readings, "\r\n\r\n\r\n");
//
//	HAL_UART_Transmit(huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
//	HAL_UART_Transmit(huart2, (uint8_t *)line, strlen(line), HAL_MAX_DELAY);
//	HAL_UART_Transmit(huart2, (uint8_t *)readings, strlen(readings), HAL_MAX_DELAY);
//}


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
